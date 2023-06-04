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

//funkcja wyswietlaj¹ca ekran pocz¹tkowy
void ekranStartowy();
//funkcja wyswietla menu z dostêpnymi opcjami interakcji
int wyswietlMenu();
//funkcja sprawdza czy znak jest polskim znakiem
bool czyPolskiZnak(char litera);
//funkcja do pobrania litery z kontrol¹
char pobierzLitere();
//funkcja po pobierania cyfry z kontrol¹ poprawnoœci wprowadzonych danych
int pobierzCyfre();
//funkcja do pobierania wyrazu z kontrol¹ 
string pobierzSlowo();
//funkcja drukuje w konsoli instrukcje pliku txt
void wyswietlInstrukcje();
//funkcja drukuje w konsoli wyniki z pliku txt
void wyswietlWyniki();
//zwraca aktualn¹ datê
string sprawdzGodzine();


#endif