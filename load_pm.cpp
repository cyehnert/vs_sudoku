#include <iostream>
using namespace std;

struct p_moves {
	int n;
	int v[9];
};

void load_pm(int *ptt, struct p_moves *pm)
{
	int i,j,k,n,m;
	n = 0;
	for (i=0;i<9;i++)
	{
		for (j=0;j<9;j++)
		{
			for (k=0;k<9;k++)
			{
				if (ptt[n] == -1)
				{
					m = pm[9*j+k].n;
					pm[9*j+k].v[m]=i+1;
					m++;
					pm[9*j+k].n=m;

				}
				n++;
			}
		}
	}
	return;
}