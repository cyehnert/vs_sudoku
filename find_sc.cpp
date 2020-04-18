#include <iostream>
using namespace std;

int find_sc(int nsoln, int *ptt, int *psoln, int *pz9)
{
	int ns;
	int zcount;  // number of zeros in a set of 9
	int ucount;  // number of unknowns in  a set of 9
	int kcount;  // number of known solutions in a set of 9 (0 or 1)
	int i,j,k;
	int ival,uval;
	ns = nsoln;
	// column solutions
	// i is for values 1 to 9
	for (i=0;i<9;i++)
	{
		// k is for cols 1 to 9
		for (k=0;k<9;k++)
		{
			zcount=0;
			ucount=0;
			kcount=0;
			// j is for rows 1 to 9
			for (j=0;j<9;j++)
			{
				ival = *(ptt+i*9*9+j*9+k);
				switch (ival)
				{
				case (-1):
					ucount++;
					uval=j;
					break;
				case (0):
					zcount++;
					break;
				case (1):
					kcount++;
					break;
				}
			}
			if (zcount == 8 && ucount == 1)
			{
				*(psoln+3*ns) = i+1;
				*(psoln+3*ns+1) = uval+1;
				*(psoln+3*ns+2) = k+1;
				ns++;
			}
			else if (zcount == 9)
			{
				(*pz9)++;
				cout << "Inconsistent Truth Table for Value " << i+1 << " at Col " << k+1 << endl;
			    cout << "z9 = " << *pz9 << endl;
			}
		}
	}
	return ns;
}