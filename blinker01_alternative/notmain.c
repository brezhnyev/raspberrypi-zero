
//-------------------------------------------------------------------------
//-------------------------------------------------------------------------

// In this example the GPIO 16 is used to blink (you will need extra LED to test it)

extern void PUT32 ( unsigned int, unsigned int );
extern unsigned int GET32 ( unsigned int );
extern void dummy ( unsigned int );

#define GPFSEL3 0x2020000C
#define GPFSEL4 0x20200004
#define GPSET1  0x2020001C // would be probably better to call this one CLR
#define GPCLR1  0x20200028 // and this one SET (see below comments)

// see VII. DIE SPEZIELLE HARDWARE
// https://uol.de/f/2/dept/informatik/ag/svs/download/reader/reader-seminar-ws2013.pdf

// Translation to english:

// To use these Pins you only need the proper addresses, that start at
// ”0x20200000“. Each address is made up from 4 Bytes, each pin occupies 3 bits. These
// Bits specify, what function the pin will have. Thereby the value ”000“ stands for Input and
// "001“ for output. The 30th and 31st bits are reserved. So the address ”0x20200000“ is for Pins 0-9 and 
// "0x20200004“ is for Pins 10-19. Up to the address ”0x20200014“ for Pins 50-53. ...
//
// 30 and 31 are reserved, then follow tripples for each of the pins (ex. 0-9):
// |..|...|...|...|...|...|...|...|...|...|...|   pins 0-9   starting at 0x20200000
// |..|...|...|...|...|...|...|...|...|...|...|   pins 10-19 starting at 0x20200004
// |..|...|...|...|...|...|...|...|...|...|...|   pins 20-29 starting at 0x20200008
// |..|...|...|...|...|...|...|...|...|...|...|   pins 30-29 starting at 0x2020000C
// |..|...|...|...|...|...|...|...|...|...|...|   pins 40-49 starting at 0x20200010
// |..|...|...|...|...|...|...|...|...|...|...|   pins 50-59 starting at 0x20200014
//
// If the pin ist set as OUT, it does not send any signal jet.
// Sending signal happens first when the address ”0x20200028“ for Pins 0 - 31 bzw.
// othwewise ”0x2020002C“ fur Pins 32 - 53 for each bit is set to 1 ...
// To disable it the addresses ”0x2020001C“ otherwise. ”0x20200020“ are used...

//-------------------------------------------------------------------------
int notmain ( void )
{
    unsigned int ra;

    // Set the 16th GPIO to OUT:
    ra=GET32(GPFSEL4);
    ra&=~(7<<18); // first cleaning the 3 bits
    ra|=(1<<18);  // then setting 1 to denote OUT
    PUT32(GPFSEL4,ra);
    int * p;

    while(1)
    {
        // also here is another way tested to set the value without asm:
        p = (int*)(GPSET1); *p = (1<<(16));
        for(ra=0;ra<0x100000;ra++) dummy(ra);
        p = (int*)(GPCLR1); *p = (1<<(16));
        for(ra=0;ra<0x100000;ra++) dummy(ra);
    }

    return(0);
}
//-------------------------------------------------------------------------
//-------------------------------------------------------------------------


//-------------------------------------------------------------------------
//
// Copyright (c) 2015 David Welch dwelch@dwelch.com
//
// Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
//
//-------------------------------------------------------------------------
