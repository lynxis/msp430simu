/**
This source shows an example on how to use the testing peripheral in the
simulator.

(C) 2002 cliechti@gmx.net


The tests below are in separate functions to simplyfy reading the
assembler output of GCC and disassembled objects.
the macros come from testing.h, look there for comments about them.

when you write tests, keep in mind that that gcc optimization and
precompiler might optimize code. (e.g. constants are recognized,
unused values are not stored even if the c code would imply it)
use variables to avoid that the precompiler inserts the result
instead of getting real msp430 code etc.
*/

#include <io.h>
#include "testing.h"

char a,b;
int r;
int ix, iy;
unsigned int uix, uiy;
long lx, ly;
unsigned long ulx, uly;

void subt1(void) {    
    SUBTEST("Example Subtest\n");       //Begin with a new test
    //set up test inputs
    a = '0';
    b = 'A';
    //perform the calculation to be tested
    r = (a << 8) | b;
    CHECK("leftshift:\t", r == 0x3041);
}

void booltest(void) {
    static char st = 0;
    SUBTEST("boolean not\n");       //Begin with a new test
    //set up test inputs
    //perform the calculation to be tested
    st = 0;
    st = !st;
    st = !st;
    r = 1;
    CHECK("st == !!st:\t", st == !!st );
    CHECK("st == 0:\t", st == 0 );
    CHECK("r  == 1:\t", r == 1 );
    CHECK("r is true?:\t", r);
    CHECK("!r == 0:\t", !r == 0);
}

void slongmul(void) {
    SUBTEST("signed long multiplication\n");       //Begin with a new test
    lx = -1L; ly = 0x1000L; CHECK("-1*0x1000:\t", (lx*ly) == -0x1000L );
    lx = -10L; ly = 0x1000L; CHECK("-10*0x1000:\t", (lx*ly) == -(10*0x1000L) );
}

void sintdiv(void) {
    SUBTEST("int division\n");       //Begin with a new test
    ix = 10;  iy = -2;  CHECK("pos/neg:\t", (ix/iy) == -5 );
    ix = -10; iy = 2;   CHECK("neg/pos:\t", (ix/iy) == -5 );
    ix = 10;  iy = 2;   CHECK("pos/pos:\t", (ix/iy) == 5 );
    ix = -10; iy = -2;  CHECK("neg/neg:\t", (ix/iy) == 5 );
    
}

void slongdiv(void) {
    SUBTEST("signed long division\n");       //Begin with a new test
    lx = 10L; ly = -2L; CHECK("10/-2:\t\t\t", (lx/ly) == -5 );
    lx = 0x10000000L; ly = -0x100L; CHECK("0x10000000L/-0x100L:\t", (lx/ly) == -0x100000L );

    lx = -10L;ly = 2L;  CHECK("-10/2:\t\t\t", (lx/ly) == -5 );
    lx = -0x10000000L; ly = 0x100L; CHECK("-0x10000000L/0x100L:\t", (lx/ly) == -0x100000L );

    lx = 10L; ly = 2L;  CHECK("10/2:\t\t\t", (lx/ly) == 5 );
    lx = 0x10000000L; ly = 0x100L; CHECK("0x10000000L/0x100L:\t", (lx/ly) == 0x100000L );

    lx = -10L;ly = -2L; CHECK("-10/-2:\t\t\t", (lx/ly) == 5 );
    lx = -0x10000000L; ly = -0x100L; CHECK("-0x10000000L/-0x100L:\t", (lx/ly) == 0x100000L );
}

void ulongdiv(void) {
    SUBTEST("unsigned long division\n");       //Begin with a new test
    ulx = 10L;uly = 2L; CHECK("10/2:\t\t", (ulx/uly) == 5 );
    ulx = 11L;uly = 2L; CHECK("11/2:\t\t", (ulx/uly) == 5 );
    ulx = 1234L;uly = 1234L;CHECK("1234/1234:\t", (ulx/uly) == 1 );
    ulx = 12345L;uly = 12345L;CHECK("12345/12345:\t", (ulx/uly) == 1 );
    ulx = 0L;uly = 99L; CHECK("0/99:\t\t", (ulx/uly) == 0 );
    ulx = 27L;uly = 4L; CHECK("27/4:\t\t", (ulx/uly) == 6 );
}

void ulongshl(void) {
    SUBTEST("unsigned long shift left\n");       //Begin with a new test
    ulx = 1L;
    CHECK("1<<0:\t\t", (ulx<<0) == 1L );
    CHECK("1<<1:\t\t", (ulx<<1) == 2L );
    CHECK("1<<2:\t\t", (ulx<<2) == 4L );
    CHECK("1<<3:\t\t", (ulx<<3) == 8L );
    CHECK("1<<5:\t\t", (ulx<<5) == 32L );
    CHECK("1<<8:\t\t", (ulx<<8) == 256L );
    CHECK("1<<11:\t\t", (ulx<<11) == 2048L );
    CHECK("1<<12:\t\t", (ulx<<12) == 4096L );
    CHECK("1<<15:\t\t", (ulx<<15) == 32768L );
    CHECK("1<<16:\t\t", (ulx<<16) == 65536L );
    CHECK("1<<20:\t\t", (ulx<<20) == 1048576L );
    CHECK("1<<31:\t\t", (ulx<<31) == 2147483648L );
    CHECK("1<<32:\t\t", (ulx<<32) == 0 );
}

void slongshl(void) {
    SUBTEST("signed long shift left\n");       //Begin with a new test
    lx = 1L;
    CHECK("1<<0:\t\t", (lx<<0) == 1L );
    CHECK("1<<1:\t\t", (lx<<1) == 2L );
    CHECK("1<<2:\t\t", (lx<<2) == 4L );
    CHECK("1<<3:\t\t", (lx<<3) == 8L );
    CHECK("1<<5:\t\t", (lx<<5) == 32L );
    CHECK("1<<8:\t\t", (lx<<8) == 256L );
    CHECK("1<<11:\t\t", (lx<<11) == 2048L );
    CHECK("1<<12:\t\t", (lx<<12) == 4096L );
    CHECK("1<<15:\t\t", (lx<<15) == 32768L );
    CHECK("1<<16:\t\t", (lx<<16) == 65536L );
    CHECK("1<<20:\t\t", (lx<<20) == 1048576L );
    CHECK("1<<31:\t\t", (lx<<31) == 2147483648L );
    CHECK("1<<32:\t\t", (lx<<32) == 0 );
}

void usintshl(void) {
    SUBTEST("unsigned int shift left\n");       //Begin with a new test
    uix = 1;
    CHECK("1<<0:\t\t", (uix<<0) == 1 );
    CHECK("1<<1:\t\t", (uix<<1) == 2 );
    CHECK("1<<2:\t\t", (uix<<2) == 4 );
    CHECK("1<<3:\t\t", (uix<<3) == 8 );
    CHECK("1<<5:\t\t", (uix<<5) == 32 );
    CHECK("1<<8:\t\t", (uix<<8) == 256 );
    CHECK("1<<11:\t\t", (uix<<11) == 2048 );
    CHECK("1<<12:\t\t", (uix<<12) == 4096 );
    CHECK("1<<15:\t\t", (uix<<15) == 32768 );
    CHECK("1<<16:\t\t", (uix<<16) == 0 );
}

void sintshl(void) {
    SUBTEST("signed int shift left\n");       //Begin with a new test
    ix = 1;
    CHECK("1<<0:\t\t", (ix<<0) == 1 );
    CHECK("1<<1:\t\t", (ix<<1) == 2 );
    CHECK("1<<2:\t\t", (ix<<2) == 4 );
    CHECK("1<<3:\t\t", (ix<<3) == 8 );
    CHECK("1<<5:\t\t", (ix<<5) == 32 );
    CHECK("1<<8:\t\t", (ix<<8) == 256 );
    CHECK("1<<11:\t\t", (ix<<11) == 2048 );
    CHECK("1<<12:\t\t", (ix<<12) == 4096 );
    CHECK("1<<15:\t\t", (ix<<15) == 1<<15 );    //32768
    CHECK("1<<16:\t\t", (ix<<16) == 0 );
}

void usintshr(void) {
    SUBTEST("unsigned int shift right\n");       //Begin with a new test
    uix = 0x8000;
    CHECK("0x8000>>0:\t", (uix>>0) == 0x8000 );
    CHECK("0x8000>>1:\t", (uix>>1) == 0x4000 );
    CHECK("0x8000>>2:\t", (uix>>2) == 0x2000 );
    CHECK("0x8000>>3:\t", (uix>>3) == 0x1000 );
    CHECK("0x8000>>5:\t", (uix>>5) ==  0x0400);
    CHECK("0x8000>>8:\t", (uix>>8) ==  0x0080);
    CHECK("0x8000>>11:\t", (uix>>11) == 0x0010 );
    CHECK("0x8000>>12:\t", (uix>>12) == 0x0008 );
    CHECK("0x8000>>15:\t", (uix>>15) == 0x0001 );
    CHECK("0x8000>>16:\t", (uix>>16) == 0 );
}

void sintshr(void) {
    SUBTEST("signed int shift right\n");       //Begin with a new test
    ix = 0x8000;
    CHECK("0x8000>>0:\t", (ix>>0) == 0x8000 );
    CHECK("0x8000>>1:\t", (ix>>1) == 0xC000 );
    CHECK("0x8000>>2:\t", (ix>>2) == 0xE000 );
    CHECK("0x8000>>3:\t", (ix>>3) == 0xF000 );
    CHECK("0x8000>>5:\t", (ix>>5) ==  0xFC00);
    CHECK("0x8000>>8:\t", (ix>>8) ==  0xFF80);
    CHECK("0x8000>>11:\t", (ix>>11) == 0xFFF0 );
    CHECK("0x8000>>12:\t", (ix>>12) == 0xFFF8 );
    CHECK("0x8000>>15:\t", (ix>>15) == 0xFFFF );
    CHECK("0x8000>>16:\t", (ix>>16) == 0xFFFF );
}


int main() {
    TEST("Example tests for mspgcc\n");    //all test files MUST start with that one
    
    subt1();
    slongmul();
    sintdiv();
    slongdiv();
    ulongdiv();
    ulongshl();
    slongshl();
    usintshl();
    sintshl();
    usintshr();
    sintshr();

    END_TEST;                 //finish tests. this is important for the simu that it know when it can abort
}

