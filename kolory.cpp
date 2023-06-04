#include "kolory.h"


//manipulatory do formatowania koloru tekstu 
ostream& domyslny(ostream& os) { return os << "\033[0m"; }
//kolor bialy
ostream& bialy(ostream& os) { return os << "\033[97m"; }
//kolor czerwony
//ostream& czerwony(ostream& os) { return os << "\033[91m"; }
//kolor zielony
ostream& zielony(ostream& os) { return os << "\033[92m"; }
//kolor ¿ó³ty
ostream& zolty(ostream& os) { return os << "\033[93m"; }
//kolor niebieski
ostream& niebieski(ostream& os) { return os << "\033[94m"; }
//kolor fioletowy
//ostream& fiolet(ostream& os) { return os << "\033[95m"; }
//kolor b³êkitny
ostream& blekitny(ostream& os) { return os << "\033[96m"; }
