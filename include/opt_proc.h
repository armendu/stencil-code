/**
 * Copyright (C) 2019 Armend Ukehaxhaj. All rights reserved
 * Prishtine, Kosova. armendd.u@hotmail.com
 *
 * @file  opt_proc.h
 *
 * @brief Provides functions for arguments handling
 *
 * @author Armend Ukehaxhaj (armendd.u@hotmail.com)
 * @date   $Date: 21, Jul 21, 2019 23:40$
 */

#ifndef _OPT_PROC__H
#define _OPT_PROC__H 1

#define ERROR_CODE  -1

int   get_client_args (int argc, char **argv, char** f_name);
int   get_server_args (int argc, char **argv, char** f_name);
void  usage_server    ();
void  usage_server    ();

#endif /* _OPT_PROC__H */
