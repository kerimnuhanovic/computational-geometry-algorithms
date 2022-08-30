//---------------------------------------------------------------------------

#ifndef FormaH
#define FormaH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <vector>
#include "pomocna.h"
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
	TImage *Slika;
	TButton *Prost_Poligon;
	TEdit *editBrojTacaka;
	TButton *generisiTacke;
	TButton *GiftWrapping;
	TButton *GrahamScan;
	TRadioButton *pripadnostKonveksnom;
	TRadioButton *dodavanjeTacki;
	TButton *Button1;
	TButton *sweepLineKruznice;
	TRadioButton *crtajKrugove;
	TButton *kdTree;
	TRadioButton *crtajPravougaonik;
	TButton *rangeTree;
	TButton *kruzniceSweepLineTacno;

	void __fastcall SlikaMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
		  int X, int Y);
	void __fastcall Prost_PoligonMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
		  int X, int Y);
	void __fastcall generisiTackeMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
		  int X, int Y);
	void __fastcall GiftWrappingMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
		  int X, int Y);
	void __fastcall GrahamScanMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
		  int X, int Y);
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall sweepLineKruzniceClick(TObject *Sender);
	void __fastcall kdTreeClick(TObject *Sender);
	void __fastcall rangeTreeClick(TObject *Sender);
	void __fastcall kruzniceSweepLineTacnoClick(TObject *Sender);
private:	// User declarations
	vector<Tacka> tacke;
	vector<Tacka> konveksni_omotac;
	vector<Kruznica*> kruznice;
	Tacka *pomocna;

	double pravougaonikA, pravougaonikB, pravougaonikC, pravougaonikD;
	void obidji(Cvor*);
	Cvor* napraviKDStablo(vector<Tacka> tackeX, vector<Tacka> tackeY, int brojac, double pocetakX,
					double krajX, double pocetakY, double krajY);
	void obilazakStabla(Cvor* trenutni, vector<Tacka*> &rezultat);
	void kdAlgoritam(Cvor *trenutni, int brojac, vector<Tacka*> &rezultat, double a, double b, double c
,double d);


	CvorRange* napraviRangeStablo(vector<Tacka> tackeX, vector<Tacka> tackeY);
	CvorRange* napraviYStablo(vector<Tacka> tackeY);

	void obidjiRange(CvorRange* cvor);

	void rangeAlgoritam(CvorRange* cvor, bool &puteviRazdvojeni, vector<Tacka*> &rezultat,
	double a, double b, double c, double d, bool lijeviDio);


	void RangeProvjeraPoY(vector<Tacka*> &rezultat, CvorRange* cvor, double c, double d);

	void ispisiSvaYStabla(CvorRange *cvor);


public:		// User declarations
	__fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
