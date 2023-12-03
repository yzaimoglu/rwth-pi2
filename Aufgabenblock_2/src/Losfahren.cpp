#include <iostream>
#include <memory>
#include "Losfahren.h"
#include "Weg.h"
#include "Fahrzeug.h"


Losfahren::Losfahren(Fahrzeug& fahrzeug, Weg& weg) : Fahrausnahme(fahrzeug, weg) {

}

// Bearbeiten der Fehlermeldung Losfahren
void Losfahren::vBearbeiten() {
	std::cout << "Das Fahrzeug mit der ID " << p_pFahrzeug.getID() << " fährt jetzt auf dem Weg mit der ID " << p_pWeg.getID() << " los." << std::endl;
}

Losfahren::~Losfahren() {
}

