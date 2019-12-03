/** 
 * Copyright (C) 2003-2019 Dipl.Ing. Dr. techn. Idriz Smaili. All rights reserved
 * Siebenbuergerstrasse 16-26/26/17, A--1220 Wien, Austria. smaili.idriz@gmail.com
 *
 * @file  nm_pipe.h
 *
 * @brief Provides functions for the named pipe functionality
 * 
 * @author (IS) Dr.techn. Dipl.-Ing. Idriz Smaili (smaili.idriz@gmail.com)
 * @date   $Date: Thu, Jun 27, 2019 1:25:09 PM$
 */

#ifndef _NM_PIPE__H
#define _NM_PIPE__H 1

#include <stdio.h>

/* define constants */
#define NMP_MSG_LEN      (int)  512
#define NMP_PERM         0666

/* define the named pipe element structure */
typedef struct _nmp_elm
{
  int   len;
  char  msg [NMP_MSG_LEN];
} nmp_elm_t;

#define NMP_ELM_LEN      (int)(sizeof (nmp_elm_t))

typedef struct _nm_pipe
{
  int       nmp_id;
  nmp_elm_t elm;
} nm_pipe_t;

int  nmp_init  (/*@out@*/ nm_pipe_t *const nmp_obj, const char *nmp_name);
void nmp_free  (/*@out@*/ nm_pipe_t *const nmp_obj);
int  nmp_send  (/*@out@*/ nm_pipe_t *const nmp_obj);
int  nmp_recv  (/*@out@*/ nm_pipe_t *const nmp_obj);

#endif /* _NM_PIPE__H */
