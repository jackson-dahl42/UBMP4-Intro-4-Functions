/*==============================================================================
 Project: Intro-4-Functions
 Date:    April 15, 2021
 
 This program demonstrates the use of functions, and variable passing between
 the main and function code.
 
 Additional program analysis and programming activities examine function code
 location, function prototypes, and reinforce the concepts of global and local
 variables.
==============================================================================*/

#include    "xc.h"              // Microchip XC8 compiler include file
#include    "stdint.h"          // Include integer definitions
#include    "stdbool.h"         // Include Boolean (true/false) definitions

#include    "UBMP4.h"           // Include UBMP4 constants and functions

// TODO Set linker ROM ranges to 'default,-0-FFF' under "Memory model" pull-down.
// TODO Set linker code offset to '1000' under "Additional options" pull-down.

// Button constant definitions
const char noButton = 0;
const char UP = 1;
const char DOWN = 2;

// Program variable definitions
unsigned char tOnLED5 = 127;
unsigned char button;

unsigned char button_pressed(void)
{
    if(SW4 == 0)
    {
        return(UP);
    }
    else if(SW5 == 0)
    {
        return(DOWN);
    }
    else
    {
        return(noButton);
    }
}

void pwm_LED5(unsigned char tOn)
{
    for(unsigned char t = 255; t != 0; t --)
    {
        if(tOn == t)
        {
            LED5 = 1;
        }
        __delay_us(20);
    }
    if(tOn < 255)
    {
        LED5 = 0;
    }
}

int main(void)
{
    OSC_config();               // Configure internal oscillator for 48 MHz
    UBMP4_config();             // Configure on-board UBMP4 I/O devices
	
    while(1)
	{
        // Read up/down buttons and adjust LED5 brightness
        button = button_pressed();
        
        if(button == UP && tOnLED5 < 255)
        {
            tOnLED5 += 1;
        }

        if(button == DOWN && tOnLED5 > 0)
        {
            tOnLED5 -= 1;
        }

        pwm_LED5(tOnLED5);
        
        // Activate bootloader when SW1 is pressed.
        if(SW1 == 0)
        {
            asm("reset");
        }
    }
}

// Move the function code to here in Program Analysis, step 5.

/* Program Analysis
 * 
 * 1.   Which function in this program will run first? How do you know?
 * 
 * 2.   What is the purpose of the 'unsigned char' variable type declaration in
 *      the button_pressed() function? Is it used by this function to receive
 *      a variable from, or return a variable to the main code?
 * 
 * 3.   How does the function call statement 'button = button_pressed();' in the
 *      main code support your answer in 2, above?
 * 
 * 4.   What is the purpose of the 'unsigned char' variable type declaration in
 *      the pwm_LED5() function? Where does the value of the variable come from?
 *      Where is this value stored in the function?
 * 
 * 5.   C language compilers typically read through the entire program in a
 *      single pass, converting the C code into machine code. The two functions,
 *      button_pressed() and pwm_LED5(), are located above the main() function
 *      so that their memory locations and variable requirements will be
 *      determined before the rest of the program compiles. When the compiler
 *      gets down to the function call statements in the main code, it already
 *      knows where those functions are be in memory, and which memory locations
 *      are used by their variables.
 * 
 *      Try moving the button_pressed() and pwm_LED5() functions to below the
 *      closing brace of the main() function, and build the code. What happens?
 * 
 *      The compiler should have reported an error, because it didn't understand
 *      what the function call was referring to, because it hasn't come across
 *      the function yet. We can eliminate this error by adding a function
 *      prototype above the main code to let the compiler know about both the
 *      functions names and variables that will be needed. A C language 'linker'
 *      program will take care of sorting out the names and locations of the
 *      functions and variables following compilation.
 * 
 *      Let's try this out. Leave the functions in their new location, below
 *      the main()  function, and add these function prototypes above main(),
 *      where the functions originally were located:

unsigned char button_pressed(void);
void pwm_LED5(unsigned char);

 *      What is the difference between the function prototype for pwm_LED5()
 *      and its actual function declaration, below?
 * 
 * 6.   Building the program now, with the included function prototypes, should
 *      work without generating errors, just as it did in the original program.
 * 
 *      In C, functions may be located above the code that calls them, below
 *      their function calls if a function prototype is supplied, or even in 
 *      completely separate files known as function libraries.
 * 
 *      Function libraries are typically joined to your project's main '.c' file
 *      using an 'include' statement to a '.h' header file containing both
 *      variable definitions and the function prototypes for an associated C
 *      file which contains the actual function code.
 * 
 *      The '#include "UBMP4.h"' statement near the top of this program is an
 *      example of a statement that adds external functions to our program. The
 *      'UBMP4.h' file contains function prototypes for functions located in
 *      the 'UBMP4.c' file, along with various symbolic constants used by both
 *      our program and the code in the UBMP4.c functions.
 * 
 *      Open the UBMP4.c file to find the setup_oscillator() and setup_ports()
 *      functions called from the main() function in this program. Are any
 *      values passed between this code and the two setup functions? How do
 *      you know?
 * 
 * 7.   The 'button' variable is a global variable because it was assigned
 *      at the beginning of the program, outside of any functions. Global
 *      variables are available to all functions. How does the 'button' variable
 *      get assigned a value? In which function does this occur?
 * 
 * 8.   Which variable does the value of tOnLED5 get transferred to in the 
 *      pwm_LED5() function? Is this variable global, or local to the LED
 *      function? Could the pwm_LED5 function use the tOnLED5 variable directly?
  * 
 * Programming Activities
 * 
 * 1.   It might be useful to have a button that instantly turns LED D5 fully
 *      on or off instead of waiting for it to brighten and dim while the UP
 *      and DOWN buttons are held to change the PWM duty cycle. But, PWM dimming
 *      dimming capability is still a useful feature that should be retained.
 * 
 *      Modify the button_pressed() and main() functions to use SW3 as an
 *      instant on button, and SW2 as an instant off button. Pressing either of
 *      these buttons will over-write the current tOnLED5 value with either 255
 *      or 0, and still allow SW4 and SW5 to adjust the brightness when pressed.
 *
 * 2.   Create a function to return the numbers 1-5 corresponding to which of
 *      the SW1 to SW5 switches are pressed, and return 0 if no switches are
 *      pressed. Then, create a function to accept a number from 1 to 5 and 
 *      light the corresponding LED beside each button.
 * 
 * 3.   Create a sound function that takes a parameter representing the tone's
 *      period or frequency. Modify your button function, above to return a
 *      variable that can be passed to the sound function to make each tone.
 * 
 * 4.   Create a function that converts an 8-bit binary number into three
 *      decimal character variables corresponding to the hundreds, tens and 
 *      ones digits represented by the binary number passed to it. For example,
 *      passing the function a value of 142 will result in the hundreds variable
 *      containing the value 1, the tens variable 4, and the ones variable 2.
 */
