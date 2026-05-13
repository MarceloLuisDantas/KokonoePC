# Instructions
| Bytecode | Opcode | Size | Body                   | Description |
|----------|--------|------|------------------------|-------------|
| 0x00     | nop    | 1    |                        | Do nothing  |
| 0x01     | ret    | 1    |                        | Return      |
| ...      |        |      |                        |
| 0x10     | lia    | 3    | lia [16b IMMN]         | load immediate 16b to A
| 0x11     | lix    | 3    | lix [16b IMMN]         | load immediate 16b to X
| 0x12     | liy    | 3    | liy [16b IMMN]         | load immediate 16b to Y
| 0x13     | liz    | 3    | liz [16b IMMN]         | load immediate 16b to Z
| 0x14     | lia.h  | 2    | lia [8b IMMN]          | load immediate 8b to A
| 0x15     | lix.h  | 2    | lix [8b IMMN]          | load immediate 8b to X
| 0x16     | liy.h  | 2    | liy [8b IMMN]          | load immediate 8b to Y
| 0x17     | liz.h  | 2    | liz [8b IMMN]          | load immediate 8b to Z
| 0x18     | ina    | 1    | ina                    | increment A
| 0x19     | inx    | 1    | inx                    | increment X
| 0x1A     | iny    | 1    | iny                    | increment Y
| 0x1B     | inz    | 1    | inz                    | increment Z
| 0x1C     | dea    | 1    | dea                    | decrement A
| 0x1D     | dex    | 1    | dex                    | decrement X
| 0x1E     | dey    | 1    | dey                    | decrement Y
| 0x1F     | dez    | 1    | dez                    | decrement Z
| 0x20     | txa    | 1    | txa                    | transfer X to A
| 0x21     | tya    | 1    | tya                    | transfer Y to A
| 0x22     | tza    | 1    | tza                    | transfer Z to A
| 0x23     | tax    | 1    | tax                    | transfer A to X
| 0x24     | tay    | 1    | tay                    | transfer A to Y 
| 0x24     | taz    | 1    | taz                    | transfer A to Z 
| 0x25     | txy    | 1    | txy                    | transfer X to Y
| 0x26     | txz    | 1    | txz                    | transfer X to Z
| 0x27     | tyx    | 1    | tyx                    | transfer Y to X 
| 0x28     | tyz    | 1    | tyz                    | transfer Y to Z 
| 0x29     | tzx    | 1    | tzx                    | transfer Z to X
| 0x2A     | tzy    | 1    | tzy                    | transfer Z to Y
| ...      |        |      |                        | 
| 0x30     | add    | 3    | add [DEST], [SRC]      | add SRC to DEST, set carry flag 
| 0x31     | adi    | 3    | add [DEST], [8b IMMN]  | add IMMN to DEST, set carry flag 
| 0x32     | adi.d  | 4    | add [DEST], [16b IMMN] | add IMMN to DEST, set carry flag 
| 0x33     | adc    | 3    | adc [DEST], [SRC]      | add SRC to DEST with carry, set carry flag  
| 0x34     | ada    | 2    | ada [SRC]              | add SRC to register A, set and carry flag 
| 0x35     | adx    | 2    | adx [SRC]              | add SRC to register X, set and carry flag 
| 0x36     | ady    | 2    | ady [SRC]              | add SRC to register Y, set and carry flag 
| 0x37     | adz    | 2    | adz [SRC]              | add SRC to register Z, set and carry flag 
| 0x38     | 
| 0x39     | 
| ...      |        |      |                        |
| 0x50     | sla    | 2    | sla [IMMN]             | shift left A by IMMN 
| 0x51     | sra    | 2    | sra [IMMN]             | shift right A by IMMN 
| 0x52     | cmp    | 3    | cmp [REG]              | compares 
| 0x53     |     |     |              | 
| 0x54     |     |     |              | 
| 0x55     |     |     |              | 
| ...      |        |      |                        |
| 0xA0     | lda    | 3    | lda [16b RAM ADDRESS]  | loads the 16b value in RAM ADDRESS to A
| 0xA1     | lda.b  | 2    | lda [1bb RAM ADDRESS]  | loads the 8b value in RAM ADDRESS to the frist 8 bits in A
| 0xA2     | sta    | 3    | sta [16b RAM ADDRESS]  | store the value in A to RAM ADDRESS
| 0xA3     | sta.b  | 2    | sta [16b RAM ADDRESS]  | store the 8 frist bits of A to RAM ADDRESS


# Pseudo Instructions
| Instruction   | Description                     | Respective Instruction                         |  
|---------------|---------------------------------|------------------------------------------------|
| li reg IMMN   | Load immediate 8b or 16b to reg | lia, lix, liy, liz, lia.h, lix.h, liy.h, liz.h |
| inc reg       | increment reg                   | ina, inx, iny, inz |
| dec reg       | decrement reg                   | dea, dex, dey, dez |
| move r1 r2    | moves the value from R1 to R2   | txa, tya, tza, tax, tay, taz, txy, txz, tyx, tyz, tzx, tzy |










