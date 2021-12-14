
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

	int max_nyeremeny()
	{
		/** /
		return rek_haszon_mikor_jatekos_lep(0, N - 1);
		/*/
		haszonmatrixok_felepitese();
		return Haszon_mikor_jatekos_lep->at(0)[N - 1];
		/**/
	}

	/// <summary>
	/// A második sor pontosan n = 2 karaktert tartalmazzon(szóközök nélkül). A sorban az i-edik karakter a 'B' legyen, ha a játékos az i-edik lépésben a balszélsõ, a 'J' betu, ha a jobbszélsõ számot választja. Több megoldás esetén bármelyik megadható.
	/// </summary>
	/// <returns>A stratégia</returns>
	string visszakovetes()
	{
		string sum = "";
		int b = 0;
		int j = N-1;
		bool jatekoslep = true;

		while (b<=j)
		{
			if (jatekoslep)
			{
				if (Haszon_mikor_jatekos_lep->at(b)[j] == T->at(b) + Haszon_mikor_ellenfel_lep->at(b + 1)[j])
				{
					sum += "B";
					b++;
				}
				else
				{
					sum += "J";
					j--;
				}
			}
			else
			{
				if (T->at(b)<T->at(j))
					j--;
				else
					b++;
			}
			jatekoslep = !jatekoslep;
		}
		return sum;
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
	/// a két mátrix igazából két felsõháromszögmátrix, amelyben a jobb felsõ sarok értékét keressük. Ezt az alatta lévõ elemekbõl állítjuk elõ "szimultán rekurzióval", azaz a mátrixok egymásra is hivatkoznak a felépítés során. Lehetne egy (nemnégyzetes) mátrixba is tárolni a jobb helykihasználás végett, de nem akartam így elbonyolítani a kódott, jobb az átláthatóság.
	/// </summary>
	void haszonmatrixok_felepitese()
	{
		Haszon_mikor_jatekos_lep = new vector<vector<int>>(N, vector<int>(N));
		Haszon_mikor_ellenfel_lep = new vector<vector<int>>(N, vector<int>(N));

		// fõátló megalkotása:
		for (int i = 0; i < N; i++)
		{
			Haszon_mikor_ellenfel_lep->at(i)[i] = 0;
			Haszon_mikor_jatekos_lep->at(i)[i] = T->at(i);
		}

		// felsõháromszögek megalkotása:
		// Ellenfél: 
		for (int intervallumhossz = 1; intervallumhossz < N; intervallumhossz++)
			for (int b = 0; b + intervallumhossz < N; b++)
			{
				int j = b + intervallumhossz;
				Haszon_mikor_ellenfel_lep->at(b)[j] =
					T->at(b) < T->at(j) ?
					Haszon_mikor_jatekos_lep->at(b)[j - 1] :
					Haszon_mikor_jatekos_lep->at(b + 1)[j];
				Haszon_mikor_jatekos_lep->at(b)[j] = max(
					T->at(j) + Haszon_mikor_ellenfel_lep->at(b)[j - 1],
					T->at(b) + Haszon_mikor_ellenfel_lep->at(b + 1)[j]
				);
			}
	}



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
		return max(
			T->at(j) + rek_haszon_mikor_ellenfel_lep(b, j - 1),
			T->at(b) + rek_haszon_mikor_ellenfel_lep(b + 1, j)
		);
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
		return T->at(b) < T->at(j)?
			rek_haszon_mikor_jatekos_lep(b, j - 1):
			rek_haszon_mikor_jatekos_lep(b + 1, j);
	}
};


int main()
{
	Jatek J;
	cout << J.max_nyeremeny() << endl;
	cout << J.visszakovetes();

}

/* 
=========== be0.txt: ==================


8
5 12 3 21 33 14 6 2

-----------------------------
ki0.txt

52
JBJB

=========== be1.txt: ==================

20
12 6 9 9 11 10 9 13 12 20 5 3 8 15 10 6 10 4 4 3

-----------------------------
ki1.txt

100
BBBJBBJJJJ

============ be2.txt ==================

1000
364 433 472 939 683 944 1703 144 290 641 1024 422 1796 1474 416 87 457 364 1731 1614 1546 1953 1197 1347 1859 529 887 1887 505 676 1954 1973 644 1557 1176 378 1139 1321 1050 1089 241 1756 706 298 115 1608 684 1062 762 488 215 1711 1329 359 929 823 331 1016 1674 35 2000 1128 861 1603 737 87 1827 470 1041 319 1754 1251 995 1986 1496 661 259 1102 1094 1542 413 409 1846 1872 591 434 4 1416 1743 932 1674 621 1272 1821 1602 667 873 852 1450 675 72 1789 446 263 1024 852 1868 448 1719 1526 1025 1517 1365 138 1338 1588 1155 260 132 1954 186 1416 1360 1745 1764 1742 1906 204 1655 440 418 493 28 569 767 561 1041 960 325 1543 1651 697 717 1965 1654 957 296 437 578 1156 1522 1614 378 1828 1474 318 1218 936 745 889 572 1352 581 952 1461 1153 804 880 1153 1222 1092 555 1597 1384 1733 1526 324 1717 1080 298 1289 1988 559 290 65 921 1779 754 1733 995 1407 760 528 617 399 1027 1393 1146 397 1352 892 580 45 1581 1831 308 1441 1651 877 1288 851 1954 1201 1489 747 904 1346 1538 964 1867 1655 239 419 937 808 686 1763 53 545 1550 1 1590 932 435 439 1241 1939 250 824 1483 1979 244 576 383 1267 1400 736 469 1365 61 1134 1880 1345 1003 876 1360 48 755 1605 532 1685 896 490 1766 1557 1758 1020 196 1398 507 1636 1289 209 546 73 1944 367 943 1556 1095 1405 162 144 541 1561 497 1787 1195 1234 480 1638 1720 1414 682 1054 1086 1828 1770 617 627 5 1058 1237 1610 1214 635 476 384 182 1882 1747 732 1114 1181 644 1626 883 1766 260 442 1358 908 1748 1247 872 1109 1542 1569 1527 397 1444 244 1661 1477 1576 1204 1328 1205 1826 1749 342 248 386 874 324 792 666 1716 1964 1339 1423 792 273 601 15 57 1476 1956 426 16 1304 1886 1768 1580 1415 283 1567 1699 81 1807 1283 741 1724 1573 1460 1665 879 1776 449 712 288 1447 659 1599 251 521 1415 1976 1158 524 94 843 1752 1288 1249 565 664 1416 415 211 592 501 1274 333 1399 1484 1036 1389 1660 1842 1590 1511 283 1448 1994 843 360 471 1191 1627 1871 965 975 530 1360 1370 934 1930 1442 1352 934 1848 142 1793 359 1301 1203 173 302 230 1301 311 1742 1394 1659 643 1448 456 370 1317 1114 1880 584 906 552 745 873 340 324 1304 1000 1253 1864 1729 62 1083 1282 459 513 1911 1295 12 230 645 300 1274 1046 1116 1123 295 1386 274 1521 818 790 1591 103 1368 1642 1269 768 926 1593 1150 1139 400 216 1358 1828 946 582 1709 1633 1722 741 244 441 456 438 331 1120 369 968 1188 288 1724 1888 652 1404 703 375 494 166 211 32 350 34 771 909 66 1864 321 925 770 413 1997 1137 1512 1773 576 1851 382 550 470 1936 1029 723 775 1912 122 1087 73 461 1518 313 155 418 1414 243 882 307 261 1488 529 1906 291 952 549 1586 854 1000 1173 1810 718 567 1919 430 648 1387 674 155 1070 889 524 1169 758 1603 195 1137 767 1344 1162 360 262 120 1462 261 1265 871 1649 557 680 867 1175 445 1260 300 812 281 149 42 1343 523 1194 1103 209 1709 1012 1293 74 1265 758 1570 1023 1476 432 1435 1189 580 45 1797 305 396 476 1757 487 926 1505 1246 1717 1955 1607 456 376 576 483 1792 983 1996 904 920 1770 9 219 1226 1078 3 1387 731 1084 827 1625 458 1897 1545 1736 231 1328 980 1979 1160 1019 749 1782 239 1330 947 1365 579 1395 1664 906 183 79 1445 1867 388 1154 513 1333 786 34 1052 883 811 354 785 1603 871 777 1528 889 1967 704 1249 452 502 1275 942 961 1439 922 724 179 1675 528 1203 1440 1007 1619 992 1024 216 1967 520 1460 480 1613 1452 1959 206 356 857 40 1279 1218 82 658 1664 334 464 1724 1202 684 37 1603 134 714 683 673 1547 170 541 1411 27 1019 1468 899 1180 855 938 294 682 1434 194 1019 1676 277 610 252 1531 419 699 256 892 1753 1577 563 359 1369 1894 1644 1340 1200 1213 537 521 1181 1317 531 209 165 4 506 1723 1715 1314 1571 755 999 950 695 1190 263 634 661 1762 1852 13 1501 1788 1424 1191 943 1591 1285 1137 1597 1895 1884 61 1704 1281 108 1777 508 1088 1580 1607 296 1094 1904 1645 467 1673 62 1028 1417 1684 1248 951 242 1667 1622 653 603 1852 315 892 1466 1540 638 1698 886 245 1206 822 1518 220 1335 639 1775 1174 1559 180 1852 568 1942 1919 220 1109 203 890 204 693 498 1415 631 1245 84 259 1688 877 1834 226 1246 1746 651 1466 437 72 788 700 292 522 1006 1432 1644 1671 716 254 226 691 433 397 359 1931 75 1294 1500 1353 1007 123 1564 620 726 905 794 629 1308 705 1997 1655 1262 1473 317 816 1837 368 1641 303 255 1786 912 1793 773 1826 590 419 1630 124 1266 435 1055 101 1752 770 940 1445 1148 981 1460 1380 88 95 1962 1849 417 1063 1386 682 1649 663 468 860 1183 1860 225 701 1616 1083 1302 356 998 1796 624 885 1708 671 433 1031 1323 1295 1482 339 1917 1722 1120 612 185 1990 684 445 575 1048 466 809 1588 1919 1363

--------------------------------

567029
JJBJBBJBJBJJJJJJJJJJBBBBJJBJBBBBJBJJBBBBBBBBBBBBBBBBBBBBJBBJJBJJBJBBBBBJJJBBBBBBBBBJJJBBBBBBBBJJJJJJJJJBBJBBJJJBJBJBBBJBBBBBBBBJJJBBBBJBBBBBBJJBBBBJBBBBBJBBBBBJJJBBJBBBBBBBBJBBBJJBJJBJJJJJBBJJJBBJJJBBBBBBJJJJBJBJBBBBBBBJJJBBJJBBJJJJBBJJBJJJBBBBBJBBJJJJJBBBBBBBBBBJBBBBBBBBBBJJJJJJJJJJJJJJBBBBBBBJJJJJJBJBBJBBBBBJBBBBBBBBBBBJBBBJBBJJJBBJBBBBBBBBBBJBBBBJJJJJJJBBBJJJJJJJJBJBJJBBBBJJJJJBBBBBBBBJJJJJJJJJJJJJBBBBBBJBJBBJBBBJJBBJJJBBJBBBJJJBJBJBBBBBBBJBBBBBJBBBJBJJJBBBBBJJBJJBBBBJBBBBBBJBBBJJJJJJJBJBBJJJ


*/
