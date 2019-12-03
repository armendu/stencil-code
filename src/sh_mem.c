/**
 * Copyright (C) 2019 Armend Ukehaxhaj. All rights reserved
 * Prishtine, Kosova. armendd.u@hotmail.com
 *
 * @file  sh_mem.c
 *
 * @brief Implements the functionality for the shared memory
 *
 * @author Armend Ukehaxhaj (armendd.u@hotmail.com)
 * @date   $Date: Sun, Jul 21, 2019 23:35$
 */

#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>

#include "sh_mem.h"
#include "f_ser.h"

/***************************************************************************/ /**
 * @brief Initializes the shared memory
 *
 * @param[in] shm_elm_t - the shared memory object
 *
 * @retval -1 - If an error occurred
 * @retval >0 - The id of the shared memory
 ******************************************************************************/
int shm_init(shm_elm_t *shm_ptr)
{
  int shm_fd;

  shm_fd = shm_open(SHM_NAME, O_RDWR | O_CREAT | SHM_PERMISSIONS, 0);

  if (shm_fd == -1)
  {
    perror("shm_init");
    return -1;
  }

  /* configure the size of the shared memory object */
  if (ftruncate(shm_fd, sizeof(shm_elm_t)) == -1)
  {
    perror("shm_init");
    return -1;
  }
  
  /* memory map the shared memory object */
  shm_ptr = mmap(0, sizeof(shm_elm_t), PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);

  if (shm_ptr == MAP_FAILED)
  {
    perror("shm_init");
    return -1;
  }

  strcpy(shm_ptr->msg, "message");
  shm_ptr->len = str_len("message");
  shm_ptr->state = SHM_EMPTY;

  printf("shm_ptr->state: %d\n", shm_ptr->state);

  return 0;
}

/***************************************************************************/ /**
 * @brief Write to the shared memory
 *
 * @param[in] shm_id - the shared memory id
 * @param[in] shm_seg - the shared memory object
 * @param[in,out] text - The text set from the shared memory
 *
 * @retval -1 - If an error occurred
 * @retval 0 - If success
 ******************************************************************************/
int shm_write(shm_elm_t *shm_ptr, const char* message)
{
  int len = 0;
  len = str_len(message);

  strcpy(shm_ptr->msg, message);
  shm_ptr->len = len;
  shm_ptr->state = SHM_FULL;

  printf("Copying %d bytes\n", len);
  return 0;
}

/***************************************************************************/ /**
 * @brief Read from the shared memory
 *
 * @param[in] shm_id - the shared memory id
 * @param[in] shmp - the shared memory object
 * @param[in,out] msg - The text set from the shared memory
 *
 * @retval -1 - If an error occurred
 * @retval 0 - If success
 ******************************************************************************/
int shm_read(shm_elm_t *shm_ptr)
{
  printf("shm_ptr %s\n\n\n\n", shm_ptr->msg);
  return 0;
}

/***************************************************************************/ /**
 * @brief Free the shared memory
 *
 * @param[in] shm_id - the shared memory id
 * @param[in] shm_obj - the shared memory object
 ******************************************************************************/
int shm_free()
{
  if (shm_unlink(SHM_NAME) == -1)
  {
    perror("shm_free");
    return -1;
  }

  return 0;
}