#include <iostream>
using namespace std;

struct p_moves {
	int n;
	int v[9];
};

int triple_test_col(int *ptt, struct p_moves *pm)
{
	// Rule 3: (a,b,c) and (a,b,c) and (a,b,c) rule
	// this test looks for three squares in a row, column or block
	// that each have exactly three possible moves that are the same
	// In this case, only these three squares can have these values
	// If the values exist elsewhere in the row, column or block as
	// possible moves, they can be removed from the truth table
	// 
	// modifications  made using the arrays tcell and tstack have extended the
	// logic in this routine, so that the three moves can show up in 
	// combinations like: (a,b),(b,c),(a,b,c) or (a,b),(a,b,c),(a,b,c)   etc.
	// which are also valid for excluding a, b, and c from other parts of the
	// logic table.  The logic here should also cover the case
	// (a,b),(a,c),(b,c) which is currently checked in the routine triset_test_col.
	// 
	// This routine returns the total number of such locations removed
	/*
	struct block_n {
		int np;
		int indx;
	} b[9];
	*/
	int i,j;
	int n, m;
	int nfound;
	int r1;         //repeat flag - if any values are found
	                // the entire algorithm must be repeated
	int x, y, z;
	int y1;
	int n1, n2, n3;
	int m1, m2, m3;
	int k1, k2;
	int i1, i2;
	int tcelln;   // number of cells in a column that "fit" a triple
	int tstackn; //  number of elements in a stack that comprise the triple
	int tcell[3];  // cell numbers (1-9) in this column that make up the triple
	int tstack[3];  // elements in this stack are in process of being "fit"
	int nelem;   // number of elements in the current cell
	int fit;
	int iadd;
	nfound = 0;
	r1 = 0;    // repeat flag
	//
	// test columns
	//
		for (j=0;j<9;j++)      // columns
	{
		n = 0;
		m = 0;
		r1 = 0;                // flag to indicate that an update to the truth table has been made
		for (i=0;i<9;i++)      // rows
		{
			nelem = pm[9*i+j].n;
			if (nelem == 3 || nelem == 2) n++;   // number of potential fitting cells in column
			if (nelem > 0) m++;   // number of cells that are not yet solved in this column
		}
		// completed column j
		if (n >= 3 && m > 3)
		{
		// Test 2: Find matching triples
			for (k1=0;k1<7;k1++)   //  k1 is the first triple, cannot be lower than 7th row
			{
				if (r1 == 1) break;
				tcelln = 0;
				tstackn = 0;
				for (i=0;i<3;i++)
				{
					tcell[i] = 0;
					tstack[i] = 0;
				}
				nelem = pm[9*k1+j].n;
				if ( nelem == 3 || nelem == 2)
				{
					n3 = 0;
					n1 = pm[9*k1+j].v[0];
					n2 = pm[9*k1+j].v[1];
					if (nelem == 3)  n3 = pm[9*k1+j].v[2];
					if (tcelln == 0)
					{
						// we are here because the stack is empty
						if (n3 == 0)    // place 2 elements in the stack
						{
							tstack[0] = n1;
							tstack[1] = n2;
							tcelln = 1;
							tstackn = 2;
							tcell[0] = k1+1;
						}
						else           // place 3 elements in the stack
						{
							tstack[0] = n1;
							tstack[1] = n2;
							tstack[2] = n3;
							tcelln = 1;
							tstackn = 3;
							tcell[0] = k1+1;
						}
					}
					//  I now have one cell's contents in the stack
					//  now loop over the remaining cells using k2 parameter
					// if a cell in this loop does not fit, go to the next one
					// if the set of cells in this secondary loop does not produce
					// a complete stack with 3 "tcells", then exit this loop and
					// advance k1 to the next.  At this point, also need to
					// reinitialize all arrays.
					for (k2=k1+1;k2<9;k2++)
					{
						if (r1 == 1) break;
						nelem = pm[9*k2+j].n;
						if (nelem == 3 || nelem == 2)
						{
							m3 = 0;
							m1 = pm[9*k2+j].v[0];
							m2 = pm[9*k2+j].v[1];
							if (nelem == 3) m3 = pm[9*k2+j].v[2];
					
						// 4 cases follow
						switch (tstackn)
						{
						case 2 :
							switch (nelem)
							{
							case 2 :
								// current cell has 2 and there are 2 in the stack
								// biset test should have already run to handle the case
								// where these are an exact match
								// now looking for one to match and the second one to
								// be added to the stack
								fit = 0;
								for (i1 = 0; i1<2; i1++)
								{
									i2 = tstack[i1];
									if (m1 == i2 ) 
									{
										fit++;
										iadd = m2;
									}
									if (m2 == i2)
									{
										fit++;
										iadd = m1;
									}
								}
								if (fit == 1)
								{
									tcelln++;
									if (tcelln > 3)
									{
										cout << "Triple Test Col error detected " << endl;
										cout << "At Col " << j+1 << " and Row " << k2+1 << endl;
										break;
									}
									tcell[tcelln-1]=k2+1;
									tstack[2] = iadd;
									tstackn = 3;
								}
								break;
							case 3 :
								// current cell has 3 and there are 2 in the stack
								// two of the elements must match and the third element
								// is added to the stack
								fit = 0;
								for (i1 = 0; i1<2; i1++)
								{
									i2 = tstack[i1];
									if (m1 == i2 || m2 == i2 || m3 == i2) fit++;
								}
								if (fit == 2)
								{
									tcelln++;
									if (tcelln > 3)
									{
										cout << "Triple Test Col error detected " << endl;
										cout << "At Col " << j+1 << " and Row " << k2+1 << endl;
										break;
									}
									tcell[tcelln-1]=k2+1;
									tstack[0] = m1;
									tstack[1] = m2;
									tstack[2] = m3;
									tstackn = 3;
								}
								break;
							}
							break;
						case 3 :
							switch (nelem)
							{
							case 2 :
								// current cell has 2 and there are 3 in the stack
								// each element must match for this cell to fit
								fit = 0;
								for (i1 = 0; i1<3; i1++)
								{
									i2 = tstack[i1];
									if (m1 == i2 || m2 == i2 ) fit++;
								}
								if (fit == 2)
								{
									tcelln++;
									if (tcelln > 3)
									{
										cout << "Triple Test Col error detected " << endl;
										cout << "At Col " << j+1 << " and Row " << k2+1 << endl;
										break;
									}
									tcell[tcelln-1]=k2+1;
								}
								break;
							case 3 :
								// current cell has 3 and there are 3 in the stack
								// each element must match for this cell to fit
								fit = 0;
								for (i1 = 0; i1<3; i1++)
								{
									i2 = tstack[i1];
									if (m1 == i2 || m2 == i2 || m3 == i2) fit++;
								}
								if (fit == 3)
								{
									tcelln++;
									if (tcelln > 3)
									{
										cout << "Triple Test Col error detected " << endl;
										cout << "At Col " << j+1 << " and Row " << k2+1 << endl;
										break;
									}
									tcell[tcelln-1]=k2+1;
								}
								break;
							}
							break;
						}  // end of switch on tstackn
						} // end of logic on nelem
					
					           
								
					}  // loop on k2, an inner loop below k1
					if (tcelln == 3)
					{
						cout << "Found a triple in column " << j+1 << endl;
						cout << "Cells are : " << tcell[0] << "  " << tcell[1] << "  " << tcell[2] << endl;
						cout << "Elements are : " << tstack[0] << "  " << tstack[1] << "  " << tstack[2] << endl;
						        /*
								the following section removes elements fitting the triple from the rest of the cells
								*/
								for (z=0;z<9;z++)
								{
									nelem = pm[9*z+j].n;
									if (nelem>0 && (z+1) != (tcell[0]) && (z+1) != (tcell[1]) && (z+1) != (tcell[2]))
									{
										for (y=0;y<nelem;y++)
										{
											y1 = pm[9*z+j].v[y];
											if (y1 == tstack[0] || y1 == tstack[1] || y1 == tstack[2])
											{
												x = ptt[9*9*(y1-1)+9*z+j];
												if (x == -1)
												{
													nfound++;
													ptt[9*9*(y1-1)+9*z+j]=0;
													r1 = 1;
												    cout << "Triple_test_col modifying location in Truth Table" << endl;
							                        cout << "Val: " << y1 << " Row: " << z+1 << " Col: " << j+1 << endl;
												}
												else
												{
													cout << "Triple_test_col trying to zero wrong location in Truth Table" << endl;
												    cout << "Val: " << y1 << " Row: " << z+1 << " Col: " << j+1 << endl;
												}  // logic on x

											}  // if test on y1

										} // loop on y
									} // if test nelem and z
								}   // end of loop on z (locate data to remove from truth table)
								
							  
					}   // tcelln is 3 so a triple was detected

				}   // cell at k1 has exactly 2 or 3 elements, so look for a triple

			}    //  loop on k1, outer loop on the cells in column j

		}  // test on n and m, true means check out data in this column

	}   // column index j

	return nfound;
}  //  triple_test_col