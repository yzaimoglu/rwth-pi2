#include <iostream>
#include <memory>
#include "Streckenende.h"
#include "vertagt_liste.h"

Streckenende::Streckenende(Fahrzeug& fahrzeug, Weg& weg) : Fahrausnahme(fahrzeug, weg) {

}

// Bearbeitung der Fehlermeldung des Streckenendes
void Streckenende::vBearbeiten() {
//	std::cout << "Das Fahrzeug mit der ID " << p_pFahrzeug.getID() << " hat auf dem Weg mit der ID " << p_pWeg.getID() << " das Streckenede erreicht." << std::endl;
//	p_pWeg.pAbgabe(p_pFahrzeug);
	// Erhalten der Fahrzeuge auf dem Weg
		vertagt::VListe<std::unique_ptr<Fahrzeug>>* fahrzeugListe = p_pWeg.getFahrzeuge();

		// Generierung eines neuen zufälligen Weges
		Weg& neuerWeg = p_pWeg.getKreuzung().pZufaelligerWeg(p_pWeg);

		// Iterieren durch die Fahrzeuge auf dem Weg und finden des gewünschten Fahrzeugs
		for(vIterator it = fahrzeugListe->begin(); it != fahrzeugListe->end(); it++) {
			if((*it).get() == &p_pFahrzeug) {
				// Löschen des Fahrzeuges aus der fahrzeugListe (VAktion)
				fahrzeugListe->erase(it);

				// Tanken des Fahrzeuges
				p_pWeg.getKreuzung().vTanken(p_pFahrzeug);

				// Setzen der Abschnittstrecke auf 0
				(*it)->resetAbschnittStrecke();

				// Setzen des Fahrzeugs auf den neugenerierten Weg
				neuerWeg.vAnnahme(move(*it));
			}
		}
		std::cout << "Das Fahrzeug mit der ID " << p_pFahrzeug.getID() << " hat auf dem Weg mit der ID " << p_pWeg.getID() << " das Streckenede erreicht." << std::endl;

		// Aktualisieren der Fahrzeugliste (Ausführen der VAktionen)
		fahrzeugListe->vAktualisieren();
		std::cout << "ZEIT     " << ":" << dGlobaleZeit << std::endl;
		std::cout << "KREUZUNG " << ":" << p_pWeg.getKreuzung().getName() << " " << p_pWeg.getKreuzung().getTankstelle() << std::endl;
		std::cout << "WECHSEL  " << ":" << p_pWeg.getName() << " -> " << neuerWeg.getName() << std::endl;
		std::cout << "FAHRZEUG " << ":" << p_pFahrzeug.getName() << std::endl;
}

Streckenende::~Streckenende() {
}

