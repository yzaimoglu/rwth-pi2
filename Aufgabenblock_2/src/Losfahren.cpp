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
	// Löschen aus dem Weg als parkendes Fahrzeug
	std::unique_ptr<Fahrzeug> lokal = p_pWeg.pAbgabe(p_pFahrzeug);
	// Hinzufügen auf den Weg als fahrendes Fahrzeug
	p_pWeg.vAnnahme(std::move(lokal));
}

Losfahren::~Losfahren() {
}

