#include <iostream>
#include <list>

using namespace std;

int findInDictionary(list<string> dictionary, string value){
    for(list<string>::iterator it = dictionary.begin(); it != dictionary.end(); it++){
        if(*it == value){
            return distance(dictionary.begin(), it);
        }
    }
    return -1;
}

int findIntegerDictionaryEquivalent(list<string> dictionary, string value){
    int counter = 256;
    for(list<string>::iterator it = dictionary.begin(); it != dictionary.end(); it++){
        if(*it == value){
            return counter;
        }
        counter++;
    }
    return -1;
}

string findStringEquivalentByIntegerInDictionary(list <string> dictionary, int index){
    int counter = 256;
    for(list<string>::iterator it = dictionary.begin(); it != dictionary.end(); it++){
        if(counter == index){
            return *it;
        }
        counter++;
    }
    return "";
}

void compressAscii(string compressable){
    cout << "Comprimindo " << compressable << " para ASCII: ";
    for(int i = 0; i < compressable.length(); i++){
        cout << (int) compressable[i] << " ";
    }
    cout << endl;
}

void compressLZW(string compressable){
    cout << "Comprimindo " << compressable << " para LZW: ";
    int dicionarioCount = 256;
    list<string> saida;
    list<string> dictionary;
    list<char> letters;
    list<int> saidaInteira;
    for(int i = 0; i < compressable.length(); i++){
        letters.push_back(compressable[i]);
    }

    for(list<char>::iterator it = letters.begin(); it != letters.end(); it++){
        char atual = *it;

        if(next(it) != letters.end()){
            char proximo = *next(it);
            string dupla = string(1, atual) + proximo;

            if(findInDictionary(dictionary, dupla) == -1){
                saida.push_back(string(1, atual));
                saidaInteira.push_back((int) atual);
                dictionary.push_back(dupla);
                dicionarioCount++;
                // cout << "Adicionando " << dupla << " ao dicionario" << endl;
            } else {
                advance(it, 1);
                proximo = *next(it);
                string tripla = dupla + proximo;
                // cout << "Procurando por tripla " <<  tripla << endl;
                if(findInDictionary(dictionary, tripla) == -1){
                    saida.push_back(dupla);
                    dictionary.push_back(tripla);
                    saidaInteira.push_back(findIntegerDictionaryEquivalent(dictionary, dupla));
                    // cout << "Adicionando " << tripla << " ao dicionario" << endl;
                }    
            }
        } else {
            saida.push_back(string(1, atual));
            saidaInteira.push_back((int) atual);
        }
    }

    for(list<int>::iterator it = saidaInteira.begin(); it != saidaInteira.end(); it++){
        cout << *it << " ";
    }
    cout << endl;
}

void descompressAscii(list<int> compressed){
    cout << "Descomprimindo ASCII para: ";
    for(list<int>::iterator it = compressed.begin(); it != compressed.end(); it++){
        cout << (char) *it;
    }
    cout << endl;
}

void descompressLZW(list<int> compressed){
    cout << "Descomprimindo para LZW: " << endl;
    int dicionarioCount = 256;
    list<string> saida;
    list<string> dictionary;

    string compressedString;

    for(list<int>::iterator it = compressed.begin(); it != compressed.end(); it++){
        int atual = *it;

        if(atual > 255){
            string novaSaida = findStringEquivalentByIntegerInDictionary(dictionary, atual);
            // cout << novaSaida << endl;
            saida.push_back(novaSaida);
            int primeiroValor = *(compressed.begin());
            dictionary.push_back(novaSaida + " " + to_string(primeiroValor));
            continue;
        }

        if(next(it) != compressed.end()){
            int proximo = *next(it);
            string convertedValue = to_string(atual) + " " + to_string(proximo);
            saida.push_back(to_string(atual));
            dictionary.push_back(convertedValue);
            // cout << "Adicionei a dupla " << convertedValue << " no dicionario" << endl;
        } else {
            saida.push_back(to_string(atual));
        }
    }

    string stringFinal = "";
    
    for(list<string>::iterator it = saida.begin(); it != saida.end(); it++){
        stringFinal += *it + " ";
    }
    
    string delimiter = " ";
    size_t pos = 0;
    string token;
    
    while ((pos = stringFinal.find(delimiter)) != string::npos) {
        token = stringFinal.substr(0, pos);
        int ascii_value = stoi(token);
        char character = static_cast<char>(ascii_value);
        cout << ascii_value << " = " << character << endl;
        stringFinal.erase(0, pos + delimiter.length());
    }
    
    if(stringFinal != ""){
        int ascii_value = stoi(stringFinal);
        char character = static_cast<char>(ascii_value);
        cout << ascii_value << " = " << character << endl;
    }
}