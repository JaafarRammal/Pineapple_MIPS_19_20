#include <iostream>

// load halfword signed
int main(){
    int foo[5] = {-1234567, -2345678, -3456789, 9999999,888888}; 
    return (int16_t) foo[3] ;
}