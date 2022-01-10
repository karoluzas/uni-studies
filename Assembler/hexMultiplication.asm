.model small
.stack 100h

.data 

erroras db "Iveskite duomeu failo pavadinima, skaiciu tarp 0-Fh, rezultatu failo pavadinima", 10, 13, '$'
failo_pavadinimas db 100 dup(' '),0
daugiklis db 0
ilgis db 0 
handle dw 0
handle2 dw 0
kiekis db 0
liekana db 0
prideti db 0
laikinas1 db 0
laikinas2 db 0  
bufferis db 150, ?, 150 dup(0)
atsakymai db 150, ?, 150 dup(0)
rez_pavadinimas db "rez.txt",0, 100 dup(' '),0

.code
             
    erroro:
	mov dx, offset erroras
	mov ah, 09h
	int 21h
	mov ah, 4Ch
	int 21h 
	
	pabaiga:
	mov ah, 4Ch
	int 21h 

strt:

	MOV DX, @data
	MOV DS, DX	
	
	mov bx, 0080h                       ; 0080h es registre prasideda duomenys susije su parametru eilute 
	xor cx, cx                          ; nunulinamas cx registras
	mov cl, es:[bx]                     ; ideda eilutes ilgi i cl
	
	lea di, failo_pavadinimas           ; i di idedamas duomenu failo pavadinimo adresas
	lea si, rez_pavadinimas             ; i si idedamas rezultatu failo pavadinimo adresas
	
	cmp cx, 0                           ; jeigu cx 0, reiskiasi nera nieko parametru eilutej
	jz erroro 
	             
	add bx, 2                           ; prie 0080h pridedama 2, toje vietoje prasideda simboliai 
	
	failo_pav:
	    mov al, es:[bx]                 ; i al idedamas simbolis eiluteje
	    cmp al, ' '                     ; palyginama ar al lygus tarpui
	    je skaiciuss                    ; jeigu taip tai sokama toliau
	    cmp al, '?'                     ; tikrina ar buvo prasyta pagalbos
	    je slash
	    jmp testi                       ; jeigu ne, tesia darba   
	    slash:
			mov ah, es:[bx+1]
	        cmp ah, '/'          	; tikrina ar sekantis simbolis '/'
	        je erroro                   ; jeigu taip printinama pagalbos zinute
	    
	    testi:	        
	    mov [di], al                    ; i failo_pavadinimas masyva idedama al reiksme
	    inc bx                          ; bx padidinamas vienetu
	    inc di                          ; di padidinamas vienetu
	    loop failo_pav                  ; ciklas kol randa pirma zodi
	    jmp erroro                      ; jeigu ciklas neranda tarpo ir tik viena zodi tai sokama i error message
	
	skaiciuss:
	    mov byte ptr [di],0             ; i gala masyvo failo_pavadinimas idedamas 0
	    inc bx                          ; bx padidinamas vienetu
	    mov al, es:[bx]                 ; i al registra idedamas skaicius
	    cmp al, '0'                     ; tikrina ar buvo ivestas skaicius
	    jb erroro 
	    cmp al, '9'
	    ja kokia_raide
	    
	    sub al, 30h                     ; jeigu ivestas sk tarp 0-9 paverciama i skaiciu
	    jmp toliau                      ; tesimas darbo
	    
	    kokia_raide:
	        cmp al, 47h
	        jb atima
	        cmp al, 60h
	        ja tikrina
 
	    
	    
	    tikrina:                        ; jeigu ivestas simbolis buvo raide didzioji, ji paverciama i mazaja
	        xor al, 00100000b            ; lyginamas al su mazuju raidziu a-f hex reiksmemis
	        
	        atima:
	        cmp al, 41h
	        jb erroro
	        cmp al, 46h
	        ja erroro
	        
	        sub al, 37h                 ; jeigu rasta tinkama raide, paverciama i skaiciu
	    
	    
	    toliau:
	    
	    mov daugiklis, al               ; issisaugojamas skaicius is al
	    inc bx                          ; bx padidinamas vienetu
	    sub cl, 4                       ; is skaitliuko atimama 4, kad kitas ciklas viektu reikiama kartu kieki
	    mov al, es:[bx]
		cmp al, ' '                		; tikrina ar sekantis po skaiciaus simbolis tarpas
	    je rez_pav                      ; jeigu taip tai soka i errora
	    jmp erroro                      
	    
	rez_pav:
	    inc bx                          ; bx padidinamas vienetu
	    cmp cl, 0
	    je rez_default
	    
	    
	    
	    mov al, es:[bx]                 ; i al idedamas sekantis simbolis
	    mov [si], al                    ; i rez_pavadinimas idedama al reiksme
	    inc si                          ; si padidinamas vienetu
	    loop rez_pav                    ; vyksta ciklas kol pasibaigia cx registras
	    
	    mov byte ptr [si],0             ; gale rez_pavadinimas idedamas 0
	    
	    rez_default:
	    
  
	;---------------------
    ;failo atidarymas
    ;---------------------	
    mov ah,3Dh
    mov al,0
    mov dx, offset failo_pavadinimas
    int 21h
    jc baigimas							; jeigu kyla problema su failo atidarymu sokama i pabaiga
	jmp ignor
	
	baigimas:
	mov ah, 4Ch
	int 21h 

    ignor:    
    mov [handle], ax
    mov bx,ax
    mov ax, 0
    mov cx, 0206h             
    ;---------------------
    ;skaitymas is failo reiksmes
    ;---------------------
    mov ah,3Fh
    mov dx, offset bufferis
    int 21h
    mov kiekis, al
    jc baigimas  
       
    mov si, 0
    mov cx, 0
    mov cl,kiekis       
    ;---------------------
    ;reiksmiu isidejimas i stack
    ;---------------------
    loopas1:
    mov ax, 0
    mov al, bufferis[si]
    push ax
    inc si
    loop loopas1
    
    
    call procedura
    
    mov al, prideti
    cmp al, 9h
    ja raides
    cmp al, 0
    je  praleidimas
    
    add al, 30h
    inc kiekis
    jmp tesinys
    raides:
        add al, 37h 
        inc kiekis
    
    
    tesinys:
    mov atsakymai[si+1], al
    
    praleidimas:
    mov si, 0
    mov ax, 0
    mov cl, kiekis
    
    loopas2:
    mov al, atsakymai[si+1]
    push ax
    inc si
    loop loopas2
    
    mov si,0
    mov ax,0
    mov cl,kiekis
    
    ;praleidimas:
    
    loopas3:
    pop ax
    mov atsakymai[si+1], al
    inc si                 
    loop loopas3
     
     
     
    mov ah, 3Ch
    mov cx, 0
    mov dx, offset rez_pavadinimas
    int 21h
    
    mov [handle], ax
    mov bx,ax
    
    mov ah, 40h
    mov cl, kiekis
    mov dx, offset atsakymai + 1
    int 21h
	mov [handle2], ax
	
	mov ah, 3eh
	mov bx, [handle]
	int 21h
	mov ax, 4c00h
	int 21h
	
	mov ah, 3eh
	mov bx, [handle2]
	int 21h
	mov ax, 4c00h
	int 21h
    
	pabaiga2:
	mov ah, 4Ch
	int 21h 
    
    
procedura PROC
pop ax
mov laikinas2, al

mov si, 0
mov cx, 0
mov cl,kiekis
dauginam:
    mov ax, 0
    pop ax              ;is steko isimamas pirmasis skaicius
    
    
    cmp ax, 'A'         ;tikrinama ar simbolis skaicius ar raide
    jl skaicius
    cmp ax, 'A'
    jge raide
    
    skaicius:           ;jeigu skaicius, konvertuojam is ASCII i atitinkama hex
        sub ax, 30h
        jmp testimas       ;tesia toliau
    
    raide:              ;jeigu raide, kovertuojam is ASCII i atitinkama hex reiksme
        ;xor al, 00100000b
        sub ax, 37h     
        jmp testimas       ;tesia toliau
    
    testimas:              ;konvertave einame toliau prie dauginimo
    mul daugiklis       ;ax = al * daugiklis
    add al, prideti     ;prie al prideda isimintina skaiciu dauginant
    
    mov laikinas1, al   ;i laikina kintamaji issaugojama al reiksme     
    and al, 00001111b   ;vyresniuosius keturis bitus pakeicia i nulius
    cmp al, 9h          ;daro palyginima su skaiciumi, jeigu skaicius <= 9h paverciame i atitnkama ASCII leteles skaiciaus reiksme, jeigu > 9h, i raides ASCII koda    
    jle sk                                                                                                                                  
    
    cmp al, 9h
    jg raid
    
        sk:
        add al, 30h
        jmp toliau2
        raid:
        add al, 37h
        jmp toliau2
        
    
    toliau2:    
    mov atsakymai[si+1], al ;i atsakymu masyva ideda atsakyma
    inc si
    
    mov al, laikinas1       ;ideda i al priestai issaugota laikinas1
    and al, 11110000b       ;palieka tik vyresniuosius bitus al'e
    ror al, 4               ;perstumia likusius bitus keturis kartus i desine
    mov prideti, al         ;issisaugome isimintina skaiciu reikalinga toliau dauginti skaicius
    
    
    dec cl
    cmp cl, 0
    je Exit
    cmp cl, 0
    jg dauginam
                         
    Exit:
    mov al, laikinas2
    push ax
    ret
 
procedura ENDP         
	
	
	
end strt