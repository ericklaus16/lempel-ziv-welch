#include <iostream>

#include "lzw.h"

using namespace std;

int main(){
    list<int> palavraComprimidaAscii = {98, 97, 110, 97, 110, 97};
    list<int> palavraComprimidaLZW = {98, 97, 110, 257, 97};

    compressAscii("banana");
    compressLZW("banana");
    descompressAscii(palavraComprimidaAscii);
    descompressLZW(palavraComprimidaLZW);
    return 0;
}