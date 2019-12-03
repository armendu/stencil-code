/**
 * Copyright (C) 2019 Armend Ukehaxhaj. All rights reserved
 * Prishtine, Kosova. armendd.u@hotmail.com
 *
 * @file  main_handler.c
 *
 * @brief Implements the functionality for communicating with message queues
 *
 * @author Armend Ukehaxhaj (armendd.u@hotmail.com)
 * @date   $Date: Sun21, Jul 21, 2019 23:42$
 */

#ifndef _RECORD_HANDLER__H
#define _RECORD_HANDLER__H 1

#include "sh_mem.h"

int handle_recording(const char *f_name, shm_elm_t *shm_ptr);

#endif /* _RECORD_HANDLER__H */