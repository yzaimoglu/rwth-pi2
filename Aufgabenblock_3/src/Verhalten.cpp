#include "Verhalten.h"

// Standardkonstruktor
Verhalten::Verhalten() {
}

// Konstruktor mit Weg
Verhalten::Verhalten(Weg& weg)
	: p_pWeg(&weg){
}

// Destruktor
Verhalten::~Verhalten() {
}

