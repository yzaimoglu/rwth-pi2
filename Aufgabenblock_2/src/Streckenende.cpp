#include <iostream>
#include <memory>
#include "Streckenende.h"
#include "vertagt_liste.h"

Streckenende::Streckenende(Fahrzeug& fahrzeug, Weg& weg) : Fahrausnahme(fahrzeug, weg) {

}

// Bearbeitung der Fehlermeldung des Streckenendes
void Streckenende::vBearbeiten() {
	std::cout << "Das Fahrzeug mit der ID " << p_pFahrzeug.getID() << " hat auf dem Weg mit der ID " << p_pWeg.getID() << " das Streckenede erreicht." << std::endl;
}

Streckenende::~Streckenende() {
}

