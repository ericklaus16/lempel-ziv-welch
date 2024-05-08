#include <iostream>

#include "lzw.h"

using namespace std;

int main(){
    compressAscii("banana");
    compressLZW("banana");
    return 0;
}