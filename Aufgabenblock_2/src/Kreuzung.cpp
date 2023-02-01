#include "PKW.h"
#include "Kreuzung.h"
#include "Weg.h"

Kreuzung::Kreuzung() {}

Kreuzung::Kreuzung(std::string sName, double dTankstelle) :
		Simulationsobjekt(sName),
		p_dTankstelle(dTankstelle) {
}

void Kreuzung::vTanken(Fahrzeug& fahrzeug) {
	// Überprüfen ob die Tankstelle überhaupt genug Inhalt hat
	if(p_dTankstelle > 0) {
		// Tankstellenkapazität setzen durch den Treibstoff, der für das Fahrzeug notwendig war
		setTankstelle(fahrzeug.dTanken(0));
	}
}

// Verbindung von zwei Wegen an einer Kreuzung
void Kreuzung::vVerbinde(std::string sNameHinweg, std::string sNameRuckweg,
		double dWegLaenge, std::weak_ptr<Kreuzung> pStartKreuzung,
		const std::weak_ptr<Kreuzung> pZielKreuzung, Tempolimit eTempolimit, bool bUeberholverbot) {

	// Erstellen der Wege als shared_ptr
	std::shared_ptr<Weg> pHinweg = std::make_shared<Weg>(sNameHinweg, dWegLaenge, pZielKreuzung, eTempolimit, bUeberholverbot);
	std::shared_ptr<Weg> pRueckweg = std::make_shared<Weg>(sNameHinweg, dWegLaenge, pStartKreuzung, eTempolimit, bUeberholverbot);

	// Bekanntmachen der Wege
	pHinweg->setRueckweg(pRueckweg);
	pRueckweg->setRueckweg(pHinweg);

	// Hinzufügen der Wege in die Wegliste der Kreuzungen
	pZielKreuzung.lock()->p_pWege.push_back(pRueckweg);
	pStartKreuzung.lock()->p_pWege.push_back(pHinweg);
}

// Annahme des Fahrzeuges in die Kreuzung
void Kreuzung::vAnnahme(std::unique_ptr<Fahrzeug> pFahrzeug, double dZeit) {
	// Tanken des Fahrzeuges bei Annahme
	vTanken(*pFahrzeug);

	// Weiterleiten des Fahrzeuges auf den nächsten Weg
	p_pWege.front()->vAnnahme(move(pFahrzeug), dZeit);
}

// Simulation einer Kreuzung
void Kreuzung::vSimulieren() {
	// Simulieren der Wege an einer Kreuzung
	std::list<std::shared_ptr<Weg>>::iterator it;

	// Iterieren über die Wege einer Kreuzung
	for(it = p_pWege.begin(); it != p_pWege.end(); it++) {
		(*it)->vSimulieren();
	}
}

// Standarddestruktor
Kreuzung::~Kreuzung() {

}

