section .text

global load_page_dir
global enable_paging

load_page_dir:
    push ebp ; Preserve ebp on the stack
    mov ebp, esp ; Store esp's original state in ebp

    mov eax, [ebp+8] ; Move the first parameter (page directory location)
    mov cr3, eax ; Move page directory location to cr3

    mov esp, ebp ; Put esp back to its original state
    pop ebp ; Restore ebp's original state from the stack
    ret

enable_paging:
    push ebp
    mov ebp, esp

    mov eax, cr0 ; Move the value from cr0 to eax
    or eax, 0x80000000 ; Set the 32nd bit in eax to enable paging
    mov cr0, eax ; Move new eax value back to cr0

    mov esp, ebp
    pop ebp
    ret
