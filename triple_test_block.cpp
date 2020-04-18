#include <iostream>
using namespace std;

struct p_moves {
	int n;
	int v[9];
};

int triple_test_block(int *ptt, struct p_moves *pm)
{
	// Rule 3: (a,b,c) and (a,b,c) and (a,b,c) rule
	// this test looks for three squares in a row, column or block
	// that each have exactly three possible moves that are the same
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
	int x, y, z;
	int y1, z1;
	//int exc1, exc2;
	
	int n1, n2, n3;
	int m1, m2, m3;
	int k1, k2;
	int is, js;
	int i1, i2;
	int kindx;
	int irow, icol;
	int tcelln;
	int tstackn;
	int tcell[3];
	int tstack[3];
	int nelem;
	int fit;
	int iadd;
	nfound = 0;
	r1 = 0;    // repeat flag
	// test blocks
	for (i=0;i<3;i++)
	{
		for (j=0;j<3;j++)
		{
			n=0;
			m=0;
			
			r1 = 0;
			for (is=0;is<3;is++)
			{
				for (js=0;js<3;js++)
				{
					kindx = 27*i+3*j+9*is+js;
					if (pm[kindx].n == 3) n++;
					if (pm[kindx].n > 0) m++;
					b[is*3+js].np = pm[kindx].n;
					b[is*3+js].indx = kindx;
				}
			}
			// completed one block (i,j)
			if (n >=3 && m > 3)
			{
				// Test 2: Find matching triples
			  for (k1=0;k1<7;k1++)
			  {
				if (r1 == 1) break;
				tcelln = 0;
				tstackn = 0;
			    for (is = 0; is < 3; is++)
				{
					tcell[is] = 0;
					tstack[is] = 0;
				}
				nelem = b[k1].np;
				if (nelem == 2 || nelem == 3)
				{
					kindx = b[k1].indx;
					n3 = 0;
					n1 = pm[kindx].v[0];
					n2 = pm[kindx].v[1];
					if (nelem == 3) n3 = pm[kindx].v[2];
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
						nelem = b[k2].np;
						if (nelem == 2 || nelem == 3)
						{
							kindx = b[k2].indx;
							m3 = 0;
							m1 = pm[kindx].v[0];
							m2 = pm[kindx].v[1];
							if (nelem == 3) m3 = pm[kindx].v[2];
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
										cout << "Triple Test Block error detected " << endl;
										cout << "At Block Row " << i+1 << " and Block Col " << j+1 << endl;
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
										cout << "Triple Test Block error detected " << endl;
										cout << "At Block Row " << i+1 << " and Block Col " << j+1 << endl;
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
										cout << "Triple Test Block error detected " << endl;
										cout << "At Block Row " << i+1 << " and Block Col " << j+1 << endl;
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
										cout << "Triple Test Block error detected " << endl;
										cout << "At Block Row " << i+1 << " and Block Col " << j+1 << endl;
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
						cout << "Found a triple in Block Row " << i+1 << " and Block Col " << j+1 << endl;
						cout << "Cells are : " << tcell[0] << "  " << tcell[1] << "  " << tcell[2] << endl;
						cout << "Elements are : " << tstack[0] << "  " << tstack[1] << "  " << tstack[2] << endl;
						        /*
								the following section removes elements fitting the triple from the rest of the cells
								*/
								for (z=0;z<9;z++)
								{
									nelem = b[z].np;
									kindx = b[z].indx;
									if (nelem>0 && (z+1) != tcell[0] && (z+1)!= tcell[1] && (z+1) != tcell[2])
									{
										for (y=0;y<nelem;y++)
										{
											
											y1 = pm[kindx].v[y];
											if (y1 == tstack[0] || y1 == tstack[1] || y1 == tstack[2])
											{
												x = ptt[9*9*(y1-1)+kindx];
												if (x == -1)
												{
													nfound++;
													ptt[9*9*(y1-1)+kindx]=0;
													r1 = 1;
													irow = (kindx/9)+1;
													icol = (kindx - (irow-1)*9) + 1;
													cout << "Triple_test_block modifying location in Truth Table" << endl;
													cout << "Row: " << irow << " Col: " << icol << " Val: " << y1 <<  endl;
												}
												else
												{
													irow = (kindx/9)+1;
													icol = (kindx - (irow-1)*9) + 1;
													cout << "Triple_test_block trying to zero wrong location in Truth Table" << endl;
													cout << "Row: " << irow << " Col: " << icol  << " Val: " << y1 <<   endl;
												}  // end of test on x
											}  // end of test on y1

										}  // end of loop on y
									}  // end of test on z and z1
								}    // end of for loop on z
								

					}
				}
			}   // end of Test 2
			} // end of if test
			
		}  // block i,j
	}
	return nfound;
}   // triple_test_block