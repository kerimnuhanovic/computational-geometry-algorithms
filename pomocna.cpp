//---------------------------------------------------------------------------

#pragma hdrstop

#include "pomocna.h"

#include <math.h>



bool operator<(Tacka A, Tacka B) {
	if(A.x < B.x) return true;
	else if(A.x == B.x) return A.y < B.y;
	return false;
}

bool operator==(Tacka A, Tacka B) {
	return abs(A.x - B.x) <= 0.000001 and abs(A.y - B.y) <= 0.000001;

}

int orijentacija(Tacka A, Tacka B, Tacka C) {
	double P = A.x*(B.y - C.y) + B.x*(C.y - A.y) + C.x*(A.y - B.y);
	if(P > 0) return -1;
	else if(P < 0) return 1;
	else return 0;
}


bool daLiSeSijeku(Duz p, Duz q) {
	return (orijentacija(p.A,p.B,q.A) != orijentacija(p.A,p.B,q.B) and
	 orijentacija(q.A,q.B,p.A) != orijentacija(q.A,q.B,p.B));
}

void Tacka::Crtaj(TImage* slika) {
	slika->Canvas->Brush->Color = clBlack;
	slika->Canvas->Ellipse(Rect(x-3,y-3,x+3,y+3));
}


void iscrtajMnogougao(vector<Tacka> A, TImage *slika) {
	slika->Canvas->MoveTo(A[A.size()-1].x,A[A.size()-1].y);
	for(int i = 0; i < A.size(); i++) {
		slika->Canvas->LineTo(A[i].x,A[i].y);
	}

}

bool jeLiUTrouglu(Tacka A, Tacka B, Tacka C, Tacka P) {
	return (orijentacija(A,B,P) == orijentacija(B,C,P) &&
			orijentacija(B,C,P) == orijentacija(C,A,P));
}

bool jeLiUKonveksnom(vector<Tacka> &konveksni, Tacka A) {
	int pocetak = 1, kraj = konveksni.size()-1;
	while(kraj-pocetak > 1) {
		int srednji = (pocetak+kraj) / 2;
		if(orijentacija(konveksni[0],konveksni[srednji], A) < 0 )
			kraj = srednji;
		else pocetak = srednji;
	}
	return jeLiUTrouglu(konveksni[0],konveksni[pocetak],konveksni[kraj],A);
}



void Tangente(vector<Tacka> &konveksni, Tacka A, int &lijeva, int &desna) {
	int n = konveksni.size();
	int pocetak = 0, kraj = konveksni.size();
	while(kraj - pocetak > 1) {
		int srednji = (pocetak+kraj) / 2;
		if(orijentacija(A,konveksni[srednji],konveksni[(srednji+1)%n]) < 0 &&  orijentacija(A,konveksni[srednji],konveksni[(srednji-1+n)%n]) < 0) {
			lijeva = srednji;
			break;
		}
		if(orijentacija(A,konveksni[srednji],konveksni[(srednji+1)%n]) < 0) {
			if(orijentacija(A,konveksni[srednji],konveksni[pocetak]) < 0 || orijentacija(A,konveksni[pocetak],konveksni[(pocetak-1+n)%n] < 0))
				kraj = srednji - 1;
			else pocetak = srednji + 1;
		}
		else {
			if(orijentacija(A,konveksni[srednji],konveksni[kraj]) < 0 || orijentacija(A,konveksni[kraj],konveksni[(kraj+1)%n]) < 0)
				pocetak = srednji + 1;
			else kraj = srednji - 1;
		}
	}
	if (lijeva == - 1) {
		if(kraj == pocetak)
			lijeva = kraj;
		else {
			if(orijentacija(A,konveksni[pocetak],konveksni[(pocetak+1)%n]) < 0 &&  orijentacija(A,konveksni[pocetak],konveksni[(pocetak-1+n)%n]) < 0) {
				lijeva = pocetak;
			}
			else lijeva = kraj;

		}
	}
}




double udaljenost(Tacka A, Tacka B) {
	return sqrt((A.x-B.x)*(A.x-B.x) + (A.y - B.y)*(A.y-B.y));
}

bool daLiSeSijekuKruznice(Kruznica* prva, Kruznica* druga) {
	if(prva == druga)
        return false;
	double min_r = min(prva->r, druga->r);
	double max_r = max(prva->r, druga->r);
	if(udaljenost(prva->centar, druga->centar) + min_r <= max_r) //provjera da li je krug unutar kruga
		return false;
	if(udaljenost(prva->centar, druga->centar) <= prva->r+druga->r)
		return true;
	return false;

}


//---------------------------------------	------------------------------------
#pragma package(smart_init)
