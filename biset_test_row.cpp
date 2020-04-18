#include <iostream>
using namespace std;

struct p_moves {
	int n;
	int v[9];
};

int biset_test_row(int *ptt, struct p_moves *pm)
{
	// Rule 1: (a,b) and (a,b) rule
	// this test looks for two squares in a row, column or block
	// that each have exactly two possible moves that are the same
	// In this case, only these two squares can have these values
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
	int p1, p2;      // matched values flags (a,b)
	int r1;         //repeat flag - if any values are found
	                // the entire algorithm must be repeated
	int x, y, z;
	int y1, z1;
	int exc1, exc2;
	int n1, n2;
	int m1, m2;
	int k1, k2;
	//int is, js;
	//int kindx;
	n = 0;
	m = 0;
	nfound = 0;
	p1 = 0;
	p2 = 0;
	r1 = 0;    // repeat flag
	// test rows
	// Test 1: For each row, count pm == 2 (n) and pm > 0 (m)
	for (i=0;i<9;i++)     // rows
	{
		n = 0;
		m = 0;
		for (j=0;j<9;j++)   // columns
		{
			if (pm[9*i+j].n == 2) n++;
			if (pm[9*i+j].n > 0) m++;
		}
		// completed this row
		if (n >= 2 && m > 2)
		{
		// Test 2: Find matching pairs
			for (k1=0;k1<8;k1++)
			{
				if (pm[9*i+k1].n == 2)
				{
					n1 = pm[9*i+k1].v[0];
					n2 = pm[9*i+k1].v[1];
					for (k2=k1+1;k2<9;k2++)
					{
						if (pm[9*i+k2].n == 2)
						{
							m1 = pm[9*i+k2].v[0];
							m2 = pm[9*i+k2].v[1];
							if (n1 == m1 && n2 == m2)
							{
								exc1 = k1;
								exc2 = k2;
								for (z=0;z<9;z++)
								{
									z1 = pm[9*i+z].n;
									if (z1>0 && z != exc1 && z!= exc2)
									{
										for (y=0;y<z1;y++)
										{
											y1 = pm[9*i+z].v[y];
											if (y1 == n1 || y1 == n2)
											{
												x = ptt[9*9*(y1-1)+9*i+z];
												if (x == -1)
												{
													nfound++;
													ptt[9*9*(y1-1)+9*i+z]=0;
													r1 = 1;
													cout << "Biset_test_row modifying location in Truth Table" << endl;
													cout << "Val: " << y1 << " Row: " << i+1 << " Col: " << z+1 << endl;
												}
												else
												{
													cout << "Biset_test_row trying to zero wrong location in Truth Table" << endl;
													cout << "Val: " << y1 << " Row: " << i+1 << " Col: " << z+1 << endl;
												}
											}

										}
									}
								}
							}
						}

					}
				}
			}
		}
	}
	return nfound;
}