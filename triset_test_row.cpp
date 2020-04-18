#include <iostream>
using namespace std;

struct p_moves {
	int n;
	int v[9];
};

int triset_test_row(int *ptt, struct p_moves *pm)
{
	// Rule 2: (a,b) and (a,c)  and (b,c) rule
	// this test looks for three squares in a row, column or block
	// that each have exactly two possible moves that match the 
	// pattern (a,b), (a,c), (b,c)
	// In this case, only these three squares can have these values
	// If the values exist elsewhere in the row, column or block as
	// possible moves, they can be removed from the truth table
	// 
	// This routine returns the total number of such locations removed
	struct pairs {
		int p;
		int q;
	} pset[9];
	int i,j;
	int n, m;
	int x, y, y1, z1;
	int nfound;
	int r1;         //repeat flag - if any values are found
	                // the entire algorithm must be repeated
	/*
	int x, y, z;
	int y1, z1;
	int exc1, exc2;
	*/
	int n1, n2;
	//int m1, m2;
	int k1;
	int k2;
	//int is, js;
	int npairs;
	int af, bf, cf;
	int lc1, lc2, lc3;
	int nc2, pfa, pfb;
	nfound = 0;
	r1 = 0;    // repeat flag
	// test rows
	// Test 1: For each row, count pm == 2 (n) and pm > 0 (m)
	for (i=0;i<9;i++)     // rows
	{
		n = 0;
		m = 0;
		npairs = 0;
		af = 0;
		bf = 0;
		cf = 0;
		lc1 = 0;
		lc2 = 0;
		lc3 = 0;
		nc2 = 0;
		pfa = 0;
		pfb = 0;
		for (j=0;j<9;j++)   // columns
		{
			if (pm[9*i+j].n == 2) npairs++;
			if (pm[9*i+j].n > 0) m++;
		}
		if (npairs >= 3)
		{

		// Test 2: Find matching pairs
			for (k1=0;k1<9;k1++)
			{
				if (pm[9*i+k1].n == 2)
				{
					n1 = pm[9*i+k1].v[0];
					n2 = pm[9*i+k1].v[1];
					nc2++;
					if (lc1 == 0)
					{
						af = n1;
						bf = n2;
						lc1 = k1+1;     
					}
					else if (lc2 == 0)
					{
						if ((n1 == af) && (n2 != bf))
						{
							cf = n2;
							pfb = 1;
							lc2 = k1+1;
						}
						else if ((n2 == bf) && (n1 != af))
						{
							cf = n1;
							pfa = 1;
							lc2 = k1+1;
						}
						else if ((n1 == bf) && (n2 != af))
						{
							cf = n2;
							pfa = 1;
							lc2 = k1+1;
						}
						else if ((n2 == af) && (n1 != bf))
						{
							cf = n1;
							pfb = 1;
							lc2 = k1+1;
						}
					}
					else if (lc3 == 0)
					{
						if (pfa == 1)
						{
							if (((n1 == af) && (n2 == cf)) || ((n1 == cf) && (n2 == af)))
								lc3 = k1+1;
						}
						if (pfb == 1)
						{
							if (((n1 == bf) && (n2 == cf)) || ((n1 == cf) && (n2 == bf)))
								lc3 = k1+1;
						}
					}    //  lc1, lc2, lc3 if test
				}    //  pm test
			}   //  k1 loop
				if ((lc3 > 0) || (nc2 == npairs)) break;
			}     // end of npairs if test
		if (lc3 > 0) 
		{
			cout << "Found a cyclic triple in row " << i+1 << endl;
			cout << "At locations: " << lc1 << " " << lc2 << " " << lc3 << endl;

		    if (m <= 3) break;
		// remove elements from the truth table
			for (k2=0;k2<9;k2++)
			{
				if ((k2+1) == lc1) continue;
				if ((k2+1) == lc2) continue;
				if ((k2+1) == lc3) continue;
				z1 = pm[9*i+k2].n;
				if (z1 > 0)
				{
					for (y=0;y<z1;y++)
					{
						y1 = pm[9*i+k2].v[y];
						if (y1 == af || y1 == bf || y1 == cf)
						{
							x = ptt[9*9*(y1-1)+9*i+k2];
							if (x == -1)
							{
								nfound++;
								ptt[9*9*(y1-1)+9*i+k2] = 0;
								r1 = 1;
								cout << "Triset_test_row modifying location in Truth Table" << endl;
								cout << "Val: " << y1 << " Row: " << i+1 << " Col: " << k2+1 << endl;
							}
							else
							{
							cout << "Triset_test_row trying to zero wrong location in Truth Table" << endl;
							cout << "Val: " << y1 << " Row: " << i+1 << " Col: " << k2+1 << endl;
							}  // endo of if test on x
					}  // end of if test on y1
				} // end of y loop
			}  // end of if test on z1
		}      // endo of k2 loop

		} // end of if test on lc3
	}   // i-loop for rows
	return nfound;
}