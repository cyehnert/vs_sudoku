#include <iostream>
using namespace std;

int find_sb(int nsoln, int *ptt, int *psoln, int *pz9)
{
	int ns;
	int zcount;  // number of zeros in a set of 9
	int ucount;  // number of unknowns in  a set of 9
	int kcount;  // number of known solutions in a set of 9 (0 or 1)
	int i;
	int jb, ib, jr, ic;
	int ival,jval,kval;
	ns = nsoln;
	// row solutions
	// i is for values 1 to 9
	for (i=0;i<9;i++)
	{
		// jb is for box rows 1 to 3
		for (jb=0;jb<3;jb++)
		{
			// ib is for box column 1 to 3
			for (ib=0;ib<3;ib++)
			{
			  zcount=0;
			  ucount=0;
			  kcount=0;
			// jr is for rows 1 - 3 within a box
			  for (jr=0;jr<3;jr++)
			  {
			// ic is for columns 1 to 3 within a box
			    for (ic=0;ic<3;ic++)
			    {
				  ival = *(ptt+i*9*9+jb*27+ib*3+jr*9+ic);
				  switch (ival)
				  {
				    case (-1):
					  ucount++;
					  jval=jb*3+jr;
					  kval=ib*3+ic;
					  break;
				    case (0):
					  zcount++;
					  break;
				    case (1):
					  kcount++;
					  break;
				  }
			    }

			    }
			     if (zcount == 8 && ucount == 1)
			     {
				    *(psoln+3*ns) = i+1;
				    *(psoln+3*ns+1) = jval+1;
				    *(psoln+3*ns+2) = kval+1;
				    ns++;
			      }
				 else if (zcount == 9)
			     {
				  (*pz9)++;
				  cout << "Inconsistent Truth Table for Value " << i+1 << " at Block Row " << jb+1 << " at Block Col " << ib+1 << endl;
				  cout << "z9 = " << *pz9 << endl;
			    }
			 }
		  }
	}
	return ns;
}