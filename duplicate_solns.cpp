#include <iostream>
#include <new>
using namespace std;

int duplicate_solns(int ns, int *psoln)
{
	int ival, irow, icol;
	int ivalk, irowk, icolk;
	int k, iter;
	int ifound = 0;
	//int m;
	//int *index;
	int *tsoln;
	int tns;
	if (ns > 1)
	{
		//index = new int [ns];
		for (iter=0;iter<ns-1;iter++)
		{
			ival = *(psoln+3*iter);
			irow = *(psoln+3*iter+1);
			icol = *(psoln+3*iter+2);
			//index[0] = 1;
			for (k=iter+1;k<ns;k++)
			{
				ivalk = *(psoln+3*k);
				irowk = *(psoln+3*k+1);
				icolk = *(psoln+3*k+2);
				if (ival == ivalk && irow == irowk && icol == icolk)
				{
					*(psoln+3*k) = 0;
					*(psoln+3*k+1) = 0;
					*(psoln+3*k+2) = 0;
					ifound = 1;
					//index[k]=0;
				}
				//else
					//index[k]=1;
			}
		}
		
		if (ifound == 1)
		{
			tns = 0;
			tsoln = new int [3*ns];
			for (k=0;k<ns;k++)
			{
				if (*(psoln+3*k) != 0 )
				{
					tsoln[3*tns] = *(psoln+3*k);
					tsoln[3*tns+1] = *(psoln+3*k+1);
					tsoln[3*tns+2] = *(psoln+3*k+2);
					tns++;
				}
			}
			for (k=0;k<3*ns;k++)
				*(psoln+k) = 0;
			for (k=0;k<3*tns;k++)
				*(psoln+k) = tsoln[k];
			ns = tns;
			delete [] tsoln;
		}
		
	}
	//delete [] index;
	return ns;
}