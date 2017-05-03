#include "hash.h"
#include <stdlib.h>
#include <stdbool.h>

typedef enum {BORRADO,VACIO,OCUPADO} estado_t;

typedef campo_hash campo_hash_t;

struct campo_hash{
	char* clave;
	void* dato;
	estado_t* estado;
};

struct hash{
	size_t cantidad;
	size_t tamanio;	
	campo_hash_t* tabla;
	hash_destruir_dato_t destructor;
}hash_t;


unsigned long func_hash(unsigned char *str){
	unsigned long h = 5381;
	int c;
	while (c = *str++)
		h = ((h << 5) + h) + c; /* h * 33 + c */
	return h;
}

void inicialiar_tabla(campo_hash_t *tabla, size_t tam){
	for(int i = 0; i < tam; i++){
		tabla[i]->estado = VACIO;
	}
} 

hash_t *hash_crear(hash_destruir_dato_t destruir_dato){
	hash_t tu_hash;
	tu_hash->tamanio = 31;
	tu_hash->cantidad = 0;
	tu_hash->destructor = destruir_dato;
	tu_hash->tabla = (campo_hash_t*)malloc(sizeof(campo_hash_t)*(tu_hash->tamanio));
	if(!(tu_hash->tabla) return NULL;
	inicialiar_tabla(tu_hash->tabla, tu_hash->tamanio);
}




