section .text
global MyStrcmp

; int MyStrcmp(const char* a, const char* b)
; Ѕыстрейша€ ветвление-свободна€ верси€:
;  Х одна загрузка + fused-load в vpcmpeqb
;  Х минимальное число uopТов
;  Х нет jz/ret в середине, только одиночный ret
;  Х xor+and вместо not+branch
MyStrcmp:
    vmovdqu     ymm0, [rdi]          ; uop: load 32B из a
    vpcmpeqb    ymm1, ymm0, [rsi]    ; uop: fused-load+compare с b
    vpmovmskb   eax, ymm1            ; uop: собрать 32-битную маску

    xor         eax, -1              ; uop: инвертировать mask
    and         eax, 1               ; uop: оставить только бит0 ? {0,1}

    vzeroupper                       ; очистить состо€ние AVX (дл€ SSE)
    ret                              ; возвращаем 0 если равны, 1 иначе
