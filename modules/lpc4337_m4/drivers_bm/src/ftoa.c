/* Copyright 2016, Eduardo Filomena - Juan Manuel Reta
 * efilomena@bioingenieria.edu.ar      jmreta@bioingenieria.edu.ar
 * Facultad de Ingeniería
 * Universidad Nacional of Entre Ríos
 * Argentina
 *
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its
 *    contributors may be used to endorse or promote products derived from this
 *    software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 */

/** \Función ftoa: 
 **
 ** Función ftoa: convierte un entero a una cadena
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
 * 20160807  v0.1 versión inicial
 */
 
/*==================[inclusions]=============================================*/
#include "ftoa.h"

/*==================[macros and definitions]=================================*/

/*==================[internal data declaration]==============================*/

/*==================[internal functions declaration]=========================*/

/*==================[internal data definition]===============================*/

/*==================[external data definition]===============================*/

/*==================[internal functions definition]==========================*/
/* A utility function to reverse a string  */


/*==================[external functions definition]==========================*/
/** \Funci�n ftoa: convierte un entero a una cadena */

// reverses a string 'str' of length 'len'
char* reverse(char *str, uint8_t len)
{
    uint8_t i=0, j=len-1, temp;
    while (i<j)
    {
        temp = str[i];
        str[i] = str[j];
        str[j] = temp;
        i++; j--;
    }

    return str;
}
 
 // Converts a given integer x to string str[].  d is the number
 // of digits required in output. If d is more than the number
 // of digits in x, then 0s are added at the beginning.
uint8_t intToStr(uint8_t x, char str[], uint8_t d)
{
    uint8_t i = 0;
    while (x)
    {
        str[i++] = (x%10) + '0';
        x = x/10;
    }
 
    // If number of digits required is more, then
    // add 0s at the beginning
    while (i < d)
        str[i++] = '0';
 
    reverse(str, i);
    str[i] = '\0';
    return i;
}

// Converts a floating point number to string.
char* ftoa(float n, char *result, uint8_t afterpoint)
{
    // Extract integer part
    uint8_t ipart = (uint8_t)n;
 
    // Extract floating part
    float fpart = n - (float)ipart;
 
    // convert integer part to string
    uint8_t i = intToStr(ipart, result, 0);
 
    // check for display option after point
    if (afterpoint != 0)
    {
        result[i] = '.';  // add dot
 
        // Get the value of fraction part upto given no.
        // of points after dot. The third parameter is needed
        // to handle cases like 233.007
        fpart = fpart * pow(10, afterpoint);
 
        intToStr((uint8_t)fpart, result + i + 1, afterpoint);
    }

    return result;
}
// sacado de: https://www.geeksforgeeks.org/convert-floating-point-number-string/





/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/