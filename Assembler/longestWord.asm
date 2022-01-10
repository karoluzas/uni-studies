;Parasykite programa, kuri iveda eilute zodziu, 
;atskirtu tarpais ir atspausdina ilgiausio zodzio ilgi. 
;Pvz.: ivedus asd fghas asd turi atspausdinti 5

.model small ;kiek nuskiatys atminties
.stack 100h ;steko dydis

.data ;segmento pradzia
    message db 'Iveskite zodziu eilute', 0Dh, 0Ah, 24h ;pasisveikinimo eilute
    buff db 255, 0, 255 dup(24h) ;buferis, kuriame talpinsiu ivesta teksta  
    message2 db 'Ilgiausio zodzio ilgis $' ;atsakymo eilute
    enteris db 0Dh, 0Ah, 24h ;nauja eilute
    
.code
mov ax, @data ;kintamieji aprasyti i AX ikeldami data segment'o adresa
mov ds, ax ;is ax i ds perkeliamas data segment'o adresas

mov ah, 9 ;spausdinama pasisveikinimo zinute
mov dx, offset message
int 21h

mov ah, 0Ah ;vykdomas nusiskaitymas
mov dx, offset buff
int 21h  


xor ax, ax ;ax einancio zodzio dydis
xor cx, cx ;cx didziausio zodzio dydis
mov si, 2

ciklas:
mov bx, si ;kelintas narys 
dec bl ;susimazinu, kad butu vienoda
cmp bl, [buff+1] ;kiek teksto ivedziau
ja paskutinis
mov bl, [buff+si]

cmp bl, 20h ;lyginu su tarpu
je lygina

inc ax
inc si
jmp ciklas

lygina: ;iesko ilgiausio
inc si
cmp ax, cx
jl nunulina
mov cx, ax
xor ax, ax
jmp ciklas  
 
nunulina:
xor ax, ax
jmp ciklas

paskutinis:
cmp ax, cx
jl pabaiga
mov cx, ax
xor ax, ax       

pabaiga:
xor si, si
mov al, cl 
mov bl, 0Ah
      
vertimoCiklas:
inc si
div bl ;dalyba is 10
xor ch, ch
mov cl, ah ;liekana
xor ah, ah
push cx ;i steka padedama liekana
cmp al, 0 ;jei skaicius nelygus nuliui, reikia toliau dalint
jne vertimoCiklas 


mov ah, 9 ;pereinama i nauja eilute
mov dx, offset enteris
int 21h

mov ah, 9 ;isspausdinamas atsakymo tekstas
mov dx, offset message2
int 21h
 
spausdinimas: 
dec si
pop cx
            
mov dx, cx
add dx, 30h ;pagal ascii lentele

mov ah, 02h
int 21h
cmp si, 0 
jne spausdinimas

mov ax, 4C00h ;uzdaroma programa
int 21h

END    