//#include "hash.h"
#include <stdlib.h>
#include <stdbool.h>

int const MAX = 70;

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


bool hash_guardar(hash_t *hash, const char *clave, void *dato){
	if(hash_pertenece(hash,clave)){
		int i = 0;
		while(hash->tabla[i]->clave != clave){
			i++;
		}
		if(hash->destructor != NULL){
			hash->destructor(hash->tabla[i]->dato);	 //esto se va a repetir hay que hacer una funcion  sobreescribir que se use con los borrados y otros
		}
		hash->tabla[i]->dato = dato;
		return true;
	}
	if(((hash->cantidad / hash->tamanio)*100) >= MAX){
		//aca es lo de redimensionar 
	}
	size_t h = func_hash(clave);
	while(h > hash->tamanio){
		h = h / (hash->tamanio);
	}
	while((hash->tabla[h]->estado != VACIO) && (hash->tabla[h]->estado != BORRADO)){
		h++;
		if(h = hash->tamanio){
			h = 0;
		}
	}
	if(hash->tabla[h]->estado == BORRADO){
		if(hash->destructor != NULL){			
			hash->destructor(hash->tabla[h]->dato);	 //esto se va a repetir hay que hacer una funcion  sobreescribir que se use con los borrados y otros
		}
	}
	hash->tabla[h]->clave = clave;
	hash->tabla[h]->dato = dato;
	hash->cantidad++;
	hash->tabla[h]->estado = OCUPADO;
	return true;
}
			
void *hash_obtener(const hash_t *hash, const char *clave){
	if(!hash_pertenece(hash,clave)) return NULL;
	int i = 0;
	while(hash->tabla[i]->clave != clave){
		i++;
	}
	return hash->tabla[i]->dato;
}
