#ifndef FTOA_H
#define FTOA_H
/** \FunciÃ³n ftoa: 
 **
 ** Función ftoa: convierte un float a una cadena
 **
 **/

/*
 * Initials     Name
 * ---------------------------
 *	EF			Eduardo Filomena
 *  JMR         Juan Manuel Reta
 */

/*
 * modification history (new versions first)
 * -----------------------------------------------------------
 * 20160807  v0.1 versiÃ³n inicial
 *
 */
/*==================[inclusions]=============================================*/
#include "stdint.h"
#include <math.h>

/*==================[macros and definitions]=================================*/

/*==================[internal data declaration]==============================*/

/*==================[internal functions declaration]=========================*/

/*==================[internal data definition]===============================*/

/*==================[external data definition]===============================*/

/*==================[internal functions definition]==========================*/

/*==================[external functions definition]==========================*/
/** \FunciÃ³n ftoa: convierte un entero a una cadena */
char* reverse(char *str, uint8_t len);

uint8_t intToStr(uint8_t x, char str[], uint8_t d);

char* ftoa(float n, char *result, uint8_t afterpoint);

/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/
#endif /* #ifndef ftoa_H */