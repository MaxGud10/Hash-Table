global MyStrcmp

section .code

MyStrcmp:   vlddqu ymm1, [rcx]
            vptest ymm1, [rdx]
            xor rax, rax
            setc al
            ret