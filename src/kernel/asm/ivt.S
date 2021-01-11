.section .text
.extern _trap_as
.global _IVT_START
_IVT_START:
.global isr_0
.type isr_0, @function
isr_0:
	pushw $0
	call _trap_as

.global isr_1
.type isr_1, @function
isr_1:
	pushw $1
	call _trap_as

.global isr_2
.type isr_2, @function
isr_2:
	pushw $2
	call _trap_as

.global isr_3
.type isr_3, @function
isr_3:
	pushw $3
	call _trap_as

.global isr_4
.type isr_4, @function
isr_4:
	pushw $4
	call _trap_as

.global isr_5
.type isr_5, @function
isr_5:
	pushw $5
	call _trap_as

.global isr_6
.type isr_6, @function
isr_6:
	pushw $6
	call _trap_as

.global isr_7
.type isr_7, @function
isr_7:
	pushw $7
	call _trap_as

.global isr_8
.type isr_8, @function
isr_8:
	pushw $8
	call _trap_as

.global isr_9
.type isr_9, @function
isr_9:
	pushw $9
	call _trap_as

.global isr_10
.type isr_10, @function
isr_10:
	pushw $10
	call _trap_as

.global isr_11
.type isr_11, @function
isr_11:
	pushw $11
	call _trap_as

.global isr_12
.type isr_12, @function
isr_12:
	pushw $12
	call _trap_as

.global isr_13
.type isr_13, @function
isr_13:
	pushw $13
	call _trap_as

.global isr_14
.type isr_14, @function
isr_14:
	pushw $14
	call _trap_as

.global isr_15
.type isr_15, @function
isr_15:
	pushw $15
	call _trap_as

.global isr_16
.type isr_16, @function
isr_16:
	pushw $16
	call _trap_as

.global isr_17
.type isr_17, @function
isr_17:
	pushw $17
	call _trap_as

.global isr_18
.type isr_18, @function
isr_18:
	pushw $18
	call _trap_as

.global isr_19
.type isr_19, @function
isr_19:
	pushw $19
	call _trap_as

.global isr_20
.type isr_20, @function
isr_20:
	pushw $20
	call _trap_as

.global isr_21
.type isr_21, @function
isr_21:
	pushw $21
	call _trap_as

.global isr_22
.type isr_22, @function
isr_22:
	pushw $22
	call _trap_as

.global isr_23
.type isr_23, @function
isr_23:
	pushw $23
	call _trap_as

.global isr_24
.type isr_24, @function
isr_24:
	pushw $24
	call _trap_as

.global isr_25
.type isr_25, @function
isr_25:
	pushw $25
	call _trap_as

.global isr_26
.type isr_26, @function
isr_26:
	pushw $26
	call _trap_as

.global isr_27
.type isr_27, @function
isr_27:
	pushw $27
	call _trap_as

.global isr_28
.type isr_28, @function
isr_28:
	pushw $28
	call _trap_as

.global isr_29
.type isr_29, @function
isr_29:
	pushw $29
	call _trap_as

.global isr_30
.type isr_30, @function
isr_30:
	pushw $30
	call _trap_as

.global isr_31
.type isr_31, @function
isr_31:
	pushw $31
	call _trap_as

.global isr_32
.type isr_32, @function
isr_32:
	pushw $32
	call _trap_as

.global isr_33
.type isr_33, @function
isr_33:
	pushw $33
	call _trap_as

.global isr_34
.type isr_34, @function
isr_34:
	pushw $34
	call _trap_as

.global isr_35
.type isr_35, @function
isr_35:
	pushw $35
	call _trap_as

.global isr_36
.type isr_36, @function
isr_36:
	pushw $36
	call _trap_as

.global isr_37
.type isr_37, @function
isr_37:
	pushw $37
	call _trap_as

.global isr_38
.type isr_38, @function
isr_38:
	pushw $38
	call _trap_as

.global isr_39
.type isr_39, @function
isr_39:
	pushw $39
	call _trap_as

.global isr_40
.type isr_40, @function
isr_40:
	pushw $40
	call _trap_as

.global isr_41
.type isr_41, @function
isr_41:
	pushw $41
	call _trap_as

.global isr_42
.type isr_42, @function
isr_42:
	pushw $42
	call _trap_as

.global isr_43
.type isr_43, @function
isr_43:
	pushw $43
	call _trap_as

.global isr_44
.type isr_44, @function
isr_44:
	pushw $44
	call _trap_as

.global isr_45
.type isr_45, @function
isr_45:
	pushw $45
	call _trap_as

.global isr_46
.type isr_46, @function
isr_46:
	pushw $46
	call _trap_as

.global isr_47
.type isr_47, @function
isr_47:
	pushw $47
	call _trap_as

.global isr_48
.type isr_48, @function
isr_48:
	pushw $48
	call _trap_as

.global isr_49
.type isr_49, @function
isr_49:
	pushw $49
	call _trap_as

.global isr_50
.type isr_50, @function
isr_50:
	pushw $50
	call _trap_as

.global isr_51
.type isr_51, @function
isr_51:
	pushw $51
	call _trap_as

.global isr_52
.type isr_52, @function
isr_52:
	pushw $52
	call _trap_as

.global isr_53
.type isr_53, @function
isr_53:
	pushw $53
	call _trap_as

.global isr_54
.type isr_54, @function
isr_54:
	pushw $54
	call _trap_as

.global isr_55
.type isr_55, @function
isr_55:
	pushw $55
	call _trap_as

.global isr_56
.type isr_56, @function
isr_56:
	pushw $56
	call _trap_as

.global isr_57
.type isr_57, @function
isr_57:
	pushw $57
	call _trap_as

.global isr_58
.type isr_58, @function
isr_58:
	pushw $58
	call _trap_as

.global isr_59
.type isr_59, @function
isr_59:
	pushw $59
	call _trap_as

.global isr_60
.type isr_60, @function
isr_60:
	pushw $60
	call _trap_as

.global isr_61
.type isr_61, @function
isr_61:
	pushw $61
	call _trap_as

.global isr_62
.type isr_62, @function
isr_62:
	pushw $62
	call _trap_as

.global isr_63
.type isr_63, @function
isr_63:
	pushw $63
	call _trap_as

.global isr_64
.type isr_64, @function
isr_64:
	pushw $64
	call _trap_as

.global isr_65
.type isr_65, @function
isr_65:
	pushw $65
	call _trap_as

.global isr_66
.type isr_66, @function
isr_66:
	pushw $66
	call _trap_as

.global isr_67
.type isr_67, @function
isr_67:
	pushw $67
	call _trap_as

.global isr_68
.type isr_68, @function
isr_68:
	pushw $68
	call _trap_as

.global isr_69
.type isr_69, @function
isr_69:
	pushw $69
	call _trap_as

.global isr_70
.type isr_70, @function
isr_70:
	pushw $70
	call _trap_as

.global isr_71
.type isr_71, @function
isr_71:
	pushw $71
	call _trap_as

.global isr_72
.type isr_72, @function
isr_72:
	pushw $72
	call _trap_as

.global isr_73
.type isr_73, @function
isr_73:
	pushw $73
	call _trap_as

.global isr_74
.type isr_74, @function
isr_74:
	pushw $74
	call _trap_as

.global isr_75
.type isr_75, @function
isr_75:
	pushw $75
	call _trap_as

.global isr_76
.type isr_76, @function
isr_76:
	pushw $76
	call _trap_as

.global isr_77
.type isr_77, @function
isr_77:
	pushw $77
	call _trap_as

.global isr_78
.type isr_78, @function
isr_78:
	pushw $78
	call _trap_as

.global isr_79
.type isr_79, @function
isr_79:
	pushw $79
	call _trap_as

.global isr_80
.type isr_80, @function
isr_80:
	pushw $80
	call _trap_as

.global isr_81
.type isr_81, @function
isr_81:
	pushw $81
	call _trap_as

.global isr_82
.type isr_82, @function
isr_82:
	pushw $82
	call _trap_as

.global isr_83
.type isr_83, @function
isr_83:
	pushw $83
	call _trap_as

.global isr_84
.type isr_84, @function
isr_84:
	pushw $84
	call _trap_as

.global isr_85
.type isr_85, @function
isr_85:
	pushw $85
	call _trap_as

.global isr_86
.type isr_86, @function
isr_86:
	pushw $86
	call _trap_as

.global isr_87
.type isr_87, @function
isr_87:
	pushw $87
	call _trap_as

.global isr_88
.type isr_88, @function
isr_88:
	pushw $88
	call _trap_as

.global isr_89
.type isr_89, @function
isr_89:
	pushw $89
	call _trap_as

.global isr_90
.type isr_90, @function
isr_90:
	pushw $90
	call _trap_as

.global isr_91
.type isr_91, @function
isr_91:
	pushw $91
	call _trap_as

.global isr_92
.type isr_92, @function
isr_92:
	pushw $92
	call _trap_as

.global isr_93
.type isr_93, @function
isr_93:
	pushw $93
	call _trap_as

.global isr_94
.type isr_94, @function
isr_94:
	pushw $94
	call _trap_as

.global isr_95
.type isr_95, @function
isr_95:
	pushw $95
	call _trap_as

.global isr_96
.type isr_96, @function
isr_96:
	pushw $96
	call _trap_as

.global isr_97
.type isr_97, @function
isr_97:
	pushw $97
	call _trap_as

.global isr_98
.type isr_98, @function
isr_98:
	pushw $98
	call _trap_as

.global isr_99
.type isr_99, @function
isr_99:
	pushw $99
	call _trap_as

.global isr_100
.type isr_100, @function
isr_100:
	pushw $100
	call _trap_as

.global isr_101
.type isr_101, @function
isr_101:
	pushw $101
	call _trap_as

.global isr_102
.type isr_102, @function
isr_102:
	pushw $102
	call _trap_as

.global isr_103
.type isr_103, @function
isr_103:
	pushw $103
	call _trap_as

.global isr_104
.type isr_104, @function
isr_104:
	pushw $104
	call _trap_as

.global isr_105
.type isr_105, @function
isr_105:
	pushw $105
	call _trap_as

.global isr_106
.type isr_106, @function
isr_106:
	pushw $106
	call _trap_as

.global isr_107
.type isr_107, @function
isr_107:
	pushw $107
	call _trap_as

.global isr_108
.type isr_108, @function
isr_108:
	pushw $108
	call _trap_as

.global isr_109
.type isr_109, @function
isr_109:
	pushw $109
	call _trap_as

.global isr_110
.type isr_110, @function
isr_110:
	pushw $110
	call _trap_as

.global isr_111
.type isr_111, @function
isr_111:
	pushw $111
	call _trap_as

.global isr_112
.type isr_112, @function
isr_112:
	pushw $112
	call _trap_as

.global isr_113
.type isr_113, @function
isr_113:
	pushw $113
	call _trap_as

.global isr_114
.type isr_114, @function
isr_114:
	pushw $114
	call _trap_as

.global isr_115
.type isr_115, @function
isr_115:
	pushw $115
	call _trap_as

.global isr_116
.type isr_116, @function
isr_116:
	pushw $116
	call _trap_as

.global isr_117
.type isr_117, @function
isr_117:
	pushw $117
	call _trap_as

.global isr_118
.type isr_118, @function
isr_118:
	pushw $118
	call _trap_as

.global isr_119
.type isr_119, @function
isr_119:
	pushw $119
	call _trap_as

.global isr_120
.type isr_120, @function
isr_120:
	pushw $120
	call _trap_as

.global isr_121
.type isr_121, @function
isr_121:
	pushw $121
	call _trap_as

.global isr_122
.type isr_122, @function
isr_122:
	pushw $122
	call _trap_as

.global isr_123
.type isr_123, @function
isr_123:
	pushw $123
	call _trap_as

.global isr_124
.type isr_124, @function
isr_124:
	pushw $124
	call _trap_as

.global isr_125
.type isr_125, @function
isr_125:
	pushw $125
	call _trap_as

.global isr_126
.type isr_126, @function
isr_126:
	pushw $126
	call _trap_as

.global isr_127
.type isr_127, @function
isr_127:
	pushw $127
	call _trap_as

.global isr_128
.type isr_128, @function
isr_128:
	pushw $128
	call _trap_as

.global isr_129
.type isr_129, @function
isr_129:
	pushw $129
	call _trap_as

.global isr_130
.type isr_130, @function
isr_130:
	pushw $130
	call _trap_as

.global isr_131
.type isr_131, @function
isr_131:
	pushw $131
	call _trap_as

.global isr_132
.type isr_132, @function
isr_132:
	pushw $132
	call _trap_as

.global isr_133
.type isr_133, @function
isr_133:
	pushw $133
	call _trap_as

.global isr_134
.type isr_134, @function
isr_134:
	pushw $134
	call _trap_as

.global isr_135
.type isr_135, @function
isr_135:
	pushw $135
	call _trap_as

.global isr_136
.type isr_136, @function
isr_136:
	pushw $136
	call _trap_as

.global isr_137
.type isr_137, @function
isr_137:
	pushw $137
	call _trap_as

.global isr_138
.type isr_138, @function
isr_138:
	pushw $138
	call _trap_as

.global isr_139
.type isr_139, @function
isr_139:
	pushw $139
	call _trap_as

.global isr_140
.type isr_140, @function
isr_140:
	pushw $140
	call _trap_as

.global isr_141
.type isr_141, @function
isr_141:
	pushw $141
	call _trap_as

.global isr_142
.type isr_142, @function
isr_142:
	pushw $142
	call _trap_as

.global isr_143
.type isr_143, @function
isr_143:
	pushw $143
	call _trap_as

.global isr_144
.type isr_144, @function
isr_144:
	pushw $144
	call _trap_as

.global isr_145
.type isr_145, @function
isr_145:
	pushw $145
	call _trap_as

.global isr_146
.type isr_146, @function
isr_146:
	pushw $146
	call _trap_as

.global isr_147
.type isr_147, @function
isr_147:
	pushw $147
	call _trap_as

.global isr_148
.type isr_148, @function
isr_148:
	pushw $148
	call _trap_as

.global isr_149
.type isr_149, @function
isr_149:
	pushw $149
	call _trap_as

.global isr_150
.type isr_150, @function
isr_150:
	pushw $150
	call _trap_as

.global isr_151
.type isr_151, @function
isr_151:
	pushw $151
	call _trap_as

.global isr_152
.type isr_152, @function
isr_152:
	pushw $152
	call _trap_as

.global isr_153
.type isr_153, @function
isr_153:
	pushw $153
	call _trap_as

.global isr_154
.type isr_154, @function
isr_154:
	pushw $154
	call _trap_as

.global isr_155
.type isr_155, @function
isr_155:
	pushw $155
	call _trap_as

.global isr_156
.type isr_156, @function
isr_156:
	pushw $156
	call _trap_as

.global isr_157
.type isr_157, @function
isr_157:
	pushw $157
	call _trap_as

.global isr_158
.type isr_158, @function
isr_158:
	pushw $158
	call _trap_as

.global isr_159
.type isr_159, @function
isr_159:
	pushw $159
	call _trap_as

.global isr_160
.type isr_160, @function
isr_160:
	pushw $160
	call _trap_as

.global isr_161
.type isr_161, @function
isr_161:
	pushw $161
	call _trap_as

.global isr_162
.type isr_162, @function
isr_162:
	pushw $162
	call _trap_as

.global isr_163
.type isr_163, @function
isr_163:
	pushw $163
	call _trap_as

.global isr_164
.type isr_164, @function
isr_164:
	pushw $164
	call _trap_as

.global isr_165
.type isr_165, @function
isr_165:
	pushw $165
	call _trap_as

.global isr_166
.type isr_166, @function
isr_166:
	pushw $166
	call _trap_as

.global isr_167
.type isr_167, @function
isr_167:
	pushw $167
	call _trap_as

.global isr_168
.type isr_168, @function
isr_168:
	pushw $168
	call _trap_as

.global isr_169
.type isr_169, @function
isr_169:
	pushw $169
	call _trap_as

.global isr_170
.type isr_170, @function
isr_170:
	pushw $170
	call _trap_as

.global isr_171
.type isr_171, @function
isr_171:
	pushw $171
	call _trap_as

.global isr_172
.type isr_172, @function
isr_172:
	pushw $172
	call _trap_as

.global isr_173
.type isr_173, @function
isr_173:
	pushw $173
	call _trap_as

.global isr_174
.type isr_174, @function
isr_174:
	pushw $174
	call _trap_as

.global isr_175
.type isr_175, @function
isr_175:
	pushw $175
	call _trap_as

.global isr_176
.type isr_176, @function
isr_176:
	pushw $176
	call _trap_as

.global isr_177
.type isr_177, @function
isr_177:
	pushw $177
	call _trap_as

.global isr_178
.type isr_178, @function
isr_178:
	pushw $178
	call _trap_as

.global isr_179
.type isr_179, @function
isr_179:
	pushw $179
	call _trap_as

.global isr_180
.type isr_180, @function
isr_180:
	pushw $180
	call _trap_as

.global isr_181
.type isr_181, @function
isr_181:
	pushw $181
	call _trap_as

.global isr_182
.type isr_182, @function
isr_182:
	pushw $182
	call _trap_as

.global isr_183
.type isr_183, @function
isr_183:
	pushw $183
	call _trap_as

.global isr_184
.type isr_184, @function
isr_184:
	pushw $184
	call _trap_as

.global isr_185
.type isr_185, @function
isr_185:
	pushw $185
	call _trap_as

.global isr_186
.type isr_186, @function
isr_186:
	pushw $186
	call _trap_as

.global isr_187
.type isr_187, @function
isr_187:
	pushw $187
	call _trap_as

.global isr_188
.type isr_188, @function
isr_188:
	pushw $188
	call _trap_as

.global isr_189
.type isr_189, @function
isr_189:
	pushw $189
	call _trap_as

.global isr_190
.type isr_190, @function
isr_190:
	pushw $190
	call _trap_as

.global isr_191
.type isr_191, @function
isr_191:
	pushw $191
	call _trap_as

.global isr_192
.type isr_192, @function
isr_192:
	pushw $192
	call _trap_as

.global isr_193
.type isr_193, @function
isr_193:
	pushw $193
	call _trap_as

.global isr_194
.type isr_194, @function
isr_194:
	pushw $194
	call _trap_as

.global isr_195
.type isr_195, @function
isr_195:
	pushw $195
	call _trap_as

.global isr_196
.type isr_196, @function
isr_196:
	pushw $196
	call _trap_as

.global isr_197
.type isr_197, @function
isr_197:
	pushw $197
	call _trap_as

.global isr_198
.type isr_198, @function
isr_198:
	pushw $198
	call _trap_as

.global isr_199
.type isr_199, @function
isr_199:
	pushw $199
	call _trap_as

.global isr_200
.type isr_200, @function
isr_200:
	pushw $200
	call _trap_as

.global isr_201
.type isr_201, @function
isr_201:
	pushw $201
	call _trap_as

.global isr_202
.type isr_202, @function
isr_202:
	pushw $202
	call _trap_as

.global isr_203
.type isr_203, @function
isr_203:
	pushw $203
	call _trap_as

.global isr_204
.type isr_204, @function
isr_204:
	pushw $204
	call _trap_as

.global isr_205
.type isr_205, @function
isr_205:
	pushw $205
	call _trap_as

.global isr_206
.type isr_206, @function
isr_206:
	pushw $206
	call _trap_as

.global isr_207
.type isr_207, @function
isr_207:
	pushw $207
	call _trap_as

.global isr_208
.type isr_208, @function
isr_208:
	pushw $208
	call _trap_as

.global isr_209
.type isr_209, @function
isr_209:
	pushw $209
	call _trap_as

.global isr_210
.type isr_210, @function
isr_210:
	pushw $210
	call _trap_as

.global isr_211
.type isr_211, @function
isr_211:
	pushw $211
	call _trap_as

.global isr_212
.type isr_212, @function
isr_212:
	pushw $212
	call _trap_as

.global isr_213
.type isr_213, @function
isr_213:
	pushw $213
	call _trap_as

.global isr_214
.type isr_214, @function
isr_214:
	pushw $214
	call _trap_as

.global isr_215
.type isr_215, @function
isr_215:
	pushw $215
	call _trap_as

.global isr_216
.type isr_216, @function
isr_216:
	pushw $216
	call _trap_as

.global isr_217
.type isr_217, @function
isr_217:
	pushw $217
	call _trap_as

.global isr_218
.type isr_218, @function
isr_218:
	pushw $218
	call _trap_as

.global isr_219
.type isr_219, @function
isr_219:
	pushw $219
	call _trap_as

.global isr_220
.type isr_220, @function
isr_220:
	pushw $220
	call _trap_as

.global isr_221
.type isr_221, @function
isr_221:
	pushw $221
	call _trap_as

.global isr_222
.type isr_222, @function
isr_222:
	pushw $222
	call _trap_as

.global isr_223
.type isr_223, @function
isr_223:
	pushw $223
	call _trap_as

.global isr_224
.type isr_224, @function
isr_224:
	pushw $224
	call _trap_as

.global isr_225
.type isr_225, @function
isr_225:
	pushw $225
	call _trap_as

.global isr_226
.type isr_226, @function
isr_226:
	pushw $226
	call _trap_as

.global isr_227
.type isr_227, @function
isr_227:
	pushw $227
	call _trap_as

.global isr_228
.type isr_228, @function
isr_228:
	pushw $228
	call _trap_as

.global isr_229
.type isr_229, @function
isr_229:
	pushw $229
	call _trap_as

.global isr_230
.type isr_230, @function
isr_230:
	pushw $230
	call _trap_as

.global isr_231
.type isr_231, @function
isr_231:
	pushw $231
	call _trap_as

.global isr_232
.type isr_232, @function
isr_232:
	pushw $232
	call _trap_as

.global isr_233
.type isr_233, @function
isr_233:
	pushw $233
	call _trap_as

.global isr_234
.type isr_234, @function
isr_234:
	pushw $234
	call _trap_as

.global isr_235
.type isr_235, @function
isr_235:
	pushw $235
	call _trap_as

.global isr_236
.type isr_236, @function
isr_236:
	pushw $236
	call _trap_as

.global isr_237
.type isr_237, @function
isr_237:
	pushw $237
	call _trap_as

.global isr_238
.type isr_238, @function
isr_238:
	pushw $238
	call _trap_as

.global isr_239
.type isr_239, @function
isr_239:
	pushw $239
	call _trap_as

.global isr_240
.type isr_240, @function
isr_240:
	pushw $240
	call _trap_as

.global isr_241
.type isr_241, @function
isr_241:
	pushw $241
	call _trap_as

.global isr_242
.type isr_242, @function
isr_242:
	pushw $242
	call _trap_as

.global isr_243
.type isr_243, @function
isr_243:
	pushw $243
	call _trap_as

.global isr_244
.type isr_244, @function
isr_244:
	pushw $244
	call _trap_as

.global isr_245
.type isr_245, @function
isr_245:
	pushw $245
	call _trap_as

.global isr_246
.type isr_246, @function
isr_246:
	pushw $246
	call _trap_as

.global isr_247
.type isr_247, @function
isr_247:
	pushw $247
	call _trap_as

.global isr_248
.type isr_248, @function
isr_248:
	pushw $248
	call _trap_as

.global isr_249
.type isr_249, @function
isr_249:
	pushw $249
	call _trap_as

.global isr_250
.type isr_250, @function
isr_250:
	pushw $250
	call _trap_as

.global isr_251
.type isr_251, @function
isr_251:
	pushw $251
	call _trap_as

.global isr_252
.type isr_252, @function
isr_252:
	pushw $252
	call _trap_as

.global isr_253
.type isr_253, @function
isr_253:
	pushw $253
	call _trap_as

.global isr_254
.type isr_254, @function
isr_254:
	pushw $254
	call _trap_as

.global isr_255
.type isr_255, @function
isr_255:
	pushw $255
	call _trap_as

.global _IVT_ENTRY_LEN
_IVT_ENTRY_LEN:
.long isr_1 - _IVT_START
