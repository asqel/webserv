; x11_window.asm
; Minimal X11 window in NASM x86-64 Linux
; Build:
; nasm -f elf64 x11_window.asm
; gcc x11_window.o -o x11_window -lX11 -no-pie
; ./x11_window

global main
extern XOpenDisplay
extern XDefaultScreen
extern XRootWindow
extern XCreateSimpleWindow
extern XMapWindow
extern XStoreName
extern XSelectInput
extern XNextEvent
extern XCloseDisplay
extern exit

SECTION .data
title       db "ASM X11 Window", 0

; Event mask constants
ExposureMask equ 0x8000
KeyPressMask equ 0x0001

SECTION .bss
display     resq 1         ; pointer to Display
event       resb 192       ; XEvent structure (enough space)

SECTION .text
main:
    ; ---------------------------
    ; Stack frame and alignment
    ; ---------------------------
    push rbp
    mov rbp, rsp
    ; Align stack to 16 bytes before call (System V ABI requirement)
    and rsp, -16

    ; ---------------------------
    ; Display *display = XOpenDisplay(NULL)
    ; ---------------------------
    xor rdi, rdi        ; NULL argument
    call XOpenDisplay
    test rax, rax
    jz .exit            ; if NULL, exit
    mov [display], rax  ; save Display*

    ; ---------------------------
    ; int screen = DefaultScreen(display)
    ; ---------------------------
    mov rdi, [display]
    call XDefaultScreen
    mov esi, eax        ; save screen number

    ; ---------------------------
    ; Window root = RootWindow(display, screen)
    ; ---------------------------
    mov rdi, [display]
    mov edx, esi        ; screen
    call XRootWindow
    mov rbx, rax        ; save root window

    ; ---------------------------
    ; XCreateSimpleWindow(display, root, 0,0, 400,300, 1, 0, 0)
    ; ---------------------------
    mov rdi, [display]  ; display
    mov rsi, rbx        ; parent (root)
    xor edx, edx        ; x = 0
    xor ecx, ecx        ; y = 0
    mov r8d, 400        ; width
    mov r9d, 300        ; height
    push 0              ; background
    push 0              ; border pixel
    push 1              ; border width
    call XCreateSimpleWindow
    add rsp, 24         ; clean up stack (3*8)
    mov rbx, rax        ; save window

    ; ---------------------------
    ; XStoreName(display, window, "title")
    ; ---------------------------
    mov rdi, [display]
    mov rsi, rbx
    lea rdx, [rel title]
    call XStoreName

    ; ---------------------------
    ; XSelectInput(display, window, ExposureMask | KeyPressMask)
    ; ---------------------------
    mov rdi, [display]
    mov rsi, rbx
    mov edx, ExposureMask | KeyPressMask
    call XSelectInput

    ; ---------------------------
    ; XMapWindow(display, window)
    ; ---------------------------
    mov rdi, [display]
    mov rsi, rbx
    call XMapWindow

.event_loop:
    ; ---------------------------
    ; XNextEvent(display, &event)
    ; ---------------------------
    mov rdi, [display]
    lea rsi, [event]
    call XNextEvent
    jmp .event_loop

.exit:
    mov edi, 0
    call exit

