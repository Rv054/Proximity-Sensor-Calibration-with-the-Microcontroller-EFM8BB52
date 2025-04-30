// Includes
//-----------------------------------------------------------------------------
#include <SI_EFM8BB52_Register_Enums.h>
#include <InitDevice.h>
#include "VL53L1X.h"

idata unsigned char I2C0_BUF_OUT[8];
idata unsigned char I2C0_BUF_IN[8];

void UART_send(char ch);
void UART_send_str(char* str);
void print_hex_byte(unsigned char byte);

//-----------------------------------------------------------------------------
// Delay function
void delay_ms(unsigned int ms){
  volatile unsigned int i, j;
  for(i=0; i<ms; i++)
    for(j=0; j<1000; j++);
}

// UART function to print something in terminal
void UART_send(char ch){
    SBUF0 = ch;
    while (!SCON0_TI);  // Wait for transmission complete
    SCON0_TI = 0;       // Clear flag
}

// UART function to print a string
void UART_send_str(char* str) {
    while (*str) {
        UART_send(*str++);
    }
}

void print_hex_byte(unsigned char byte)
{
    char hex_chars[] = "0123456789ABCDEF";

    UART_send('0');
    UART_send('x');
    UART_send(hex_chars[(byte >> 4) & 0x0F]);  // High nibble
    UART_send(hex_chars[byte & 0x0F]);         // Low nibble
    UART_send('\r');
    UART_send('\n');
}
//-----------------------------------------------------------------------------

bit I2C0_transfer(unsigned int address, unsigned int *write_buf, unsigned int *read_buf, unsigned int write_len, unsigned int read_len)
{
    unsigned int i;
    unsigned int timeout;

    // ---------- Write phase ----------
    if (write_len > 0)
    {
        SMB0CN0_STA = 1;               // Generate START
        timeout = 10000;
        while (!SMB0CN0_SI && timeout--);           // Wait for SI
        if (!timeout) {
            UART_send_str("START timeout\r\n");
            return 0;
        }
        SMB0CN0_SI = 0;

        SMB0DAT = address & ~0x01;     // Send address with write bit
        timeout = 10000;
        while (!SMB0CN0_SI && timeout--);           // Wait for ACK
        if (!timeout) {
            UART_send_str("ADDR (write) NACK\r\n");
            SMB0CN0_STO = 1;
            SMB0CN0_SI = 0;
            return 0;
        }
        SMB0CN0_SI = 0;

        for (i = 0; i < write_len; i++)
        {
            SMB0DAT = write_buf[i];    // Send data
            timeout = 10000;
            while (!SMB0CN0_SI && timeout--);       // Wait for ACK
            if (!timeout) {
                UART_send_str("DATA (write) timeout\r\n");
                SMB0CN0_STO = 1;
                SMB0CN0_SI = 0;
                return 0;
            }
            SMB0CN0_SI = 0;
        }
    }

    // ---------- Read phase ----------
    if (read_len > 0)
    {
        SMB0CN0_STA = 1;               // Repeated START
        timeout = 10000;
        while (!SMB0CN0_SI && timeout--);           // Wait for SI
        if (!timeout) {
            UART_send_str("RESTART timeout\r\n");
            return 0;
        }
        SMB0CN0_SI = 0;

        SMB0DAT = address | 0x01;      // Send address with read bit
        timeout = 10000;
        while (!SMB0CN0_SI && timeout--);           // Wait for ACK
        if (!timeout) {
            UART_send_str("ADDR (read) NACK\r\n");
            SMB0CN0_STO = 1;
            SMB0CN0_SI = 0;
            return 0;
        }
        SMB0CN0_SI = 0;

        for (i = 0; i < read_len; i++)
        {
            // If last byte, do NOT acknowledge
            if (i == read_len - 1)
                SMB0CN0_ACK = 0;
            else
                SMB0CN0_ACK = 1;

            timeout = 10000;
            while (!SMB0CN0_SI && timeout--);       // Wait for data byte
            if (!timeout) {
                UART_send_str("DATA (read) timeout\r\n");
                SMB0CN0_STO = 1;
                SMB0CN0_SI = 0;
                return 0;
            }
            read_buf[i] = SMB0DAT;     // Read data
            SMB0CN0_SI = 0;
        }
    }

    SMB0CN0_STO = 1;                   // Generate STOP
    SMB0CN0_SI = 0;

    return 1;  // Success
}

//-----------------------------------------------------------------------------
// Pin Definitions
//-----------------------------------------------------------------------------
unsigned int dist;

//-----------------------------------------------------------------------------
// SiLabs_Startup() Routine
// ----------------------------------------------------------------------------
// This function is called immediately after reset, before the initialization
// code is run in SILABS_STARTUP.A51 (which runs before main() ). This is a
// useful place to disable the watchdog timer, which is enable by default
// and may trigger before main() in some instances.
//-----------------------------------------------------------------------------
void SiLabs_Startup (void)
{
  // Disable the watchdog here
}
 
//-----------------------------------------------------------------------------
// Main Routine
//-----------------------------------------------------------------------------
void main (void)
{
   enter_DefaultMode_from_RESET();

   VL53L1X_Init();
   VL53L1X_StartRanging();
   while (1) {
        dist = VL53L1X_ReadDistance();

        UART_send_str("Distance = ");
        print_hex_byte((dist >> 8) & 0xFF);  // High byte
        print_hex_byte(dist & 0xFF);          // Low byte
        UART_send_str("\r\n");

        delay_ms(1000);
      }
}
