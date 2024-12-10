/*****************************************************************************
* File Name        : main.c
*
* Description      : This source file contains the main routine for non-secure
*                    application in the CM33 CPU
*
* Related Document : See README.md
*
*******************************************************************************
* Copyright 2024, Cypress Semiconductor Corporation (an Infineon company) or
* an affiliate of Cypress Semiconductor Corporation.  All rights reserved.
*
* This software, including source code, documentation and related
* materials ("Software") is owned by Cypress Semiconductor Corporation
* or one of its affiliates ("Cypress") and is protected by and subject to
* worldwide patent protection (United States and foreign),
* United States copyright laws and international treaty provisions.
* Therefore, you may use this Software only as provided in the license
* agreement accompanying the software package from which you
* obtained this Software ("EULA").
* If no EULA applies, Cypress hereby grants you a personal, non-exclusive,
* non-transferable license to copy, modify, and compile the Software
* source code solely for use in connection with Cypress's
* integrated circuit products.  Any reproduction, modification, translation,
* compilation, or representation of this Software except as specified
* above is prohibited without the express written permission of Cypress.
*
* Disclaimer: THIS SOFTWARE IS PROVIDED AS-IS, WITH NO WARRANTY OF ANY KIND,
* EXPRESS OR IMPLIED, INCLUDING, BUT NOT LIMITED TO, NONINFRINGEMENT, IMPLIED
* WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. Cypress
* reserves the right to make changes to the Software without notice. Cypress
* does not assume any liability arising out of the application or use of the
* Software or any product or circuit described in the Software. Cypress does
* not authorize its products for use in any products where a malfunction or
* failure of the Cypress product may reasonably be expected to result in
* significant property damage, injury or death ("High Risk Product"). By
* including Cypress's product in a High Risk Product, the manufacturer
* of such system or application assumes all risk of such use and in doing
* so agrees to indemnify Cypress against all liability.
*******************************************************************************/


/******************************************************************************
 * Header Files
 *****************************************************************************/

#include "cybsp.h"
#include "cy_pdl.h"


/******************************************************************************
 * Macros
 *****************************************************************************/

/* LED blink period in miliseconds */
#define BLINKY_LED_DELAY_MSEC 500U

/******************************************************************************
 * Global Variables
 *****************************************************************************/


/******************************************************************************
 * Function Prototypes
 *****************************************************************************/


/******************************************************************************
 * Function Definations
 *****************************************************************************/

/**
 * @brief Main function of M33 Non-secure project
 *
 * This is the non-secure main function for M33 CPU. It toggles a user LED 
 * periodically.
 *
 * @return Should not return
 *
 */
int main(void)
{
    cy_rslt_t result;

    cy_stc_gpio_pin_config_t pinConfig = {
            .outVal =       1UL,                           /* Output = Low; Active low */
            .driveMode =    CY_GPIO_DM_STRONG_IN_OFF,      /* Strong Drive, input buffer off */
            .hsiom =        P8_5_GPIO,                     /* Software controlled pin */
            .intMask =      0UL,                           /* Disable port interrupt for this pin */
            .vtrip =        CY_GPIO_VTRIP_CMOS,            /* CMOS voltage trip */
            .slewRate =     CY_GPIO_SLEW_FAST,             /* Fast slew rate */
            .driveSel =     CY_GPIO_DRIVE_1_2              /* Half drive strength */
    };

    /* Initialize the device and board peripherals */
    result = cybsp_init();

    /* Board init failed. Stop program execution */
    if (result != CY_RSLT_SUCCESS)
    {
        CY_ASSERT(0);
    }

    /* Enable global interrupts */
    __enable_irq();

    /* Initialize pin P0.3 */
    if(CY_GPIO_SUCCESS != Cy_GPIO_Pin_Init(P8_5_PORT, P8_5_NUM, &pinConfig))
    {
         CY_ASSERT(0);
    }

    for (;;)
    {
         Cy_GPIO_Inv(P8_5_PORT, P8_5_NUM);
         Cy_SysLib_Delay(BLINKY_LED_DELAY_MSEC);
    }
}

/* [] END OF FILE */
