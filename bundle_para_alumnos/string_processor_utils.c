#include <stdbool.h>
#include <stdio.h>
#include "string_processor.h"
#include "string_processor_utils.h"

//TODO: debe implementar
/**
*	Debe devolver el largo de la lista pasada por parámetro
*/
uint32_t string_proc_list_length(string_proc_list* list){ 
	uint32_t largo	= 0;
	string_proc_node* actual = list->first;
	while(actual != NULL){
		largo++;
		actual = actual->next;
	}

	return largo; 
}

//TODO: debe implementar
/**
*	Debe insertar el nodo con los parámetros correspondientes en la posición indicada por index desplazando en una
*	posición hacia adelante los nodos sucesivos en caso de ser necesario, la estructura de la lista debe ser
*	actualizada de forma acorde
*	si index es igual al largo de la lista debe insertarlo al final de la misma
*	si index es mayor al largo de la lista no debe insertar el nodo
*	debe devolver true si el nodo pudo ser insertado en la lista, false en caso contrario
*/
bool string_proc_list_add_node_at(string_proc_list* list, string_proc_func f, string_proc_func g, 
														string_proc_func_type type,	uint32_t index){ 
	if(index > string_proc_list_length(list))return false;

	string_proc_node* nuevo = string_proc_node_create(f,g,type);
	string_proc_node* actual = list->first;
	uint32_t i = 0;
	while(i < index){
		actual = actual->next;
		i++;
	}

	if(index == 0){ 
		nuevo->next = list->first;
		if(list->first != NULL)list->first->previous = nuevo;
		list->first = nuevo;
	}

	if(index == string_proc_list_length(list)){
		nuevo->previous = list->last;
		if(list->last != NULL)list->last->next = nuevo;
		list->last = nuevo;
		return true;
	}


	if(index != 0 && index != string_proc_list_length(list)){
		string_proc_node_destroy(nuevo);
		string_proc_node* ultimo = list->last;
		list->last = actual;
		string_proc_node* next = actual->next;
		string_proc_list_add_node(list, f, g, type);
		list->last->next = next;
		next->next = list->last;
		list->last = ultimo;
	} 	

	return true; 
}

//TODO: debe implementar
/**
*	Debe eliminar el nodo que se encuentra en la posición indicada por index de ser posible
*	la lista debe ser actualizada de forma acorde y debe devolver true si pudo eliminar el nodo o false en caso contrario
*/
bool string_proc_list_remove_node_at(string_proc_list* list, uint32_t index){
	if(index >= string_proc_list_length(list) || string_proc_list_length(list) == 0)return false;

	string_proc_node* actual = list->first;
	uint32_t i = 0;
	while(i < index){
		actual = actual->next;
		i++;
	}

	//Si el nodo a eliminar era el primero, actualizo la lista
	if(index == 0){
		list->first = actual->next;
		if(actual->next != NULL)actual->next->previous = NULL;
	}
	//Si el nodo a eliminar era el ultimo, actualizo la lista
	if(index == string_proc_list_length(list)-1){
		list->last = actual->previous;
		if(actual->previous != NULL)actual->previous->next = NULL;
	}

	string_proc_node_destroy(actual);

	return true; 
}

//TODO: debe implementar
/**
*	Debe devolver una copia de la lista pasada por parámetro copiando los nodos en el orden inverso
*/
string_proc_list* string_proc_list_invert_order(string_proc_list* list){ 
	string_proc_list* nueva_lista = string_proc_list_create(list->name);
	if(string_proc_list_length(list) == 0)return nueva_lista;

	string_proc_node* actual = list->first;
	while(actual != NULL){
		string_proc_list_add_node(nueva_lista, actual->f, actual->g, actual->type);
		actual = actual->next;
	}

	return nueva_lista; 
}

//TODO: debe implementar
/**
*	Hace una llamada sucesiva a los nodos de la lista pasada por parámetro siguiendo la misma lógica
*	que string_proc_list_apply pero comienza imprimiendo una línea 
*	"Encoding key 'valor_de_la_clave' through list nombre_de_la_list\n"
* 	y luego por cada aplicación de una función f o g escribe 
*	"Applying function at [direccion_de_funcion] to get 'valor_de_la_clave'\n"
*/
void string_proc_list_apply_print_trace(string_proc_list* list, string_proc_key* key, bool encode, FILE* file){
	fprintf(file, "Encoding key '%s", key->value);
	fprintf(file, "' through list %s\n", list->name);

	if(encode){
		string_proc_node* actual = list->first;
		while(actual != NULL){
			actual->f(key);
			fprintf(file, "Applying function at [%p", actual->f);
			fprintf(file, "] to get '%s", key->value);
			fprintf(file, "'\n");
			actual = actual->next;
		}
	} else {
		string_proc_node* actual = list->last;
		while(actual != NULL){
			actual->g(key);
			fprintf(file, "Applying function at [%p", actual->g);
			fprintf(file, "] to get '%s", key->value);
			fprintf(file, "'\n");
			actual = actual->previous;
		}
	}

}

//TODO: debe implementar
/**
*	Debe desplazar en dos posiciones hacia adelante el valor de cada caracter de la clave pasada por parámetro
*	si el mismo se encuentra en una posición impar, resolviendo los excesos de representación por saturación
*/
void saturate_2_odd(string_proc_key* key){
	uint32_t i;
	for(i = 0; i < key->length; i++){
		if(i%2 == 1)key->value[i] = saturate_int(((int32_t)key->value[i]) + 2);
	}
}

//TODO: debe implementar
/**
*	Debe desplazar en dos posiciones hacia atrás el valor de cada caracter de la clave pasada por parámetro
*	si el mismo se encuentra en una posición impar, resolviendo los excesos de representación por saturación
*/
void unsaturate_2_odd(string_proc_key* key){
	uint32_t i;
	for(i = 0; i < key->length; i++){
		if(i%2 == 1)key->value[i] = saturate_int(((int32_t)key->value[i]) - 2);
	}
}

bool esPrimo(const uint32_t i){
	uint32_t cantDivisores = 0;
	for(uint32_t j=1; j<=i; j++){
		if(i%j == 0)cantDivisores++;
	}
	return cantDivisores == 2;
}
//TODO: debe implementar
/**
*	Debe desplazar en tantas posiciones como sea la posición hacia adelante del valor de cada caracter de la clave pasada por parámetro
*	si el mismo se encuentra en una posición que sea un número primo, resolviendo los excesos de representación con wrap around
*/
void shift_position_prime(string_proc_key* key){
	uint32_t i;
	for(i = 0; i < key->length; i++){
		if(esPrimo(i))key->value[i] = wrap_around_int(((int32_t)key->value[i]) + i);
	}
}

//TODO: debe implementar
/**
*	Debe desplazar en tantas posiciones como sea la posición hacia atrás del valor de cada caracter de la clave pasada por parámetro
*	si el mismo se encuentra en una posición que sea un número primo, resolviendo los excesos de representación con wrap around
*/
void unshift_position_prime(string_proc_key* key){
	uint32_t i;
	for(i = 0; i < key->length; i++){
		if(esPrimo(i))key->value[i] = wrap_around_int(((int32_t)key->value[i]) - i);
	}
}
