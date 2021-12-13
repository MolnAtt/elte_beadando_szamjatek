
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

	int maximalis_nyeremény()
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
/// "A játékos minden lépésben választhat egy számot a még az asztalon lévõ sorozatból, vagy a balszélsõt, vagy a jobbszélsõt, és leveszi a választott számot. [...] A játék akkor ér véget, ha elfogyott minden szám. A játékos nyereménye az általa választott számok összege.
/// Írjon olyan programot, amely kiszámítja a játékos által elérhetõ maximális nyeremény értékét és meg is adja, hogy ezt milyen lépésekkel érheti el!"
/// </summary>
/// <param name="b">bal oldali szám indexe</param>
/// <param name="j">jobb oldali szám indexe</param>
/// <returns>a játékos haszna az ellenfél lépése után.</returns>
	int rek_haszon_mikor_jatekos_lep(int b, int j)
	{
		if (b == j)
			return T->at(b);

		return max(T->at(j) + rek_haszon_mikor_ellenfel_lep(b, j - 1),
			T->at(b) + rek_haszon_mikor_ellenfel_lep(b + 1, j));
	}

	/// <summary>
	/// "A játékos minden lépése után a játékvezetõ leveszi a tábláról a balszélsõ és a jobbszélsõ szám közül a nagyobbikat, ha egyenlõk, akkor a balszélsõt.  A játék akkor ér véget, ha elfogyott minden szám."
	/// </summary>
	/// <param name="b">bal oldali szám indexe</param>
	/// <param name="j">jobb oldali szám indexe</param>
	/// <returns>a játékos haszna az ellenfél lépése után.</returns>
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
	cout << J.maximalis_nyeremény();

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
