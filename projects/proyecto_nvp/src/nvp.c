/* Copyright 2018, Gassmann Dustin
 * All rights reserved.
 *
 */

/** \brief Blinking Bare Metal example source file
 **
 ** This is a mini example of the CIAA Firmware.
 **
 **/

/** \addtogroup CIAA_Firmware CIAA Firmware
 ** @{ */

/** \addtogroup Examples CIAA Firmware Examples
 ** @{ */
/** \addtogroup Baremetal Bare Metal example source file
 ** @{ */

/*
 * Initials     Name
 * ---------------------------
 * DG           Dustin Gassmann
 */	

/*
 * modification history (new versions first)
 * -----------------------------------------------------------
 * yyyymmdd v0.0.1 initials initial version
 */

/*==================[inclusions]=============================================*/
#include "nvp.h"       /* <= own header */
#include "led.h"



int main(void)
{ 



   /* perform the needed initialization here */
	boardConfig();

	Init_Leds();



    //Variables
   
	    
	while(1){
		
		Led_Toggle( RED_LED );
	}

	return 0;


}

/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/

