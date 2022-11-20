#pragma once
#include "./touch.h"

extern touch_pads_t *vile;
void device_hooks_fn(struct mg_connection *c, int ev, void *ev_data, void *fn_data);
