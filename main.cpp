#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <fstream>
#include <Windows.h>
#include <iomanip>
#include "kolory.h"
#include "funkcje.h"
#include "klasy.h"


using namespace std;


int main() {
	setlocale(LC_ALL, "Polish");
	srand(time(NULL));
	string aktualna_data; //zmienna przechowujaca aktualn¹ datê
	//otwarcie pliku do zapisu dzia³añ
	FILE* log = fopen("log.txt", "a+");
	if (log == NULL) {
		cout << "\n\nBlad otwarcia pliku \"log.txt\".\nKoniec programu.";
		exit(0);
	}
	aktualna_data = sprawdzGodzine();
	fprintf(log, "%sRozpoczecie pracy programu.\n", aktualna_data.c_str());

	ekranStartowy(); //wypisanie ekranu startowego
	int wybrana_opcja = 1; //wybrana opcja interakcji dla Menu
	//pêta wyboru opcji interakcji w menu
	do {
		Wisielec* nowa_gra;
		wybrana_opcja = wyswietlMenu();
		//1 - instrukcja
		if (wybrana_opcja == 1) {
			aktualna_data = sprawdzGodzine();
			fprintf(log, "%sWyswietlenie instrukcji gry.\n", aktualna_data.c_str());
			system("cls");
			cout <<blekitny<<"\n\t\tInstrukcje i zasady gry "<<zolty<<"\"Wisielec\"\n\n"<< bialy;
			wyswietlInstrukcje();
			cout << zielony<< "\n\n\tPowodzenia! :)"<<domyslny;
			cout << "\n\nWciœnij Enter, by kontynuowaæ...";
			//czyszczenie bufora
			cin.clear();
			cin.ignore(99999, '\n');
			continue;
		}
		//2 - tryb jednoosobowy
		else if (wybrana_opcja == 2) {
			int czy_zagrac_ponownie = 1; // 1, jesli tak
			//wpis do log.txt
			aktualna_data = sprawdzGodzine();
			fprintf(log, "%sRozpoczecie gry w trybie jednoosobowym.\n", aktualna_data.c_str());
			//pêtla gry 
			while (czy_zagrac_ponownie == 1) {
				system("cls");
				nowa_gra = new GraJednoosobowa();
				nowa_gra->grajWGre();
				cout << bialy << "\n\n\tCzy chcesz zagraæ ponownie?\n" << domyslny;
				cout << "\tWprowadŸ " << zolty << "1" << domyslny << ", jeœli tak lub inny dowolny klawisz, by wróciæ do menu.\n";
				cin >> czy_zagrac_ponownie;
				//czyszczenie bufora
				cin.clear();
				cin.ignore(99999, '\n');
			}
			//wpis do log.txt
			aktualna_data = sprawdzGodzine();
			fprintf(log, "%sZakonczenie gry w trybie jednoosobowym.\n", aktualna_data.c_str());
			continue;
		}
		//3 - tryb dwuosobowy
		else if (wybrana_opcja == 3) {
			int czy_zagrac_ponownie = 1; // 1, jesli tak
			//wpis do log.txt
			aktualna_data = sprawdzGodzine();
			fprintf(log, "%sRozpoczecie gry w trybie dwuosobowym.\n", aktualna_data.c_str());
			//pêtla gry
			while (czy_zagrac_ponownie == 1) {
				system("cls");
				nowa_gra = new GraDwuosobowa();
				nowa_gra->grajWGre();
				cout << bialy << "\n\n\tCzy chcesz zagraæ ponownie?\n" << domyslny;
				cout << "\tWprowadŸ " << zolty << "1" << domyslny << ", jeœli tak lub inny dowolny klawisz, by wróciæ do menu.\n";
				cin >> czy_zagrac_ponownie;
				//czyszczenie bufora
				cin.clear();
				cin.ignore(99999, '\n');
			}
			//wpis do log.txt
			aktualna_data = sprawdzGodzine();
			fprintf(log, "%sZakonczenie gry w trybie dwuosobowym.\n", aktualna_data.c_str());
			continue;
		}
		// 4 - tryb z komputerem
		else if (wybrana_opcja == 4) {
			int czy_zagrac_ponownie = 1; // 1, jesli tak
			//wpis do log.txt
			aktualna_data = sprawdzGodzine();
			fprintf(log, "%sRozpoczecie gry w trybie z komputerem.\n", aktualna_data.c_str());
			//pêtla gry
			while (czy_zagrac_ponownie == 1) {
				system("cls");
				nowa_gra = new GraZKomputerem();
				nowa_gra->grajWGre();
				cout << bialy << "\n\n\tCzy chcesz zagraæ ponownie?\n" << domyslny;
				cout << "\tWprowadŸ " << zolty << "1" << domyslny << ", jeœli tak lub inny dowolny klawisz, by wróciæ do menu.\n";
				cin >> czy_zagrac_ponownie;
				//czyszczenie bufora
				cin.clear();
				cin.ignore(99999, '\n');
			}
			//wpis do log.txt
			aktualna_data = sprawdzGodzine();
			fprintf(log, "%sZakonczenie gry w trybie z komputerem.\n", aktualna_data.c_str());
			continue;
		}
		//5 - tablica wynikow
		else if (wybrana_opcja == 5) {
			system("cls");
			cout << bialy << "\n\tOto wyniki graczy:\n\n";
			wyswietlWyniki();
			//wpis do log.txt
			aktualna_data = sprawdzGodzine();
			fprintf(log, "%sWyswietlenie rankingu graczy.\n", aktualna_data.c_str());
			cout << domyslny<< "\n\nWciœnij Enter, by kontynuowaæ..."<< bialy;
			//czyszczenie bufora
			cin.clear();
			cin.ignore(99999, '\n');
			continue;
		}
	} while (wybrana_opcja != 6);

	system("cls");
	cout << blekitny<< "\n\n\tDziêkujê za grê!\n\n";
	cout << zolty << "\tDo zobaczenia nastêpnym razem!\n\n\n" << domyslny;
	//wpis do log.txt
	aktualna_data = sprawdzGodzine();
	fprintf(log, "%sZakonczenie pracy programu.\n", aktualna_data.c_str());
	fclose(log);
	return 0;
}