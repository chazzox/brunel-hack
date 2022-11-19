// Copyright (c) 2022 Leo Durrant
// Under the MIT License

#include "mongoose.h"

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
