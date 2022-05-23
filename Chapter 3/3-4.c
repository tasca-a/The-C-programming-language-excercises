/*
    In a two's complement number representation, our version of i toa does not handle the largest negative number, that is, 
    the value of n equal to -(2wordsize-l). Explain why not.

    Because when we make n positive (n = -n) in a two's complement number representation we invert all the bits, and to obtain the
    correct value we then must add 1. In the case of the largest negative number, the act of adding 1 overflows n, so we turn back to
    having the largest negative number again.
*/