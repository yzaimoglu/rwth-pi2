#include "Simulation.h"
#include "Kreuzung.h"
#include "PKW.h"
#include "Fahrrad.h"
#include "SimuClient.h"
#include <map>

extern double dGlobaleZeit;

void Simulation::vSimulieren(double dZeit, double dZeitschritt) {
	dGlobaleZeit = 0.0;
	while (dGlobaleZeit < dZeit) {
		for(auto it = mKreuzungen.begin(); it != mKreuzungen.end(); it++) {
			it->second->vSimulieren();
			vSleep(50);
		}
		dGlobaleZeit += dZeitschritt;
	}

}

void Simulation::vEinlesen(std::istream& i, bool bMitGrafik) {
	int iZeile = 0;
	while (!i.eof()) {
		iZeile++;
		std::string objekt = "";
		try {
			i >> objekt;
			std::cout << objekt << std::endl;
		} catch (std::exception &e) {
			throw std::runtime_error("Fehler beim Einlesen der Datei; Zeile: " + std::to_string(iZeile));
		}

		if (objekt == "KREUZUNG") {
			std::shared_ptr<Kreuzung> pKreuzung = std::make_shared<Kreuzung>();

			i >> *pKreuzung;
			if (bMitGrafik) {
				int posX, posY;
				try {
					i >> posX >> posY;
				} catch (std::exception & e) {
					throw std::runtime_error("Fehler beim Einlesen der Kreuzungskoord.; Zeile: " + std::to_string(iZeile));
				}

				bZeichneKreuzung(posX, posY);
			}

			if (mKreuzungen.find(pKreuzung->getName()) != mKreuzungen.end())
				throw std::runtime_error("Fehler da die Kreuzung schon existiert; Zeile: " + std::to_string(iZeile));

			mKreuzungen.insert(std::pair<std::string, std::shared_ptr<Kreuzung>>(pKreuzung->getName(), std::move(pKreuzung)));
		} else if (objekt == "STRASSE") {
			std::string NameQ, NameZ, NameW1, NameW2;
			double Laenge;
			int iTL;
			Tempolimit TL;
			int iUeberholverbot;
			bool bUeberholverbot;

			try {
				i >> NameQ >> NameZ >> NameW1 >> NameW2 >> Laenge >> iTL >> iUeberholverbot;
			}
			catch (exception& e){
				throw std::runtime_error("Fehler beim Einlesen von einem Weg; Zeile: " + std::to_string(iZeile));
			}

			switch (iTL) {
			case 1 :
				TL = Tempolimit::INNERORTS;
				break;
			case 2 :
				TL = Tempolimit::LANDSTRASSE;
				break;
			case 3 :
				TL = Tempolimit::AUTOBAHN;
				break;
			default:
				throw std::runtime_error("Fehler beim Lesen des Tempolimits; Zeile: " + std::to_string(iZeile));
				break;
			}

			switch (iUeberholverbot) {
			case 0:
				bUeberholverbot = false;
				break;
			case 1:
				bUeberholverbot = true;
				break;
			default:
				throw std::runtime_error("Fehler beim Lesen des Überholverbots; Zeile: " + std::to_string(iZeile));
				break;
			}

			if (mKreuzungen.find(NameQ) == mKreuzungen.end() || mKreuzungen.find(NameZ) == mKreuzungen.end())
				throw std::runtime_error("Fehler beim Finden der Kreuzungen; Zeile: " + std::to_string(iZeile));
			else {
				auto pQuelle = mKreuzungen.find(NameQ)->second;
				auto pZiel = mKreuzungen.find(NameZ)->second;

				pQuelle->vVerbinde(NameW1, NameW2, Laenge, pQuelle, pZiel, TL, bUeberholverbot);

				if (bMitGrafik) {
					try {
						int iAnzahl;
						i >> iAnzahl;
						int* iKoordinaten = new int[2 * iAnzahl];

						for (int k = 0; k < iAnzahl; k++) {
							i >> iKoordinaten[2 * k] >> iKoordinaten[2 * k + 1];
						}

						bZeichneStrasse(NameW1, NameW2, int(Laenge), iAnzahl, iKoordinaten);
						delete iKoordinaten;
					} catch (std::exception &e) {
						throw std::runtime_error("Fehler beim Lesen der Wegkoordinaten; Zeile: " + std::to_string(iZeile));
					}
				}
			}
		} else if (objekt == "PKW") {
			std::unique_ptr<PKW> pAuto = std::make_unique<PKW>();
			string sKrName;
			double dStartzeit;

			try {
				i >> *pAuto >> sKrName >> dStartzeit;
			} catch (exception & e) {
				throw("Fehler beim Lesen des PKW; Zeile: " + std::to_string(iZeile));
			}

			auto pKreuzung = mKreuzungen.find(sKrName);

			if (pKreuzung == mKreuzungen.end())
				throw string("Fehler beim Finden der Startkreuzung des PKW; Zeile: " + std::to_string(iZeile));
			else {
				pKreuzung->second->vAnnahme(std::move(pAuto), dStartzeit);
			}
		} else if (objekt == "FAHRRAD") {
			std::unique_ptr<Fahrrad> pFahrrad = std::make_unique<Fahrrad>();
			std::string sKrName;
			double dStartzeit;

			try {
				i >> *pFahrrad >> sKrName >> dStartzeit;
			} catch (std::exception &e) {
				throw std::runtime_error("Fehler beim Einlesen eines Fahrrads; Zeile: " + std::to_string(iZeile));
			}

			auto pKreuzung = mKreuzungen.find(sKrName);

			if (pKreuzung == mKreuzungen.end())
				throw runtime_error("Fehler beim Finden der Startkreuzung des Fahrrads; Zeile: " + std::to_string(iZeile));
			else {
				pKreuzung->second->vAnnahme(std::move(pFahrrad), dStartzeit);
			}
		} else
			throw runtime_error("Unbekanntes Simulationsobjekt "+ objekt + "; Zeile: " + std::to_string(iZeile));
	}
}
