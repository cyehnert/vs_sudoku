#include <iostream>
using namespace std;

int is_soln(int nval, int nrow, int ncol, int nsoln, int soln[])
{
	int i, ifound;
	ifound = 0;
	for (i=0;i<nsoln;i++)
	{
		if (nval == soln[3*i] && nrow == soln[3*i+1] && ncol == soln[3*i+2])
			ifound = 1;
	}
	return ifound;
}