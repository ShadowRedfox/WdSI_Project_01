// WdSI_Project.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<iostream>
#include<time.h>
#include<string>
#include<vector>
#include<algorithm>
#include<math.h>

using namespace std;

#define wiel_pop 1024
#define max_iter 50
#define prawd_mut 0.02
#define podzbior_k (wiel_pop/4)


class osobnik
{
public:
	bool l_bin[23];
	float ocena;
	osobnik()
	{
		for (int i = 0; i < 23; i++)
		{
			l_bin[i] = NULL;
		}
		ocena = 0;
	}
	float przystosowanie(int x)
	{
		float a = 5 + ((7 * x) / (pow(2, 22) - 1));
		return log10(pow(a, 3)) - log10(pow(a, 5)) + pow(cos(4 * a), 3);
	}




};

bool porownaj(osobnik a, osobnik b)
{
	if (a.ocena > b.ocena)
		return true;
	else
		return false;
}

void mutuj(osobnik &a)
{
	int losuj = rand() % 23;
	bool x = rand() % 2;
	a.l_bin[losuj] = x;
}

int bin2dec(osobnik a)
{
	int x=0;
	for (int i = 0; i < 23; i++)
	{
		if (a.l_bin[i])
			x += pow(2, i);
	}
	return x;
}
int _tmain(int argc, _TCHAR* argv[])
{
	srand(time(NULL));
	vector<osobnik> populacja;
	vector<osobnik> populacjaNew;
	for (int i = 0; i < wiel_pop; i++)
	{
		bool l_bin_tmp[23];
		osobnik osobnikTmp;
		for (int j = 0; j < 23; j++)
		{
			l_bin_tmp[j] = rand() % 2;
			osobnikTmp.l_bin[j] = l_bin_tmp[j];
		}
		populacja.push_back(osobnikTmp);
	}

	for (int k = 0; k < max_iter; k++)
	{
		for (int i = 0; i < wiel_pop; i++)
		{
			populacja[i].ocena = populacja[i].przystosowanie(bin2dec(populacja[i]));
		}
		sort(populacja.begin(), populacja.end(), porownaj);
		//cout.precision(10);
		cout << k + 1 << "\tBest: " << populacja[0].ocena << "\t";
		for (int i = 0; i < 23; i++)
		{
			cout << populacja[0].l_bin[i];
		}
		cout << "\t" << 5 + ((7 * bin2dec(populacja[0])) / (pow(2, 22) - 1)) << endl;

		populacjaNew.clear();
		int esize = 2;			//w przypadku 1 nie byloby to parzyste, wiec 2 najlepszym rozwiazaniem
		populacjaNew.push_back(populacja[0]);
		populacjaNew.push_back(populacja[1]);

		for (int i = esize; i < wiel_pop; i+=2)
		{
			int rand1 = rand() % podzbior_k;
			int rand2 = rand() % podzbior_k;
			int m_podzialu1 = rand() % 23;
			int m_podzialu2 = rand() % 23;
			if (m_podzialu1 > m_podzialu2)
			{
				int tmp = m_podzialu1;
				m_podzialu1 = m_podzialu2;
				m_podzialu2 = tmp;
			}
			osobnik tmp1, tmp2;
			for (int j = 0; j < m_podzialu1; j++)
			{
				tmp1.l_bin[j] = populacja[rand1].l_bin[j];
				tmp2.l_bin[j] = populacja[rand2].l_bin[j];
			}
			for (int j = m_podzialu1; j < m_podzialu2; j++)
			{
				tmp1.l_bin[j] = populacja[rand2].l_bin[j];
				tmp2.l_bin[j] = populacja[rand1].l_bin[j];
			}
			for (int j = m_podzialu2; j < 23; j++)
			{
				tmp1.l_bin[j] = populacja[rand1].l_bin[j];
				tmp2.l_bin[j] = populacja[rand2].l_bin[j];
			}
			if (rand() < prawd_mut) mutuj(tmp1);
			if (rand() < prawd_mut) mutuj(tmp2);
			populacjaNew.push_back(tmp1);
			populacjaNew.push_back(tmp2);
		}
		swap(populacja, populacjaNew);
	}


	//ale one ladne byly
	system("pause>plik");
	return 0;
}

