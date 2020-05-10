#include <iostream>
#include<queue>
#include<stack>
using namespace std;
struct nyja {
	int vlera;
	nyja* majtas;
	nyja* djathtas;
};
class pema_binare_e_kerkimit {
public:
	nyja* rrenja = NULL;
	int numri_vlerava;

	nyja* nyje_e_re(int _vlera) {
		nyja* n = new nyja();
		n->vlera = _vlera;
		n->majtas = NULL;
		n->djathtas = NULL;
		numri_vlerava = numri_vlerava + 1;
		return n;
	}

	nyja* shto(nyja* _nyja_fillestare, int _vlera) {
		if (_nyja_fillestare == NULL) {
			_nyja_fillestare = this->nyje_e_re(_vlera);
		}
		else if (_nyja_fillestare->vlera == _vlera) {
			cout << "Vlera " << _vlera << " nuk mund te shtohet, pasi ajo gjendet ne peme.\n";
		}
		else if (_vlera <= _nyja_fillestare->vlera) {
			_nyja_fillestare->majtas = shto(_nyja_fillestare->majtas, _vlera);
		}
		else {
			_nyja_fillestare->djathtas = shto(_nyja_fillestare->djathtas, _vlera);
		}
		return _nyja_fillestare;
	}

	nyja* kerko(nyja* _nyja_fillestare, int _vlera) {
		nyja* rezultati;
		if (_nyja_fillestare == NULL)
			rezultati = NULL;
		else if (_nyja_fillestare->vlera == _vlera)
			rezultati = _nyja_fillestare;
		else if (_vlera < _nyja_fillestare->vlera)
			rezultati = kerko(_nyja_fillestare->majtas, _vlera);
		else
			rezultati = kerko(_nyja_fillestare->djathtas, _vlera);
		return rezultati;
	}

	nyja* minimalja(nyja* _nyja_fillestare) {
		if (_nyja_fillestare->majtas != NULL)
			minimalja(_nyja_fillestare->majtas);
		else
			return _nyja_fillestare;
	}

	nyja* maksimalja(nyja* _nyja_fillestare) {
		if (_nyja_fillestare->djathtas != NULL)
			maksimalja(_nyja_fillestare->djathtas);
		else
			return _nyja_fillestare;
	}

	void pershko_gjeresia_se_pari() {
		cout << "\nPershkimi gjeresia se pari: ";
		queue<nyja*> rreshti;
		rreshti.push(rrenja);
		while (!rreshti.empty())
		{
			nyja* n = rreshti.front();
			cout << n->vlera << " ";
			rreshti.pop();
			if (n->majtas != NULL)
				rreshti.push(n->majtas);
			if (n->djathtas != NULL)
				rreshti.push(n->djathtas);
		}
	}

	void pershko_thelesia_se_pari() {
		cout << "\nPershkimi thellesia se pari: ";
		stack<nyja*> steku;
		steku.push(rrenja);
		while (!steku.empty())
		{
			nyja* n = steku.top();
			cout << n->vlera << " ";
			steku.pop();
			if (n->djathtas != NULL)
				steku.push(n->djathtas);
			if (n->majtas != NULL)
				steku.push(n->majtas);
		}
	}

	void pershko_pre_order(nyja* _nyja_fillestare) {
		if (_nyja_fillestare != NULL)
		{
			cout << _nyja_fillestare->vlera << " ";
			pershko_pre_order(_nyja_fillestare->majtas);
			pershko_pre_order(_nyja_fillestare->djathtas);
		}
	}

	void pershko_in_order(nyja* _nyja_fillestare) {
		if (_nyja_fillestare != NULL)
		{
			pershko_in_order(_nyja_fillestare->majtas);
			cout << _nyja_fillestare->vlera << " ";
			pershko_in_order(_nyja_fillestare->djathtas);
		}
	}

	void pershko_post_order(nyja* _nyja_fillestare) {
		if (_nyja_fillestare != NULL)
		{
			pershko_post_order(_nyja_fillestare->majtas);
			pershko_post_order(_nyja_fillestare->djathtas);
			cout << _nyja_fillestare->vlera << " ";
		}
	}

	nyja* largo(nyja* _nyja_fillestare, int _vlera) {
		if (_nyja_fillestare == NULL) {
			cout << "Vlera " << _vlera << " nuk gjendet ne peme. Asnje vlere nuk eshte larguar.";
		}
		else if (_vlera == _nyja_fillestare->vlera) {
			if (_nyja_fillestare->majtas == NULL && _nyja_fillestare->djathtas == NULL) {
				_nyja_fillestare = NULL;
				numri_vlerava = numri_vlerava - 1;
			}
			else if (_nyja_fillestare->majtas == NULL) {
				numri_vlerava = numri_vlerava - 1;
				return _nyja_fillestare->djathtas;
			}
			else if (_nyja_fillestare->djathtas == NULL) {
				numri_vlerava = numri_vlerava - 1;
				return _nyja_fillestare->majtas;
			}
			else {
				nyja* nyja_max = maksimalja(_nyja_fillestare->majtas);
				nyja* zevendesuesja = this->nyje_e_re(nyja_max->vlera);
				zevendesuesja->djathtas = _nyja_fillestare->djathtas;
				zevendesuesja->majtas = largo(_nyja_fillestare->majtas, nyja_max->vlera);
				numri_vlerava = numri_vlerava - 1;
				return zevendesuesja;
			}
		}
		else if (_vlera <= _nyja_fillestare->vlera)
		{
			_nyja_fillestare->majtas = largo(_nyja_fillestare->majtas, _vlera);
		}
		else
		{
			_nyja_fillestare->djathtas = largo(_nyja_fillestare->djathtas, _vlera);

		}
		return _nyja_fillestare;
	}

	int lartesiaPemes(nyja* rrenja)						//1.LARTESIA
	{
		if (rrenja == NULL)
			return 0;
		queue<nyja*> q;
		q.push(rrenja);
		int lartesia = 0;
		while (1)
		{
			int numriNyjeve = q.size();
			if (numriNyjeve == 0)
				return lartesia;
			lartesia++;
			while (numriNyjeve > 0)
			{
				nyja* nyje = q.front();
				q.pop();
				if (nyje->majtas != NULL)
					q.push(nyje->majtas);
				if (nyje->djathtas != NULL)
					q.push(nyje->djathtas);
				numriNyjeve--;
			}
		}
	}

	nyja* paraardhesi(nyja* _nyja_fillestare, int para) {				//2.Paraardhesi
		nyja* par;
		if (_nyja_fillestare == NULL) {
			cout << "Nyja nuk ekziston";
		}
		while (_nyja_fillestare != NULL) {
			if (_nyja_fillestare->vlera == para) {
				if (_nyja_fillestare->djathtas)
				{
					par = _nyja_fillestare->djathtas;
					while (par->majtas)
					{
						par = par->majtas;
					}
				}
			}
			else if (_nyja_fillestare->vlera < para) {
				par = _nyja_fillestare;
				_nyja_fillestare = _nyja_fillestare->djathtas;
			}
			else
				return _nyja_fillestare;
		}
	}

	nyja* pasardhesi(nyja* _nyja_fillestare, int pas) {				//3.Pasardhesi
		nyja* aktuale = kerko(_nyja_fillestare, pas);
		if (aktuale->djathtas != NULL)
		{
			return minimalja(aktuale->djathtas);
		}
		else {
			nyja* pas_ar = NULL;
			nyja* fund = _nyja_fillestare;
			while (fund != aktuale)
			{
				if (aktuale->vlera < fund->vlera)
				{
					pas_ar = fund;
					fund = fund->majtas;
				}
				else {
					fund = fund->djathtas;
				}
			}
			return pas_ar;
		}
	}

	bool Pema_eKompletuar(nyja* root)				//4.E kompletuar
	{
		if (root == NULL)
			return true;

		queue<nyja*> q;
		q.push(root);
		bool flag = false;

		while (!q.empty())
		{
			nyja* temp = q.front();
			q.pop();

			if (temp->majtas)
			{
				if (flag == true)
					return false;

				q.push(temp->majtas);
			}
			else
				flag = true;

			if (temp->djathtas)
			{
				if (flag == true)
					return false;

				q.push(temp->djathtas);
			}
			else
				flag = true;
		}
		return true;
	}

	int nr_iPas(nyja* _nyja_fillestare, int pas) {}

};
	void main() {
		pema_binare_e_kerkimit p;

		p.rrenja = p.shto(p.rrenja, 6);
		p.rrenja = p.shto(p.rrenja, 5);
		p.rrenja = p.shto(p.rrenja, 9);
		p.rrenja = p.shto(p.rrenja, 4);
		p.rrenja = p.shto(p.rrenja, 5);
		p.rrenja = p.shto(p.rrenja, 12);
		p.rrenja = p.shto(p.rrenja, 8);
		p.rrenja = p.shto(p.rrenja, 11);
		p.rrenja = p.shto(p.rrenja, 15);

		p.rrenja = p.largo(p.rrenja, 6);
		p.rrenja = p.largo(p.rrenja, 1);

		nyja* ekziston = p.kerko(p.rrenja, 7);
		if (ekziston != NULL)
			cout << "\nVlera "
			<< ekziston->vlera << " gjendet ne peme.";
		else
			cout << "\nVlera e kerkuar nuk gjendet ne peme.";

		p.pershko_gjeresia_se_pari();
		p.pershko_thelesia_se_pari();

		cout << "\nPershkimi pre order: ";
		p.pershko_pre_order(p.rrenja);
		cout << "\nPershkimi in order: ";
		p.pershko_in_order(p.rrenja);
		cout << "\nPershkimi post order: ";
		p.pershko_post_order(p.rrenja);

		nyja* min = p.minimalja(p.rrenja);
		cout << "\nMinimalja: " << min->vlera;
		nyja* max = p.maksimalja(p.rrenja);
		cout << "\nMaksimalja: " << max->vlera << endl;
		cout << "Numri i vlerave ne peme: " << p.numri_vlerava << endl;
		cout << "Lartesia e pemes eshte: " << p.lartesiaPemes(p.rrenja) << endl;		//1.Lartesia

		nyja* para_ardhesi = p.paraardhesi(p.rrenja, 8);
		cout << "Nyja paraardhese e numrit 8 eshte " << para_ardhesi->vlera << endl;	//2.Paraardhesi

		nyja* pas_ardhesi = p.pasardhesi(p.rrenja, 9);
		cout << "Nyja pasardhese e numrit 9 eshte " << pas_ardhesi->vlera << endl;		//3.Pasardhesi

		if (p.Pema_eKompletuar(p.rrenja) == true)										//4.e Kompletuar
			cout << "Pema eshte e kompletuar";
		else
			cout << "Pema nuk eshte e kompletuar";


	}


