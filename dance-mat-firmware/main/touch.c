#include <math.h>
#include "./touch.h"
#include "./logger.h"
#include "driver/touch_sensor.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "./hardware.h"

#define PERIOD 10
#define INIT(a) ESP_ERROR_CHECK(touch_pad_config(a, 0)); \
  lprintf(LOG_INFO, "Pad %d setup...\n", a);
#define pad_read(a, b, c) touch_pad_read(a, b); if (calibrate_flag - TUNING_AMOUNT) { c = *b; } (*b) = (*b) < c;

static void poll_pads(void *ptr)
{
    int calibrate_flag = 1;
    touch_pads_t *ret_v = (touch_pads_t *) ptr;

    while (1) {
        pthread_mutex_lock(&ret_v->lock);
        pad_read(START_PAD, &ret_v->start_pad, START_T);
        pad_read(SELECT_PAD, &ret_v->select_pad, SELECT_T);
        pad_read(X_PAD, &ret_v->x_pad, X_T);
        pad_read(O_PAD, &ret_v->o_pad, O_T);
        pad_read(LEFT_PAD, &ret_v->left_pad, LEFT_T);
        pad_read(RIGHT_PAD, &ret_v->right_pad, RIGHT_T);
        pad_read(UP_PAD, &ret_v->up_pad, UP_T);
        pad_read(DOWN_PAD, &ret_v->down_pad, DOWN_T);
        pthread_mutex_unlock(&ret_v->lock);
        calibrate_flag = 0;

        vTaskDelay(200 / PERIOD);
    }
}

void init_pads(touch_pads_t *ptr)
{
    touch_pad_init();
    touch_pad_set_voltage(TOUCH_HVOLT_2V7, TOUCH_LVOLT_0V5, TOUCH_HVOLT_ATTEN_1V);

    INIT(START_PAD);
    INIT(SELECT_PAD);
    INIT(X_PAD);
    INIT(O_PAD);
    INIT(LEFT_PAD);
    INIT(RIGHT_PAD);
    INIT(UP_PAD);
    INIT(DOWN_PAD);

    pthread_mutex_t __tmp = PTHREAD_MUTEX_INITIALIZER;
    ptr->lock = __tmp;
    xTaskCreate(&poll_pads, "pads_poll", 4096, ptr, 5, NULL);
}

void print_pads(touch_pads_t *ret)
{
    pthread_mutex_lock(&ret->lock);
    lprintf(LOG_INFO, "Start: %d, Select: %d, X: %d, O: %d, Left: %d, Right: %d, Up: %d, Down: %d\n",
            ret->start_pad,
            ret->select_pad,
            ret->x_pad,
            ret->o_pad,
            ret->left_pad,
            ret->right_pad,
            ret->up_pad,
            ret->down_pad);
    pthread_mutex_unlock(&ret->lock);
}

dance_mat_status_t get_status(touch_pads_t *pads)
{
    dance_mat_status_t status = 0;
    pthread_mutex_lock(&pads->lock);
    status |= START_PAD && pads->start_pad;
    status |= SELECT_PAD && pads->select_pad;
    status |= UP_PAD && pads->up_pad;
    status |= DOWN_PAD && pads->down_pad;
    status |= LEFT_PAD && pads->left_pad;
    status |= RIGHT_PAD && pads->right_pad;
    status |= X_PAD && pads->x_pad;
    status |= O_PAD && pads->o_pad;
    pthread_mutex_unlock(&pads->lock);
    return status;
}
