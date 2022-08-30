//---------------------------------------------------------------------------

#ifndef pomocnaH
#define pomocnaH

#include <algorithm>
#include <vector>
using namespace std;


struct Tacka {
	double x,y;
	Tacka(double x = 0, double y = 0):x(x),y(y) {}
	void Crtaj(TImage*);
};

bool operator<(Tacka A, Tacka B);
bool operator==(Tacka,Tacka);

struct Duz {
	Tacka A, B;
	Duz(Tacka C, Tacka D):A(C),B(D) {
		if(B < A) swap(A,B);
	}
};


struct Kruznica {
	Tacka centar;
	double r;
	Kruznica(Tacka a, double r1):r(r1), centar(a) {}
	void nacrtajKruznicu(TImage* slika) {

		//liniju ispod ukljuciti priliko crtanja krugova
		slika->Canvas->Brush->Style = bsClear;
		slika->Canvas->Ellipse(Rect(centar.x-r,centar.y-r,centar.x+r,centar.y+r));

	}
};


struct KruznicePoX {
	bool operator() (pair<pair<bool, Tacka>,Kruznica*> prva, pair<pair<bool, Tacka>,Kruznica*> druga)
	 const {
		if(prva.first.second.x < druga.first.second.x)
			return false;
		return true;
	}
};

struct TackePoY {
	bool operator() (pair<Tacka, Kruznica*> prva, pair<Tacka,Kruznica*> druga) const {
		if(prva.first.y < druga.first.y)
			return true;
		return false;
	}
};


int orijentacija(Tacka A, Tacka B, Tacka C);
bool daLiSeSijeku(Duz p, Duz q);
void iscrtajMnogougao(vector<Tacka>, TImage*);

bool jeLiUTrouglu(Tacka A, Tacka B, Tacka C, Tacka P);
bool jeLiUKonveksnom(vector<Tacka> &konveksni, Tacka A);
void Tangente(vector<Tacka> &konveksni, Tacka A, int &lijeva, int &desna);

double udaljenost(Tacka A, Tacka B);
bool daLiSeSijekuKruznice(Kruznica* prva, Kruznica* druga);







struct KruzniceKriterij {
	bool operator() (pair<Tacka, pair<bool, Kruznica*>> prva, pair<Tacka, pair<bool, Kruznica*>> druga) const {

		if(druga.second.second == prva.second.second) { //ako polukruznice pripadaju istoj kruznici
			if(druga.second.first <= prva.second.first) { // gornja ide ispred donje u stablu

				return false;
			}
			else {


			return true;
			}
		}
		double presjekY;
		if(prva.first.x > druga.first.x) { //prva iza druge po x
			if(druga.second.first == 0) {
			// ako je prvu poredimo sa gornjom polukruznicom presjecnu tacku uzimamo sa minusom
			//ispred korijena
			// u suprotnom sa +
			presjekY = - sqrt(druga.second.second->r*druga.second.second->r -
							(prva.first.x-druga.second.second->centar.x)*(prva.first.x-druga.second.second->centar.x))
							+ druga.second.second->centar.y;

			}
			else if(druga.second.first == 1) {

					presjekY = +sqrt(druga.second.second->r*druga.second.second->r -
									(prva.first.x-druga.second.second->centar.x)*(prva.first.x-druga.second.second->centar.x))
									+ druga.second.second->centar.y;
			}
			Tacka t(prva.first.x, presjekY);
			if(orijentacija(druga.first,t, prva.first) > 0) {

				return true;
			}
			else {

				return false;
			}
		}
		else {
			if(prva.second.first == 0) {

				presjekY = - sqrt(prva.second.second->r*prva.second.second->r -
							(druga.first.x-prva.second.second->centar.x)*(druga.first.x-prva.second.second->centar.x))
							+ prva.second.second->centar.y;

			}
			else if(prva.second.first == 1) {

					presjekY = +sqrt(prva.second.second->r*prva.second.second->r -
									(druga.first.x-prva.second.second->centar.x)*(druga.first.x-prva.second.second->centar.x))
									+ prva.second.second->centar.y;
				}
			Tacka t(druga.first.x, presjekY);
			if(orijentacija(prva.first,t, druga.first) > 0) {

				return false;
			}
			else {

				return true;
			}

		}


	}
};

struct Cvor {
	double px, kx, py, ky;
	Tacka *tacka;
	Cvor* ld;
	Cvor* dd;
	double srednji;
	Cvor(double px, double kx, double py, double ky, Tacka* tacka,
		 Cvor* ld, Cvor* dd, double srednji): px(px), kx(kx), py(py), ky(ky), tacka(tacka), ld(ld),
		 dd(dd), srednji(srednji) {}

};
   /*
struct KDTackePoX {
	bool operator() (Tacka prva, Tacka druga) {
		if(prva.x < druga.x)
			return true;
		else return false;
	}
} kdTackePoX;

struct KDTackePoY {
	bool operator() (Tacka prva, Tacka druga) const {
		if(prva.y < druga.y)
			return true;
		else return false;
	}
} kdTackePoY;
	 */
struct CvorRange {
	double srednji;
	CvorRange* stabloY;
	CvorRange* ld;
	CvorRange* dd;
	Tacka* tacka;

	CvorRange(double srednji, CvorRange* stabloY = nullptr, CvorRange* ld=nullptr,
	CvorRange* dd=nullptr, Tacka* tacka=nullptr): srednji(srednji),
	stabloY(stabloY), ld(ld), dd(dd), tacka(tacka) {};
};

//---------------------------------------------------------------------------
#endif
