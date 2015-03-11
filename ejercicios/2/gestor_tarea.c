#include "gestor_tarea.h"
#include <string.h>

struct gestor_tarea {
	struct tarea	*tareas[10];
	uint32_t	num_tareas;

	uint32_t 	flags;
};

int binsearch(struct tarea *t[], int size, struct tarea *key)
{
	int low = 0, high = size - 1;
	int prioridad = tarea_attr_get_u32(key, TAREA_ATTR_PRIORIDAD);

	if (prioridad > tarea_attr_get_u32(t[high], TAREA_ATTR_PRIORIDAD))
		return size;
	while (high > low) {
		int mid = (low + high) / 2;
		if (tarea_attr_get_u32(t[mid], TAREA_ATTR_PRIORIDAD) > prioridad)
			high = mid;
		else low = mid + 1;
	}
	return low;
}

struct gestor_tarea *gestor_tarea_alloc(void)
{
	return (struct gestor_tarea *)malloc(sizeof(struct gestor_tarea));
}

void gestor_tarea_free(struct gestor_tarea *g)
{
	int i;

	for (i = 0; i < g->num_tareas; i++)
		tarea_free(g->tareas[i]);

	xfree(g);
}

bool gestor_tarea_attr_is_set(const struct gestor_tarea *g, uint16_t attr)
{
	return g->flags & (1 << attr);
}

void gestor_tarea_attr_unset_tarea(struct gestor_tarea *g, uint32_t pos)
{
	if (pos < 0 || pos >= g->num_tareas)
		return;

	tarea_free(g->tareas[pos]);
	int i;
	for (i = pos; i < g->num_tareas; i++) {
		g->tareas[i] = g->tareas[i+1];
	}

	g->num_tareas--;
	if (g->num_tareas == 0) {
		g->flags &= ~(1 << GESTOR_TAREA_ATTR_TAREAS);
		g->flags &= ~(1 << GESTOR_TAREA_ATTR_NUM_TAREAS);
	}
}

void gestor_tarea_attr_set_tarea(struct gestor_tarea *g, struct tarea *t)
{
	if (g->num_tareas > 10)
		printf("No se admiten más tareas\n");
	else {
		int i, pos;
		if(g->num_tareas > 0)
			pos = binsearch(g->tareas, g->num_tareas, t);
		else
			pos = 0;

		for (i = g->num_tareas - 1; i >= pos; i--) {
			g->tareas[i+1] = g->tareas[i];
		}

		g->tareas[pos] = t;
		g->num_tareas++;

		g->flags |= (1 << GESTOR_TAREA_ATTR_TAREAS);
		g->flags |= (1 << GESTOR_TAREA_ATTR_NUM_TAREAS);
	}
}

struct tarea *gestor_tarea_attr_get_tarea(struct gestor_tarea *g, uint32_t pos)
{
	return g->tareas[pos];
}

int gestor_tarea_snprintf(char *buf, size_t size, struct gestor_tarea *g)
{
	int i, ret = 0;

	for (i = 0; i < g->num_tareas; i++) {
		ret += tarea_snprintf(buf + ret, size - ret, g->tareas[i]);
	}
	return ret;
}
