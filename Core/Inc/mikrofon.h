/*
 * mikrofon.h
 *
 *  Created on: Nov 6, 2026
 *      Author: Zofia Kozłowska
 */

#ifndef INC_MIKROFON_H_
#define INC_MIKROFON_H_

#include "main.h"


HAL_StatusTypeDef Mikrofon_Start(void);
void Mikrofon_Process(void);

extern volatile uint32_t audioLevel;




#endif /* INC_MIKROFON_H_ */
