#pragma once
#include "./hardware.h"
#include <pthread.h>

void init_pads();

typedef struct touch_pads_t {
    unsigned short int start_pad, select_pad, x_pad, o_pad, left_pad, right_pad, down_pad, up_pad;
    pthread_mutex_t lock;
} touch_pads_t;

void print_pads(touch_pads_t *pads);

typedef enum dance_mat_status_t {
    START_DOWN = 1 << 0,
    SELECT_DOWN = 1 << 1,
    X_DOWN = 1 << 2,
    O_DOWN = 1 << 3,
    UP_DOWN = 1 << 4,
    LEFT_DOWN = 1 << 5,
    RIGHT_DOWN = 1 << 6,
    DOWN_DOWN = 1 << 7,
} dance_mat_status_t;

dance_mat_status_t get_status(touch_pads_t *pads);
