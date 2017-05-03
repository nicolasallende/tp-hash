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
};
