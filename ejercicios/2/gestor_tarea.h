#include "tarea.h"

enum {
	GESTOR_TAREA_ATTR_TAREAS = 0,
	GESTOR_TAREA_ATTR_NUM_TAREAS,

	__GESTOR_TAREA_ATTR_MAX
};

#define GESTOR_TAREA_ATTR_MAX (__TAREA_ATTR_MAX -1)
#define xfree(ptr)	free((void *)ptr)

struct gestor_tarea;

struct gestor_tarea *gestor_tarea_alloc(void);
void gestor_tarea_free(struct gestor_tarea *);

bool gestor_tarea_attr_is_set(const struct gestor_tarea *g, uint16_t attr);

void gestor_tarea_attr_unset_tarea(struct gestor_tarea *g, uint32_t pos);

void gestor_tarea_attr_set_tarea(struct gestor_tarea *g, struct tarea *t);

struct tarea *gestor_tarea_attr_get_tarea(struct gestor_tarea *g, uint32_t pos);

int gestor_tarea_snprintf(char *buf, size_t size, struct gestor_tarea *g);
