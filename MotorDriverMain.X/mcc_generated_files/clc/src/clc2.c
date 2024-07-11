/**
 * CLC2 Generated Driver File.
 * 
 * @file clc2.c
 * 
 * @ingroup  clc2
 * 
 * @brief This file contains the API implementations for the CLC2 driver.
 *
 * @version CLC2 Driver Version 1.1.0
*/
/*
? [2024] Microchip Technology Inc. and its subsidiaries.

    Subject to your compliance with these terms, you may use Microchip 
    software and any derivatives exclusively with Microchip products. 
    You are responsible for complying with 3rd party license terms  
    applicable to your use of 3rd party software (including open source  
    software) that may accompany Microchip software. SOFTWARE IS ?AS IS.? 
    NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS 
    SOFTWARE, INCLUDING ANY IMPLIED WARRANTIES OF NON-INFRINGEMENT,  
    MERCHANTABILITY, OR FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT 
    WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY 
    KIND WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF 
    MICROCHIP HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE 
    FORESEEABLE. TO THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP?S 
    TOTAL LIABILITY ON ALL CLAIMS RELATED TO THE SOFTWARE WILL NOT 
    EXCEED AMOUNT OF FEES, IF ANY, YOU PAID DIRECTLY TO MICROCHIP FOR 
    THIS SOFTWARE.
*/


#include <xc.h>
#include "../clc2.h"

static void (*CLC2_CLCI_InterruptHandler)(void);
static void CLC2_DefaultCLCI_ISR(void);

void CLC2_Initialize(void) 
{
    
    // LCG1POL not_inverted; LCG2POL not_inverted; LCG3POL inverted; LCG4POL not_inverted; LCPOL not_inverted; 
    CLC2POL = 0x4;
    // LCD1S CLCIN0 (CLCIN0PPS); 
    CLC2SEL0 = 0x0;
    // LCD2S CLCIN1 (CLCIN1PPS); 
    CLC2SEL1 = 0x1;
    // LCD3S CLCIN0 (CLCIN0PPS); 
    CLC2SEL2 = 0x0;
    // LCD4S CLCIN0 (CLCIN0PPS); 
    CLC2SEL3 = 0x0;
    // LCG1D1N disabled; LCG1D1T disabled; LCG1D2N disabled; LCG1D2T enabled; LCG1D3N disabled; LCG1D3T disabled; LCG1D4N disabled; LCG1D4T disabled; 
    CLC2GLS0 = 0x8;
    // LCG2D1N disabled; LCG2D1T enabled; LCG2D2N disabled; LCG2D2T disabled; LCG2D3N disabled; LCG2D3T disabled; LCG2D4N disabled; LCG2D4T disabled; 
    CLC2GLS1 = 0x2;
    // LCG3D1N disabled; LCG3D1T enabled; LCG3D2N disabled; LCG3D2T disabled; LCG3D3N disabled; LCG3D3T disabled; LCG3D4N disabled; LCG3D4T disabled; 
    CLC2GLS2 = 0x2;
    // LCG4D1N disabled; LCG4D1T disabled; LCG4D2N disabled; LCG4D2T disabled; LCG4D3N disabled; LCG4D3T disabled; LCG4D4N disabled; LCG4D4T disabled; 
    CLC2GLS3 = 0x0;
    // LCMODE JK flip-flop with R; LCINTN disabled; LCINTP enabled; LCEN enabled; 
    CLC2CON = 0x96;

    // Clear the CLC interrupt flag
    PIR3bits.CLC2IF = 0;
    //Configure interrupt handlers
    CLC2_CLCI_SetInterruptHandler(CLC2_DefaultCLCI_ISR);
    // Enabling CLC2 interrupt.
    PIE3bits.CLC2IE = 1;
}

void CLC2_Enable(void) 
{
    CLC2CONbits.LC2EN = 1;
}

void CLC2_Disable(void) 
{
    CLC2CONbits.LC2EN = 0;
}

void CLC2_ISR(void)
{   
    // Clear the CLC interrupt flag
    PIR3bits.CLC2IF = 0;

    if (CLC2_CLCI_InterruptHandler != NULL)
    {
        CLC2_CLCI_InterruptHandler();
    }
}

void CLC2_CLCI_SetInterruptHandler(void (* InterruptHandler)(void))
{
    CLC2_CLCI_InterruptHandler = InterruptHandler;
}

static void CLC2_DefaultCLCI_ISR(void)
{
    //Add your interrupt code here or
    //Use CLC2_CLCI_SetInterruptHandler() function to use custom ISR
}

bool CLC2_OutputStatusGet(void) 
{
    return(CLC2CONbits.LC2OUT);
}
/**
 End of File
*/
