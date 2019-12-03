/**
 * Copyright (C) 2019 Armend Ukehaxhaj. All rights reserved
 * Prishtine, Kosova. armendd.u@hotmail.com
 *
 * @file  server.c
 *
 * @brief Implements the functionality for the server
 *
 * @author Armend Ukehaxhaj (armendd.u@hotmail.com)
 * @date   $Date: Sun, Jul 21, 2019 23:34$
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/mman.h>

#include "main_handler.h"
#include "opt_proc.h"

int main(int argc, char **argv)
{
  char *f_name = NULL;

  /* Set the mode and retrieve the file name */
  int result = get_server_args(argc, argv, &f_name);

  if (result == ERROR_CODE)
  {
    return -1;
  }

  if(start_server(f_name) == -1)
  {
    printf("An error occurred. Quiting..\n");
    return -1;
  }

  return 0;
}