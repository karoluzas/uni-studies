
; You may customize this and other start-up templates; 
; The location of this template is c:\emu8086\inc\0_com_template.txt

org 100h

.MODEL small        ; atminties modelis
.STACK 100h         ; steko dydis
.DATA               ; duomenu segmentas
   
zinute db 0Ah,0Dh,"Iveskite skaiciu hex: $"   
   
laikinas1 dw ?  ; kaire puse simboliu
laikinas2 dw ?  ; desine puse simboliu
 
input_buffer db 5, ?, 5 dup<0>  ; inputo bufferis

                 


.CODE               ; kodo segmentas
strt:
mov ax, @data       ; ds registro inicializavimas
mov ds, ax           

; zinutes spausdinimas
mov ah, 09h
mov dx, offset zinute
int 21h

; inputas
mov ah, 0Ah
mov dx, offset input_buffer 
int 21h

  
  
; Pirmojo simbolio pavertimas
mov al,input_buffer[2]  ; Priskiria al'ui pirmaji simboli 

sk1_1:          
cmp al,'9'          ; palyginia al su '9' (ascii 39), tikrina ar ivesta reiksme skaicius
ja sk1_2            ; jeigu ne 0 - 9 tai soka toliau

sub al, 30h         ; jeigu reiksme skaicius, pavercia reiksme i skaiciu (pvz 39 paverstu i 9)
jmp pirmas_simbolis ; soka i simbolio pavertima

sk1_2:              ; jeigu simbolis a - f tai vygdo sia procedura
or al, 00100000b    ; panaikina didziasias raides
sub al, 57h         ; pavercia simboli i skaiciu

pirmas_simbolis:    ; simbolio pavertimas
mov bl,16           ; priskiria bl registrui 16, 10h reiksmes
mul bl              ; ax = al * bl
mov laikinas1, ax   ; i laikina reiksme ikelia ax registra



;Antro simbolio pavertimas
mov al,input_buffer[3]

sk2_1:
cmp al,'9'
ja sk2_2

sub al, 30h
jmp antras_simbolis

sk2_2:
or al, 00100000b
sub al,57h

antras_simbolis:
xor ah,ah
add laikinas1, ax

push laikinas1
  
  

;Trecio simbolio pavertimas
mov al,input_buffer[4]  

sk3_1:
cmp al,'9'
ja sk3_2

sub al,30h
jmp trecias_simbolis

sk3_2:
or al, 00100000b
sub al,57h

trecias_simbolis:
mov bl,16
mul bl
mov laikinas2, ax

 
 
;Ketvirtas simbolio pavertimas
mov al,input_buffer[5]

sk4_1:
cmp al,'9'
ja sk4_2

sub al,30h
jmp ketvirtas_simbolis

sk4_2:
or al,00100000b
sub al,57h

ketvirtas_simbolis:
xor ah,ah
add laikinas2, ax


; Konvertavimas i dvejataine sistema
; Laikinas1 pavertimas

pop bx
push laikinas2

mov ah,02h

mov dl,0Ah
int 21h             ; nauja eilute

mov cx,4
loopas1:
mov dl,0
rcl bl,1
adc dl,30h
int 21h
loop loopas1

mov dl,' '
int 21h

mov cx,4
loopas2:
mov dl,0
rcl bl,1
adc dl,30h
int 21h
loop loopas2

mov dl,' '
int 21h

; Laikinas2 pavertimas
pop bx

mov cx,4
loopas3:
mov dl,0
rcl bl,1
adc dl,30h
int 21h
loop loopas3 

mov dl,' '
int 21h

mov cx,4
loopas4:
mov dl,0
rcl bl,1
adc dl,30h
int 21h
loop loopas4
 
 
 
 
 
 
 
 

mov ax,4C00h      ; programos darbo pabaiga
int 21h
end strt

ret




