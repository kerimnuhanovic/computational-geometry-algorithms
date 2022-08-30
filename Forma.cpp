//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Forma.h"
#include <queue>
#include <set>
#include <stdlib.h>
#include <time.h>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
	Slika->Canvas->FillRect(Rect(0,0,Slika->Width,Slika->Height));
	pomocna = nullptr;
	pravougaonikA = INT_MAX;

}



//---------------------------------------------------------------------------
void __fastcall TForm1::SlikaMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
		  int X, int Y)
{
	if(dodavanjeTacki-> Checked) {
		Tacka nova(X,Y);
		nova.Crtaj(Slika);
		tacke.push_back(nova);
	}
	else if(pripadnostKonveksnom-> Checked){
		Tacka A(X,Y);
		if(jeLiUKonveksnom(konveksni_omotac,A))
			ShowMessage("Tacka je u konveksnom omotacu!");
		else {
			int lijeva = -1, desna = -1;
			Tangente(konveksni_omotac,Tacka(X,Y),lijeva,desna);
			Slika->Canvas->MoveTo(X,Y);
			Slika->Canvas->LineTo(konveksni_omotac[lijeva].x,konveksni_omotac[lijeva].y);

		};
	}
	else if(crtajKrugove -> Checked) {
		if(pomocna==nullptr) {
			pomocna = new Tacka(X,Y);
		}
		else {
			Tacka druga(X,Y);
			Kruznica* k = new Kruznica(*pomocna, udaljenost(*pomocna,druga));
			kruznice.push_back(k);
			k->nacrtajKruznicu(Slika);
			pomocna = nullptr;
		}

	}
	else if(crtajPravougaonik -> Checked) {
		if(pravougaonikA == INT_MAX) {
			pravougaonikA = X;
			pravougaonikC = Y;
		}
		else {
			pravougaonikB = X;
			pravougaonikD = Y;

			Slika->Canvas->MoveTo(pravougaonikA,pravougaonikC);
			Slika->Canvas->LineTo(pravougaonikA + (pravougaonikB-pravougaonikA), pravougaonikC);


			Slika->Canvas->MoveTo(pravougaonikA + (pravougaonikB-pravougaonikA), pravougaonikC);
			Slika->Canvas->LineTo(pravougaonikB, pravougaonikD);

			Slika->Canvas->MoveTo(pravougaonikB, pravougaonikD);
			Slika->Canvas->LineTo(pravougaonikA, pravougaonikD);

			Slika->Canvas->MoveTo(pravougaonikA, pravougaonikD);
			Slika->Canvas->LineTo(pravougaonikA, pravougaonikC);

		}
	}

}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
void __fastcall TForm1::Prost_PoligonMouseDown(TObject *Sender, TMouseButton Button,
		  TShiftState Shift, int X, int Y)
{

	for(int i = 1; i < tacke.size(); i++) {
		if(tacke[i] < tacke[0]) {
			swap(tacke[0],tacke[i]);
		}
	}

	Tacka najmanja = tacke[0];
	sort(tacke.begin()+1,tacke.end(), [najmanja] (Tacka A, Tacka B)->bool {
		if(orijentacija(najmanja, A, B) == 1) return true;
		return false;

	});

	iscrtajMnogougao(tacke, Slika);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::generisiTackeMouseDown(TObject *Sender, TMouseButton Button,
		  TShiftState Shift, int X, int Y)
{
	int brojTacaka = editBrojTacaka->Text.ToInt();
	for(int i = 0; i < brojTacaka; i++) {
		Tacka t(rand() % Slika->Width,rand() % Slika->Height);
		tacke.push_back(t);
		t.Crtaj(Slika);
	}
}
//---------------------------------------------------------------------------
void __fastcall TForm1::GiftWrappingMouseDown(TObject *Sender, TMouseButton Button,
		  TShiftState Shift, int X, int Y)
{
	//naci ekstremnu tacku (u nasem slucaju tacka sa najmanjom x koordinatom)
	Tacka najmanja = tacke[0];
	for(int i = 1; i < tacke.size(); i++) {
		if(tacke[i] < najmanja)
			najmanja = tacke[i];
	}

	konveksni_omotac.push_back(najmanja);
	int n = tacke.size();

	while(true) {
		Tacka zadnja = konveksni_omotac[konveksni_omotac.size()-1];
		int indeks_nove = 0;
		if(zadnja == tacke[indeks_nove]) {
			indeks_nove = 1;
		}
		for(int i = 2; i < n; i++) {
			if(orijentacija(zadnja, tacke[indeks_nove], tacke[i]) < 0) {
				indeks_nove = i;
			}
		}

		if(tacke[indeks_nove] == najmanja)
			break;

		konveksni_omotac.push_back(tacke[indeks_nove]);


	}
	iscrtajMnogougao(konveksni_omotac, Slika);

}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------

void __fastcall TForm1::GrahamScanMouseDown(TObject *Sender, TMouseButton Button,
		  TShiftState Shift, int X, int Y)
{
	for(int i = 1; i < tacke.size(); i++) {
		if(tacke[i] < tacke[0]) {
			swap(tacke[i], tacke[0]);
		}
	}
	Tacka najmanja = tacke[0];
	sort(tacke.begin()+1, tacke.end(), [najmanja] (Tacka A, Tacka B) -> bool {
	   if(orijentacija(najmanja, A, B) > 0) return true; return false;
	});

	konveksni_omotac.push_back(tacke[0]);
	konveksni_omotac.push_back(tacke[1]);
	for(int i = 2; i <  tacke.size(); i++) {
		Tacka predzadnja = konveksni_omotac[konveksni_omotac.size()-2];
		Tacka zadnja = konveksni_omotac[konveksni_omotac.size()-1];
		while(orijentacija(predzadnja,zadnja,tacke[i]) < 0) {
			konveksni_omotac.pop_back();
			zadnja = predzadnja;
			predzadnja = konveksni_omotac[konveksni_omotac.size()-2];

		}
		konveksni_omotac.push_back(tacke[i]);
	}
	iscrtajMnogougao(konveksni_omotac, Slika);

}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button1Click(TObject *Sender)
{
	srand (time(NULL));
	int brojKruznica = editBrojTacaka->Text.ToInt();
	for(int i = 0; i < brojKruznica; i++) {
		Tacka t(70+rand() % (Slika->Width-140),70+rand() % (Slika->Height-140));
		double radius = 1+rand() % 3;
		Kruznica* k = new Kruznica(t,radius);
		kruznice.push_back(k);
		k->nacrtajKruznicu(Slika);
		/*ShowMessage(k->centar.x);
		ShowMessage(k->centar.y);
		ShowMessage(Slika->Width);  */
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::sweepLineKruzniceClick(TObject *Sender)
{
	priority_queue<pair<pair<bool, Tacka>,Kruznica*>,
	vector<pair<pair<bool, Tacka>,Kruznica*>>,KruznicePoX> eventi; //proslijedit kriterij


	for(int i = 0; i < kruznice.size(); i++) {
		Tacka pocetna(kruznice[i]->centar.x-kruznice[i]->r,kruznice[i]->centar.y);
		eventi.push({{0,pocetna}, kruznice[i]});
		Tacka krajnja(kruznice[i]->centar.x+kruznice[i]->r,kruznice[i]->centar.y);
		eventi.push({{1, krajnja}, kruznice[i]});
	}

	set<pair<Tacka, Kruznica*>, TackePoY> aktivne;        // proslijedit kriterij
	while(!eventi.empty()) {
		auto trenutni = eventi.top();
		eventi.pop();
		Tacka gornja(trenutni.second->centar.x,trenutni.second->centar.y-trenutni.second->r);
		Tacka donja(trenutni.second->centar.x, trenutni.second->centar.y+trenutni.second->r);
		if(trenutni.first.first == 0) {

			auto par1 = aktivne.insert({gornja, trenutni.second});
			auto par2 = aktivne.insert({donja, trenutni.second});

			auto it_gornja = par1.first;
			auto it_donja = par2.first;


			auto prethodni_gornja = it_gornja;
			auto sljedeci_gornja = it_gornja;
			sljedeci_gornja++;
			auto prethodni_donja = it_donja;
			auto sljedeci_donja = it_donja;
			prethodni_donja--;


			if(it_gornja != aktivne.begin()) {
				prethodni_gornja--;
				if(daLiSeSijekuKruznice(trenutni.second, (*prethodni_gornja).second)) {
					ShowMessage("Postoji presjek!");
					return;
				}
			}
			if((*sljedeci_gornja).second != trenutni.second) {
				if(daLiSeSijekuKruznice(trenutni.second, (*sljedeci_gornja).second)) {
					ShowMessage("Postoji presjek!");
					return;
				}
			}


			if((*prethodni_donja).second != trenutni.second) {
				if(daLiSeSijekuKruznice(trenutni.second, (*prethodni_donja).second)) {
					ShowMessage("Postoji presjek!");
					return;
				}
			}

			if(it_donja != (--aktivne.end())) {
				sljedeci_donja++;
				if(daLiSeSijekuKruznice(trenutni.second, (*sljedeci_donja).second)) {
					ShowMessage("Postoji presjek!");
					return;
				}
			}


		}
		else {

			aktivne.erase({gornja, trenutni.second});
			aktivne.erase({donja, trenutni.second});
		}
	}
	ShowMessage("Ne postoji presjek!");

}
//---------------------------------------------------------------------------

void __fastcall TForm1::kdTreeClick(TObject *Sender)
{
	vector<Tacka> tackeX;
	vector<Tacka> tackeY;
	for (int i = 0; i < tacke.size(); i++) {
		tackeX.push_back(tacke[i]);
		tackeY.push_back(tacke[i]);
	}
	/*
	sort(tackeX.begin(), tackeX.end(), kdTackePoX);

	sort(tackeY.begin(), tackeY.end(), kdTackePoY);
	  */
      sort(tackeX.begin(), tackeX.end(), [] (Tacka A, Tacka B) -> bool {
	   if(A.x <= B.x) return true; else return false;
	});

	sort(tackeY.begin(), tackeY.end(), [] (Tacka A, Tacka B) -> bool {
	  if(A.y <= B.y) return true; else return false;
	});
	Cvor *korijen = napraviKDStablo(tackeX, tackeY, 0, INT_MIN, INT_MAX, INT_MIN, INT_MAX);



	vector<Tacka*> rezultat;
	kdAlgoritam(korijen, 0,rezultat, pravougaonikA, pravougaonikB, pravougaonikC,
	pravougaonikD);

	//ShowMessage(rezultat.size());
	for(int i = 0; i < rezultat.size(); i++) {
		Slika->Canvas->Brush->Color = clRed;
		Slika->Canvas->Brush->Style = bsSolid;
		Slika->Canvas->Ellipse(Rect(rezultat[i]->x-3,rezultat[i]->y-3,rezultat[i]->x+3,rezultat[i]->y+3));
	}


}


void TForm1::obidji(Cvor* cvor) {
	static int brojac = 0;
	if(cvor == nullptr)
		return;

	if(cvor->tacka != nullptr) {
		ShowMessage(cvor->tacka->x);
		ShowMessage(cvor->tacka->y);
	}

	obidji(cvor->ld);
	obidji(cvor->dd);

}


Cvor* TForm1::napraviKDStablo(vector<Tacka> tackeX, vector<Tacka> tackeY, int brojac, double pocetakX,
					double krajX, double pocetakY, double krajY) {
	if(tackeX.size() == 1) {

		Tacka* p = new Tacka(tackeX[0].x, tackeX[0].y);
		Cvor* trenutni = new Cvor(pocetakX, krajX, pocetakY, krajY, p, nullptr, nullptr, p->x);
		//posljednji aribut u prethodnom redu nebitan jer smo dosli do tacke, pa je postavljen na p->x
		return trenutni;
	}



	//X nivo
	if(brojac % 2 == 0) {
		Tacka srednji = tackeX[tackeX.size()/2];
		vector<Tacka> tackeXLijevo;
		vector<Tacka> tackeYLijevo;

		vector<Tacka> tackeXDesno;
		vector<Tacka> tackeYDesno;
		for(int i = 0; i < tackeX.size(); i++) {
			if(tackeX[i].x < srednji.x)
				tackeXLijevo.push_back(tackeX[i]);
			else if(tackeX[i].x == srednji.x && tackeX[i].y != srednji.y) {
				tackeXLijevo.push_back(tackeX[i]);
			}
			else tackeXDesno.push_back(tackeX[i]);
			if(tackeY[i].x < srednji.x)
				tackeYLijevo.push_back(tackeY[i]);
			else if(tackeY[i].x == srednji.x && tackeY[i].y != srednji.y) {
				tackeYLijevo.push_back(tackeY[i]);
			}
			else tackeYDesno.push_back(tackeY[i]);
		}

		Cvor *trenutni = new Cvor(pocetakX, krajX, pocetakY, krajY, nullptr, nullptr, nullptr,
		srednji.x);

		trenutni->ld = napraviKDStablo(tackeXLijevo, tackeYLijevo, brojac+1, pocetakX, srednji.x,
		pocetakY, krajY);

		trenutni->dd = napraviKDStablo(tackeXDesno, tackeYDesno, brojac+1, srednji.x, krajX,pocetakY,
		krajY);

		return trenutni;
	}
	else {
		Tacka srednji = tackeY[tackeY.size()/2];
		vector<Tacka> tackeXLijevo;
		vector<Tacka> tackeYLijevo;

		vector<Tacka> tackeXDesno;
		vector<Tacka> tackeYDesno;
		for(int i = 0; i < tackeY.size(); i++) {
			if(tackeX[i].y < srednji.y)
				tackeXLijevo.push_back(tackeX[i]);
			else if(tackeX[i].y == srednji.y && tackeX[i].x != srednji.x) {
				tackeXLijevo.push_back(tackeX[i]);
			}
			else tackeXDesno.push_back(tackeX[i]);
			if(tackeY[i].y < srednji.y)
				tackeYLijevo.push_back(tackeY[i]);
			else if(tackeY[i].y == srednji.y && tackeY[i].x != srednji.x) {
				tackeYLijevo.push_back(tackeY[i]);
			}
			else tackeYDesno.push_back(tackeY[i]);
		}

		Cvor *trenutni = new Cvor(pocetakX, krajX, pocetakY, krajY, nullptr, nullptr, nullptr,
		srednji.y);

		trenutni->ld = napraviKDStablo(tackeXLijevo, tackeYLijevo, brojac+1, pocetakX, krajX,
		pocetakY, srednji.y);

		trenutni->dd = napraviKDStablo(tackeXDesno, tackeYDesno, brojac+1, pocetakX, krajX,srednji.y,
		krajY);

		return trenutni;



	}





}

void TForm1::obilazakStabla(Cvor* trenutni, vector<Tacka*> &rezultat) {
	if(trenutni == nullptr)
		return;
	if(trenutni->tacka != nullptr) {
		rezultat.push_back(trenutni->tacka);

	}
	obilazakStabla(trenutni->ld, rezultat);
	obilazakStabla(trenutni->dd, rezultat);
}



void TForm1::kdAlgoritam(Cvor *trenutni, int brojac, vector<Tacka*> &rezultat, double a, double b, double c
,double d) {


	if(trenutni->tacka != nullptr) {

		if(trenutni->tacka->x >= a && trenutni->tacka->x <= b && trenutni->tacka->y >= c
		   && trenutni->tacka->y <= d)  {
		   rezultat.push_back(trenutni->tacka);
		   }
		return;
	}

	if(trenutni->px >= a && trenutni->kx <= b and trenutni->py >= c && trenutni->ky <= d) {

		obilazakStabla(trenutni, rezultat);
	}
	if(brojac % 2 == 0) {
		if(a >= trenutni -> srednji) {
			//ShowMessage("Odoh desno");
			kdAlgoritam(trenutni->dd, brojac+1, rezultat, a, b, c,d);
		 }
		 else if(b <= trenutni->srednji) {
			 //ShowMessage("Odoh lijevo");
			 kdAlgoritam(trenutni->ld, brojac+1, rezultat, a, b, c,d);

		 }
		 else {

			//ShowMessage("Odoh i desno i lijevo");
			kdAlgoritam(trenutni->dd, brojac+1, rezultat, trenutni->srednji, b, c,d);
			kdAlgoritam(trenutni->ld, brojac+1, rezultat, a, trenutni->srednji, c,d);

		 }
	}
	else {
		if(c >= trenutni -> srednji) {

			//ShowMessage("Odoh gore");
			kdAlgoritam(trenutni->dd, brojac+1, rezultat, a, b, c,d);
		 }
		 else if(d <= trenutni->srednji) {

			//ShowMessage("Odoh dole");
			 kdAlgoritam(trenutni->ld, brojac+1, rezultat, a, b, c,d);

		 }
		 else {

			//ShowMessage("Odoh i dole i gore");
			kdAlgoritam(trenutni->dd, brojac+1, rezultat, a, b, trenutni->srednji,d);
			kdAlgoritam(trenutni->ld, brojac+1, rezultat, a, b, c,trenutni->srednji);

		 }
	}
}



//---------------------------------------------------------------------------

void __fastcall TForm1::rangeTreeClick(TObject *Sender)
{
	vector<Tacka> tackeX;
	vector<Tacka> tackeY;


	for (int i = 0; i < tacke.size(); i++) {
		tackeX.push_back(tacke[i]);
		tackeY.push_back(tacke[i]);
	}
	sort(tackeX.begin(), tackeX.end(), [] (Tacka A, Tacka B) -> bool {
	   if(A.x <= B.x) return true; else return false;
	});

	sort(tackeY.begin(), tackeY.end(), [] (Tacka A, Tacka B) -> bool {
	  if(A.y <= B.y) return true; else return false;
	});

	//ShowMessage(tackeX.size()+tackeY.size());
	CvorRange* korijen = napraviRangeStablo(tackeX, tackeY);
	//ShowMessage("Stablo napravljeno");
	vector<Tacka*> rezultat;
	bool puteviRazdvojeni = false;
	rangeAlgoritam(korijen, puteviRazdvojeni, rezultat, pravougaonikA, pravougaonikB, pravougaonikC,
	pravougaonikD, false);

	for(int i = 0; i < rezultat.size(); i++) {
		Slika->Canvas->Brush->Color = clRed;
		Slika->Canvas->Brush->Style = bsSolid;
		Slika->Canvas->Ellipse(Rect(rezultat[i]->x-3,rezultat[i]->y-3,rezultat[i]->x+3,rezultat[i]->y+3));
	}


}


void TForm1::obidjiRange(CvorRange* cvor) {
	if(cvor == nullptr)
		return;
	obidjiRange(cvor->ld);
	if(cvor->ld == nullptr)
		ShowMessage(cvor->srednji);
	obidjiRange(cvor->dd);
}


CvorRange* TForm1::napraviRangeStablo(vector<Tacka> tackeX, vector<Tacka> tackeY) {

	if(tackeX.size() == 1) {
		Tacka *nova = new Tacka(tackeX[0].x,tackeX[0].y);
		CvorRange* trenutni = new CvorRange(tackeX[0].x, nullptr, nullptr, nullptr, nova);
		return trenutni;
	}


	Tacka srednji = tackeX[tackeX.size()/2-1];
	vector<Tacka> lijevoX;
	vector<Tacka> lijevoY;

	vector<Tacka> desnoX;
	vector<Tacka> desnoY;

	for(int i = 0; i < tackeX.size(); i++) {
		if(tackeX[i].x < srednji.x) {
			lijevoX.push_back(tackeX[i]);
		}
		else if(tackeX[i].x == srednji.x and tackeX[i].y == srednji.y) {
			lijevoX.push_back(tackeX[i]);
		}
		else desnoX.push_back(tackeX[i]);
		if(tackeY[i].x < srednji.x) {
			lijevoY.push_back(tackeY[i]);
		}
		else if(tackeY[i].x == srednji.x && tackeY[i].y == srednji.y) {
			lijevoY.push_back(tackeY[i]);
		}
		else desnoY.push_back(tackeY[i]);
	}

	CvorRange *trenutni = new CvorRange(srednji.x, nullptr, nullptr, nullptr,nullptr);
	//ShowMessage(tackeY.size());
	trenutni->stabloY = napraviYStablo(tackeY);
	//ShowMessage("Napravljeno y stablo");
	trenutni->ld  = napraviRangeStablo(lijevoX, lijevoY);
	trenutni->dd = napraviRangeStablo(desnoX, desnoY);

	return trenutni;


}


CvorRange* TForm1::napraviYStablo(vector<Tacka> tackeY) {

	if(tackeY.size() == 1) {
		//ShowMessage("USAO kod keca u y stablu");
		Tacka *nova = new Tacka(tackeY[0].x, tackeY[0].y);
		CvorRange* trenutni = new CvorRange(tackeY[0].y, nullptr,nullptr,nullptr, nova);
		return trenutni;
	}


	Tacka srednji = tackeY[tackeY.size()/2-1];

	vector<Tacka> lijevoY;


	vector<Tacka> desnoY;

	for(int i = 0; i < tackeY.size(); i++) {
		if(tackeY[i].y < srednji.y) {
			lijevoY.push_back(tackeY[i]);
		}
		else if(tackeY[i].y == srednji.y and tackeY[i].x == srednji.x) {

			lijevoY.push_back(tackeY[i]);
		}
		else desnoY.push_back(tackeY[i]);
	}



	CvorRange* trenutni = new CvorRange(srednji.y, nullptr, nullptr, nullptr, nullptr);


	trenutni->ld = napraviYStablo(lijevoY);

	trenutni->dd = napraviYStablo(desnoY);
	return trenutni;
}

void TForm1::rangeAlgoritam(CvorRange* cvor, bool &puteviRazdvojeni, vector<Tacka*> &rezultat,
	double a, double b, double c, double d, bool lijeviDio) {

	if(cvor->tacka != nullptr) {
		if(cvor->tacka->x >= a and cvor->tacka->x <= b and cvor->tacka->y >= c and cvor->tacka->y <=d)
			rezultat.push_back(cvor->tacka);
		return;
	}
	//ShowMessage("Prosao");
	if(!puteviRazdvojeni) {
		if(a <= cvor->srednji and b >= cvor->srednji) {
			puteviRazdvojeni = true;
			rangeAlgoritam(cvor->ld, puteviRazdvojeni, rezultat, a,b,c,d,true);
			rangeAlgoritam(cvor->dd, puteviRazdvojeni, rezultat, a,b,c,d,false);
		}
		else if(a > cvor->srednji) {

			rangeAlgoritam(cvor->dd, puteviRazdvojeni, rezultat, a,b,c,d,lijeviDio);
		}
		else if(b <= cvor->srednji) {

			rangeAlgoritam(cvor->ld, puteviRazdvojeni, rezultat, a,b,c,d,lijeviDio);
		}
	}
	else {
		if(lijeviDio) {
			if(a <= cvor->srednji) {
				RangeProvjeraPoY(rezultat, cvor->dd, c,d);
				rangeAlgoritam(cvor->ld, puteviRazdvojeni, rezultat, a,b,c,d, true);
			}
			else rangeAlgoritam(cvor->dd, puteviRazdvojeni, rezultat, a,b,c,d, true);
		}
		else {
			if(b > cvor->srednji) {
				RangeProvjeraPoY(rezultat, cvor->ld, c,d);
				rangeAlgoritam(cvor->dd, puteviRazdvojeni, rezultat, a,b,c,d, false);
			}
			else rangeAlgoritam(cvor->ld, puteviRazdvojeni, rezultat, a,b,c,d, false);

		}

	}

}

void TForm1::RangeProvjeraPoY(vector<Tacka*> &rezultat, CvorRange* cvor, double c, double d) {
	if(cvor->tacka != nullptr) {
		if(cvor->tacka->y >= c && cvor->tacka->y <= d) {
			rezultat.push_back(cvor->tacka);
		}
		return;

	}
	RangeProvjeraPoY(rezultat, cvor->ld, c,d);
	RangeProvjeraPoY(rezultat, cvor->dd, c,d);
}



void TForm1::ispisiSvaYStabla(CvorRange *cvor) {
	if(cvor->tacka != nullptr) {
		return;
	}

	obidjiRange(cvor->stabloY);
	ispisiSvaYStabla(cvor->ld);
	ispisiSvaYStabla(cvor->dd);
}

//---------------------------------------------------------------------------


void __fastcall TForm1::kruzniceSweepLineTacnoClick(TObject *Sender)
{
   priority_queue<pair<pair<bool, Tacka>,Kruznica*>,
	vector<pair<pair<bool, Tacka>,Kruznica*>>,KruznicePoX> eventi;


	for(int i = 0; i < kruznice.size(); i++) {
		Tacka pocetna(kruznice[i]->centar.x-kruznice[i]->r,kruznice[i]->centar.y);
		eventi.push({{0,pocetna}, kruznice[i]}); // dodaje se "početna tačka"
		Tacka krajnja(kruznice[i]->centar.x+kruznice[i]->r,kruznice[i]->centar.y);
		eventi.push({{1, krajnja}, kruznice[i]}); // dodaje se "krajnja tačka"

	}

	set<pair<Tacka, pair<bool, Kruznica*>>, KruzniceKriterij> aktivne;
	while(!eventi.empty()) {
		auto trenutni = eventi.top();
		eventi.pop();
		if(trenutni.first.first == 0) {

			auto par1 = aktivne.insert({trenutni.first.second,{0,trenutni.second}});  //gornja polu
			auto par2 = aktivne.insert({trenutni.first.second,{1,trenutni.second}});  //donja polu




			auto it_gornja = par1.first;
			auto it_donja = par2.first;


			auto prethodni_gornja = it_gornja;
			auto sljedeci_gornja = it_gornja;
			sljedeci_gornja++;
			auto prethodni_donja = it_donja;
			auto sljedeci_donja = it_donja;
			prethodni_donja--;


			if(it_gornja != aktivne.begin()) { // ukoliko dodana gornja polukruznica ima
				//prethodnika, provjerimo sa prethodnikom da li se sijece
				prethodni_gornja--;
				if(daLiSeSijekuKruznice(trenutni.second, (*prethodni_gornja).second.second)) {
					ShowMessage("Postoji presjek!");
					return;
				}
			}
			if((*sljedeci_gornja).second.second != trenutni.second) {
				// ovdje se vrsi poredjenje sa sljedbenikom od gornje
				// pošto će sljedbenik gornje pri umetanju uvijek biti njena odgovarajuća
				// donja polukruznica, ova provjera nije potrebna, ostalo iz prethodno uradjenog
				// algoritma
				if(daLiSeSijekuKruznice(trenutni.second, (*sljedeci_gornja).second.second)) {
					ShowMessage("Postoji presjek!");
					return;
				}
			}


			if((*prethodni_donja).second.second != trenutni.second) {
				//analogno iznad napisanom komentaru samo za donju polu, njena prethodna
				// pri umetanju je uvijek njena odgovarajuča gornja polukruznica
				if(daLiSeSijekuKruznice(trenutni.second, (*prethodni_donja).second.second)) {
					ShowMessage("Postoji presjek!");
					return;
				}
			}

			if(it_donja != (--aktivne.end())) {
				//ako donjapolukruznica ima sljedbenika, provjeramo da li se siječe sa idućim
				sljedeci_donja++;
				if(daLiSeSijekuKruznice(trenutni.second, (*sljedeci_donja).second.second)) {
					ShowMessage("Postoji presjek!");
					return;
				}
			}


		}
		else {
			Tacka pocetna(trenutni.second->centar.x-trenutni.second->r, trenutni.second->centar.y);
			auto it1 = aktivne.find({pocetna,{0,trenutni.second}});


			auto it2 = aktivne.find({pocetna,{1,trenutni.second}});


			// provjere presjeka između eventualno novonastalih susjeda
			// pri brisanju
			auto it1prethodni = it1;
			auto it1sljedeci = it1;

			auto it2prethodni = it2;
			auto it2sljedeci = it2;

			if(it1 != aktivne.begin()) {
				it1prethodni--;
				it1sljedeci++;
				if(daLiSeSijekuKruznice(it1prethodni->second.second, it1sljedeci->second.second)) {
					ShowMessage("Postoji presjek");
					return;
				}
			}

			if(it2 != (--aktivne.end())) {
				it2prethodni--;
				it2sljedeci++;
				if(daLiSeSijekuKruznice(it2prethodni->second.second, it2sljedeci->second.second)) {
					ShowMessage("Postoji presjek");
					return;
				}
			}
			aktivne.erase(it1);
			aktivne.erase(it2);



		}
	}
	ShowMessage("Ne postoji presjek!");

}
//---------------------------------------------------------------------------

