/**
 * Copyright (C) 2019 Armend Ukehaxhaj. All rights reserved
 * Prishtine, Kosova. armendd.u@hotmail.com
 *
 * @file  opt_proc.c
 *
 * @brief Implements the functionality for argument handling
 *
 * @author Armend Ukehaxhaj (armendd.u@hotmail.com)
 * @date   $Date: 21, Jul 21, 2019 23:40$
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include <signal.h>

#include "opt_proc.h"

/***************************************************************************/ /**
 * @brief Returns the synopsis for server
 ******************************************************************************/
void usage_server()
{
  printf ("\nSYNOPSIS\n");
  printf ("\nserver [OPTION] ... \n");
  printf ("\t -f arg, (mandatory) the log file name\n");
}

/***************************************************************************/ /**
 * @brief Returns the synopsis for client
 ******************************************************************************/
void usage_client()
{
  printf ("\nSYNOPSIS\n");
  printf ("\nclient [OPTION] ... \n");
  printf ("\t -f arg,      (mandatory) the file name\n");
  printf ("\t -t arg,      (optional) the number of seconds to wait\n");
}

/***************************************************************************/ /**
 * @brief Gets the arguments for the client process
 *
 * @param[in]     argc    - no. of arguments
 * @param[in]     argv    - argument value
 * @param[in,out] f_name  - the file name
 *
 * @retval -1 - If the f_name was not specified
 * @retval >0 - The seconds given by the user
 * @retval  0 - If seconds given by the user are negative
 ******************************************************************************/
int get_client_args(int argc, char **argv, char** f_name)
{
  int f_set 	= 0;
  int n_secs 	= 0;

  /* Check no. of arguments */
	if(argc < 2)
	{
		printf("Too few arguments provided. \n");
		usage_client();
		return ERROR_CODE;
	}

	int opt;
	while ((opt = getopt(argc, argv, "f:t:h")) != -1)
	{
		switch (opt)
		{
			case 'f':
        f_set = opt;
				*f_name = optarg;
				break;
			case 'h':
				usage_client();
				return ERROR_CODE;
			case 't':
				n_secs = atoi(optarg);
				break;
			default:
				usage_client();
				return ERROR_CODE;
		}
	}
	
	if (f_set == 0)
	{
		printf("The option '-f' is mandatory\n");
		usage_client();
		return ERROR_CODE;
	}

	return (n_secs > 0) ? n_secs : 0;
}

/***************************************************************************/ /**
 * @brief Gets the arguments for the server process
 *
 * @param[in]     argc    - no. of arguments
 * @param[in]     argv    - argument value
 * @param[in,out] f_name  - the file name
 *
 * @retval -1 - If the user didn't provide the f_name
 * @retval  0 - If the f_name was specified
 ******************************************************************************/
int get_server_args(int argc, char **argv, char** f_name)
{
  int f_set = 0;

  /* Check no. of arguments */
	if(argc < 2)
	{
		printf("Too few arguments provided. \n");
		usage_server();
		return ERROR_CODE;
	}

	int opt;
	while ((opt = getopt(argc, argv, "f:h")) != -1)
	{
		switch (opt)
		{
			case 'f':
        f_set = opt;
				*f_name = optarg;
				break;
			case 'h':
			default:
				usage_server();
				return ERROR_CODE;
		}
	}
	
	if (f_set == 0)
	{
		printf("The option '-f' is mandatory\n");
		usage_server();
		return ERROR_CODE;
	}

  return 0;
}