#include <iostream>
using namespace std;

struct p_moves {
	int n;
	int v[9];
};

int triset_test_block(int *ptt, struct p_moves *pm)
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
	struct block_n {
		int np;
		int indx;
	} b[9];
	int i,j;
	int n, m;
	int nfound;
	int r1;         //repeat flag - if any values are found
	                // the entire algorithm must be repeated
	int x, y;
	int y1, z1;
	int n1, n2;
	int k1, k2;
	int is, js;
	int kindx;
	int npairs;
	int af, bf, cf;
	int lc1, lc2, lc3;
	int nc2, pfa, pfb;
	n = 0;
	m = 0;
	nfound = 0;
	r1 = 0;    // repeat flag
	// test blocks
	for (i=0;i<3;i++)
	{
		for (j=0;j<3;j++)
		{
			n=0;
			m=0;
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
			for (is=0;is<3;is++)
			{
				for (js=0;js<3;js++)
				{
					kindx = 27*i+3*j+9*is+js;
					if (pm[kindx].n == 2) npairs++;
					if (pm[kindx].n > 0) m++;
					b[is*3+js].np = pm[kindx].n;
					b[is*3+js].indx = kindx;
				}
			}
			//if (npairs >=3 && m > 3)
			if (npairs >= 3)
			{
				// Test 2: Find matching pairs
				for (k1=0;k1<9;k1++)
			    {
					if (b[k1].np == 2)
				    {
						kindx = b[k1].indx;
						n1 = pm[kindx].v[0];
						n2 = pm[kindx].v[1];
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
						}   
					}   // end test on  b[k1].np
					if ((lc3 > 0) || (nc2 == npairs)) break;
				}  // loop on k1
			    // end of Test 2
			} // end of npairs if test
			if (lc3 > 0)
			{
				cout << "Found a cyclic triple in block " << i+1 << "   "  << j+1 << endl;
				cout << "At locations: " << lc1 << " " << lc2 << " " << lc3 << endl;
					// remove elements from the truth table
				if (m <= 3) break;
				for (k2=0;k2<9;k2++)
				{
					if ((k2+1) == lc1) continue;
					if ((k2+1) == lc2) continue;
					if ((k2+1) == lc3) continue;

					//kindx = b[k2].indx;
					z1 = b[k2].np;
					if (z1 > 0)
					{
						kindx = b[k2].indx;
						for (y=0;y<z1;y++)
						{
							y1 = pm[kindx].v[y];
							if (y1 == af || y1 == bf || y1 == cf)
							{
								x = ptt[9*9*(y1-1)+kindx];
								if (x == -1)
								{
									nfound++;
									ptt[9*9*(y1-1)+kindx] = 0;
									r1 = 1;
									cout << "Triset_test_block modifying location in Truth Table" << endl;
									cout << "Val: " << y1 << " Loc: " << kindx+1 << endl;
								}
								else
								{
									cout << "Triset_col trying to zero wrong location in Truth Table" << endl;
									cout << "Val: " << y1 << " Loc: " << kindx+1 << endl;
								}  // endo of if test on x
							}  // end of if test on y1
						} // end of y loop
					}  // end of if test on z1
				}      // endo of k2 loop
			}    //  end of lc3 test
			
		}  // block i,j
	}
	return nfound;
}

			