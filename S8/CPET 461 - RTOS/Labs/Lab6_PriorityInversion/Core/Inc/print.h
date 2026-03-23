/*
 * print.h
 *
 *  Created on: Feb 12, 2026
 *      Author: Jeffrey T
 */

#ifndef INC_PRINT_H_
#define INC_PRINT_H_

#include "cmsis_os.h"

void Print_Init();
void Print_Line(const char *msg, ...);

#endif /* INC_PRINT_H_ */
