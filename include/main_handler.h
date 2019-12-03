/**
 * Copyright (C) 2019 Armend Ukehaxhaj. All rights reserved
 * Prishtine, Kosova. armendd.u@hotmail.com
 *
 * @file  main_handler.h
 *
 * @brief Provides functions for the message queue communication
 *
 * @author Armend Ukehaxhaj (armendd.u@hotmail.com)
 * @date   $Date: Sun, Jul 21, 2019 23:36$
 */

#ifndef _MAIN_HANDLER__H
#define _MAIN_HANDLER__H 1

#define SERVER_QUEUE_NAME   "/server_mq"
#define QUEUE_PERMISSIONS   0666
#define MAX_MESSAGES        10
#define MSQ_LEN             30
#define MAX_MSG_SIZE 		256
#define MSG_BUFFER_SIZE 	512

typedef struct _msq_elm
{
    int     p_id;           /* client's process id              */
    int     len;            /* length in bytes of the msg       */
    char    msg[MSQ_LEN];   /* the message, i.e. pipe's name    */
} msq_elm_t;

int start_server(const char *f_name);
int start_client(const char *f_name, const int n_secs);

#endif /* _MAIN_HANDLER__H */
