#include "klasy.h"

//Wisielec
//konstruktor
Wisielec::Wisielec() {
	odczytSlowZPliku("slowa.txt");
	slowo_do_zgadniecia = baza_slow[rand() % LICZBA_SLOW];
	zresetujUzyteLitery();
	pozostale_proby = ILOSC_PROB;
	nick_aktualny_gracz =  '\0' ;
	pkt_aktualny_gracz = 0;
}
//resetowanie u¿ytych liter - wype³nianie tablicy uzyte_litery[] znakami '\0'
void Wisielec::zresetujUzyteLitery() {
	for (int i = 0; i < ALFABET; i++)
		uzyte_litery[i] = '\0';
}

//funkcja wpisuje zaktualizowane wyniki
void Wisielec::zapiszWynik() { 
	string temp_nicki[ILOSC_NICK];//zmienna do tymczasowego przechowania istniej¹cych ju¿ nicków w pliku wyniki.txt
	int temp_punkty[ILOSC_NICK]; //zmienna do tymczasowego przechowania punktow istniejacych juz graczy w pliku ]
	bool czy_nick_istnieje = false; //czy taki sam nick istnieje ju¿ w wynikach
	int ilosc_wynikow = 0; //ilosc wynikow w pliku wyniki.txt
	FILE* plik_wyniki = fopen("wyniki.txt", "a+");
	if (plik_wyniki == NULL) {
		cout << "\n\nBlad otwarcia pliku \"wyniki.txt\".\nKoniec programu.";
		exit(0);
	}
	FILE* temp = fopen("temp.txt", "a+"); //plik ktory przechowa zaktualizowane dane
	if (temp == NULL) {
		cout << "\n\nBlad otwarcia pliku \"temp.txt\".\nKoniec programu.";
		exit(0);
	}
	char c_napis[100]; //zmienna typu C napis do tymczasowego przechowania pojedynczego napisu
	while (!feof(plik_wyniki) && fscanf(plik_wyniki, "%s %d", c_napis, &temp_punkty[ilosc_wynikow]) == 2) {
		temp_nicki[ilosc_wynikow] = c_napis;
		//jesli nick istnieje juz w bazie
		if (temp_nicki[ilosc_wynikow] == nick_aktualny_gracz) {
			temp_punkty[ilosc_wynikow] += pkt_aktualny_gracz;
			czy_nick_istnieje = true;
		}
		ilosc_wynikow++;
	}
	//jesli nick nie istnieje w bazie
	if (czy_nick_istnieje == false) {
		temp_nicki[ilosc_wynikow] = nick_aktualny_gracz;
		temp_punkty[ilosc_wynikow] = pkt_aktualny_gracz;
		ilosc_wynikow++;
	}
	for (int j = 0; j < ilosc_wynikow; j++) {
		const char* temp_napis = temp_nicki[j].c_str(); //konwersja string na c-napis
		fprintf(temp, "%s %d\n", temp_napis, temp_punkty[j]); //wpisanie do pliku temp.txt
	}
	//zamkniecie plikow
	fclose(plik_wyniki);
	fclose(temp);
	//usuwanie nieaktualnego juz pliku wyniki.txt
	remove("wyniki.txt");
	//zmiana nazwy z temp.txt na wyniki.txt
	rename("temp.txt", "wyniki.txt");
}

//wyœwietlanie aktualnego stanu gry
void Wisielec::wyswietlGre() {
	cout << bialy;
	cout << "Aktualnie gra: " << zolty << nick_aktualny_gracz << bialy << endl;
	cout << bialy << "\n\tU¿yte litery: " << zielony;
	for (int i = 0; i < ALFABET; i++) {
		if (uzyte_litery[i] != '\0')
			cout << uzyte_litery[i] << " ";
	}
	cout << bialy << "\n\tPozosta³e próby: " << blekitny << pozostale_proby << bialy << "\n\n";
	cout << "\t    _______   \n";
	cout << "\t   |       |  \n";
	cout << "\t   |       " << (pozostale_proby < 7 ? "O" : "") << endl;
	cout << "\t   |      " << (pozostale_proby < 4 ? "/" : " ") << (pozostale_proby < 6 ? "|" : "") << (pozostale_proby < 5 ? "\\" : "") << endl;
	cout << "\t   |       " << (pozostale_proby < 3 ? "|" : "") << endl;
	cout << "\t   |      " << (pozostale_proby < 2 ? "/" : "") << " " << (pozostale_proby < 1 ? "\\" : "") << endl;
	cout << "\t___|___       \n\n\t";
	for (int i = 0; i < slowo_do_zgadniecia.length(); i++) {
		char letter = slowo_do_zgadniecia[i];
		if (czyLiteraUzyta(letter))
			cout << letter << " ";
		else
			cout << "_ ";
	}
}
//sprawdzanie, czy litera zosta³a juz u¿yta przez gracza
bool Wisielec::czyLiteraUzyta(char litera) {
	int indeks = litera - 'a';
	return uzyte_litery[indeks] == litera;
}
//zapisywanie podanej litery jako u¿ytej
void Wisielec::zapiszLitereJakoUzyta(char litera) {
	int indeks = litera - 'a';
	uzyte_litery[indeks] = litera;
}
//funkcja sprawdza, czy gracz ma jeszcze dostêpne próby i czy osi¹gniêto koniec gry
bool Wisielec::czyKoniecGry() {
	if (pozostale_proby == 0) {
		system("cls");
		wyswietlGre();
		cout << "\n\n\n\tPrzegrana! Tajne s³owo to: " << zolty << slowo_do_zgadniecia << bialy << endl;
		return true;
	}
	for (char litera : slowo_do_zgadniecia) {
		if (!czyLiteraUzyta(litera)) 
			return false;
	}
	system("cls");
	wyswietlGre();
	cout << zolty << "\n\n\n\tWygrana! Gratulacje!" << bialy;
	pkt_aktualny_gracz++;
	return true;
}
//funkcja obslugujaca mechanizm odgadywania litery
void Wisielec::gra() {
	char podana_litera;
	do {
		system("cls");
		wyswietlGre();
		cout << "\n\n\tZgadnij literê: ";
		podana_litera = pobierzLitere();
		podana_litera = tolower(podana_litera);
		if (czyLiteraUzyta(podana_litera)) {
			cout << domyslny << "\tTa litera zosta³a ju¿ u¿yta." << bialy << endl;
			Sleep(500);
			continue;
		}
		zapiszLitereJakoUzyta(podana_litera);
		if (slowo_do_zgadniecia.find(podana_litera) == string::npos)
			pozostale_proby--;
	} while (!czyKoniecGry());

}
//funkcja odczytuje wyrazy z pliku i zapisuje je do tablicy baza_slow[]
void Wisielec::odczytSlowZPliku(const string& nazwa_pliku) {
	ifstream file(nazwa_pliku);
	if (file.is_open()) {
		string slowo;
		for (int i = 0; getline(file, slowo); i++) {
			if (i < LICZBA_SLOW) 
				baza_slow[i] = slowo;
			else 
				break;
		}
		file.close();
	}
	else {
		cout << "B³¹d podczas otwierania pliku." << endl;
		exit(0);
	}
}
//destruktor
Wisielec::~Wisielec() { };


//GraJednoosobowa
//konstruktor
GraJednoosobowa::GraJednoosobowa() : Wisielec() {}
//funkcja do obs³ugi gry w trybie dla jednego gracza
void GraJednoosobowa::grajWGre() {
	cout << "\n\tPodaj swój nick: ";
	nick_aktualny_gracz = pobierzSlowo();
	gra(); //funkcja odpowiadaj¹ca za przebieg pojedynczej gry
	zapiszWynik();
}
//destruktor
GraJednoosobowa::~GraJednoosobowa() {};

//GraDwuosobowa
//konstruktor
GraDwuosobowa::GraDwuosobowa() : Wisielec() {
	nick_gracz1 =  '\0' ;
	nick_gracz2 = '\0';
	pkt_gracz2 = 0;
}
//funkcja do obs³ugi gry w trybie dla dwóch graczy
void GraDwuosobowa::grajWGre() {
	cout << "Podaj nick gracza nr. 1: ";
	nick_gracz1 = pobierzSlowo();
	cout << "Podaj nick gracza nr. 2: ";
	nick_gracz2 = pobierzSlowo();
	
	cout << zolty << nick_gracz1 << domyslny << ", wprowadŸ s³owo do odgadniêcia przez " << zolty << nick_gracz2 << domyslny << ": ";
	string slowo_od_gracza = pobierzSlowo();  //s³owo do odgadniêcia, wprowadzone przez gracza
	nick_aktualny_gracz = nick_gracz2;
	zresetujUzyteLitery();
	slowo_do_zgadniecia = slowo_od_gracza;
	pozostale_proby = ILOSC_PROB;
	gra();
	zapiszWynik();//zapis wyniku gracza

	cout << domyslny << "\n\n\n\tWciænij Enter by kontynuowaæ..." << bialy;
	cin.ignore(); //czyszczenie bufora
	system("cls");
	cout << zolty << nick_gracz2 << domyslny << ", wprowadŸ s³owo do odgadniêcia przez " << zolty << nick_gracz1 << domyslny << ": ";
	slowo_od_gracza = pobierzSlowo();
	nick_aktualny_gracz = nick_gracz2;
	zresetujUzyteLitery();
	slowo_do_zgadniecia = slowo_od_gracza;
	pozostale_proby = ILOSC_PROB;
	gra();
	zapiszWynik();//zapis wyniku gracza
}


//destruktor
GraDwuosobowa::~GraDwuosobowa() {};


//GraZKomputerem
//konstruktor
GraZKomputerem::GraZKomputerem() : Wisielec() {
	nick_gracz = '\0' ;
	nick_komputer = "Komputer"; //pisana z duzej litery nigdy nie zostanie podmieniona przez gracza- gracz moze miec nick pisany tylko malymi literami
}
//funkcja do obs³ugi gry w trybie gry z komputerem
void GraZKomputerem::grajWGre()  {
	system("cls");
	cout << "\n\tPodaj swój nick: ";
	nick_gracz = pobierzSlowo();
	cout << "\n\n";
	cout << zolty<< nick_gracz <<bialy<< ", wprowadŸ s³owo do odgadniêcia przez komputer "<<domyslny<<"(bez polskich znaków): "<<bialy;
	slowo_do_zgadniecia = pobierzSlowo();
	//zresetujUzyteLitery();
	//pozostale_proby = ILOSC_PROB;
	nick_aktualny_gracz = nick_komputer; //zmiana nicku na komputer
	pkt_aktualny_gracz = 0;
	system("cls");
	wyswietlGre();
	cout << "\nKomputer próbuje odgadn¹æ s³owo..." << endl;
	while (!czyKoniecGry()) {
		char guess = getRandomLetter();
		zapiszLitereJakoUzyta(guess);
		if (slowo_do_zgadniecia.find(guess) == string::npos) {
			pozostale_proby--;
		}
		system("cls");
		wyswietlGre();
		Sleep(1000);
	}
	zapiszWynik();//zapis wyniku komputera
	cout << "\nWciœnij Enter by kontynuowaæ...";
	getchar();
	//gracz zgaduje
	nick_aktualny_gracz = nick_gracz; //zmiana nicku na gracza
	//resetowanie parametrow
	pkt_aktualny_gracz = 0;
	zresetujUzyteLitery();
	slowo_do_zgadniecia = baza_slow[rand() % LICZBA_SLOW];
	pozostale_proby = ILOSC_PROB;
	for (int i = 2; i >= 0; i--) {
		system("cls");
		cout << "\n\n\t" << zolty<< nick_aktualny_gracz << bialy<<" , "<<blekitny<<"Komputer " <<bialy<<"losuje dla Ciebie s³owo..."<<domyslny<<" [" << i << " sek.]"<<bialy;
		Sleep(1000);
	}
	gra();
	zapiszWynik();//zapis wyniku gracza
}
//losowanie litery, która bêdzie prób¹ komputera w grze
char GraZKomputerem::getRandomLetter() {
	char letter;
	do {
		letter = static_cast<char>('a' + rand() % 26);
	} while (czyLiteraUzyta(letter));
	return letter;
}
//destruktor
GraZKomputerem::~GraZKomputerem() {};