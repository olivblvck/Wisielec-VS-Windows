#pragma once
#ifndef KLASY_H
#define KLASY_H

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
#include <fstream>
#include <Windows.h>
#include <iomanip>
#include "kolory.h"
#include "funkcje.h"

#define ALFABET 26
#define LICZBA_SLOW  150
#define ILOSC_PROB 7
#define ILOSC_NICK 150

using namespace std;


//klasa bazowa Wisielec
class Wisielec {
protected:
	char uzyte_litery[ALFABET]; //litery ju� wykorzystane przez gracza
	string baza_slow[LICZBA_SLOW]; //tablica przechowujaca wyrazy do gry z pliku
	string slowo_do_zgadniecia; //wylosowany wyraz z tablicy s�ow do odgadni�cia przez gracza
	int pozostale_proby; //ilo�� pr�b gracza
	string nick_aktualny_gracz; //nick gracza, ktory aktualnie prowadzi rozgrywke
	int pkt_aktualny_gracz; //zdobyte punkty aktualnego gracza
public:
	Wisielec(); //konstruktor
	//resetowanie u�ytych liter - wype�nianie tablicy uzyte_litery[] znakami '\0'
	void zresetujUzyteLitery();
	//funkcja wpisuje zaktualizowane wyniki
	void zapiszWynik();
	//wy�wietlanie aktualnego stanu gry
	void wyswietlGre();
	//sprawdzanie, czy litera zosta�a juz u�yta
	bool czyLiteraUzyta(char litera);
	//zapisywanie litery do tablicy liter juz uzytych
	void zapiszLitereJakoUzyta(char litera);
	//funkcja sprawdza, czy gracz ma jeszcze dost�pne pr�by i czy osi�gni�to koniec gry
	bool czyKoniecGry();
	//funkcja obslugujaca mechanizm  odgadywania litery
	void gra();
	//funkcja wirtualna do obs�ugi trybu gry
	virtual void grajWGre() = 0;
	//funkcja odczytuje wyrazy z pliku i zapisuje je do tablicy baza_slow[]
	void odczytSlowZPliku(const string& plik);
	virtual ~Wisielec(); //destruktor
};


//Klasa GraJednoosobowa - klasa dziedzicz�ca po klasie Wisielec
class GraJednoosobowa : public Wisielec {
public:
	GraJednoosobowa();//konstruktor
	//funkcja do obs�ugi gry w trybie dla jednego gracza
	void grajWGre() override;
	//dekonstruktor
	~GraJednoosobowa();//destruktor
};


//Klasa GraDwuosobowa - klasa dziedzicz�ca po klasie Wisielec
class GraDwuosobowa : public Wisielec {
protected:
	string nick_gracz1; //nick pierwszego gracza
	string nick_gracz2; //nick drugiego gracza
	int pkt_gracz2;
public:
	GraDwuosobowa();//konstruktor
	//funkcja do obs�ugi gry w trybie dla dw�ch graczy
	void grajWGre() override;
	~GraDwuosobowa();//~destruktor
};


//Klasa GraZKomputerem - klasa dziedzicz�ca po klasie Wisielec
class GraZKomputerem : public Wisielec {
protected:
	string nick_gracz; //nick gracza, ktory zmierzy sie z komputerem
	string nick_komputer; //nick komputera
public:
	GraZKomputerem(); //konstruktor
	//funkcja do obs�ugi gry w trybie gry z komputerem
	void grajWGre() override;
	//losowanie litery, kt�ra b�dzie pr�b� komputera w grze
	char getRandomLetter();
	~GraZKomputerem(); //destruktor
};

#endif // KLASY_H