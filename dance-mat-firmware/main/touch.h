#pragma once
#include "./hardware.h"
#include <pthread.h>

void init_pads();

typedef struct touch_pads_t {
    unsigned short int start_pad, select_pad, x_pad, o_pad, left_pad, right_pad, down_pad, up_pad;
    pthread_mutex_t lock;
} touch_pads_t;

void print_pads(touch_pads_t *pads);
