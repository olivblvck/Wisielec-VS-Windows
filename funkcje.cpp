#define _CRT_SECURE_NO_WARNINGS 
#include "funkcje.h"
#include "kolory.h"

using namespace std;

//funkcja wyswietlaj¹ca ekran pocz¹tkowy
void ekranStartowy() {
	for (int i = 2; i >= 0; i--) {
		system("cls");
		cout << bialy;
		cout << "\n\n\tTrwa uruchamianie gry " << blekitny << "Wisielec " << bialy;
		cout << "\n\n\t\t  [" << i << " sek.]";
		cout << zolty << "\n\n\tAutor projektu: Oliwia Witkowska.\n\n";
		cout << bialy;
		Sleep(1000);
	}
}

//funkcja wyswietla menu z dostêpnymi opcjami interakcji
int wyswietlMenu() {
	int decyzja;
	system("cls");
	cout << bialy;
	cout << "\n\tWitaj w grze " << blekitny << "Wisielec!\n\n";
	cout << zolty << "\t\t1" << bialy << " - Wyœwietl instrukcje i zasady gry\n";
	cout << zolty << "\t\t2" << bialy << " - Gra jednoosobowa\n";
	cout << zolty << "\t\t3" << bialy << " - Gra dla dwóch graczy\n";
	cout << zolty << "\t\t4" << bialy << " - Gra z komputerem\n";
	cout << zolty << "\t\t5" << bialy << " - Wyœwietl wyniki graczy \n";
	cout << zolty << "\t\t6" << bialy << " - Zakoñcz dzia³anie programu \n";
	cout << domyslny << "\n\tWprowadŸ cyfrê i zatwierdŸ Enterem: ";
	decyzja = pobierzCyfre();
	cout << bialy;
	return decyzja;
}

//funkcja zwraca false, jesli wprowadzono polski znak typu ¹, ê etc.
bool czyPolskiZnak(char litera) {
	return ((litera > 'z' || litera < 'a') && (litera > 'Z' || litera < 'A'));
}


//funkcja do pobrania litery od uzytkownika z wykluczeniem polskich znakow typu ¹, ê...
char pobierzLitere() {
	char litera;
	while (!scanf_s("%c", &litera) || czyPolskiZnak(litera) || getchar() != '\n') {
		cout << "B³êdne dane. WprowadŸ ponownie (pamiêtaj, by nie wprowadzaæ polskich znaków): ";
		while (getchar() != '\n')
			;
	}
	return litera;
}

//funkcja po pobierania cyfry z kontrol¹ poprawnoœci wprowadzonych danych
int pobierzCyfre() {
	int cyfra;
	while (!scanf_s("%d", &cyfra) || getchar() != '\n') {
		cout << "B³êdne dane. WprowadŸ ponownie: ";
		while (getchar() != '\n')
			;
	}
	return cyfra;
}

//funkcja do pobierania wyrazu z kontrol¹ polskich znaków
//zamienia duze litery na male, a male pozostawia bez zmian
//funkcja nie dopuszcza wejscia ze spacj¹ 
string pobierzSlowo() {
	string wyraz;
	while (!getline(cin, wyraz) || any_of(wyraz.begin(), wyraz.end(), czyPolskiZnak)) {
		cout << "B³êdne dane. WprowadŸ ponownie (pamiêtaj, by nie wprowadzaæ polskich znaków): ";
	}
	// konwersja liter na ma³e
	for (int i = 0; i < wyraz.length(); i++) {
		wyraz[i] = tolower(wyraz[i]);
	}
	return wyraz;
}

//funkcja drukuje w konsoli instrukcje z pliku txt
void wyswietlInstrukcje() {
	setlocale(LC_ALL, ""); // Ustawienie domyœlnego kodowania znaków dla strumieni
	FILE* stream;
	char bufor[100];
	//otwieranie pliku
	stream = fopen("instrukcja.txt", "a+");
	if (stream == NULL) {
		cout << "\nWyst¹pi³ b³¹d podczas otwarcia pliku \"instrukcja.txt\". Koniec programu.\n\n";
		exit(0);
	}
	while (!feof(stream)) {
		fgets(bufor, 100, stream);
		printf("\t%s", bufor);
	}
	fclose(stream);
	setlocale(LC_ALL, "Polish");
}

//funkcja drukuje w konsoli wyniki z pliku txt
void wyswietlWyniki() {
	setlocale(LC_ALL, ""); // Ustawienie domyœlnego kodowania znaków dla strumieni
	//otwieranie pliku
	FILE* plik_wyniki = fopen("wyniki.txt", "a+");
	if (plik_wyniki == NULL) {
		cout << "\n\nBlad otwarcia pliku \"wyniki.txt\".\nKoniec programu.";
		exit(0);
	}
	char c_napis[100];
	int temp_punkty;
	while (!feof(plik_wyniki) && fscanf(plik_wyniki, "%s %d", c_napis, &temp_punkty) == 2) {
		//printf("\t%s %d\n", c_napis, temp_punkty);
		cout <<"\t"<< blekitny <<left <<setw(20)<< c_napis << "  " << zolty << temp_punkty << endl;
	}
	cout << bialy;
	fclose(plik_wyniki);
	setlocale(LC_ALL, "Polish");
}

//zwraca aktualn¹ datê
string sprawdzGodzine() {
	time_t czas;
	struct tm* data;
	char godzina[80];
	time(&czas);
	data = localtime(&czas);
	strftime(godzina, 80, "%d.%m.%Y\t%H:%M:%S\t", data);
	return godzina;
}
