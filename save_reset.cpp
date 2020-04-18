#include <iostream>
using namespace std;

struct p_moves {
	int n;
	int v[9];
};

void save_reset(int guess_mode, struct p_moves *pm, struct p_moves *pm_sav, int board[9][9], int board_sav[9][9])
{
	int i,j,k,n;
	n = 0;
	// guess_mode = 1 means copy from pm to pm_sav
	// guess_mode = 0 means copy from pm_sav to pm
	switch (guess_mode)
	{
	case 0:
		for (j=0;j<9;j++)
		{
			for (k=0;k<9;k++)
			{
				board[j][k] = board_sav[j][k];
				pm[9*j+k].n = pm_sav[9*j+k].n;
				for (i=0;i<9;i++)
					pm[9*j+k].v[i] = pm_sav[9*j+k].v[i];
			}
		}
		break;
	case 1:
		for (j=0;j<9;j++)
		{
			for (k=0;k<9;k++)
			{
				board_sav[j][k] = board[j][k];
				pm_sav[9*j+k].n = pm[9*j+k].n;
				for (i=0;i<9;i++)
					pm_sav[9*j+k].v[i] = pm[9*j+k].v[i];
			}
		}
		break;
	}
			
	return;
}