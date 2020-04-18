#include <iostream>
#include <fstream>
#include <new>
#include <stdio.h>
using namespace std;

struct p_moves {
	int n;
	int v[9];
};
struct guess {
	int row;
	int col;
	int val;
};
int str_to_digit(char );
void board_display(int [9][9]);
char digit_to_str(int a);
void load_tt(int a, int b, int c, int *d);
int find_s(int nsoln, int *ptt, int *psoln, int *pz9);
int find_sc(int nsoln, int *ptt, int *psoln, int *pz9);
int find_sb(int nsoln, int *ptt, int *psoln, int *pz9);
int find_sp(int nsoln, int *ptt, int *psoln, int *pz9);
int duplicate_solns(int ns, int *psoln);
int is_soln(int nval, int nrow, int ncol, int nsoln, int soln[]);
void init_pm(struct p_moves *pm);
void load_pm(int *ptt,struct p_moves *pm);
void save_reset(int guess_mode, struct p_moves *pm, struct p_moves *pm_sav, int [9][9], int [9][9]);
int biset_test_row(int *ptt,struct p_moves *pm);
int biset_test_col(int *ptt,struct p_moves *pm);
int biset_test_block(int *ptt,struct p_moves *pm);
int triset_test_row(int *ptt,struct p_moves *pm);
int triset_test_col(int *ptt,struct p_moves *pm);
int triset_test_block(int *ptt,struct p_moves *pm);
int triple_test_row(int *ptt,struct p_moves *pm);
int triple_test_col(int *ptt,struct p_moves *pm);
int triple_test_block(int *ptt,struct p_moves *pm);

int main(void)
{
	FILE *fp;
	FILE *ft;
	int board[9][9];
	int board_sav[9][9];
	int tt[729];
	int *ptt;    // pointer to truth table
	int tt_sav[729];  // save truth table on a guess
	int *ptt_sav;  // pointer to saved truth table
	char s;
	int nf;
	int ns;
	int *pz9;     // need pointer here so I can update value of z9 inside find_s, etc
	int z9;       // number of inconsistencies in truth table
	int i,j,k,m;
	char fname[30];
	char pline[15];
	int dgt[9];
	int nsoln;     //number of solutions
	int soln[99];
	int *psoln;
	int nval, nrow, ncol;
	int istop;
	int icheck;
	int nfound;
	int nfound_sum;
	int guess_mode;
	struct p_moves *pm;
	struct p_moves *pm_sav;
	struct guess gs_sav;
	//
	cout << "Please enter filename of numbers file : ";
   cin >> fname;
   cout << fname << endl;
   fp = fopen(fname,"r");
   //fp = fopen_s(fname);
   //if (inp.is_open()){
   if (fp != NULL) {
	   cout << "File " << fname << " is open.\n";
   }
   else
   {
	   cout << "File " << fname << " is not open.\n";
   }
   if (fp == NULL) {
	   cout << "Cannot open file " << fname << ".\n";
	   //return 1;
   }
   j=0;
   nfound=0;
   do{
	   fgets(pline,15,fp);
	   nf=strlen(pline);
	   
	   for (k=0;k<nf-1;k++)
	   {
		   s = pline[k];
		   dgt[k] = str_to_digit(s);
		   board[j][k] = dgt[k];
	   }
	   j++;
	   //cout << "Reading Sring " << pline << endl;
	   //cout << "Containing " << nf-1 << " characters." << endl;
   }while (j<nf-1 && (!feof(fp)));
   fclose(fp);
   /*
   for (j=0; j<nf-1; j++)
   {
	   for (k=0; k<nf-1; k++)
	   {
		   if (board[j][k] != 0)
		   cout << "J " << j << " K " << k << " " << board[j][k] << endl;
	   }
   }
   */
  // board_display(board);
   //  initialize truth tables tt

		   guess_mode = 0;
		   z9 = 0;
		   for (i=0;i<729;i++)
		    tt[i] = -1;    // initialize all locations to unknown (-1)
   // intialize structure of possible moves
		   pm = new struct p_moves [81];
		   init_pm(pm);
		   pm_sav = new struct p_moves [81];  // load this array if a guess is made
		   
	
   //  for each non-zero element in board, fill in the appropriate 
   //  truth table locations
   //  i : first index : range 0 to 8 for table values 1 to 9
   //  j : second index : range 0 to 8 for rows 1 to 9 starting  top to bottom
   //  k : third index  : range 0 to 8 for cols 1 to 9 starting left to right
   ptt = tt;   // assign ptt to beginning of truth table
   ptt_sav = tt_sav; // assign ptt_sav to beginning of saved truth table
   pz9 = &z9;
   for (j=0;j<9;j++)
   {
	   for (k=0;k<9;k++)
	   {
		   i = board[j][k];
		   if (i != 0) load_tt(i,j,k,ptt);
	   }
   }
   // count locations loaded
   /*
   m=0;
   for (i=0;i<729;i++)
       if (tt[i] == 1) 
	   {
		   m++;
//		   cout << "Location " << m << " at " << i << endl;
	   }
	   */
	load_pm(ptt,pm);
    nfound_sum = 0;
	nfound = biset_test_row(ptt,pm);
	if (nfound > 0)
		cout << "Biset_Row Altered " << nfound << " locations in truth table" << endl;
	nfound_sum += nfound;
	nfound = biset_test_col(ptt,pm);
	if (nfound > 0)
		cout << "Biset_Col Altered " << nfound << " locations in truth table" << endl;
	nfound_sum += nfound;
	if (nfound_sum > 0) 
	{
		init_pm(pm);
		load_pm(ptt,pm);
		nfound_sum = 0;
	}
	nfound = biset_test_block(ptt,pm);
		if (nfound > 0)
		cout << "Biset_Block Altered " << nfound << " locations in truth table" << endl;
	nfound_sum += nfound;
	if (nfound_sum > 0) 
	{
		init_pm(pm);
		load_pm(ptt,pm);
		nfound_sum = 0;
	}
	nfound = triset_test_row(ptt,pm);
	if (nfound > 0)
		cout << "Triset_Row Altered " << nfound << " locations in truth table" << endl;
	nfound_sum += nfound;
    nfound = triset_test_col(ptt,pm);
	if (nfound > 0)
		cout << "Triset_Col Altered " << nfound << " locations in truth table" << endl;
	nfound_sum += nfound;
	if (nfound_sum > 0) 
	{
		init_pm(pm);
		load_pm(ptt,pm);
		nfound_sum = 0;
	}
	nfound = triset_test_block(ptt,pm);
	if (nfound > 0)
		cout << "Triset_Block Altered " << nfound << " locations in truth table" << endl;
	nfound_sum += nfound;
	if (nfound_sum > 0) 
	{
		init_pm(pm);
		load_pm(ptt,pm);
		nfound_sum = 0;
	}
	//
    nfound = triple_test_row(ptt,pm);
	if (nfound > 0)
		cout << "Triple_Row Altered " << nfound << " locations in truth table" << endl;
	nfound_sum += nfound;
    nfound = triple_test_col(ptt,pm);
	if (nfound > 0)
		cout << "Triple_Col Altered " << nfound << " locations in truth table" << endl;
	nfound_sum += nfound;
	if (nfound_sum > 0) 
	{
		init_pm(pm);
		load_pm(ptt,pm);
		nfound_sum = 0;
	}
	//
	nfound = triple_test_block(ptt,pm);
	if (nfound > 0)
		cout << "Triple_Block Altered " << nfound << " locations in truth table" << endl;
	nfound_sum += nfound;
	if (nfound_sum > 0) 
	{
		init_pm(pm);
		load_pm(ptt,pm);
		nfound_sum = 0;
	}
	
	//cout << "Biset Altered " << nfound << " locations in truth table" << endl;

   //cout << "found " << m << " locations set in truth table " << endl;
   // number of solutions
   nsoln = 0;
   z9 = 0;
   for (i=0;i<99;i++) soln[i]=0;
   psoln = soln;
   nsoln = find_s(nsoln, ptt, psoln, pz9);
   nsoln = find_sc(nsoln, ptt, psoln, pz9);
   nsoln = find_sb(nsoln, ptt, psoln, pz9);
   nsoln = find_sp(nsoln, ptt, psoln, pz9);
   ns = nsoln;
   nsoln = duplicate_solns(ns, psoln);
   /*
   cout << "found " << nsoln << "  solutions." << endl;
   for (i=0;i<nsoln;i++)
	   cout << "Val  Row  Col  " << soln[3*i] << " " << soln[3*i+1] << " " << soln[3*i+2] << endl;
	   */
   //
   istop = 1;
   do
   {
		cout << "User Options : " << endl;
		cout << "     c - edit possible moves at one location " << endl;
		cout << "     d - display the board " << endl;
		cout << "     g - enter a guess " << endl;
		cout << "     n - how many moves are available? " << endl;
		cout << "     m - enter a move " << endl;
		cout << "     p - display the possible moves grid " << endl;
		cout << "     r - reset position to previous guess " << endl;
		cout << "     s - save the current position " << endl;
		cout << "     t - save the current truth table " << endl;
		cout << "     q - quit the program" << endl;
		cin >> s;
	    switch (s)
	   {
		   case 'c':
			   cout << "Enter row   : ";
			   cin >> nrow;
			   cout << "Enter col   : ";
			   cin >> ncol;
			   if (nrow > 9) nrow = 9;
			   if (ncol > 9) ncol = 9;
			   m = pm[9*(nrow-1)+ncol-1].n;
			   if (m == 0)
				   cout << "No moves available " ;
			   else
				   for (j=0;j<m;j++)
					   cout << pm[9*(nrow-1)+ncol-1].v[j] << "  ";
			   cout << endl;
			   break;
		   case 'd':
			   board_display(board);
			   break;
		   case 'g':
			   if (guess_mode == 0)
			   {
			   guess_mode = 1;
			   for (i=0;i<729;i++) ptt_sav[i] = ptt[i];
			   save_reset(guess_mode, pm, pm_sav, board, board_sav);
			   cout << "Enter row   : ";
			   cin >> nrow;
			   cout << "Enter col   : ";
			   cin >> ncol;
			   cout << "Enter value : ";
			   cin >> nval;
			   gs_sav.row = nrow;
			   gs_sav.col = ncol;
			   gs_sav.val = nval;
			   cout << "Current position has been saved" << endl;
			   cout << "Proceeding with guess without checking logic" << endl;
			       board[nrow-1][ncol-1] = nval;
				   load_tt(nval,nrow-1,ncol-1,ptt);
				   init_pm(pm);
				   load_pm(ptt,pm);
					nfound_sum = 0;
					nfound = biset_test_row(ptt,pm);
					if (nfound > 0)
						cout << "Biset_Row Altered " << nfound << " locations in truth table" << endl;
					nfound_sum += nfound;
					nfound = biset_test_col(ptt,pm);
					if (nfound > 0)
						cout << "Biset_Col Altered " << nfound << " locations in truth table" << endl;
					nfound_sum += nfound;
					if (nfound_sum > 0) 
						{
							init_pm(pm);
							load_pm(ptt,pm);
							nfound_sum = 0;
						}
					nfound = biset_test_block(ptt,pm);
					if (nfound > 0)
						cout << "Biset_Block Altered " << nfound << " locations in truth table" << endl;
					nfound_sum += nfound;
					if (nfound_sum > 0) 
					{
						init_pm(pm);
						load_pm(ptt,pm);
						nfound_sum = 0;
					}
					nfound = triset_test_row(ptt,pm);
					if (nfound > 0)
						cout << "Triset_Row Altered " << nfound << " locations in truth table" << endl;
					nfound_sum += nfound;
                    nfound = triset_test_col(ptt,pm);
					if (nfound > 0)
						cout << "Triset_Col Altered " << nfound << " locations in truth table" << endl;
					nfound_sum += nfound;
					if (nfound_sum > 0) 
					{
						init_pm(pm);
						load_pm(ptt,pm);
						nfound_sum = 0;
					}
					nfound = triset_test_block(ptt,pm);
					if (nfound > 0)
						cout << "Triset_Block Altered " << nfound << " locations in truth table" << endl;
					nfound_sum += nfound;
					if (nfound_sum > 0) 
					{
						init_pm(pm);
						load_pm(ptt,pm);
						nfound_sum = 0;
					}
					//
					nfound = triple_test_row(ptt,pm);
	                if (nfound > 0)
		                cout << "Triple_Row Altered " << nfound << " locations in truth table" << endl;
	                nfound_sum += nfound;
                    nfound = triple_test_col(ptt,pm);
	                if (nfound > 0)
		                cout << "Triple_Col Altered " << nfound << " locations in truth table" << endl;
	                nfound_sum += nfound;
	                if (nfound_sum > 0) 
	                {
		               init_pm(pm);
		               load_pm(ptt,pm);
		               nfound_sum = 0;
	                }
					//
	                nfound = triple_test_block(ptt,pm);
	                if (nfound > 0)
		                cout << "Triple_Block Altered " << nfound << " locations in truth table" << endl;
	                nfound_sum += nfound;
	                if (nfound_sum > 0) 
	                {
		               init_pm(pm);
		               load_pm(ptt,pm);
		               nfound_sum = 0;
	                }
					//cout << "Biset Altered " << nfound << " locations in truth table" << endl;
					nsoln = 0;
					for (i=0;i<99;i++) soln[i]=0;
					 psoln = soln;
					 nsoln = find_s(nsoln, ptt, psoln, pz9);
				     nsoln = find_sc(nsoln, ptt, psoln, pz9);
					 nsoln = find_sb(nsoln, ptt, psoln, pz9);
					 nsoln = find_sp(nsoln, ptt, psoln, pz9);
					 ns = nsoln;
					 nsoln = duplicate_solns(ns, psoln);
			   }
			   else
				   cout << "A current guess is in progress. Need to reset the board to make a new guess." << endl;
			   break;
		   case 'n':
			   cout << "Number of solutions: " << nsoln << endl;
			   break;
		   case 'm':
			   cout << "Enter row   : ";
			   cin >> nrow;
			   cout << "Enter col   : ";
			   cin >> ncol;
			   cout << "Enter value : ";
			   cin >> nval;
			   // need to check nval, nrow, and ncol against the list of solutions
			   icheck = is_soln(nval,nrow,ncol,nsoln,soln);
			   if (icheck == 1)
			   {
				   cout << "OK to continue" << endl;
			       board[nrow-1][ncol-1] = nval;
				   load_tt(nval,nrow-1,ncol-1,ptt);
				   init_pm(pm);
				   load_pm(ptt,pm);
					nfound_sum = 0;
					nfound = biset_test_row(ptt,pm);
					if (nfound > 0)
						cout << "Biset_Row Altered " << nfound << " locations in truth table" << endl;
					nfound_sum += nfound;
					nfound = biset_test_col(ptt,pm);
					if (nfound > 0)
						cout << "Biset_Col Altered " << nfound << " locations in truth table" << endl;
					nfound_sum += nfound;
					if (nfound_sum > 0) 
						{
							init_pm(pm);
							load_pm(ptt,pm);
							nfound_sum = 0;
						}
					nfound = biset_test_block(ptt,pm);
					if (nfound > 0)
						cout << "Biset_Block Altered " << nfound << " locations in truth table" << endl;
					nfound_sum += nfound;
					if (nfound_sum > 0) 
					{
						init_pm(pm);
						load_pm(ptt,pm);
						nfound_sum = 0;
					}
					nfound = triset_test_row(ptt,pm);
					if (nfound > 0)
						cout << "Triset_Row Altered " << nfound << " locations in truth table" << endl;
					nfound_sum += nfound;
                    nfound = triset_test_col(ptt,pm);
					if (nfound > 0)
						cout << "Triset_Col Altered " << nfound << " locations in truth table" << endl;
					nfound_sum += nfound;
					if (nfound_sum > 0) 
					{
						init_pm(pm);
						load_pm(ptt,pm);
						nfound_sum = 0;
					}
					nfound = triset_test_block(ptt,pm);
					if (nfound > 0)
						cout << "Triset_Block Altered " << nfound << " locations in truth table" << endl;
					nfound_sum += nfound;
					if (nfound_sum > 0) 
					{
						init_pm(pm);
						load_pm(ptt,pm);
						nfound_sum = 0;
					}
					nfound = triple_test_row(ptt,pm);
	                if (nfound > 0)
		                cout << "Triple_Row Altered " << nfound << " locations in truth table" << endl;
	                nfound_sum += nfound;
                    nfound = triple_test_col(ptt,pm);
	                if (nfound > 0)
		                cout << "Triple_Col Altered " << nfound << " locations in truth table" << endl;
	                nfound_sum += nfound;
	                if (nfound_sum > 0) 
	                {
		               init_pm(pm);
		               load_pm(ptt,pm);
		               nfound_sum = 0;
	                }
					
					nfound = triple_test_block(ptt,pm);
	                if (nfound > 0)
		                cout << "Triple_Block Altered " << nfound << " locations in truth table" << endl;
	                nfound_sum += nfound;
	                if (nfound_sum > 0) 
	                {
		               init_pm(pm);
		               load_pm(ptt,pm);
		               nfound_sum = 0;
	                }
					//cout << "Biset Altered " << nfound << " locations in truth table" << endl;
					nsoln = 0;
					for (i=0;i<99;i++) soln[i]=0;
					 psoln = soln;
					 nsoln = find_s(nsoln, ptt, psoln, pz9);
				     nsoln = find_sc(nsoln, ptt, psoln, pz9);
					 nsoln = find_sb(nsoln, ptt, psoln, pz9);
					 nsoln = find_sp(nsoln, ptt, psoln, pz9);
					 ns = nsoln;
					 nsoln = duplicate_solns(ns, psoln);
			   }
			   else
				   cout << "Cannot confirm this location" << endl;
			   break;
		   case 'p':
			   	cout << "Edit PM array" << endl;
				for (i=0;i<9;i++)
				{
					for (j=0;j<9;j++)
					{
						cout << pm[9*i+j].n << " ";
					}
					cout << endl;
					}
			   break;
		   case 'r':
			   if (guess_mode == 1)
			   {
			     guess_mode = 0;
				 cout << "Reset truth table with z9 = " << z9 << endl;
				 cout << "Previously saved row   = " << gs_sav.row << endl;
				 cout << "Previously saved col   = " << gs_sav.col << endl;
				 cout << "Previously saved value = " << gs_sav.val << endl;
			     for (i=0;i<729;i++) ptt[i] = ptt_sav[i];
			     save_reset(guess_mode, pm, pm_sav, board, board_sav);
				 // if an inconsistency has been found, make adjustment in truth table
				 if (z9 != 0) 
				 {
					 cout << "Updating Truth Tables after Reset from Inconsistency." << endl;
					 ptt[9*9*(gs_sav.val-1) + 9*(gs_sav.row-1) + gs_sav.col-1] = 0;
			     	 init_pm(pm);
					 load_pm(ptt,pm);
			   }
				 nsoln = 0;
				 z9 = 0;
			     for (i=0;i<99;i++) soln[i]=0;
					 psoln = soln;
					 nsoln = find_s(nsoln, ptt, psoln, pz9);
				     nsoln = find_sc(nsoln, ptt, psoln, pz9);
					 nsoln = find_sb(nsoln, ptt, psoln, pz9);
					 nsoln = find_sp(nsoln, ptt, psoln, pz9);
					 ns = nsoln;
					 nsoln = duplicate_solns(ns, psoln);
			   }
			   else
				   cout << "Can request this following a previous guess." << endl;
			   break;
		   case 's':
			   //  board position
			   cout << "Please enter filename of file to save: ";
			   cin >> fname;
			   cout << fname << endl;
			   fp = fopen(fname,"w");
			   for (j=0;j<9;j++)
			   {
				   for (k=0;k<9;k++)
				   {
					   fprintf(fp, "%c",digit_to_str(board[j][k]));
				   }
				   fprintf(fp,"\n");
			   }
			   fclose(fp);
			   break;
		   case 't':
			   //   truth table
			   cout << "Please enter filename of file to save: ";
			   cin >> fname;
			   cout << fname << endl;
			    ft = fopen(fname,"w");
				m=0;
				for(i=0;i<9;i++)
				{
				 fprintf(ft," %d : \n",i+1);
				 for (k=0; k<9;k++)
				 {
					for (j=0;j<9;j++)
					{
					  if (tt[m] < 0)
						fprintf(ft," %d ",tt[m]);
					  else
						 fprintf(ft,"  %d ",tt[m]);
					 m++;
					 }
					fprintf(ft,"\n");
				  }
	             }
	             fclose(ft);
				break;
		   case 'q':
			   istop = 0;
			   break;
	   }
   } while (istop == 1);
   delete [] pm;
return 0;
}