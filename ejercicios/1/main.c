#include "tarea.h"
#include <assert.h>

/***********************************************************\
* *
* NO SE HA REALIZADO LA LIBERACIÓN COMPLETA DE LOS STRUCTS
* USAR BAJO SU PROPIA RESPONSABILIDAD
* *
\***********************************************************/

static int test1(void)
{
	printf("\n### TEST ALLOC ###\n");
	struct tarea *t1;
	t1 = tarea_alloc();
	printf("La dirección de t1 después del alloc es %p\n", t1);
	assert(t1 != NULL);

	printf("\n### TEST FREE ###\n");
	tarea_free(t1);
	printf("La dirección de t1 después del free es %p\n", t1);
	// assert(t == NULL);
	return 0;
}

static int test2(void)
{
	printf("\n### TEST IS SET ###\n");
	struct tarea *t2;
	t2 = tarea_alloc();

	tarea_attr_set_str(t2, TAREA_ATTR_NOMBRE_TAREA, "Cortafuegos");
	bool b1 = tarea_attr_is_set(t2, TAREA_ATTR_NOMBRE_TAREA);
	assert(b1 == true);
	printf(b1 ? "nombre_tarea está activo\n" : "nombre_tarea no está activo\n");

	bool b2 = tarea_attr_is_set(t2, TAREA_ATTR_DESC_TAREA);
	assert(b2 == false);
	printf(b2 ? "desc_tarea está activo\n" : "desc_tarea no está activo\n");

	bool b3 = tarea_attr_is_set(t2, TAREA_ATTR_ID);
	assert(b3 == false);
	printf(b3 ? "id está activo\n" : "id no está activo\n");

	tarea_attr_set_str(t2, TAREA_ATTR_USUARIO, "Jose");
	bool b4 = tarea_attr_is_set(t2, TAREA_ATTR_USUARIO);
	assert(b4 == true);
	printf(b4 ? "usuario está activo\n" : "usuario no está activo\n");

	bool b5 = tarea_attr_is_set(t2, TAREA_ATTR_PRIORIDAD);
	assert(b5 == false);
	printf(b5 ? "prioridad está activo\n" : "prioridad no está activo\n");

	// tarea_free(t2);
	return 0;
}

static int test3(void)
{
	printf("\n### TEST SET + GET ###\n");
	struct tarea *t3;
	t3 = tarea_alloc();

	tarea_attr_set_str(t3, TAREA_ATTR_NOMBRE_TAREA, "Cortafuegos");
	assert(strcmp(tarea_attr_get_str(t3, TAREA_ATTR_NOMBRE_TAREA),
					"Cortafuegos") == 0);
	printf("El nombre de la tarea es: %s\n",
		tarea_attr_get_str(t3, TAREA_ATTR_NOMBRE_TAREA));

	tarea_attr_set_str(t3, TAREA_ATTR_DESC_TAREA,
		"Bloquea el acceso no autorizado");
	assert(strcmp(tarea_attr_get_str(t3, TAREA_ATTR_DESC_TAREA),
				"Bloquea el acceso no autorizado") == 0);
	printf("La desc. de la tarea es: %s\n",
		tarea_attr_get_str(t3, TAREA_ATTR_DESC_TAREA));

	tarea_attr_set_str(t3, TAREA_ATTR_USUARIO, "Jose");
	assert(strcmp(tarea_attr_get_str(t3, TAREA_ATTR_USUARIO),
				"Jose") == 0);
	printf("El usuario de la tarea es: %s\n",
		tarea_attr_get_str(t3, TAREA_ATTR_USUARIO));

	tarea_attr_set_u32(t3, TAREA_ATTR_PRIORIDAD, 0);
	assert(tarea_attr_get_u32(t3, TAREA_ATTR_PRIORIDAD) == 0);
	printf("La prioridad de la tarea es: %d\n",
		tarea_attr_get_u32(t3, TAREA_ATTR_PRIORIDAD));

	tarea_attr_set_u32(t3, TAREA_ATTR_ID, 8);
	assert(tarea_attr_get_u32(t3, TAREA_ATTR_ID) == 8);
	printf("El id de la tarea es: %d\n",
		tarea_attr_get_u32(t3, TAREA_ATTR_ID));

	// tarea_free(t3);
	return 0;
}

static int test4(void)
{
	printf("\n### TEST UNSET + SNPRINTF ###\n");
	struct tarea *t4;
	char info[250];

	t4 = tarea_alloc();

	tarea_attr_set_str(t4, TAREA_ATTR_NOMBRE_TAREA, "Cortafuegos");
	tarea_attr_set_str(t4, TAREA_ATTR_DESC_TAREA,
		"Bloquea el acceso no autorizado");
	tarea_attr_set_str(t4, TAREA_ATTR_USUARIO, "Jose");
	tarea_attr_set_u32(t4, TAREA_ATTR_PRIORIDAD, 0);
	tarea_attr_set_u32(t4, TAREA_ATTR_ID, 8);

	tarea_snprintf(info, sizeof(info), t4);
	printf("ANTES:\n%s", info);

	tarea_attr_unset(t4, TAREA_ATTR_DESC_TAREA);
	assert(tarea_attr_get_str(t4, TAREA_ATTR_DESC_TAREA) == NULL);

	tarea_snprintf(info, sizeof(info), t4);
	printf("DESPUÉS:\n%s", info);


	tarea_free(t4);
	return 0;
}

int main(void)
{
	test1();
	test2();
	test3();
	test4();

	return 0;
}
