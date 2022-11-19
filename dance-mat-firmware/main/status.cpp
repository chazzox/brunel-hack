#include <string.h>
#include <stdio.h>
#include "./status.h"
#include "./hardware.h"
#include "./logger.h"

#define LCD_LEN 16
#define LCD_H 2
#define LCD_H_RES              80
#define LCD_V_RES              14

void init_lcd()
{
}

void display_state(wifi_state_t w_state, dance_mat_status_t dm_state)
{
    char top_line[LCD_LEN + 1];
    snprintf(top_line, sizeof(top_line), "%s %c", w_state.name, w_state.hosting ? '/' : 'x');

    char bottom_line[LCD_LEN + 1];
    memset(bottom_line, 0, sizeof(bottom_line));
    for (int i = 0; i < 7; i++) {
        bottom_line[i] = dm_state & (1 << i) ? DANCE_MAT_STATUS_STR[i] : ' ';
    }
}
