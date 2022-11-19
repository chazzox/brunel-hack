// Copyright (c) 2020-2022 Cesanta Software Limited
// All rights reserved

#include "mongoose.h"

static time_t s_boot_timestamp = 0;              // Updated by SNTP
static struct mg_connection *s_sntp_conn = NULL; // SNTP connection

// Define a system time alternative
time_t ourtime(time_t *tp)
{
    time_t t = s_boot_timestamp + (time_t)(mg_millis() / 1000);
    if (tp != NULL)
        *tp = t;
    return t;
}

// Send simulated metrics data to the dashboard, for chart rendering
static void timer_metrics_fn(void *param)
{
    send_notification(param, "{%Q:%Q,%Q:[%lu, %d]}", "name", "metrics", "data",
                      (unsigned long)ourtime(NULL),
                      10 + (int)((double)rand() * 10 / RAND_MAX));
}

// SNTP connection event handler. When we get a response from an SNTP server,
// adjust s_boot_timestamp. We'll get a valid time from that point on
static void sfn(struct mg_connection *c, int ev, void *ev_data, void *fn_data)
{
    if (ev == MG_EV_SNTP_TIME)
    {
        uint64_t t = *(uint64_t *)ev_data;
        s_boot_timestamp = (time_t)((t - mg_millis()) / 1000);
        c->is_closing = 1;
    }
    else if (ev == MG_EV_CLOSE)
    {
        s_sntp_conn = NULL;
    }
    (void)fn_data;
}

static void timer_sntp_fn(void *param)
{ // SNTP timer function. Sync up time
    struct mg_mgr *mgr = (struct mg_mgr *)param;
    if (s_sntp_conn == NULL && s_boot_timestamp == 0)
    {
        s_sntp_conn = mg_sntp_connect(mgr, NULL, sfn, NULL);
    }
}

// HTTP request handler function
void device_hooks_fn(struct mg_connection *c, int ev, void *ev_data,
                     void *fn_data)
{
    if (ev == MG_EV_HTTP_MSG)
    {
        struct mg_http_message *hm = (struct mg_http_message *)ev_data;

        if (mg_http_match_uri(hm, "/"))
        {
            mg_http_reply(c, 200, "", "yo\n"); // Testing endpoint
        }
        else
        {
            mg_http_reply(c, 404, "", "Resource not found\n");
        }

        MG_DEBUG(("%lu %.*s %.*s -> %.*s", c->id, (int)hm->method.len,
                  hm->method.ptr, (int)hm->uri.len, hm->uri.ptr, (int)3,
                  &c->send.buf[9]));
    }
}
