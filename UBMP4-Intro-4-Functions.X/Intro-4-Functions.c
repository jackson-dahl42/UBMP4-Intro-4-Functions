/*==============================================================================
 Project: Intro-4-Functions
 Date:    May 16, 2021
 
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

// TODO Set linker ROM ranges to 'default,-0-7FF' under "Memory model" pull-down.
// TODO Set linker code offset to '800' under "Additional options" pull-down.

#define A1

#ifdef originalProgramAnalysis
// Button constant definitions
const char noButton = 0;
const char UP = 1;
const char DOWN = 2;

// Program variable definitions
unsigned char LED5Brightness = 125;
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

void pwm_LED5(unsigned char pwmValue)
{
    for(unsigned char t = 255; t != 0; t --)
    {
        if(pwmValue == t)
        {
            LED5 = 1;
        }
        __delay_us(20);
    }
    // End the pulse if pwmValue < 255
    if(pwmValue < 255)
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
        
        if(button == UP && LED5Brightness < 255)
        {
            LED5Brightness += 1;
        }

        if(button == DOWN && LED5Brightness > 0)
        {
            LED5Brightness -= 1;
        }

        // PWM LED5 with current brightness
        pwm_LED5(LED5Brightness);
        
        // Activate bootloader if SW1 is pressed.
        if(SW1 == 0)
        {
            RESET();
        }
    }
}
#endif
#ifdef programAnalysis
// Button constant definitions
const char noButton = 0;
const char UP = 1;
const char DOWN = 2;

// Program variable definitions
unsigned char LED5Brightness = 125;
unsigned char button;

// Question 5

unsigned char button_pressed(void);

void pwm_LED5(unsigned char);

int main(void)
{
    OSC_config();               // Configure internal oscillator for 48 MHz
    UBMP4_config();             // Configure on-board UBMP4 I/O devices
	
    while(1)
	{
        // Read up/down buttons and adjust LED5 brightness
        button = button_pressed();
        
        if(button == UP && LED5Brightness < 255)
        {
            LED5Brightness += 1;
        }

        if(button == DOWN && LED5Brightness > 0)
        {
            LED5Brightness -= 1;
        }

        // PWM LED5 with current brightness
        pwm_LED5(LED5Brightness);

        // Activate bootloader if SW1 is pressed.
        if(SW1 == 0)
        {
            RESET();
        }
    }
}

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

void pwm_LED5(unsigned char pwmValue)
{
    for(unsigned char t = 255; t != 0; t --)
    {
        if(pwmValue == t)
        {
            LED5 = 1;
        }
        __delay_us(20);
    }
    // End the pulse if pwmValue < 255
    if(pwmValue < 255)
    {
        LED5 = 0;
    }
}
#endif
#ifdef A1
// Program that decreases and increases brightness with SW4 and SW5, but
// the LED can also be turned on or off with SW2 and SW3
// Button constant definitions
const char noButton = 0;
const char UP = 1;
const char DOWN = 2;

// Program variable definitions
unsigned char LED5Brightness = 125;
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
    else if(SW3 == 0)
    {
        return(3);
    }
    else if(SW2 == 0)
    {
        return(4);
    }
    else 
    {
        return(noButton);
    }
}

void pwm_LED5(unsigned char pwmValue)
{
    for(unsigned char t = 255; t != 0; t --)
    {
        if(pwmValue == t)
        {
            LED5 = 1;
        }
        __delay_us(20);
    }
    // End the pulse if pwmValue < 255
    if(pwmValue < 255)
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
        
        if(button == UP && LED5Brightness < 255)
        {
            LED5Brightness += 1;
        }

        if(button == DOWN && LED5Brightness > 0)
        {
            LED5Brightness -= 1;
        }

        if(button == 3)
        {
            LED5Brightness = 255;
        }

        if(button == 4)
        {
            LED5Brightness = 0;
        }

        // PWM LED5 with current brightness
        pwm_LED5(LED5Brightness);
        
        // Activate bootloader if SW1 is pressed.
        if(SW1 == 0)
        {
            RESET();
        }
    }
}
#endif
#ifdef A2
// Program that uses two functions to give functionality to all 4 buttons.
// One function returns a number 0-4 corresponding to the switch, and the other
// activates a light if given a number 0-4

// Program variable definitions

unsigned char button;

unsigned char button_pressed(void)
{
    if(SW2 == 0)
    {
        return(1);
    }
    else if(SW3 == 0)
    {
        return(2);
    }
    else if(SW4 == 0)
    {
        return(3);
    }
    else if(SW5 == 0)
    {
        return(4);
    }
    else
    {
        return(0);
    }
}

void light(unsigned char button)
{
    if(button == 1)
    {
        LED3 = 1;
    }
    else if(button == 2)
    {
        LED4 = 1;
    }
    else if(button == 3)
    {
        LED5 = 1;
    }
    else if(button == 4)
    {
        LED6 = 1;
    }
    else
    {
        LED3 = 0;
        LED4 = 0;
        LED5 = 0;
        LED6 = 0;
    }
}

int main(void)
{
    OSC_config();               // Configure internal oscillator for 48 MHz
    UBMP4_config();             // Configure on-board UBMP4 I/O devices
	
    while(1)
	{
        button = button_pressed();

        light(button);

        if(SW1 == 0)
        {
            RESET();
        }
    }
}
#endif
#ifdef A3
unsigned char period;

unsigned char button_pressed(void)
{
    if(SW2 == 0)
    {
        return(1);
    }
    else if(SW3 == 0)
    {
        return(2);
    }
    else if(SW4 == 0)
    {
        return(3);
    }
    else if(SW5 == 0)
    {
        return(4);
    }
    else
    {
        return(0);
    }
}

void tone(unsigned char period)
{       
    if(period != 0)
    {
        for(unsigned char cycles = 50; cycles != 0; cycles--)
        {
            BEEPER = !BEEPER;
            for(unsigned int p = period; p != 0; p--);
        }
    }
}

int main(void)
{
    OSC_config();               // Configure internal oscillator for 48 MHz
    UBMP4_config();             // Configure on-board UBMP4 I/O devices
	
    while(1)
	{
        period = button_pressed();

        tone(period);

        if(SW1 == 0)
        {
            RESET();
        }
    }
}
#endif
#ifdef A4
// This program has a function that spilts the digits of a number into sepearate variables.
// So when 123 is inputed into the function then three variables "1", "2", and "3" are made. 
// I confirmed the function worked by using an if statement to check if the individual variables
// were equal to the one in the number. You could confirm by using printf to print the variables
// using a terminal, but I tried to confirm using the UBMP4. The program activity says,"For example, 
// passing the function a value of 142 will result in the hundreds variable containing the
// value 1, the tens variable containing 4, and the ones variable 2. How could you test this 
// function to verify that it works?

unsigned char eight_bit_binary_value = 123;
ones = ' ';
tens = ' ';
hundreds = ' ';

    unsigned char modulo(unsigned char n)
    {
        while(n >= 10)
        {
            n -= 10;
        }

        return(n);
    }

    void function(unsigned char number)
    {
        ones = modulo(number) + '0';
        tens = modulo(number / 10) + '0';
        hundreds = modulo(number / 100) + '0';
    }

int main(void)
{
    OSC_config();               // Configure internal oscillator for 48 MHz
    UBMP4_config();             // Configure on-board UBMP4 I/O devices

    while(1)
	{
        function(eight_bit_binary_value);
        if(ones == '3' && tens == '2' && hundreds == '1')
        {
            LED3 = 1;
        }

        if(SW1 == 0)
        {
            RESET();
        }
    }
}
#endif
// Move the function code to here in Program Analysis, step 5.


/* Program Analysis
 * 
 * 1.   Which function in this program will run first? How do you know?

 The first function that runs in the program is the int main(void) function. This
 is the main function or starting function of the program and all the code is run in here.
 I know because this function contains the while loop, and for the other functions to run
 they need to be in the while loop. Also thinking logically, the other functions depend on 
 int main, but int main doesnt depend on the others.

 * 
 * 2.   What is the purpose of the 'unsigned char' variable type declaration in
 *      the button_pressed() function? Is it used by this function to receive
 *      a variable from, or return a variable to the main code?

 The purpose of the "unsigned char" variable type declaration before the button_pressed() function
 is to basically return a variable to the main code. It declares the function as an unsigned char
 which means the function has to return a value from inside the function. It determines its value from
 the if statements inside the function.

 * 
 * 3.   How does the function call statement 'button = button_pressed();' in the
 *      main code support your answer in 2, above?

It supports my answer because it declares that button is eqaul to the value of button_pressed(), which means
it has a value. Also, because the parameter in the function button_pressed() is empty that means the function 
is not receiving a variable from the code.

 This statement just redifines the function. Now when ever the word "button" that value that was determined
 in the "button_pressed()" function will be used for button in the while loop.
 * 
 * 4.   What is the purpose of the 'unsigned char' variable type declaration in
 *      the pwm_LED5() function? Where does the value of the variable come from?
 *      Where does this value get stored in the function?

 The purpose of the unsigned char in the brackets of the pwm_LED5() function is that it acts as
 a parameter. The value of the PWMValue which is the parameter in the brackets is determined when
 the function is called. The value of the variable comes form the while loop or main code. For
 example if I were to call the function in the program pwm_LED5(5) then the value of the unsigned
 char PWMvalue variable would be 5, and it can be used in the function.
 * 
 * 5.   C language compilers typically read through the entire program in a
 *      single pass, converting C code into machine code. The two functions,
 *      button_pressed() and pwm_LED5(), are located above the main() function
 *      so that their memory locations and variable requirements will be
 *      determined before the rest of the program compiles. When the compiler
 *      interprets the function call statements in the main code, it already
 *      knows where those functions are be in memory and which memory locations
 *      are used by their variables.
 * 
 *      Try moving the button_pressed() and pwm_LED5() functions to below the
 *      closing brace of the main() function, and build the code. What happens?
 * 
 *      The compiler should have reported an error since it did not understand
 *      what the function call was referring to because it had not seen the
 *      function before the function call. We can eliminate this error by adding
 *      a function prototype above the main code. The function prototype is like
 *      the function declaration (the first line of the function), and lets the
 *      compiler know both the function's name and the type of variables that
 *      the function will use. A C language 'linker' program will take care of
 *      sorting out the names and memory locations of all of the functions and
 *      variables in a program following the compilation step.
 * 
An error does occur.

 *      Let's try this out. Leave the functions in their new location, below
 *      the main() function, and add the two function prototypes (shown below)
 *      above main(), in the location where the functions were originally
 *      located:

unsigned char button_pressed(void);

void pwm_LED5(unsigned char);

 *      What is the difference between the function prototype for pwm_LED5()
 *      and the actual pwm_LED5() function declaration statement later in the
 *      code?

 The difference is that pwm_LED5() does not have unsigned char PWMvalue, it is just unsigned char.
 * 
 * 6.   Building the program with the added function prototypes should now work
 *      without generating errors, just as it did in the original program.
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
 *      Open the UBMP4.c file to find the OSC_config() and UBMP4_config()
 *      functions called from the main() function in this program. Are any
 *      values passed between this code and the two setup functions? How do
 *      you know?

When I opened the UBMP4.c file I found the two functions and they are shown below.

void OSC_config(void)
{
    OSCCON = 0xFC;              // Set 16MHz HFINTOSC with 3x PLL enabled
    ACTCON = 0x90;              // Enable active clock tuning from USB clock
    while(!PLLRDY);             // Wait for PLL lock (disable for simulation)
}

void UBMP4_config(void)
{
    OPTION_REG = 0b01010111;    // Enable port pull-ups, TMR0 internal, div-256

    LATA = 0b00000000;          // Clear Port A latches before configuring PORTA
    TRISA = 0b00001111;         // Set RUNLED and Beeper pins as outputs
    ANSELA = 0b00000000;        // Make all Port A pins digital
    WPUA = 0b00001000;          // Enable weak pull-up on SW1 input only

    LATB = 0b00000000;          // Clear Port B latches before configuring PORTB
    TRISB = 0b11110000;         // Enable pushbutton pins as inputs (SW2-SW5)
    ANSELB = 0b00000000;        // Make all Port B pins digital
    WPUB = 0b11110000;          // Enable weak pull-ups on pushbutton inputs

    LATC = 0b00000000;          // Clear Port C latches before configuring PORTC
    TRISC = 0b00001111;         // Set LED pins as outputs, H1-H4 pins as inputs
    ANSELC = 0b00000000;        // Make all Port C pins digital

    // Enable interrupts here, if required.
}

The functions have void as the paramater, and void as a declaration meaning they can't return a value
or recieve a value. They just act almost like a variable, but for a big block of code. When you type 
the function into the main program it places the code from the UBMP4.c functions into your main code
and runs them.

 * 
 * 7.   The 'button' variable is a global variable because it was assigned
 *      at the beginning of the program, outside of any functions. Global
 *      variables are available to all functions. How does the 'button' variable
 *      get assigned a value? In which function does this occur?

 The button variable is assigned its value in a while loop in the the int main function.
 In the int main function there is a while loop. In side the while loop there is a statement
 that declares button = button_pressed(); this statement gives it its value. This occurs in the
 int main function, but the value of button is determined by a seperate function called button_pressed().
 * 
 * 8.   Which variable does the value of LED5Brightness get transferred to in
 *      the pwm_LED5() function? Is this variable global, or local to the LED
 *      function? Could the pwm_LED5 function use the LED5Brightness variable
 *      directly, instead of transferring its value to another variable?

 The variable that the value of LED5Brightness gets transferred to in pwm_LED5() is the variable called
 PWMvalue. PWMvalue is the parameter of the function pwm which is the value that is put in the brackets of
 pwm_LED5(). An number, value, or variable put in the brackets of pwm_LED5() will transfer its value
 to PWMvalue. In short when the statement pwm_LED5(LED5Brightness) then LED5Brightness = PWMvalue inside
 the function.
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
 *      these buttons will over-write the current LED5Brightness value with
 *      either 255 or 0, while still allowing SW4 and SW5 to adjust the
 *      brightness in smaller increments when pressed.
 *
 * 2.   Create a function that will return a number from 1-4 corresponding to
 *      which of the SW2 to SW5 switches is pressed, or return 0 if no switches
 *      are pressed. Then, create a function that will accept a number from 1 to
 *      4 that lights the corresponding LED beside each button.
 * 
 * 3.   Create a sound function that receives a parameter representing a tone's
 *      period. Modify your button function, above, to return a variable that
 *      will be passed to the sound function to make four different tones.
 * 
 * 4.   A function that converts an 8-bit binary value into its decimal
 *      equivalent would be useful for helping us to debug our programs. Create
 *      a function that converts an 8-bit binary number into three decimal
 *      character variables representing the hundreds, tens and ones digits
 *      of the binary number passed to it. For example, passing the function
 *      a value of 142 will result in the hundreds variable containing the
 *      value 1, the tens variable containing 4, and the ones variable 2. How
 *      could you test this function to verify that it works? Try it!
 */
