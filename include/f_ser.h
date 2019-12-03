 /**
 * Copyright (C) 2019 Bsc. Armend Ukehaxhaj. All rights reserved
 * Rr. Agim Ramadani pn., Prishtine, Kosovo. armendd.u@hotmail.com
 *
 * @file  f_ser.h
 *
 * @brief Provides functions for the file serialization
 * 
 * @author (IS) Bsc. Armend Ukehaxhaj (armendd.u@hotmail.com)
 * @date   $Date: 19 May 19, 18:02:25 WEST 2019 $
 */

#ifndef _F_SER_H_
#define _F_SER_H 1_

#include <stdio.h>

#define SER_EOF         -2
#define SER_ALLOC_ERROR -1
#define SER_INT_LEN      4

int str_len   (          /*@null@*/ const char  *str);
int str_write (FILE *fp, /*@null@*/ const char  *str);

#endif /* _F_SER_H */