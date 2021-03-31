//
//  asm.s
//  LabWork_APK_1
//
//  Created by Belousov Ilya on 29.03.21.
//

.text
.globl _myOperation

_myOperation:
    mov %esi, %edi
    add %esi, %edi
    mov %edi, %eax
ret
