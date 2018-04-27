
/*
 * Copyright (C) YoungJoo Kim (vozlt)
 */


#ifndef _NGX_HTTP_STREAM_STS_NODE_H_INCLUDED_
#define _NGX_HTTP_STREAM_STS_NODE_H_INCLUDED_

#define NGX_HTTP_STREAM_SERVER_TRAFFIC_STATUS_DEFAULT_QUEUE_LEN  64


typedef struct {
    ngx_msec_t                                         time;
    ngx_msec_int_t                                     msec;
} ngx_http_stream_server_traffic_status_node_time_t;


typedef struct {
    ngx_http_stream_server_traffic_status_node_time_t  times[NGX_HTTP_STREAM_SERVER_TRAFFIC_STATUS_DEFAULT_QUEUE_LEN];
    ngx_int_t                                          front;
    ngx_int_t                                          rear;
    ngx_int_t                                          len;
} ngx_http_stream_server_traffic_status_node_time_queue_t;


typedef struct {
    /* unsigned type:5 */
    unsigned                                                 type;

    ngx_msec_t                                               connect_time;
    ngx_http_stream_server_traffic_status_node_time_queue_t  connect_times;

    ngx_msec_t                                               first_byte_time;
    ngx_http_stream_server_traffic_status_node_time_queue_t  first_byte_times;

    ngx_msec_t                                               session_time;
    ngx_http_stream_server_traffic_status_node_time_queue_t  session_times;
} ngx_http_stream_server_traffic_status_node_upstream_t;


typedef struct {
    u_char                                                   color;
    ngx_atomic_t                                             stat_connect_counter;
    ngx_atomic_t                                             stat_active_counter;
    ngx_atomic_t                                             stat_in_bytes;
    ngx_atomic_t                                             stat_out_bytes;
    ngx_atomic_t                                             stat_1xx_counter;
    ngx_atomic_t                                             stat_2xx_counter;
    ngx_atomic_t                                             stat_3xx_counter;
    ngx_atomic_t                                             stat_4xx_counter;
    ngx_atomic_t                                             stat_5xx_counter;

    ngx_msec_t                                               stat_session_time;
    ngx_http_stream_server_traffic_status_node_time_queue_t  stat_session_times;

    /* deals with the overflow of variables */
    ngx_atomic_t                                             stat_connect_counter_oc;
    ngx_atomic_t                                             stat_in_bytes_oc;
    ngx_atomic_t                                             stat_out_bytes_oc;
    ngx_atomic_t                                             stat_1xx_counter_oc;
    ngx_atomic_t                                             stat_2xx_counter_oc;
    ngx_atomic_t                                             stat_3xx_counter_oc;
    ngx_atomic_t                                             stat_4xx_counter_oc;
    ngx_atomic_t                                             stat_5xx_counter_oc;

    ngx_http_stream_server_traffic_status_node_upstream_t    stat_upstream;

    ngx_uint_t                                               port;
    int                                                      protocol;
    u_short                                                  len;
    u_char                                                   data[1];
} ngx_http_stream_server_traffic_status_node_t;


ngx_int_t ngx_http_stream_server_traffic_status_node_generate_key(ngx_pool_t *pool,
    ngx_str_t *buf, ngx_str_t *dst, unsigned type);
ngx_int_t ngx_http_stream_server_traffic_status_node_position_key(ngx_str_t *buf,
    size_t pos);

ngx_rbtree_node_t *ngx_http_stream_server_traffic_status_node_lookup(
    ngx_rbtree_t *rbtree, ngx_str_t *key, uint32_t hash);
void ngx_http_stream_server_traffic_status_node_zero(
    ngx_http_stream_server_traffic_status_node_t *stsn);
void ngx_http_stream_server_traffic_status_find_name(ngx_http_request_t *r,
    ngx_str_t *buf);
ngx_rbtree_node_t *ngx_http_stream_server_traffic_status_find_node(ngx_http_request_t *r,
    ngx_str_t *key, unsigned type, uint32_t key_hash);


#endif /* _NGX_HTTP_STREAM_STS_NODE_H_INCLUDED_ */

/* vi:set ft=c ts=4 sw=4 et fdm=marker: */
