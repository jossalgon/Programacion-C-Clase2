#include "gestor_tarea.h"
#include <assert.h>

static int test1(void)
{
	printf("\n### TEST ALLOC ###\n");
	struct gestor_tarea *g1;
	g1 = gestor_tarea_alloc();
	printf("La dirección de g1 después del alloc es %p\n", g1);
	assert(g1 != NULL);

	printf("\n### TEST FREE ###\n");
	gestor_tarea_free(g1);
	printf("La dirección de g1 después del free es %p\n", g1);
	// assert(t == NULL);
	return 0;
}

static int test2(void)
{
	printf("\n### TEST IS SET ###\n");
	struct tarea *t1;
	struct gestor_tarea *g2;
	t1 = tarea_alloc();

	tarea_attr_set_str(t1, TAREA_ATTR_NOMBRE_TAREA, "Limpiador");
	tarea_attr_set_str(t1, TAREA_ATTR_DESC_TAREA,
		"Realiza limpieza profunda de archivos duplicados");
	tarea_attr_set_str(t1, TAREA_ATTR_USUARIO, "Jose");
	tarea_attr_set_u32(t1, TAREA_ATTR_PRIORIDAD, 5);
	tarea_attr_set_u32(t1, TAREA_ATTR_ID, 27);

	g2 = gestor_tarea_alloc();
	gestor_tarea_attr_set_tarea(g2, t1);
	bool b = gestor_tarea_attr_is_set(g2, GESTOR_TAREA_ATTR_TAREAS);
	assert(b == true);
	printf(b ? "tareas está activo\n" : "tareas no está activo\n");

	gestor_tarea_free(g2);
	return 0;
}

static int test3(void)
{
	printf("\n### TEST SET(ORDENADO) + GET ###\n");
	struct tarea *t1, *t2, *t3;
	struct gestor_tarea *g3;

	t1 = tarea_alloc();

	tarea_attr_set_str(t1, TAREA_ATTR_NOMBRE_TAREA, "Limpiador");
	tarea_attr_set_str(t1, TAREA_ATTR_DESC_TAREA,
		"Realiza limpieza profunda de archivos duplicados");
	tarea_attr_set_str(t1, TAREA_ATTR_USUARIO, "Jose");
	tarea_attr_set_u32(t1, TAREA_ATTR_PRIORIDAD, 5);
	tarea_attr_set_u32(t1, TAREA_ATTR_ID, 27);

	t2 = tarea_alloc();

	tarea_attr_set_str(t2, TAREA_ATTR_NOMBRE_TAREA, "Antivirus");
	tarea_attr_set_str(t2, TAREA_ATTR_DESC_TAREA,
		"Escanea el ordenador en busca de programas maliciosos");
	tarea_attr_set_str(t2, TAREA_ATTR_USUARIO, "Juan");
	tarea_attr_set_u32(t2, TAREA_ATTR_PRIORIDAD, 1);
	tarea_attr_set_u32(t2, TAREA_ATTR_ID, 87);

	t3 = tarea_alloc();

	tarea_attr_set_str(t3, TAREA_ATTR_NOMBRE_TAREA, "Cortafuegos");
	tarea_attr_set_str(t3, TAREA_ATTR_DESC_TAREA,
		"Bloquea el acceso no autorizado");
	tarea_attr_set_str(t3, TAREA_ATTR_USUARIO, "Jose");
	tarea_attr_set_u32(t3, TAREA_ATTR_PRIORIDAD, 0);
	tarea_attr_set_u32(t3, TAREA_ATTR_ID, 8);

	g3 = gestor_tarea_alloc();
	gestor_tarea_attr_set_tarea(g3, t2);
	gestor_tarea_attr_set_tarea(g3, t1);
	gestor_tarea_attr_set_tarea(g3, t3);

	assert(gestor_tarea_attr_get_tarea(g3, 0) == t3);
	assert(gestor_tarea_attr_get_tarea(g3, 1) == t2);
	assert(gestor_tarea_attr_get_tarea(g3, 2) == t1);

	printf(((gestor_tarea_attr_get_tarea(g3, 0) == t3) &&
		(gestor_tarea_attr_get_tarea(g3, 1) == t2) &&
		(gestor_tarea_attr_get_tarea(g3, 2) == t1)) ?
	"Las tareas están ordenadas\n" : "Las tareas no están ordenadas\n");

	gestor_tarea_free(g3);
	return 0;
}

static int test4(void)
{
	printf("\n### TEST UNSET(ORDENADO) + SNPRINTF ###\n");
	struct tarea *t1, *t2, *t3;
	struct gestor_tarea *g4;
	char info[4000];

	t1 = tarea_alloc();

	tarea_attr_set_str(t1, TAREA_ATTR_NOMBRE_TAREA, "Limpiador");
	tarea_attr_set_str(t1, TAREA_ATTR_DESC_TAREA,
		"Realiza limpieza profunda de archivos duplicados");
	tarea_attr_set_str(t1, TAREA_ATTR_USUARIO, "Jose");
	tarea_attr_set_u32(t1, TAREA_ATTR_PRIORIDAD, 5);
	tarea_attr_set_u32(t1, TAREA_ATTR_ID, 27);

	t2 = tarea_alloc();

	tarea_attr_set_str(t2, TAREA_ATTR_NOMBRE_TAREA, "Antivirus");
	tarea_attr_set_str(t2, TAREA_ATTR_DESC_TAREA,
		"Escanea el ordenador en busca de programas maliciosos");
	tarea_attr_set_str(t2, TAREA_ATTR_USUARIO, "Juan");
	tarea_attr_set_u32(t2, TAREA_ATTR_PRIORIDAD, 1);
	tarea_attr_set_u32(t2, TAREA_ATTR_ID, 87);

	t3 = tarea_alloc();

	tarea_attr_set_str(t3, TAREA_ATTR_NOMBRE_TAREA, "Cortafuegos");
	tarea_attr_set_str(t3, TAREA_ATTR_DESC_TAREA,
		"Bloquea el acceso no autorizado");
	tarea_attr_set_str(t3, TAREA_ATTR_USUARIO, "Jose");
	tarea_attr_set_u32(t3, TAREA_ATTR_PRIORIDAD, 0);
	tarea_attr_set_u32(t3, TAREA_ATTR_ID, 8);

	g4 = gestor_tarea_alloc();
	gestor_tarea_attr_set_tarea(g4, t2);
	gestor_tarea_attr_set_tarea(g4, t1);
	gestor_tarea_attr_set_tarea(g4, t3);

	gestor_tarea_snprintf(info, sizeof(info), g4);
	printf("ANTES:\n%s", info);

	gestor_tarea_attr_unset_tarea(g4, 1);
	//En la posición 1 estaba t2 "Antivirus"
	assert(gestor_tarea_attr_get_tarea(g4, 1) != t2);

	gestor_tarea_snprintf(info, sizeof(info), g4);
	printf("DESPUÉS:\n%s", info);
	assert(gestor_tarea_attr_get_tarea(g4, 0) == t3);
	assert(gestor_tarea_attr_get_tarea(g4, 1) == t1);

	printf(((gestor_tarea_attr_get_tarea(g4, 0) == t3) &&
		(gestor_tarea_attr_get_tarea(g4, 1) == t1)) ?
	"Las tareas están ordenadas\n" : "Las tareas no están ordenadas\n");


	gestor_tarea_free(g4);
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
