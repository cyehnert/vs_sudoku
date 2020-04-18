#include <iostream>
using namespace std;

void board_display(int board[9][9])
{
	
	int j, k;
	cout << "_______________________________________________________" << endl;
	for (j=0;j<9;j++)
	{
	   for (k=0;k<9;k++)
	  {
		cout << "|  " << "   ";
	  }
	  cout << "|" << endl;
	  for (k=0;k<9;k++)
	  {
		  if (board[j][k] != 0)
		      cout << "|  " << board[j][k] << "  ";
		  else
			  cout << "|     ";
	  }
	  cout << "|" << endl;
	  /*
	  for (k=0;k<9;k++)
	  {
		cout << "|  " << "   ";
	  }
	  cout << "|" << endl;
	  */
	  if (j == 2 || j == 5 || j == 8)
	  cout << "|_________________|_________________|_________________|" << endl;
	  else
	  cout << "| ____ _____ ____ | ____ _____ ____ | ____ _____ ____ |" << endl;
	  //cout << "_______________________________________________________" << endl;
	  
	}
	
}