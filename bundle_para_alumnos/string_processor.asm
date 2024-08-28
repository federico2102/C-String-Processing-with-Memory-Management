; FUNCIONES de C
	extern malloc
	extern free
	extern fopen
	extern fclose
	extern fprintf
	extern str_len
	extern str_cmp
	extern str_copy

; /** defines bool y puntero **/
	%define NULL 0
	%define TRUE 1
	%define FALSE 0

;LISTA
;Defino offsets para lista
%define lista_offset_name 0
%define lista_offset_first 8
%define lista_offset_last 16
;Defino el tamanio de la estructura lista
%define tamanio_lista 24

;NODO
;Defino offsets para nodo
%define nodo_offset_next 0
%define nodo_offset_prev 8
%define nodo_offset_f 16
%define nodo_offset_g 24
%define nodo_offset_type 32
;Defino el tamanio de la estructura nodo
%define tamanio_nodo 40

;KEY_T
;Defino offsets para key_t
%define key_t_offset_long 0
%define key_t_offset_value 4
;Defino el tamanio de la estructura key_t
%define tamanio_key_t 12


section .data


section .text

global string_proc_list_create
string_proc_list_create:
	push r12
	mov r12, rdi	;pila alineada y puntero a nombre de la lista en r12

	mov rdi, tamanio_lista
	call malloc
	mov qword[rax+lista_offset_name], r12
	mov qword[rax+lista_offset_first], NULL
	mov qword[rax+lista_offset_last], NULL

	pop r12

	ret

global string_proc_node_create
string_proc_node_create:
	push r12
	push r13
	push r14	;pila alineada

	mov r12, rdi	;funcion f en r12
	mov r13, rsi	;funcion g en r13
	mov r14, rdx	;tipo en r14

	mov rdi, tamanio_nodo
	call malloc
	mov qword[rax+nodo_offset_next], NULL
	mov qword[rax+nodo_offset_prev], NULL
	mov qword[rax+nodo_offset_f], r12
	mov qword[rax+nodo_offset_g], r13
	mov qword[rax+nodo_offset_type], r14

	pop r14
	pop r13
	pop r12

	ret

global string_proc_key_create
string_proc_key_create:
	push r12
	push r13
	sub rsp, 8
	mov r12, rdi	;guardo en r12 el puntero al valor

	call str_len
	mov r13d, eax	;guardo en r13 la longitud del valor
	mov rdi, r12
	call str_copy	;hago una copia del valor recibido
	mov r12, rax	;guardo la copia del valor en r12
	mov rdi, tamanio_key_t
	call malloc
	mov dword[rax+key_t_offset_long], r13d
	mov qword[rax+key_t_offset_value], r12
	
	add rsp, 8
	pop r13
	pop r12

	ret

global string_proc_list_destroy
string_proc_list_destroy:
	push r12
	push r13
	push r14
	mov r12, rdi ;guardo en r12 el puntero a la lista

	mov r13, qword[r12+lista_offset_first] ;guardo el puntero al primer elemento en r13
	
	.ciclo:
	cmp r13, NULL
	je .fin ;si no existe primer elemento la lista esta vacia
	mov r14, qword[r13+nodo_offset_next] ;guardo el puntero al nodo que sigue en r14
	mov rdi, r13 
	call string_proc_node_destroy ;llamo a la funcion que borra el nodo actual
	mov r13, r14 ; Guardo el nuevo nodo a borrar
	jmp .ciclo ; vuelvo a ciclar para continuar con el siguiente nodo a borrar


	.fin:
	mov rdi, r12 ; Paso a rdi el puntero a la lista
	call free ; Libero la memoria ocupada por la lista

	pop r14
	pop r13
	pop r12

	ret

global string_proc_node_destroy
string_proc_node_destroy:
	push r12
	push r13
	push r14

	mov r14, rdi
	mov r12, qword[r14+nodo_offset_prev] ;guardo en r12 el puntero al nodo anterior
	mov r13, qword[r14+nodo_offset_next] ;guardo en r13 el puntero al nodo siguiente
	cmp r12, NULL
	je .eliminoPrimerElemento ;si el anterior es NULL es porque es el primer nodo
	cmp r13, NULL
	je .eliminoUltimoElemento ;si el siguiente es NULL es porque es el ultimo nodo
	mov qword[r12+nodo_offset_next], r13
	mov qword[r13+nodo_offset_prev], r12
	jmp .fin

	.eliminoPrimerElemento:
	cmp r13, NULL
	je .fin ;hay un solo nodo
	mov qword[r13+nodo_offset_prev], NULL
	jmp .fin

	.eliminoUltimoElemento:
	cmp r12, NULL
	je .fin ;hay un solo nodo
	mov qword[r12+nodo_offset_next], NULL

	.fin:
	mov rdi, r14
	call free

	pop r14
	pop r13
	pop r12

	ret

global string_proc_key_destroy
string_proc_key_destroy:
	push r12
	mov r12, rdi	;guardo en r12 el puntero al key a destruir

	mov rdi, qword[rdi+key_t_offset_value]
	call free
	mov rdi, r12
	call free

	pop r12

	ret

global string_proc_list_add_node
string_proc_list_add_node:
	push r12
	push r13
	push r14
	mov r12, rdi ;guardo en r12 el puntero a la lista

	mov rdi, rsi
	mov rsi, rdx
	mov rdx, rcx
	call string_proc_node_create
	mov r14, rax

	mov r13, qword[r12+lista_offset_last] ;guardo en r13 el ultimo nodo de la lista
	mov qword[r14+nodo_offset_prev], r13
	mov qword[r14+nodo_offset_next], NULL
	mov qword[r12+lista_offset_last], r14 ;el nuevo nodo ahora es el ultimo de la lista
	cmp r13, NULL
	je .listaVacia ;si r13 es NULL significa que la lista estaba vacia
	mov qword[r13+nodo_offset_next], r14
	jmp .fin

	.listaVacia:
	mov qword[r12+lista_offset_first], r14 ;el nuevo nodo ahora es el primero y ultimo de la lista

	.fin:
	pop r14
	pop r13
	pop r12

	ret

global string_proc_list_apply
string_proc_list_apply:
	push r12
	push r13
	push r14
	mov r12, rdi ;guardo en r12 el puntero a la lista
	mov r14, rsi ;dejo en rdi el valor 'key' que le pasare por parametro a f o a g

	cmp rdx, 1
	je .aplicarF ;si salto es porque el valor de encode era true y debo aplicar f, caso contrario aplico g
	mov r12, qword[r12+lista_offset_last] ;guardo en r12 el puntero al ultimo nodo de la lista
	.aplicarG:
	cmp r12, NULL
	je .fin
	mov r13, qword[r12+nodo_offset_g]
	mov rdi, r14
	call r13
	mov r12, qword[r12+nodo_offset_prev]
	jmp .aplicarG

	.aplicarF:
	mov r12, qword[r12+lista_offset_first]
	.ciclo:
	cmp r12, NULL
	je .fin
	mov r13, qword[r12+nodo_offset_f]
	mov rdi, r14
	call r13
	mov r12, qword[r12+nodo_offset_next]
	jmp .ciclo

	.fin:
	pop r14
	pop r13
	pop r12

	ret

;AUXILIARES
; global str_copy
; str_copy:

; 	push r12
; 	push r13
; 	push r14

; 	mov r12, rdi ; guardo en r12 el puntero al dato a copiar
; 	call str_len ; me fijo que tamanio tiene el dato a copiar
; 	mov r14, rax ; guardo en r15 el tamanio del dato a copiar
; 	mov rdi, r14  
; 	call malloc
; 	mov r13, 0
	
; 	.ciclo:
; 	cmp r13, r14 ; Me fijo si estoy en la ultima letra
; 	je .fin 
; 	mov al, byte[r12+r13] 
; 	mov byte[rax+r13], al ; Copio el dato a la nueva posicion de memoria
; 	inc r13  
; 	jmp .ciclo

; 	.fin:

; 	pop r14
; 	pop r13
; 	pop r12

; 	ret

; global str_len
; str_len:

; 	push r12
; 	push r13
; 	sub rsp, 8

; 	mov r12, rdi
; 	mov r13, 0 ; Seteo a r13 en 0 para usarlo de contador 

; 	.ciclo:
; 	mov al, byte[r12+r13]
; 	cmp al, 0 ; Me fijo si llegue al final de la palabra
; 	je .fin
; 	inc r13 ; No llegue al final de la palabra, entonces hay otra letra
; 	jmp .ciclo

; 	.fin:
; 	inc r13
; 	mov rax, r13 ; Muevo el tamanio de la palabra a rax

; 	add rsp, 8
; 	pop r13
; 	pop r12
	
; 	ret			

; global str_cmp
; str_cmp:

; 	push r12
; 	push r13
; 	push r14
; 	push r15
; 	sub rsp, 8

; 	mov r12, rdi 	;guardo en r12 el puntero a la primera palabra a comparar
; 	mov r13, rsi 	;guardo en r13 el puntero a la segunda palabra a comparar
; 	mov r14, 0 		;seteo r14 en 0 para usarlo como iterador en un ciclo

; 	.ciclo:
; 	cmp byte[r12+r14], 0 	;me fijo si llegue al final de la primera palabra
; 	je .finPrimeraPalabra
; 	cmp byte[r13+r14], 0 	;me fijo si llegue al final de la segunda palabra
; 	je .esMayor 
; 	mov al, byte[r13+r14] 	;muevo una letra al registro al para poder usar cmp
; 	mov r15, r14 
; 	inc r14
; 	cmp byte[r12+r15], al 	;comparo byte a byte
; 	je .ciclo
; 	jns .esMayor 
; 	mov rax, 1 				;si llegue aca es porque r12 es menor que r13
; 	jmp .fin

; 	.finPrimeraPalabra:
; 	cmp byte[r13+r14], 0 	;me fijo si tambien llegue al final de la segunda palabra
; 	je .sonIguales 
; 	mov rax, 1 
; 	jmp .fin

; 	.esMayor:
; 	mov rax, -1
; 	jmp .fin

; 	.sonIguales:
; 	mov rax, 0
; 	jmp .fin

; 	.fin:
; 	add rsp, 8
; 	pop r15
; 	pop r14
; 	pop r13
; 	pop r12

; 	ret