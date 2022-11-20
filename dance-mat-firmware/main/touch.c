#include <math.h>
#include "./touch.h"
#include "./logger.h"
#include "driver/touch_sensor.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "./hardware.h"

#define THRESHOLD 10
#define PERIOD 5
#define INIT(a) ESP_ERROR_CHECK(touch_pad_config(a, 0));

static void poll_pads(void *ptr)
{
    int calibrate_flag = 1;
    touch_pads_t *ret_v = (touch_pads_t *) ptr;

    while (1) {
        pthread_mutex_lock(&ret_v->lock);
        touch_pad_read(START_PAD, &ret_v->start_pad);
        if (calibrate_flag) {
            START_T = (*&ret_v->start_pad);
        }
        (ret_v->start_pad) = abs((*&ret_v->start_pad) - START_T) > THRESHOLD;

        touch_pad_read(SELECT_PAD, &ret_v->select_pad);
        if (calibrate_flag) {
            SELECT_T = (*&ret_v->select_pad);
        }
        (ret_v->select_pad) = abs((*&ret_v->select_pad) - SELECT_T) > THRESHOLD;

        touch_pad_read(X_PAD, &ret_v->x_pad);
        if (calibrate_flag) {
            X_T = (*&ret_v->x_pad);
        }
        (ret_v->x_pad) = abs((*&ret_v->x_pad) - X_T) > THRESHOLD;

        touch_pad_read(O_PAD, &ret_v->o_pad);
        if (calibrate_flag) {
            O_T = (*&ret_v->o_pad);
        }
        (ret_v->o_pad) = abs((*&ret_v->o_pad) - O_T) > THRESHOLD;

        touch_pad_read(LEFT_PAD, &ret_v->left_pad);
        if (calibrate_flag) {
            LEFT_T = (*&ret_v->left_pad);
        }
        ret_v->left_pad = abs(ret->left_pad - LEFT_T) > THRESHOLD / 2;//ret_v->left_pad < 100; // cursed

        touch_pad_read(RIGHT_PAD, &ret_v->right_pad);
        if (calibrate_flag) {
            RIGHT_T = (*&ret_v->right_pad);
        }
        lprintf(LOG_WARNING, "\t%d\n", ret_v->right_pad);
        ret_v->right_pad = abs(ret_v->right_pad - RIGHT_T) > THRESHOLD / 2;

        touch_pad_read(UP_PAD, &ret_v->up_pad);
        if (calibrate_flag) {
            UP_T = (*&ret_v->up_pad);
        }
        ret_v->up_pad = ret_v->up_pad == 0;

        touch_pad_read(DOWN_PAD, &ret_v->down_pad);
        if (calibrate_flag) {
            DOWN_T = (*&ret_v->down_pad);
        }
        ret_v->down_pad = abs(ret_v->down_pad - DOWN_T) > THRESHOLD;
        pthread_mutex_unlock(&ret_v->lock);

        calibrate_flag = 0;

        vTaskDelay(PERIOD);
    }
}

void init_pads(touch_pads_t *ptr)
{
    touch_pad_init();
    touch_pad_set_voltage(TOUCH_HVOLT_2V7, TOUCH_LVOLT_0V8, TOUCH_HVOLT_ATTEN_1V);

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
    status |= pads->start_pad ? START_PAD : 0;
    status |= pads->select_pad ? SELECT_PAD : 0;
    status |= pads->up_pad ? UP_PAD : 0;
    status |= pads->down_pad ? DOWN_PAD : 0;
    status |= pads->left_pad ? LEFT_PAD : 0;
    status |= pads->right_pad ? RIGHT_PAD : 0;
    status |= pads->x_pad ? X_PAD : 0;
    status |= pads->o_pad ? O_PAD : 0;
    pthread_mutex_unlock(&pads->lock);

    print_pads(pads);
    return status;
}
