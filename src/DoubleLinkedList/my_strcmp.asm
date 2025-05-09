section .text
global MyStrcmp

MyStrcmp:
    vmovdqu     ymm0,       [rdi]       
    vpcmpeqb    ymm1, ymm0, [rsi] 
    vpmovmskb   eax,  ymm1     

    xor         eax, 0xFFFFFFFF   
    jz          .equal  
              
    mov         eax, 1            
    ret

.equal:
    xor         eax, eax          
    ret



