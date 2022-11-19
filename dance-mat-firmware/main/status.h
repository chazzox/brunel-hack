#pragma once

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

#define DANCE_MAT_STATUS_STR "()xo^<>v"

typedef struct wifi_state_t {
    char *name;
    int hosting;
} wifi_state_t;

extern "C" {
void init_lcd();
void display_state(wifi_state_t w_state, dance_mat_status_t dm_state);
};
