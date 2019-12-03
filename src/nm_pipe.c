/**
 * Copyright (C) 2003-2019 Dipl.Ing. Dr. techn. Idriz Smaili. All rights reserved
 * Siebenbuergerstrasse 16-26/26/17, A--1220 Wien, Austria. smaili.idriz@gmail.com
 *
 * @file  nm_pipe.c
 *
 * @brief Implements the named pipe functionality
 * 
 * @author (IS) Dr.techn. Dipl.-Ing. Idriz Smaili (smaili.idriz@gmail.com)
 * @date   $Date: Thu, Jun 27, 2019 2:07:09 PM$
 */

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>

#include "nm_pipe.h"

/***************************************************************************//** 
 * @brief Public member - initializes a named pipe
 *
 * This functions initializes a named pipe
 *
 * @param[in,out] nmp_obj - a object describing the name pipe including its 
 *                      element
 *
 * @retval -1 : on error
 * @retval  0 : on success
 ******************************************************************************/
int nmp_init  (nm_pipe_t *const nmp_obj, const char *nmp_name)
{
  nmp_obj->nmp_id = -1;
  
  /* create the fifo if it was not already created */
  if (mkfifo (nmp_name, NMP_PERM) == -1)
    {
      if (errno != EEXIST)
        {
          perror   ("Error: failed creating a named pipe -");
          return -1;
        }
    }

  /* open the fifo */
  if ((nmp_obj->nmp_id = open (nmp_name, O_RDWR)) <0)
    {
      perror   ("Error: openning a named pipe failed -");
      return -1;
    }

  return 0;
}

/***************************************************************************//** 
 * @brief Public member - closes a named pipe
 *
 * This functions closes a named pipe
 *
 * @param[in,out] nmp_obj - a object describing the name pipe including its 
 *                      element
 *
 * @retval 
 ******************************************************************************/
void nmp_free (nm_pipe_t *const nmp_obj)
{
  if (nmp_obj->nmp_id != -1)
    {
      (void) close (nmp_obj->nmp_id);
    }
}

/***************************************************************************//** 
 * @brief Public member - sends a message through the named pipe
 *
 * This functions sends a message through the named pipe.
 *
 * @param[in,out] nmp_obj - a object describing the name pipe including its 
 *                      element
 *
 * @param[in]     msg - pointer to the data needs to be written 
 * @param[in]     len - number of bytes needs to be written 
 *
 * @retval -1 : on error
 * @retval number of sent bytes : on success
 ******************************************************************************/
int nmp_send  (nm_pipe_t *const nmp_obj)
{
  register int res = -1;

  res = write (nmp_obj->nmp_id, &nmp_obj->elm, nmp_obj->elm.len + sizeof (int));

  if (res == -1)
    {
      perror ("msq_send:: send message failed");
    }

  printf ("\n nmp_send: len= %d, msg= '%s'", nmp_obj->elm.len,
          &nmp_obj->elm.msg [0]);
  
  return res;
}

/***************************************************************************//** 
 * @brief Public member - receives a message through the message queue
 *
 * This functions receives a message through the message queue.
 *
 * @param[in,out] msq_obj - a object describing the msg queue including its 
 *                      element
 * @retval -1 : on error
 * @retval number of sent bytes : on success
 ******************************************************************************/
int nmp_recv  (nm_pipe_t *const nmp_obj)
{
  int res = -1;
  int len = 0;

  res = read (nmp_obj->nmp_id, &len, sizeof (int));
  
  if (res <0)
    {
      perror ("msq_recv:: receive message failed");
    }

  res = read (nmp_obj->nmp_id, &nmp_obj->elm.msg [0], len);
  if (res <0)
    {
      perror ("msq_recv:: receive message failed");
    }

  nmp_obj->elm.len = len; 
  printf ("\n nmp_recv: len= %d, msg= '%s'", nmp_obj->elm.len,
          &nmp_obj->elm.msg [0]);
  return res;
}
