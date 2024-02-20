#include<iostream>
#include<vector>
#include<string>
#include<windows.h>
#include<iomanip>
#include<fstream>

using namespace std;

void curataConsola()
{
	system("cls");
}

class Utilizator
{
protected:
	string numeUtilizator;
	string parolaUtilizator;
public:
	Utilizator()
	{
		this->numeUtilizator = "";
		this->parolaUtilizator = "";
	}

	Utilizator(string numeutilizator, string parolautilizator)
	{
		this->numeUtilizator = numeutilizator;
		this->parolaUtilizator = parolautilizator;
	}

	virtual void afiseazaStoc() = 0;
};

class Produse
{
protected:
	string numeProdus;
	string descriereProdus;
	float pretProdus;
	string dataFabricatie;
	float cantitateDisponibila;
	float cantitateAdaugataInCos;

public:
	Produse()
	{
		this->numeProdus = "";
		this->descriereProdus = "";
		this->pretProdus = 0;
		this->dataFabricatie = "";
		this->cantitateDisponibila = 0;
	}

	Produse(string numeProdus, string descriereProdus, float pretProdus, string dataFabricatie, float cantitateDisponibila)
	{
		this->numeProdus = numeProdus;
		this->descriereProdus = descriereProdus;
		if (pretProdus >= 0)
		{
			this->pretProdus = pretProdus;
		}
		this->dataFabricatie = dataFabricatie;
		if (cantitateDisponibila > 0)
		{
			this->cantitateDisponibila = cantitateDisponibila;
		}
	}

	Produse(const Produse& pr)
	{
		this->numeProdus = pr.numeProdus;
		this->descriereProdus = pr.descriereProdus;
		this->pretProdus = pr.pretProdus;
		this->dataFabricatie = pr.dataFabricatie;
		this->cantitateDisponibila = pr.cantitateDisponibila;
	}

	Produse& operator=(const Produse& pr)
	{
		if (this != &pr)
		{
			this->numeProdus = pr.numeProdus;
			this->descriereProdus = pr.descriereProdus;
			this->pretProdus = pr.pretProdus;
			this->dataFabricatie = pr.dataFabricatie;
			this->cantitateDisponibila = pr.cantitateDisponibila;
		}

		return *this;
	}

	Produse& operator+=(float marirePret)
	{
		this->pretProdus += marirePret;
		return *this;
	}

	bool operator<(const Produse& p)
	{
		return this->cantitateDisponibila < p.cantitateDisponibila;
	}

	Produse& operator-(float micsorarePret)
	{
		if (micsorarePret < this->pretProdus)
			this->pretProdus = this->pretProdus - micsorarePret;
		else
			this->pretProdus = 0;
		return *this;
	}

	void setNumeProdus(const string& nume)
	{
		numeProdus = nume;
	}

	void setDescriereProdus(const string& descriere)
	{
		descriereProdus = descriere;
	}

	void setPretProdus(float pret)
	{
		if (pret > 0)
			pretProdus = pret;
	}

	void setDataFabricatie(const string& data)
	{
		dataFabricatie = data;
	}

	void setCantitateDisponibila(float cantitate)
	{
		if (cantitate > 0)
			cantitateDisponibila = cantitate;
	}

	string getNumeProdus()
	{
		return numeProdus;
	}

	string getDescriereProdus()
	{
		return descriereProdus;
	}
	
	float getPretProdus()
	{
		return pretProdus;
	}

	float getCantitateDisponibila()
	{
		return cantitateDisponibila;
	}

	string getDataFabricatie()
	{
		return dataFabricatie;
	}

	float getCantitateAdaugataInCos()
	{
		return cantitateAdaugataInCos;
	}

	void setCantitateAdaugataInCos(float cantitate) {
		if (cantitate > 0)
			cantitateAdaugataInCos = cantitate;
	}

	void actualizeazaStoc(float cantitateVanduta)
	{
		if (cantitateVanduta >= 0 && cantitateVanduta <= cantitateDisponibila) 
		{
			cantitateDisponibila -= cantitateVanduta;
		}
		else 
		{
			cout << "Eroare la actualizarea stocului pentru produsul " << numeProdus << "." << endl;
		}
	}

	virtual void afisareDetaliiProdus() = 0;
	virtual ~Produse() {}
};

class ProduseElectronice : public Produse
{
public:
	string garantie;
	string categorie;

	ProduseElectronice() : Produse()
	{
		this->garantie = "";
		this->categorie = "";
	}

	ProduseElectronice(string numeProdus, string descriereProdus, string dataFabricatie, float pretProdus, float cantitateDisponibila, string garantie, string categorie) : Produse(numeProdus, descriereProdus, pretProdus, dataFabricatie, cantitateDisponibila)
	{
		this->garantie = garantie;
		this->categorie = categorie;
	}

	ProduseElectronice(const ProduseElectronice& pre) : Produse(pre)
	{
		this->garantie = pre.garantie;
		this->categorie = pre.categorie;
	}

	ProduseElectronice& operator=(const ProduseElectronice& pre)
	{
		if (this != &pre)
		{
			this->garantie = pre.garantie;
			this->categorie = pre.categorie;
		}

		return *this;
	}

	string getGarantie()
	{
		return garantie;
	}

	void afisareDetaliiProdus()
	{
		cout << setw(25) << numeProdus << setw(30) << descriereProdus << setw(22) << pretProdus << setw(36) << dataFabricatie << setw(20) << cantitateDisponibila << setw(28) << garantie << endl;

	}

	void setGarantie(string& garantie)
	{
		this->garantie = garantie;
	}
};

class ProduseMobilier : public Produse
{
public:
	string material;
	string categorie;

	ProduseMobilier() : Produse()
	{
		this->material = "";
	}

	ProduseMobilier(string numeProdus, string descriereProdus, string dataFabricatie, float pretProdus, float cantitateDisponibila, string material, string categorie) : Produse(numeProdus, descriereProdus, pretProdus, dataFabricatie, cantitateDisponibila)
	{
		this->material = material;
	}

	ProduseMobilier(const ProduseMobilier& prm) : Produse(prm)
	{
		this->material = prm.material;
		this->categorie = prm.categorie;
	}

	ProduseMobilier& operator=(const ProduseMobilier& prm)
	{
		if (this != &prm)
		{
			this->material = prm.material;
			this->categorie = prm.categorie;
		}

		return *this;
	}

	string getMaterial()
	{
		return material;
	}
	void afisareDetaliiProdus()
	{
		cout << setw(18) << numeProdus << setw(30) << descriereProdus << setw(30) << dataFabricatie << setw(25) << pretProdus << setw(20) << cantitateDisponibila << setw(25) << material << endl;
	}

	void setMaterial(const string& material)
	{
		this->material = material;
	}
};

class Client : public Utilizator
{
protected:
	string numePersoana;
	string prenumePersoana;
	string adresaPersoana;
	string numarTelefon;
	string adresaEmail;
	int varstaPersoana;
public:
	vector<Produse*> produseMagazin;
	vector<ProduseElectronice*> produseElectronice;
	vector<ProduseMobilier*> produseMobilier;
	vector<Produse*> cosProduse;
	Client()
	{
		this->numePersoana = "";
		this->prenumePersoana = "";
		this->adresaPersoana = "";
		this->numarTelefon = "";
		this->adresaEmail = "";
		this->varstaPersoana = 0;
	}

	Client(string numePersoana, string prenumePersoana, string adresaPersoana, string numarTelefon, string adresaEmail, int varsta, string numeUtilizator, string parolaUtilizator) : Utilizator()
	{
		this->numePersoana = numePersoana;
		this->prenumePersoana = prenumePersoana;
		this->adresaEmail = adresaEmail;
		this->numarTelefon = numarTelefon;
		this->adresaEmail = adresaEmail;
		this->varstaPersoana = varsta;
	}

	Client(const vector<Produse*>& produseMagazin)
	{
		this->numePersoana = "";
		this->produseMagazin = produseMagazin;
	}

	string getNumePersoana()
	{
		return numePersoana;
	}
	string getPrenumePersoana()
	{
		return prenumePersoana;
	}
	string getAdresaPersoana()
	{
		return adresaPersoana;
	}
	string getNumarTelefon()
	{
		return numarTelefon;
	}
	string getAdresaEmail()
	{
		return adresaEmail;
	}
	float getVarstaPersoana()
	{
		return varstaPersoana;
	}

	bool autentificareClient(const string& nume, const string& parola) const
	{
		vector<pair<string, string>> utilizatoriClienti = 
		{
			{"user1", "parola1"},
			{"user2", "parola2"},
		};

		for (const auto& utilizator : utilizatoriClienti)
		{
			if (utilizator.first == nume && utilizator.second == parola)
			{
				return true;
			}
		}

		return false;
	}

	void afiseazaStoc()
	{
		cout << endl << "1. Produse de tip 'Electronice' ";
		cout << endl << "2. Produse de tip 'Mobilier' ";
		cout << endl << "3. Iesire ";
		string optiune;
		cout << endl << endl << "----------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
		cout << "Introduceti cifra corespunzatoare tipului de produs pe care doriti sa le vizualizati: ";
		cin >> optiune;
		string categorieAfisare;
		if (optiune == "1")
		{
			categorieAfisare = "Electronice";
			curataConsola();
			cout << "------------------------------------------------------------AFISARE PRODUSE ELECTRONICE MAGAZIN-------------------------------------------------------------" << endl << endl;
			if (categorieAfisare == "Electronice")
			{
				cout << setw(25) << "Denumire Produs" << setw(30) << "Descriere Produs" << setw(25) << "Pret Produs" << setw(30) << "Data Fabricatie" << setw(30) << "Cantitate Disponibila" << setw(25) << "Garantie Produs" << endl << endl;
				for (const auto& produs : produseElectronice)
				{
					produs->afisareDetaliiProdus();
				}
			}
		}
		else if (optiune == "2")
		{
			categorieAfisare = "Mobilier";
			curataConsola();
			cout << "---------------------------------------------------------------AFISARE PRODUSE MOBILIER MAGAZIN-------------------------------------------------------------" << endl;
			if (categorieAfisare == "Mobilier")
			{
				cout << setw(25) << "Denumire Produs" << setw(30) << "Descriere Produs" << setw(25) << "Pret Produs" << setw(30) << "Data Fabricatie" << setw(30) << "Cantitate Disponibila" << setw(25) << "Material Produs" << endl << endl;
				for (const auto& produs : produseMobilier)
				{
					produs->afisareDetaliiProdus();
				}
			}
		}
		else
		{
			return;
		}
		cout << "------------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
		cout << "Apasa orice tasta pentru a reveni in meniul anterior !";
		cin.ignore();
		cin.get();
	}

	void adaugaInCos(Produse* produs, float cantitate)
	{
		if (cantitate > 0 && cantitate <= produs->getCantitateDisponibila())
		{
			bool produsExistent = false;
			for (auto& produsCos : cosProduse)
			{
				if (produsCos->getNumeProdus() == produs->getNumeProdus())
				{
					produsCos->setCantitateAdaugataInCos(produsCos->getCantitateAdaugataInCos() + cantitate);
					produsExistent = true;
					break;
				}
			}

			if (!produsExistent)
			{
				produs->setCantitateAdaugataInCos(cantitate);
				cosProduse.push_back(produs);
			}
		}
		else
		{
			cout << "Cantitate invalida." << endl;
		}
	}
 
	void afisareCos()
	{
		for (auto& produsCos : cosProduse)
		{
			cout << setw(15) << produsCos->getNumeProdus() << setw(27) << produsCos->getPretProdus() << setw(27) << produsCos->getCantitateAdaugataInCos() << endl;
		}
	}

	void raportAfisare()
	{
		int i = 1;
		cout << "Format Raport: Numar Raport, Denumire Produs Comandat, Pret Produs Comandat, Cantitatea Cumparata" << endl << endl;
		for (auto& produsCos : cosProduse)
		{
			cout << "Raportul " << i << ":" << " " << produsCos->getNumeProdus() << ", " << produsCos->getPretProdus() << ", " << produsCos->getCantitateAdaugataInCos() << endl;
				i++;
		}
	}

	void stergeDinCos(const string& numeProdus, float cantitate)
	{
		for (auto it = cosProduse.begin(); it != cosProduse.end(); ++it)
		{
			if ((*it)->getNumeProdus() == numeProdus)
			{
				float cantitateDinCos = (*it)->getCantitateAdaugataInCos();

				if (cantitate <= cantitateDinCos)
				{
					(*it)->setCantitateAdaugataInCos(cantitateDinCos - cantitate);
					(*it)->setCantitateDisponibila((*it)->getCantitateDisponibila() + cantitate);

					if ((*it)->getCantitateAdaugataInCos() == 0)
					{
						delete* it;
						cosProduse.erase(it);
					}
					cout << "Produsul " << "'" << numeProdus << "'" << " a fost eliminat din cos cu succes !" << endl;
				}
				else
				{
					cout << "Cantitatea de eliminat este mai mare decat cantitatea din cos !" << endl;
				}

				return;
			}
		}

		cout << "Produsul cu numele " << "'" << numeProdus << "'" << " nu exista in cosul de cumparaturi !" << endl;
	}

	void completeazaDatePersonale()
	{
		string nume, prenume, adresa, numarTelefon, adresaEmail;
		int varsta;

		cout << "Introduceti numele: ";
		cin.ignore();
		getline(cin, nume);

		cout << "Introduceti prenumele: ";
		getline(cin, prenume);

		cout << "Introduceti adresa: ";
		getline(cin, adresa);

		cout << "Introduceti numarul de telefon: ";
		getline(cin, numarTelefon);

		cout << "Introduceti adresa de email: ";
		getline(cin, adresaEmail);

		cout << "Introduceti varsta: ";
		cin >> varsta;

		this->numePersoana = nume;
		this->prenumePersoana = prenume;
		this->adresaPersoana = adresa;
		this->numarTelefon = numarTelefon;
		this->adresaEmail = adresaEmail;
		this->varstaPersoana = varsta;

		cout << endl << "Datele personale au fost introduse cu succes !" << endl;
	}

	bool trimiteComanda()
	{
		if (cosProduse.empty()) {
			cout << "Cosul de cumparaturi este gol. Adaugati produse inainte de a trimite comanda." << endl;
			return false;
		}
		cout << endl << endl << "-----------------------------------------------------------------REZUMATUL COMENZII--------------------------------------------------------" << endl << endl;
		cout << setw(25) << "Denumire Produs" << setw(25) << "Pret Produs" << setw(30) << "Cantitate Selectata" << endl << endl;
		afisareCos();
		for (const auto& produs : cosProduse) {
			if (produs->getCantitateAdaugataInCos() > produs->getCantitateDisponibila()) {
				cout << "Nu exista suficient stoc pentru produsul " << produs->getNumeProdus() << "." << endl;
				return false;
			}
		}
		for (const auto& produs : cosProduse) 
		{
			produs->actualizeazaStoc(produs->getCantitateAdaugataInCos());
		}

		cout << endl << "Comanda a fost trimisa cu succes ! " << endl;
		return true;
	}

	bool generareRaportClient(ofstream& fisiertxt) 
	{
		if (cosProduse.empty()) {
			fisiertxt << "Cosul de cumparaturi este gol. Adaugati produse inainte de a trimite comanda." << endl;
			return false;
		}

		streambuf* oldCoutStreamBuf = cout.rdbuf();
		cout.rdbuf(fisiertxt.rdbuf());
		raportAfisare();
		cout.rdbuf(oldCoutStreamBuf);

		for (const auto& produs : cosProduse) {
			if (produs->getCantitateAdaugataInCos() > produs->getCantitateDisponibila()) 
			{
				cout << "Nu exista suficient stoc pentru produsul " << produs->getNumeProdus() << "." << endl;
				return false;
			}
		}
		for (const auto& produs : cosProduse) 
		{
			produs->actualizeazaStoc(produs->getCantitateAdaugataInCos());
		}
		cosProduse.clear();

		return true;
	}
};

class Magazin : public Utilizator
{
public:
	vector<Produse*> produseMagazin;
	vector<Produse*> produseElectronice;
	vector<Produse*> produseMobilier;
	vector<Produse*> produseComandate;
	Magazin() {}

	bool autentificareMagazin(const string& nume, const string& parola) const
	{
		vector<pair<string, string>> utilizatoriMagazin =
		{
			{"magazin1", "parola1"},
			{"magazin2", "parola2"},
		};

		for (const auto& utilizator : utilizatoriMagazin)
		{
			if (utilizator.first == nume && utilizator.second == parola)
			{
				return true;
			}
		}
		return false;
	}

	void stergeProdus(const string& numeProdus)
	{
		for (auto it = produseElectronice.begin(); it != produseElectronice.end(); ++it)
		{
			if ((*it)->getNumeProdus() == numeProdus)
			{
				delete* it; 
				produseElectronice.erase(it); 
				cout << "Produsul " << "'" << numeProdus << "'" << " a fost sters cu succes !" << endl << endl;
				return;
			}
		}
		for (auto it = produseMobilier.begin(); it != produseMobilier.end(); ++it)
		{
			if ((*it)->getNumeProdus() == numeProdus)
			{
				delete* it; 
				produseMobilier.erase(it); 
				cout << "Produsul " << "'" << numeProdus << "'" << " a fost sters cu succes !" << endl << endl;
				return;
			}
		}
		cout << "Produsul cu numele " << "'" << numeProdus << "'" << " nu a fost identificat !" << endl;
	}

	void editeazaProdus()
	{
		string numeProdus;
		cout << "Introduceti numele produsului pe care doriti sa-l editati: ";
		cin.ignore();
		getline(cin, numeProdus);

		for (auto& produs : produseMagazin)
		{
			if (produs->getNumeProdus() == numeProdus)
			{
				cout << "Produsul a fost gasit ! Introduceti noile informatii: " << endl << endl;

				string NumeProdus2, DescriereProdus2, DataFabricatie2, Categorie2, Garantie2, Material2;
				float PretProdus2, CantitateDisponibila2;

				cout << "* Nume produs: ";
				getline(cin, NumeProdus2);

				cout << "* Descriere produs: ";
				getline(cin, DescriereProdus2);

				cout << "* Data fabricatie: ";
				getline(cin, DataFabricatie2);
				
				cout << "* Pret produs: ";
				cin >> PretProdus2;
	
				cout << "* Cantitate disponibila: ";
				cin >> CantitateDisponibila2;

				cout << "* Categorie ('Electronice' / 'Mobilier'): ";
				cin.ignore();
				getline(cin, Categorie2);

				if (Categorie2 == "Electronice")
				{
					cout << "* Garantie: ";
					getline(cin, Garantie2);
				}
				else if (Categorie2 == "Mobilier")
				{
					cout << "* Material: ";
					getline(cin, Material2);
				}

				produs->setNumeProdus(NumeProdus2);
				produs->setDescriereProdus(DescriereProdus2);
				produs->setDataFabricatie(DataFabricatie2);
				produs->setPretProdus(PretProdus2);
				produs->setCantitateDisponibila(CantitateDisponibila2);

				if (Categorie2 == "Electronice" && dynamic_cast<ProduseElectronice*>(produs))
				{
					ProduseElectronice* produsElectronice = dynamic_cast<ProduseElectronice*>(produs);
					produsElectronice->setGarantie(Garantie2);
				}
				else if (Categorie2 == "Mobilier" && dynamic_cast<ProduseMobilier*>(produs))
				{
					ProduseMobilier* produsMobilier = dynamic_cast<ProduseMobilier*>(produs);
					produsMobilier->setMaterial(Material2);
				}

				cout << "Produsul " << "'" << numeProdus << "'" << " a fost editat cu succes !" << endl << endl;
				return;
			}
		}
		cout << endl << "Produsul cu numele " << "'" << numeProdus << "'" << " nu a fost gasit in sistemul magazinului !" << endl;
	}

	void afiseazaStoc()
	{
		cout << endl << "1. Produse de tip 'Electronice' ";
		cout << endl << "2. Produse de tip 'Mobilier' ";
		cout << endl << "3. Iesire ";
		string optiune;
		cout << endl << endl << "----------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
		cout << "Introduceti cifra corespunzatoare tipului de produse pe care doriti sa le vizualizati: ";
		cin >> optiune;
		string categorieAfisare;
		if (optiune == "1")
		{ 
			categorieAfisare = "Electronice";
			curataConsola();
			cout << "------------------------------------------------------------AFISARE PRODUSE ELECTRONICE MAGAZIN-------------------------------------------------------------" << endl;
			if (categorieAfisare == "Electronice")
			{
				cout << endl;
				cout << setw(25) << "Denumire Produs" << setw(30) << "Descriere Produs" << setw(25) << "Pret Produs" << setw(30) << "Data Fabricatie" << setw(30) << "Cantitate Disponibila" << setw(25) << "Garantie Produs" << endl << endl;
				for (const auto& produs : produseElectronice)
				{
					produs->afisareDetaliiProdus();
					cout << endl;
				}
			}
		}
		else if (optiune == "2")
		{
			categorieAfisare = "Mobilier";
			curataConsola();
			cout << "---------------------------------------------------------------AFISARE PRODUSE MOBILIER MAGAZIN-------------------------------------------------------------" << endl;
			if (categorieAfisare == "Mobilier")
			{
				cout << endl;
				cout << setw(25) << "Denumire Produs" << setw(30) << "Descriere Produs" << setw(25) << "Pret Produs" << setw(30) << "Data Fabricatie" << setw(30) << "Cantitate Disponibila" << setw(25) << "Material Produs" << endl << endl;
				for (const auto& produs : produseMobilier)
				{
					produs->afisareDetaliiProdus();
					cout << endl;
				}
			}
		}
		else
		{
			return;
		}
		cout << endl << "------------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
		cout << "Apasa orice tasta pentru a reveni in meniul anterior !";
		cin.ignore();
		cin.get();
	}

	void adaugaProdus(const string& numeProdus, const string& descriereProdus, const string& dataFabricatie, float pretProdus, float cantitateDisponibila, const string& categorie, const string& garantie = "", const string& material = "")
	{
		if (categorie == "Electronice")
		{
			ProduseElectronice* produs = new ProduseElectronice(numeProdus, descriereProdus, dataFabricatie, pretProdus, cantitateDisponibila, garantie, categorie);
			produseMagazin.push_back(produs);
			produseElectronice.push_back(produs);
		}
		else if (categorie == "Mobilier")
		{
			ProduseMobilier* produs = new ProduseMobilier(numeProdus, descriereProdus, dataFabricatie, pretProdus, cantitateDisponibila, material, categorie);
			produseMagazin.push_back(produs);
			produseMobilier.push_back(produs);
		}
		else
		{
			cout << endl << "Categoria selectata nu este recunoscuta." << endl;
		}
	}
};

class Meniu
{
	public:
		Magazin* magazin;
		Client* client;
		string numeMagazin;
		Meniu()
		{
			this->numeMagazin = "";
		}
		Meniu(Magazin* mag) : magazin(mag) {}
		void afisareMeniu()
		{
			string tipUtilizator;
			string optiuneNavigareMagazin;
			cout << "--------------------------------------------------------BUN VENIT PE PAGINA MAGAZINULUI ELECTRONIC--------------------------------------------------------" << endl << endl;
			cout << "1. Client" << endl;
			cout << "2. Magazin" << endl;
			cout << "3. Iesire" << endl << endl;
			cout << "----------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
			cout << endl << "Introduceti cifra corespunzatoare tipului de utilizator cu care doriti sa va logati: " << endl;
			cin >> tipUtilizator;
			if (tipUtilizator == "1")
			{
				client = new Client();
				do
				{
					curataConsola();
					cout << "----------------------------------------------------------------AUTENTIFICARE CLIENT----------------------------------------------------------------------" << endl;
					cout << endl << "Nume Utilizator: ";
					string numeUtilizator = getNumeUtilizator();
					cout << "Parola: ";
					string parolaUtilizator = getParolaUtilizator();
					if (client->autentificareClient(numeUtilizator, parolaUtilizator))
					{
						afisareMeniuClient();
					}
					else
					{
						cout << endl << "Datele de autentificare introduse nu sunt valide !" << endl;
						cout << "Veti primi posibilitatea de a le introduce iar in 5 secunde !" << endl;
						for (int i = 5; i > 0; i--)
						{
							cout << i << endl;
							Sleep(1000);
						}
					}
				} while (true);
			}
			else if (tipUtilizator == "2")
			{
				do
				{
					curataConsola();
					cout << "----------------------------------------------------------------AUTENTIFICARE ADMINISTRATOR---------------------------------------------------------------" << endl;
					cout << endl << "Nume Utilizator: ";
					string numeUtilizator = getNumeUtilizator();
					cout << "Parola: ";
					string parolaUtilizator = getParolaUtilizator();
					if (magazin->autentificareMagazin(numeUtilizator, parolaUtilizator))
					{
							afisareMeniuMagazin();
					}
					else
					{
						cout << endl << "Datele de autentificare introduse nu sunt valide !" << endl;
						cout << "Veti primi posibilitatea de a le introduce iar in 5 secunde !" << endl;
						for (int i = 5; i > 0; i--)
						{
							cout << i << endl;
							Sleep(1000);
						}
					}
				} while (true);
			}
			else if (tipUtilizator == "3")
			{
				curataConsola();
				return;
			}
		}

		string getNumeUtilizator()
		{
			string numeUtilizator;
			cin >> numeUtilizator;
			return numeUtilizator;
		}

		string getParolaUtilizator()
		{
			string parolaUtilizator;
			cin >> parolaUtilizator;
			return parolaUtilizator;
		}

		void afisareMeniuClient()
		{
			curataConsola();
			cout << "---------------------------------------------------------------MENIU FUNCTIONALITATI CLIENT---------------------------------------------------------------" << endl;
			cout << endl << "1. Vizualizeaza produsele din magazin ";
			cout << endl << "2. Selecteaza si adauga produse din magazin in cosul de cumparaturi ";
			cout << endl << "3. Selecteaza si sterge produse din cosul de cumparaturi ";
			cout << endl << "4. Trimite comanda + Completare Date Personale ";
			cout << endl << "5. Generare raport privind comenzile trimise ";
			cout << endl << "6. Iesire" << endl;
			cout << endl << "----------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
			cout << endl << "Introduceti cifra corespunzatoare tipului de functionalitate pe care doriti sa il implementati: ";
			string optiuneNavigareMagazin;
			cin >> optiuneNavigareMagazin;
			curataConsola();
			if (optiuneNavigareMagazin == "1")
			{
				curataConsola();
				cout << "----------------------------------------------------------------OPTIUNE VIZUALIZARE PRODUSE---------------------------------------------------------------" << endl;
				magazin->afiseazaStoc();
				afisareMeniuClient();
			}
			else if (optiuneNavigareMagazin == "2")
			{
				int optiune;
				curataConsola();
				cout << "--------------------------------------------------------------OPTIUNE ADAUGARE PRODUSE IN COS-------------------------------------------------------------" << endl;
				cout << endl << "1. Selecteaza si adauga produse din magazin in cosul de cumparaturi ";
				cout << endl << "2. Iesire ";
				cout << endl << endl << "----------------------------------------------------------------------------------------------------------------------------------------------------------" << endl << endl;
				cout << "Introduceti cifra corespunzatoare optiunii pe care doriti sa o implementati: ";
				cin >> optiune;
				curataConsola();
				if (optiune == 1)
				{
					cout << "--------------------------------------------------------------OPTIUNE ADAUGARE PRODUSE IN COS-------------------------------------------------------------" << endl << endl;
					string numeProdus;
					cout << "Introduceti numele produsului pe care doriti sa-l adaugati in cos: ";
					cin.ignore();
					getline(cin, numeProdus);
					cout << "Introduceti cantitatea dorita din acel produs: ";
					float cantitateSelectata;
					cin >> cantitateSelectata;
					Produse* produsSelectat = nullptr;
					for (const auto& produs : magazin->produseMagazin)
					{
						if (produs->getNumeProdus() == numeProdus)
						{
							produsSelectat = produs;
							break;
						}
					}
					if (produsSelectat != nullptr && produsSelectat->getCantitateDisponibila() >= cantitateSelectata)
					{
						client->adaugaInCos(produsSelectat, cantitateSelectata);
						cout << endl << "Produsul cu numele " << "'" << numeProdus << "'" << " a fost adaugat in cos cu succes!" << endl << endl << endl;
						cout << setw(18) << "Denumire Produs" << setw(30) << "Pret Produs" << setw(30) << "Cantitate Selectata" << endl << endl;
						client->afisareCos();
					}
					else
					{
						cout << "Produsul cu numele " << "'" << numeProdus << "'" << " nu a fost gasit in magazin sau cantitatea " << cantitateSelectata << " depaseste stocul detinut de magazin !";
					}

					cout << endl << "Apasa orice tasta pentru a reveni in meniul anterior !";
					cin.ignore();
					cin.get();
					afisareMeniuClient();
				}
				else if (optiune == 2)
				{
					afisareMeniuClient();
				}

			}
			else if (optiuneNavigareMagazin == "3")
			{
				int optiune;
				curataConsola();
				cout << "--------------------------------------------------------------OPTIUNE STERGERE PRODUSE DIN COS------------------------------------------------------------" << endl;
				cout << endl << "1. Selecteaza si sterge produse din cosul de cumparaturi ";
				cout << endl << "2. Iesire";
				cout << endl << endl << "----------------------------------------------------------------------------------------------------------------------------------------------------------" << endl << endl;
				cout << "Introduceti cifra corespunzatoare optiunii pe care doriti sa o implementati: ";
				cin >> optiune;
				curataConsola();
				if (optiune == 1)
				{
					curataConsola();
					cout << "---------------------------------------------------------------OPTIUNE STERGERE PRODUSE DIN COS---------------------------------------------------------------" << endl << endl;
					cout << "Introduceti numele produsului din cos pe care doriti sa-l stergeti: ";
					string numeProdus;
					cin.ignore();
					getline(cin, numeProdus);

					float cantitate;
					cout << "Introduceti cantitatea de produs din cos pe care doriti sa o stergeti: ";
					cin >> cantitate;
					client->stergeDinCos(numeProdus, cantitate);

					cout << "Apasa orice tasta pentru a reveni la meniu !";
					cin.ignore();
					cin.get();
					afisareMeniuClient();
				}
				else if (optiune == 2)
				{
					afisareMeniuClient();
				}
			}
			else if (optiuneNavigareMagazin == "4")
			{
				int optiune;
				curataConsola();
				cout << "--------------------------------------------------------------MENIU TRIMITERE COMANDA------------------------------------------------------------" << endl;
				cout << endl << "1. Trimite Comanda ";
				cout << endl << "2. Iesire ";
				cout << endl << endl << "----------------------------------------------------------------------------------------------------------------------------------------------------------" << endl << endl;
				cout << "Introduceti cifra corespunzatoare optiunii pe care doriti sa o implementati: ";
				cin >> optiune;
				curataConsola();
				if (optiune == 1)
				{
					curataConsola();
					client->trimiteComanda();
					cout << endl;
					client->completeazaDatePersonale();
					cout << endl << "Comanda a fost trimisa cu succes !" << endl;
					cout << "Veti fi redirectionat in meniul anterior in 5 secunde!" << endl;
					for (int i = 5; i > 0; i--) {
						cout << endl << i;
						Sleep(1000);
					}
					afisareMeniuClient();
				}
				else if (optiune == 2)
				{
					afisareMeniuClient();
				}
			}
			else if (optiuneNavigareMagazin == "5")
			{
				curataConsola();
				cout << "----------------------------------------------------------------MENIU CREARE RAPORT COMENZI----------------------------------------------------------------" << endl << endl;
				cout << "Procedura de prelucrare si creare a raportului va dura 5 secunde ! ";
				ofstream raport("Raport_Comenzi_Client.txt");
				if (raport.is_open()) {

					client->generareRaportClient(raport);
					raport.close();
				}
				Sleep(5000);
				cout << "Vei fi redirectionat in meniul anterior in 5 secunde !";
				for (int i = 5; i > 0; i--)
				{
					cout << endl << i;
					Sleep(1000);
				}
				afisareMeniuClient();
			}
			
			else if (optiuneNavigareMagazin == "6")
			{
				afisareMeniu();
			}
		}
		void afisareMeniuMagazin()
		{
			curataConsola();
			int alegere;
			cout << "------------------------------------------------------------MENIU FUNCTIONALITATI ADMINISTRATOR-----------------------------------------------------------" << endl;
			cout << endl << "1. Adaugare produse in sistemul magazinului ";
			cout << endl << "2. Afisare stoc curent al magazinului ";
			cout << endl << "3. Editare produse din sistemul magazinului ";
			cout << endl << "4. Stergere produse din sistemul magazinului ";
			cout << endl << "5. Prelucrare comenzi + Generare Raport";
			cout << endl << "6. Iesire " << endl << endl;
			cout << "----------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
			cout << endl << "Introduceti cifra corespunzatoare tipului de functionalitate pe care doriti sa il implementati: ";
			cin >> alegere;
			if (alegere == 1)
			{
				curataConsola();
				cout << "------------------------------------------------------------------MENIU ADAUGARE PRODUSE------------------------------------------------------------------" << endl << endl;
				cout << "1. Adaugare produs " << endl;
				cout << "2. Iesire " << endl << endl;
				cout << "----------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
				cout << endl << "Introduceti cifra corespunzatoare optiunii pe care doriti sa o implementati: ";
				int optiune;
				cin >> optiune;
				if (optiune == 1)
				{
					string numeProdus, descriereProdus, dataFabricatie, categorie, garantie, material;
					float pretProdus, cantitateDisponibila;
					curataConsola();
					cout << "---------------------------------------------------------------OPTIUNE ADAUGARE PRODUSE---------------------------------------------------------------" << endl << endl;
					cout << "Introduceti numele produsului: ";
					cin.ignore();
					getline(cin, numeProdus);

					cout << "Introduceti descrierea produsului: ";
					getline(cin, descriereProdus);

					cout << "Introduceti data de fabricatie a produsului: ";
					getline(cin, dataFabricatie);

					cout << "Introduceti pretul produsului: ";
					cin >> pretProdus;
					
					cout << "Introduceti cantitatea disponibila din stocul de produs: ";
					cin >> cantitateDisponibila;

					cout << "Introduceti categoria de produs ( 'Electronice' / 'Mobilier' ): ";
					cin.ignore();
					getline(cin, categorie);

					if (categorie == "Electronice")
					{
						cout << "Introduceti perioada de garantie a produsului: ";
						getline(cin, garantie);
					}
					else if (categorie == "Mobilier")
					{
						cout << "Introduceti materialul din care este alcatuit produsul: ";
						getline(cin, material);
					}

					magazin->adaugaProdus(numeProdus, descriereProdus, dataFabricatie, pretProdus, cantitateDisponibila, categorie, garantie, material);
					cout << endl << "Produsul " << "'" << numeProdus << "'" << " a fost introdus cu succes !" << endl;
					cout << "Veti fi redirectionat in meniul anterior in 5 secunde !";
					for (int i = 5; i > 0; i--)
					{
						cout << endl << i;
						Sleep(1000);
					}
					afisareMeniuMagazin();

				}
				else if (optiune == 2)
				{
					afisareMeniuMagazin();
				}
			}
			else if (alegere == 2)
			{
				curataConsola();
				cout << "----------------------------------------------------------------OPTIUNE VIZUALIZARE PRODUSE---------------------------------------------------------------" << endl;
				magazin->afiseazaStoc();
				afisareMeniuMagazin();
			}
			else if (alegere == 3)
			{
				curataConsola();
				cout << "------------------------------------------------------------------MENIU EDITARE PRODUSE-------------------------------------------------------------------" << endl << endl;
				cout << "1. Editeaza produs " << endl;
				cout << "2. Iesire " << endl << endl;
				cout << "----------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
				cout << endl << "Introduceti cifra corespunzatoare optiunii pe care doriti sa o implementati: ";
				int optiune;
				cin >> optiune;
				curataConsola();
				if (optiune == 1)
				{
					cout << "----------------------------------------------------------------OPTIUNE EDITARE PRODUSE----------------------------------------------------------------" << endl << endl;
					magazin->editeazaProdus();
					cout << "Veti fi redirectionat in meniul anterior in 5 secunde !" << endl;
					for (int i = 5; i > 0; i--)
					{
						cout << i << endl;
						Sleep(1000);
					}
					afisareMeniuMagazin();
				}
				else if (optiune == 2)
				{
					afisareMeniuMagazin();
				}
			}
			else if (alegere == 4)
			{
				curataConsola();
				cout << "------------------------------------------------------------------MENIU STERGERE PRODUSE------------------------------------------------------------------" << endl << endl;
				cout << "1. Stergere produs " << endl;
				cout << "2. Iesire " << endl << endl;
				cout << "----------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
				cout << endl << "Introduceti cifra corespunzatoare optiunii pe care doriti sa o implementati: ";
				int optiune;
				cin >> optiune;
				string numeProdus;
				if (optiune == 1)
				{
					curataConsola();
					cout << "-----------------------------------------------------------------OPTIUNE STERGERE PRODUSE-----------------------------------------------------------------" << endl << endl;
					cout << "Introduceti numele produsului pe care doriti sa-l stergeti: ";
					cin.ignore();
					getline(cin, numeProdus);
					magazin->stergeProdus(numeProdus);

					cout << "Vei fi redirectionat in meniul anterior in 5 secunde !";
					for (int i = 5; i > 0; i--)
					{
						cout << endl << i;
						Sleep(1000);
					}
					afisareMeniuMagazin();
				}
				else if (optiune == 2)
				{
					afisareMeniuMagazin();
				}
			}
			else if (alegere == 5)
			{
				curataConsola();
				cout << "----------------------------------------------------------------MENIU CREARE RAPORT CLIENTI----------------------------------------------------------------" << endl << endl;
				cout << "Procedura de prelucrare si creare a raportului va dura 5 secunde ! ";
				ofstream raport("Raport_Comenzi_Magazin.txt");
				if (raport.is_open()) {

					client->generareRaportClient(raport);
					raport.close();
				}
				Sleep(5000);
				cout << "Vei fi redirectionat in meniul anterior in 5 secunde !";
				for (int i = 5; i > 0; i--)
				{
					cout << endl << i;
					Sleep(1000);
				}
				afisareMeniuMagazin();
			}
			else if (alegere == 6)
			{
				curataConsola();
				afisareMeniu();
			}
		}
	};
	
	void main()
	{
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsole, FOREGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_BLUE);
		SetConsoleScreenBufferSize(hConsole, { 100, 300 });
		int varianta;
		cout << "1. Testare Supraincarcare de Operatori" << endl;
		cout << "2. Accesare Meniu Functionalitati" << endl << endl;
		cout << "OBS 1: Odata ce alegem o optiune nu putem reveni la alta, nu am mai implementat acest lucru, deci rulati aplicatia de 2 ori, pentru verificarea ambelor optiuni !" << endl;
		cout << "OBS 2: Date Conectare Client: user1, parola1 sau user2, parola2" << endl;
		cout << "OBS 3: Date Conectare Magazin ( Administrator ): magazin1, parola1 sau magazin2, parola2" << endl;
		cout << endl << "Alegeti o varianta: " << endl;
		cin >> varianta;
		if (varianta == 1)
		{
			curataConsola();
			ProduseElectronice produsElectronic("Lenovo", "Destinat gamerilor", "15 ianuarie", 2500, 20, "10 ani", "Electronice");
			cout << endl << "Testare supraincarcare operator +=";
			produsElectronic += 100;
			cout << endl << "Pret in urma sumei: ";
			cout << produsElectronic.getPretProdus();
			cout << endl << endl << "Testare supraincarcare operator <";
			ProduseMobilier produsMobilier("Scaun gaming", "Destinat gamerilor", "20 ianuarie 2014", 800, 12, "Plastic", "Mobilier");
			cout << endl << "Cantitatea disponibila mai mica este: ";
			if (produsElectronic < produsMobilier)
				cout << produsElectronic.getCantitateDisponibila();
			else
				cout << produsMobilier.getCantitateDisponibila();
			cout << endl << endl << "Testare supraincarcare operator -";
			ProduseElectronice produsElectronic2("Samsung", "Telefon cu touchscreen", "12 martie 2022", 1500, 10, "5 ani", "Electronice");
			cout << endl << "Pret in urma diferentei: ";
			produsElectronic2 - 1000;
			cout << produsElectronic2.getPretProdus();
		}
		else
		{
			curataConsola();
			Magazin magazin;
			Meniu meniuUtilizare(&magazin);
			meniuUtilizare.afisareMeniu();
		}
	}
