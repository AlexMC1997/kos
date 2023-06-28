#include <stdarg.h>
#include <stddef.h>
#include <stdbool.h>
#include "terminal.h"
#include "vgatext.h"
#include "string.h"
#include "panic.h"
#include "assert.h"
#include "multiboot.h"
#include "kmmap.h"
#include "cpu.h"
#include "acpi.h"
#include "pic.h"
#include "idt.h"
#include "gdt.h"
#include "io.h"
#include "pfa.h"
#include "vmm.h"
#include "kmm.h"
#include "sll.h"
#include "queue.h"
#include "stack.h"
#include "kvm.h"
#include "mem.h"
#include "util.h"
#include "ps2.h"
#include "console.h"

extern const GDT_Desc* GDT_DESCRIPT_PTR;

Kernel the_kernel = {
    .pd = KERN_PD,
    .idt = KERN_IDT,
    .gdt = NULL,
    .stack_base = KERN_STACK,
    .code_base = KERN_BASE,
};

//Initializes the exception system, including the PIC and interrupts
void except_init()
{
    idt_init();
    pic_init();
    tss_init();
    sti();
}

//Initializes physical memory, including the Page Frame Allocator
void mem_init(size_t len, multiboot_mmap* m_mmap)
{
    kmmap_init(len, m_mmap);
    pfa_init(kmmap_len, kmmap);
}

//Initializes the kernel's virtual memory space,
//including its heap manager
void kvm_init()
{
    register uint32_t reg_esp asm("%esp");
    vmm_pd_vm_alloc(1, 0xFFFFF, (Alloc_Flags){1, 0, 0, 0}, the_kernel.pd);
    PT_Entry* pt = pd_addr_p(the_kernel.pd + 0x3FF) << 12;

    pt[0x3FF].addr_0_3 = phys(reg_esp) >> 12;
    pt[0x3FF].addr_4_19 = phys(reg_esp) >> 16;
    pt[0x3FF].valid = 1;
    pt[0x3FF].present = 1;

    reg_esp += 0xFFFFF000 - align(reg_esp, PG_SIZE);

    the_kernel.gdt = GDT_DESCRIPT_PTR;

    kmm_init();
}

//Initializes IO and other devices
void dev_init()
{
    vga_text_init();
    ps2_init();
    ps2_kb_init();
}

static void list_lambda(SLL_Node* node)
{
    static char arr[100];
    static size_t i = 0;
    arr[i] = (char)(node->data);
    i++;
    if (i == 5) {
        tputs(arr);
        i = 0;
    }
}

static int pfa_testing()
{
    const int arrsize = 200;

    pg_num_4k_t arr[arrsize];

    for (int i = 0; i < arrsize; i+=2) {
        pfa_pf_alloc(PF_4K, arr + i);
        pfa_pf_alloc(PF_16K, arr + i + 1);
    }

    for(int i = 0; i < arrsize; i++) {
        for (int j = i + 1; j < arrsize; j++) {
            if (arr[i] == arr[j])
                panic("Duplicate page!");
        }
    }

    return 0;
}

void destructor(SLL_Node* node) 
{
    kfree(node->data, TEST3_OBJ);
}

void kmm_testing()
{
    test* arr[30];

    for (int i = 0; i < 9; i++) {
        arr[i] = kmalloc(TEST_OBJ);
        arr[i]->smth = i * i;
        for (int k = 0; k <= i; k++)
            arr[i]->smwh[k] = 0x30 + k;
    }

    for (int i = 0; i < 9; i++) {
        tprintf("smth: %d\nsmwh: %s\n", arr[i]->smth, arr[i]->smwh);
        tprintf("Addr: %x\n", (uint32_t)arr[i]);
    }

    test3* head = kmalloc(TEST3_OBJ);
    head->smth = kmalloc(TEST2_OBJ);
    head->smth->smth = 0;
    memcpy(head->smth->smwh, "Alex", 5);
    test3* cur = head;

    for (int i = 1; i < 200; i++) {
        cur->next = kmalloc(TEST3_OBJ);
        cur = cur->next;
        cur->smth = kmalloc(TEST2_OBJ);
        cur->smth->smth = i;
        memcpy(cur->smth->smwh, "Alex", 5);
    }
    cur->next = NULL;
    cur = head;

    do {
        tprintf("%d: %s\n", cur->smth->smth, cur->smth->smwh);
        cur = cur->next;
    } while (cur);
    
    cur = head;
    do {
        cur->smth->smth = 42;
        memcpy(cur->smth->smwh, "Poly", 5);
        cur = cur->next;
    } while (cur);
    
    cur = head;
    do {
        tprintf("%d: %s\n", cur->smth->smth, cur->smth->smwh);
        cur = cur->next;
    } while (cur);


    test* freetst = kmalloc(TEST_OBJ);
    tprintf("Addr: %x\n", (size_t)freetst);
    kfree(freetst, TEST_OBJ);
    freetst = kmalloc(TEST_OBJ);
    tprintf("Addr: %x\n", (size_t)freetst);

    SLL* myList = sll_new_empty();

    for (size_t i = 0; i < 0x50; i++) 
        sll_add_front(myList, i);
    
    for (size_t i = 0; i < 0x50; i++) {
        tprintf("%d: %s\n", i, sll_contains_val(myList, i) ? "False" : "True");
        sll_remove_back(myList);
        tprintf("%d: %s\n", i, sll_contains_val(myList, i) ? "False" : "True");
    }
    
    SLL* newList = sll_new_v(5,
        'A',
        'l',
        'e',
        'x',
        '\0'
    );

    sll_foreach(newList, list_lambda);
    sll_destroy(newList);
    sll_destroy(myList);

    SLL* newerList = sll_new_v(
        5,
        'P',
        'o',
        'l',
        'y',
        '\0'
    );

    newerList = sll_new_v(
        5,
        'N',
        'a',
        'n',
        'o',
        '\0'
    );

    sll_foreach(newerList, list_lambda);

    tputc('\n');

    Queue* myQ = queue_new_empty();
    queue_enqueue(myQ, "hello");
    queue_enqueue(myQ, "there");
    queue_enqueue(myQ, "how");
    queue_enqueue(myQ, "are");
    queue_enqueue(myQ, "you");
    queue_enqueue(myQ, "?");

    size_t len = queue_len(myQ);
    for (size_t i = 0; i < len; i++)
        tputs(queue_dequeue(myQ)), tputc(' ');
    
    Stack* myStack = stack_new_empty();

    stack_push(myStack, "hello");
    stack_push(myStack, "there");
    stack_push(myStack, "how");
    stack_push(myStack, "are");
    stack_push(myStack, "you");
    stack_push(myStack, "?");
    tputc('\n');

    len = stack_len(myStack);
    for (size_t i = 0; i < len; i++)
        tputs(stack_pop(myStack)), tputc(' ');
    
    Queue* myQueue = queue_new_empty();

    for (size_t i = 0; i < 100; i++)
        queue_enqueue(myQueue, kmalloc(TEST3_OBJ));

    tprintf("%x\n", queue_peek(myQueue));
    queue_destroy_p(myQueue, destructor);

    myQueue = queue_new_empty();
    queue_enqueue(myQueue, kmalloc(TEST3_OBJ));
    tprintf("%x\n", queue_peek(myQueue));
    tprintf("%x\n", queue_dequeue(myQueue));
}

//Kernel C entry; passed GRUB info for parsing
void kern_main(uint32_t magic, multiboot_info* mbi)
{
    if (magic != MULTIBOOT_MAGIC)
        panic("Multiboot magic mismatch.");


    cpu_init();
    mem_init(mbi->mmap_length, mbi->mmap_addr);
    acpi_init();

    except_init();
    kvm_init();

    dev_init();
    terminal_init();

    // kmm_testing();

    console_main();

    return;
}