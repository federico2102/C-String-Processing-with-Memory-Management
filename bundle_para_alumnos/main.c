#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include "string_processor.h"
#include "string_processor_utils.h"

/**
*	crea y destruye a una lista vacía
*/
void test_create_destroy_list(){
	string_proc_list * list	= string_proc_list_create("nueva lista");
	string_proc_list_destroy(list);
}

/**
*	crea y destruye un nodo
*	para esta función es conveniente haber implementado al menos un par de funciones
*	(por ej. shift_2, unshift_2)
*/
void test_create_destroy_node(){
	string_proc_node* node	= string_proc_node_create(&shift_2, &unshift_2, REVERSIBLE);
	string_proc_node_destroy(node);
}

/**
*	crea y destruye una clave 
*/
void test_create_destroy_key(){
	string_proc_key* key	= string_proc_key_create("hola mundo");
	string_proc_key_destroy(key);
}

/**
*	crea una lista y la imprime por salida standard (stdout)		
*/
void test_print_list(){
	string_proc_list * list	= string_proc_list_create("nueva lista");
	string_proc_list_print(list, stdout);
	string_proc_list_destroy(list);
}

/**
*	crea una lista con un solo nodo con  f:shift_2, g:unshift_2, type:reversible
*	y prueba encode y decode por separado sobre "hola mundo" imprimiendo
*	el string procesado (aplicando encode primero y luego decode a través de string_proc_list_apply) 
* 	e imprima ambos strings por salida estandard seguido de un '\n'
*/
void test_shift_2(){
	printf("Probando shift_2, unshift_2\n============\n");
	string_proc_list * list	= string_proc_list_create("nueva lista");
	string_proc_list_add_node(list, &shift_2, &unshift_2, REVERSIBLE);
	string_proc_key* key	= string_proc_key_create("hola mundo");
	string_proc_list_apply(list, key, true);
	printf("%s\n", key->value);
	string_proc_list_apply(list, key, false);
	printf("%s\n", key->value);
	printf("\n");
	string_proc_key_destroy(key);
	string_proc_list_destroy(list);
}

/**
*	crea una lista con un solo nodo con  f:shift_position, g:unshift_position, type:reversible
*	y prueba encode y decode por separado sobre "hola mundo" imprimiendo
*	el string procesado (aplicando encode primero y luego decode) e imprima ambos strings por salida estandard seguido de un '\n'
*/
void test_shift_position(){
	printf("Probando shift_positon, unshift_position\n============\n");
	string_proc_list * list	= string_proc_list_create("nueva lista");
	string_proc_list_add_node(list, &shift_position, &unshift_position, REVERSIBLE);
	string_proc_key* key	= string_proc_key_create("hola mundo");

	string_proc_list_apply(list, key, true);
	printf("%s\n", key->value);
	string_proc_list_apply(list, key, false);
	printf("%s\n", key->value);
	printf("\n");
	string_proc_key_destroy(key);
	string_proc_list_destroy(list);
}

/**
*	crea una lista con un solo nodo con  f:saturate_2, g:unsaturate_2, type:irreversible
*	y prueba encode y decode por separado sobre "hola mundo" imprimiendo
*	el string procesado (aplicando encode primero y luego decode) e imprima ambos strings por salida estandard seguido de un '\n'
*/
void test_saturate_2(){
	printf("Probando saturate_2, unsaturate_2\n============\n");
	string_proc_list * list	= string_proc_list_create("nueva lista");
	string_proc_list_add_node(list, &saturate_2, &unsaturate_2, IRREVERSIBLE);
	string_proc_key* key	= string_proc_key_create("hola mundo");

	string_proc_list_apply(list, key, true);
	printf("%s\n", key->value);
	string_proc_list_apply(list, key, false);
	printf("%s\n", key->value);
	printf("\n");
	string_proc_key_destroy(key);
	string_proc_list_destroy(list);
}

/**
*	crea una lista con un solo nodo con f:saturate_position, g:unsaturate_position, type:irreversible
*	y prueba encode y decode por separado sobre "hola mundo" imprimiendo
*	el string procesado (aplicando encode primero y luego decode) e imprima ambos strings por salida estandard seguido de un '\n'
*/
void test_saturate_position(){
	printf("Probando saturate_position, unsaturate_position\n============\n");
	string_proc_list * list	= string_proc_list_create("nueva lista");
	string_proc_list_add_node(list, &saturate_position, &unsaturate_position, IRREVERSIBLE);
	string_proc_key* key	= string_proc_key_create("hola mundo");

	string_proc_list_apply(list, key, true);
	printf("%s\n", key->value);
	string_proc_list_apply(list, key, false);
	printf("%s\n", key->value);
	printf("\n");
	string_proc_key_destroy(key);
	string_proc_list_destroy(list);
}

/**
*	crea una lista con dos nodos 
*		- el primero con f:shif_2, g:unshift_2, type:reversible
*		- el primero con f:shif_position, g:unshift_position, type:reversible
*	y prueba encode y decode por separado sobre "hola mundo!" imprimiendo
*	el string procesado (aplicando encode primero y luego decode) e imprima ambos strings por salida estandard seguido de un '\n'
*	Consiga la copia que invierte las funciones de la lista y pruebe ésta con el string 
*	"hemos ido demasiado lejos y se acerca la hora de detenernos a reflexionar" imprimiendo
*	el string procesado (aplicando encode primero y luego decode) e imprima ambos strings por salida estandard seguido de un '\n'
*/
void test_combo_reversible(){
	printf("Probando combo reversible\n============\n");
	string_proc_list * list	= string_proc_list_create("nueva lista");
	string_proc_list_add_node(list, &unshift_2, &shift_2, REVERSIBLE);
	string_proc_list_add_node(list, &unshift_position, &shift_position, REVERSIBLE);
	string_proc_key* key	= string_proc_key_create("hola mundo");
	string_proc_list_apply(list, key, true);
	printf("%s\n", key->value);
	string_proc_list_apply(list, key, false);
	printf("%s\n", key->value);
	printf("\n");

	printf("Probando combo irreversible invertido\n============\n");
	string_proc_list* inverted_list	= string_proc_list_invert(list);
	string_proc_key* inverted_key	= string_proc_key_create("hemos ido demasiado lejos y se acerca la hora de detenernos a reflexionar");
	string_proc_list_apply(inverted_list, inverted_key, true);
	printf("%s\n", inverted_key->value);
	string_proc_list_apply(inverted_list, inverted_key, false);
	printf("%s\n", inverted_key->value);
	printf("\n");
	string_proc_key_destroy(inverted_key);
	string_proc_list_destroy(inverted_list);

	string_proc_key_destroy(key);
	string_proc_list_destroy(list);
}

/**
*	crea una lista con dos nodos 
*		- el primero con f:shif_2, g:unshift_2, type:reversible
*		- el primero con f:saturate_position, g:saturate_position, type:irreversible
*	y prueba encode y decode por separado sobre "hola mundo!" imprimiendo
*	el string procesado (aplicando encode primero y luego decode) e imprima ambos strings por salida estandard seguido de un '\n'
*	Consiga la copia que invierte las funciones de la lista y pruebe ésta con el string 
*	"hemos ido demasiado lejos y se acerca la hora de detenernos a reflexionar" imprimiendo
*	el string procesado (aplicando encode primero y luego decode) e imprima ambos strings por salida estandard seguido de un '\n'
*	Consiga la copia que filtra la primer lista dejando sólo los nodos reversibles
*	y pruebe ésta con el string "mother forgive me" imprimiendo
*	el string procesado (aplicando encode primero y luego decode) e imprima ambos strings por salida estandard seguido de un '\n'
*/
void test_combo_irreversible(){
	printf("Probando combo irreversible\n============\n");
	string_proc_list * list	= string_proc_list_create("nueva lista");
	string_proc_list_add_node(list, &shift_2, &unshift_2, REVERSIBLE);
	string_proc_list_add_node(list, &unsaturate_position, &saturate_position, REVERSIBLE);
	string_proc_key* key	= string_proc_key_create("hola mundo");

	string_proc_list_apply(list, key, true);
	printf("%s\n", key->value);
	string_proc_list_apply(list, key, false);
	printf("%s\n", key->value);
	printf("\n");

	printf("Probando combo irreversible invertido\n============\n");
	string_proc_list* inverted_list	= string_proc_list_invert(list);
	string_proc_key* inverted_key	= string_proc_key_create("hemos ido demasiado lejos y se acerca la hora de detenernos a reflexionar");
	string_proc_list_apply(inverted_list, inverted_key, true);
	printf("%s\n", inverted_key->value);
	string_proc_list_apply(inverted_list, inverted_key, false);
	printf("%s\n", inverted_key->value);
	printf("\n");

	printf("Probando combo filtrado\n============\n");
	string_proc_list* filtered_list	= string_proc_list_filter_by_type(list, REVERSIBLE);
	string_proc_key* filtered_key	= string_proc_key_create("mother forgive me");
	string_proc_list_apply(filtered_list, inverted_key, true);
	printf("%s\n", inverted_key->value);
	string_proc_list_apply(filtered_list, inverted_key, false);
	printf("%s\n", inverted_key->value);
	printf("\n");
	string_proc_list_apply(filtered_list, filtered_key, true);
	printf("%s\n", filtered_key->value);
	string_proc_list_apply(filtered_list, filtered_key, false);
	printf("%s\n", filtered_key->value);
	printf("\n");

	string_proc_key_destroy(filtered_key);
	string_proc_list_destroy(filtered_list);

	string_proc_key_destroy(inverted_key);
	string_proc_list_destroy(inverted_list);

	string_proc_key_destroy(key);
	string_proc_list_destroy(list);
}

//TODO:debe implementar
/**
*	crea una lista con 0, 1, 5 nodos respectivamente e imprime su longitud 
*/
void test_list_length(){
	printf("Probando largo lista\n============\n");
	//Lista vacia
	string_proc_list * list	= string_proc_list_create("nueva lista");
	printf("List length:%d\n", string_proc_list_length(list));

	//Lista con un solo nodo
	string_proc_list_add_node(list, &unshift_position_prime, &shift_position_prime, REVERSIBLE);
	printf("List length:%d\n", string_proc_list_length(list));

	//Lista con 5 nodos
	string_proc_list_add_node(list, &saturate_2_odd, &unsaturate_2_odd, REVERSIBLE);
	string_proc_list_add_node(list, &unshift_position_prime, &shift_position_prime, REVERSIBLE);
	string_proc_list_add_node(list, &unsaturate_2_odd, &saturate_2_odd, REVERSIBLE);
	string_proc_list_add_node(list, &unshift_position_prime, &shift_position_prime, REVERSIBLE);
	printf("List length:%d\n", string_proc_list_length(list));

	string_proc_list_destroy(list);
}

//TODO:debe implementar
/**
*	para todos los casos imprimir los estados de la lista
*	crea una lista vacía y le agrega y quita un elemento al comienzo
*	crea una lista con cinco nodos irreversibles y:
*		agrega y quita al comienzo un nodo reversible
*		agrega y quita al final un nodo reversible
*		intenta agregar y quitar un nodo reversible fuera de rango
*		agrega y quita un nodo reversible en la posición 2
*/
void test_list_add_remove_node(){
	printf("Probando agregar y quitar nodo\n============\n");
	string_proc_list * list	= string_proc_list_create("nueva lista");
	string_proc_list_add_node(list, &unshift_position_prime, &shift_position_prime, IRREVERSIBLE);
	//Imprimo lista con un solo nodo
	string_proc_list_print(list,stdout);
	//Quito el nodo e imprimo lista
	string_proc_list_remove_node_at(list, 0);
	string_proc_list_print(list,stdout);

	//Creo lista con 5 nodos irreversibles y la imprimo
	string_proc_list_add_node(list, &unshift_position_prime, &shift_position_prime, IRREVERSIBLE);
	string_proc_list_add_node(list, &saturate_2_odd, &unsaturate_2_odd, IRREVERSIBLE);
	string_proc_list_add_node(list, &unshift_position_prime, &shift_position_prime, IRREVERSIBLE);
	string_proc_list_add_node(list, &unsaturate_2_odd, &saturate_2_odd, IRREVERSIBLE);
	string_proc_list_add_node(list, &unshift_position_prime, &shift_position_prime, IRREVERSIBLE);
	string_proc_list_print(list,stdout);

	//Agrego y quito nodo reversible al principio e imprimo cada caso
	string_proc_list_add_node_at(list, &unshift_position_prime, &shift_position_prime, REVERSIBLE, 0);
	string_proc_list_print(list,stdout);
	string_proc_list_remove_node_at(list, 0);
	string_proc_list_print(list,stdout);

	//Intento agregar y quitar nodo reversible fuera de rango e imprimo cada caso
	string_proc_list_add_node_at(list, &unshift_position_prime, &shift_position_prime, REVERSIBLE,	7);
	string_proc_list_print(list,stdout);
	string_proc_list_remove_node_at(list, 9);
	string_proc_list_print(list,stdout);

	//Agrego y quito un nodo reversible en la posicion 2 e imprimo cada caso
	string_proc_list_add_node_at(list, &unshift_position_prime, &shift_position_prime, REVERSIBLE,	2);
	string_proc_list_print(list,stdout);
	string_proc_list_remove_node_at(list, 2);
	string_proc_list_print(list,stdout);

	string_proc_list_destroy(list);
}

//TODO:debe implementar
/**
*	crea una lista con cinco nodos irreversibles, uno reversible y uno irreversible (en ese orden), imprimirla, conseguir la copia de orden inverso 
*	(string_proc_list_invert_order) e imprimir la copia
*/
void test_list_invert_order(){
	printf("Probando invertir el orden de la lista\n============\n");
	// Creo la lista y la imprimo
	string_proc_list* list	= string_proc_list_create("nueva lista");
	string_proc_list_add_node(list, &unshift_position_prime, &shift_position_prime, IRREVERSIBLE);
	string_proc_list_add_node(list, &unshift_position_prime, &shift_position_prime, REVERSIBLE);
	string_proc_list_add_node(list, &unshift_position_prime, &shift_position_prime, IRREVERSIBLE);
	string_proc_list_add_node(list, &unshift_position_prime, &shift_position_prime, IRREVERSIBLE);
	string_proc_list_add_node(list, &saturate_2_odd, &unsaturate_2_odd, IRREVERSIBLE);
	string_proc_list_add_node(list, &unshift_position_prime, &shift_position_prime, IRREVERSIBLE);
	string_proc_list_add_node(list, &unsaturate_2_odd, &saturate_2_odd, IRREVERSIBLE);
	string_proc_list_print(list,stdout);

	//Invierto la lista y la imprimo
	string_proc_list* nueva_lista = string_proc_list_invert_order(list);
	string_proc_list_print(nueva_lista,stdout);

	string_proc_list_destroy(list);
	string_proc_list_destroy(nueva_lista);
}

//TODO:debe implementar
/**
*	crea una lista con cinco nodos irreversibles, uno reversible y uno irreversible (en ese orden), imprimirla, conseguir la copia de orden inverso 
*	(string_proc_list_invert_order) y hace la llamada a string_proc_list_apply_print_trace
*/
void test_list_apply_print_trace(){
	printf("Probando apply print trace\n============\n");
	// Creo la lista y la imprimo
	string_proc_list* list	= string_proc_list_create("nueva lista");
	string_proc_list_add_node(list, &unshift_position_prime, &shift_position_prime, IRREVERSIBLE);
	string_proc_list_add_node(list, &unshift_position_prime, &shift_position_prime, REVERSIBLE);
	string_proc_list_add_node(list, &unshift_position_prime, &shift_position_prime, IRREVERSIBLE);
	string_proc_list_add_node(list, &unshift_position_prime, &shift_position_prime, IRREVERSIBLE);
	string_proc_list_add_node(list, &saturate_2_odd, &unsaturate_2_odd, IRREVERSIBLE);
	string_proc_list_add_node(list, &unshift_position_prime, &shift_position_prime, IRREVERSIBLE);
	string_proc_list_add_node(list, &unsaturate_2_odd, &saturate_2_odd, IRREVERSIBLE);
	string_proc_list_print(list,stdout);

	//Invierto la lista y hago la llamada a string_proc_list_apply_print_trace
	string_proc_list* nueva_lista = string_proc_list_invert_order(list);
	string_proc_key* key	= string_proc_key_create("hemos ido demasiado lejos y se acerca la hora de detenernos a reflexionar");
	string_proc_list_apply_print_trace(nueva_lista, key, true, stdout);

	string_proc_key_destroy(key);
	string_proc_list_destroy(list);
	string_proc_list_destroy(nueva_lista);
}

//TODO:debe implementar
/**
*	probar las funciones saturate_2_odd, unsaturate_2_odd, shift_position_prime, unshift_position_prime
*	sobre el string "hemos ido demasiado lejos y se acerca la hora de detenernos a reflexionar"
*/
void test_odd_prime(){
	printf("Probando operaciones sobre posiciones impares y primas\n============\n");
	//Creo una lista con un nodo con las funciones saturate_2_odd y unsaturate_2_odd, luego las aplico e imprimo los valores
	string_proc_list* list	= string_proc_list_create("nueva lista");
	string_proc_list_add_node(list, &saturate_2_odd, &unsaturate_2_odd, IRREVERSIBLE);
	string_proc_key* key	= string_proc_key_create("hemos ido demasiado lejos y se acerca la hora de detenernos a reflexionar");
	string_proc_list_apply(list, key, true);
	printf("Value: %s\n", key->value);
	string_proc_list_apply(list, key, false);
	printf("Value: %s\n", key->value);

	//Elimino el nodo de la lista y agrego uno nuevo con las funciones shift_position_prime y unshift_position_prime y hago lo mismo que antes
	string_proc_list_remove_node_at(list,0);
	string_proc_list_add_node(list, &shift_position_prime, &unshift_position_prime, REVERSIBLE);
	string_proc_list_apply(list, key, true);
	printf("Value: %s\n", key->value);
	string_proc_list_apply(list, key, false);
	printf("Value: %s\n", key->value);

	string_proc_key_destroy(key);
	string_proc_list_destroy(list);

}

/**
*	Corre los test a se escritos por lxs alumnxs	
*/
void run_tests(){

	//tests principales
	test_create_destroy_list();

	test_create_destroy_node();

	test_create_destroy_key();

	test_print_list();

	test_shift_2();
	
	test_shift_position();

	test_saturate_2();

	test_saturate_position();

	test_combo_reversible();

	test_combo_irreversible();

	//tests utilidades
	test_list_length();
	
	test_list_add_remove_node();

	test_list_invert_order();

	test_list_apply_print_trace();

	test_odd_prime();

}

int main (void){
	run_tests();
	return 0;    
}
