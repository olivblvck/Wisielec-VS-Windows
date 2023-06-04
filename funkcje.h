#pragma once
#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include <iostream>
#include <string>
#include <fstream>
#include <cctype>
#include <algorithm>
#include <Windows.h>
using namespace std;

//funkcja wyswietlaj�ca ekran pocz�tkowy
void ekranStartowy();
//funkcja wyswietla menu z dost�pnymi opcjami interakcji
int wyswietlMenu();
//funkcja sprawdza czy znak jest polskim znakiem
bool czyPolskiZnak(char litera);
//funkcja do pobrania litery z kontrol�
char pobierzLitere();
//funkcja po pobierania cyfry z kontrol� poprawno�ci wprowadzonych danych
int pobierzCyfre();
//funkcja do pobierania wyrazu z kontrol� 
string pobierzSlowo();
//funkcja drukuje w konsoli instrukcje pliku txt
void wyswietlInstrukcje();
//funkcja drukuje w konsoli wyniki z pliku txt
void wyswietlWyniki();
//zwraca aktualn� dat�
string sprawdzGodzine();


#endif