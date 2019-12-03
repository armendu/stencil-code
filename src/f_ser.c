/**
 * Copyright (C) 2019 Bsc. Armend Ukehaxhaj. All rights reserved
 * Rr. Agim Ramadani pn., Prishtine, Kosovo. armendd.u@hotmail.com
 *
 * @file  f_ser.c
 *
 * @brief Implements functions for serialization
 * 
 * @author (IS) Bsc. Armend Ukehaxhaj (armendd.u@hotmail.com)
 * @date   $Date: 19 May 19, 18:02:55 WEST 2019 $
 */

#include <stdio.h>
#include <malloc.h>
#include <unistd.h>

#include "f_ser.h"

/***************************************************************************//** 
 * @brief Returns the number of characters in a given string
 *
 * @param[in] input string
 *
 * @retval number of characters
 ******************************************************************************/
int str_len (const char *str)
{
  register int count = 0;

  while (*str++ != '\0')
    {
      count++;
    }

  return count;
}

/***************************************************************************//** 
 * @brief Writes an input string into the file 
 *
 * @param[in,out] fp - file pointer
 * @param[in] str - the input string
 *
 * @retval 0  in case an error was occured
 * @retval >0 number of bytes written in the file
 ******************************************************************************/
int str_write (FILE *fp, const char *str)
{
  int status = 0;
  int length = 0; 

  length = str_len (str);

  status = (int) fwrite ((const void *) str, (size_t) 1, 
                         (size_t) length, fp);

  if (status == 0)
  {
    printf ("\nError writing string '%s' to the file", str);
  }

  return status;
}