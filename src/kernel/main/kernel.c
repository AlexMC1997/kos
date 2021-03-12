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

//Initializes the exception system, including the PIC and interrupts
void except_init()
{
    idt_init();
    tputs("IDT initialized\n");
    pic_init();
    tputs("PIC initialized\n");
    tss_init();
    tputs("TSS initialized\n");
}

//Initializes physical memory, including the Page Frame Allocator
void mem_init(size_t len, multiboot_mmap* m_mmap)
{
    kmmap_init(len, m_mmap);
    tputs("Kernel memory map initialized.\n");
    pfa_init(kmmap_len, kmmap);
    tputs("Page Frame Allocator initialized.\n");
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

//Kernel C entry; passed GRUB info for parsing
void kern_main(uint32_t magic, multiboot_info* mbi)
{
    if (magic != MULTIBOOT_MAGIC)
        panic("Multiboot magic mismatch.");

    vga_text_init();
    terminal_init();

    cpu_init();
    mem_init(mbi->mmap_length, mbi->mmap_addr);
    acpi_init();


    except_init();

    kmm_init();
    tputs("Kernel Memory Manager initialized.\n");

    tprintf("%x\n", r_esp());

    // pfa_testing();
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

    SLL* newerList = sll_new_v(5,
        'P',
        'o',
        'l',
        'y',
        '\0'
    );

    newerList = sll_new_v(5,
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
    
    return;
}