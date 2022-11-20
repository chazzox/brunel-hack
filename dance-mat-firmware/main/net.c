// Copyright (c) 2022 Leo Durrant
// Under the MIT License

#include "mongoose.h"

// HTTP request handler function
void device_hooks_fn(struct mg_connection *c, int ev, void *ev_data,
                     void *fn_data)
{
    if (ev == MG_EV_CONNECT)
    {
        c->fn_data = 0L;
    }
    else if (ev == MG_EV_HTTP_MSG)
    {
        struct mg_http_message *hm = (struct mg_http_message *)ev_data;

        if (mg_http_match_uri(hm, "/"))
        {
            mg_http_reply(c, 200, NULL, "yo\n"); // Testing endpoint
        }
        else if (mg_http_match_uri(hm, "/dance"))
        {
            // Upgrade to websocket. From now on, a connection is a full-duplex
            // Websocket connection, which will receive MG_EV_WS_MSG events.
            mg_ws_upgrade(c, hm, NULL);
            c->fn_data = 1L;
        }
        else
        {
            mg_http_reply(c, 404, NULL, "Resource not found\n");
        }

        MG_INFO(("%lu %.*s %.*s -> %.*s", c->id, (int)hm->method.len,
                 hm->method.ptr, (int)hm->uri.len, hm->uri.ptr, (int)3,
                 &c->send.buf[9]));
    }
    else if (ev == MG_EV_WS_MSG)
    {
        // Got websocket frame. Received data is wm->data. Echo it back!
        struct mg_ws_message *wm = (struct mg_ws_message *)ev_data;
        mg_ws_send(c, wm->data.ptr, wm->data.len, WEBSOCKET_OP_TEXT);
    }
    // else if (ev == MG_EV_POLL && c->fn_data == 1L)
    // {
    //     // blast data to the client
    //     char *message[128];

    //     // HOW INPUT WORKS
    //     // up value: (1) - Up, (0) - Neutral, (-1) - Down
    //     // right value: (1) - Right, (0) - Neutral, (-1) - Left
    //     // X, O, Start, Select value: (1) - Pressed, (0) - Neutral
    //     // TODO: Send actual data
    //     snprintf(message,
    //              sizeof(message),
    //              "{\"up\": %d, \"right\": %d, \"X\": %d, \"O\": %d, \"start\": %d, \"select\": %d}",
    //              0, 0, 0, 0, 0, 0);
    //     mg_ws_send(c, message, sizeof(message), WEBSOCKET_OP_TEXT);
    // }
    else if (ev == MG_EV_CLOSE)
    {
        // Connection closed. Remove it from the list.
        MG_DEBUG(("%lu Connection closed", c->id));
    }
}