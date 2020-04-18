#include <iostream>
using namespace std;

struct p_moves {
	int n;
	int v[9];
};

void init_pm(struct p_moves *pm)
{
	int j,k,m;
	for (j=0;j<9;j++)
	{
		for (k=0;k<9;k++)
		{
			pm[j*9+k].n = 0;
			for (m=0;m<9;m++) pm[j*9+k].v[m]=0;
		}
	}
  return;
}