
#include <iostream>
#include <vector>

using namespace std;

class Jatek
{
public:

	Jatek()
	{
		cin >> N;
		T = new vector<int>(N);
		for (int i = 0; i < N; i++)
			cin >> T->at(i);
	}

	int maximalis_nyerem�ny()
	{
		/** /
		return rek_haszon_mikor_jatekos_lep(0, N - 1);
		/*/
		haszonmatrixok_felepitese();
		return Haszon_mikor_jatekos_lep[0][N - 1];
		/**/
	}


	~Jatek()
	{
	}

private:
	int N;
	vector<int>* T;
	vector<vector<int>>* Haszon_mikor_jatekos_lep;
	vector<vector<int>>* Haszon_mikor_ellenfel_lep;

	/// <summary>
/// "A j�t�kos minden l�p�sben v�laszthat egy sz�mot a m�g az asztalon l�v� sorozatb�l, vagy a balsz�ls�t, vagy a jobbsz�ls�t, �s leveszi a v�lasztott sz�mot. [...] A j�t�k akkor �r v�get, ha elfogyott minden sz�m. A j�t�kos nyerem�nye az �ltala v�lasztott sz�mok �sszege.
/// �rjon olyan programot, amely kisz�m�tja a j�t�kos �ltal el�rhet� maxim�lis nyerem�ny �rt�k�t �s meg is adja, hogy ezt milyen l�p�sekkel �rheti el!"
/// </summary>
/// <param name="b">bal oldali sz�m indexe</param>
/// <param name="j">jobb oldali sz�m indexe</param>
/// <returns>a j�t�kos haszna az ellenf�l l�p�se ut�n.</returns>
	int rek_haszon_mikor_jatekos_lep(int b, int j)
	{
		if (b == j)
			return T->at(b);

		return max(T->at(j) + rek_haszon_mikor_ellenfel_lep(b, j - 1),
			T->at(b) + rek_haszon_mikor_ellenfel_lep(b + 1, j));
	}

	/// <summary>
	/// "A j�t�kos minden l�p�se ut�n a j�t�kvezet� leveszi a t�bl�r�l a balsz�ls� �s a jobbsz�ls� sz�m k�z�l a nagyobbikat, ha egyenl�k, akkor a balsz�ls�t.  A j�t�k akkor �r v�get, ha elfogyott minden sz�m."
	/// </summary>
	/// <param name="b">bal oldali sz�m indexe</param>
	/// <param name="j">jobb oldali sz�m indexe</param>
	/// <returns>a j�t�kos haszna az ellenf�l l�p�se ut�n.</returns>
	int rek_haszon_mikor_ellenfel_lep(int b, int j)
	{
		if (b == j)
			return 0;

		if (T->at(b) < T->at(j))
			return rek_haszon_mikor_jatekos_lep(b, j - 1);
		else
			return rek_haszon_mikor_jatekos_lep(b + 1, j);
	}
};


int main()
{
	Jatek J;
	cout << J.maximalis_nyerem�ny();

}

/* 
=============================
be0.txt:
8
5 12 3 21 33 14 6 2
-----------------------------
ki0.txt
52
JBJB
=============================
be1.txt: 
20
12 6 9 9 11 10 9 13 12 20 5 3 8 15 10 6 10 4 4 3
-----------------------------
ki1.txt
100
BBBJBBJJJJ
=============================

*/
