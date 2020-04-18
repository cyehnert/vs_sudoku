#include <iostream>
using namespace std;

void load_tt(int i, int j, int k, int *ptt)
{
    int m;
	
	int ibox;
	int jr;
	int kc;
	// this routine sets up the truth table based
	// on simplistic zeroing of locations in a
	// column, row, plane or 3x3 block where a
	// given value is located
	
	// i is a board value (non-zero)
	// j is a board row
	// k is a board col
	// ptt is a pointer to a truth table
	// set all values in column k
	for (m=0;m<9;m++)
		*(ptt + 9*9*(i-1) +9*j + m) = 0;
		//tt[i-1][j][m]=0;
	// set all values in row j
	for (m=0;m<9;m++)
		*(ptt+9*9*(i-1)+9*m+k) = 0;
		//tt[i-1][m][k]=0;
	
	// set all values in each plane at location (j,k)
	for (m=0;m<9;m++)
		*(ptt+9*9*m+9*j+k)=0;
		//tt[m][j][k]=0;
	// set all values in the 3x3 box containing the location (j,k)
	// box definitions
	// Box 1: rows 1-3, cols 1-3
	// Box 2: rows 1-3, cols 4-6
	// Box 3: rows 1-3, cols 7-9
	// Box 4: rows 4-6, cols 1-3
	// Box 5: rows 4-6, cols 4-6
	// Box 6: rows 4-6, cols 7-9
	// Box 7: rows 7-9, cols 1-3
	// Box 8: rows 7-9, cols 4-6
	// Box 9: rows 7-9, cols 7-9
	
	switch (j)
	{
	case 0:
		jr = 1;
		break;
	case 1:
		jr = 1;
		break;
	case 2:
		jr = 1;
		break;
	case 3:
		jr = 2;
		break;
	case 4:
		jr = 2;
		break;
	case 5:
		jr = 2;
		break;
	case 6:
		jr = 3;
		break;
	case 7:
		jr = 3;
		break;
	case 8:
		jr = 3;
		break;
	}
	switch (k)
	{
	case 0:
		kc = 1;
		break;
	case 1:
		kc = 1;
		break;
	case 2:
		kc = 1;
		break;
	case 3:
		kc = 2;
		break;
	case 4:
		kc = 2;
		break;
	case 5:
		kc = 2;
		break;
	case 6:
		kc = 3;
		break;
	case 7:
		kc = 3;
		break;
	case 8:
		kc = 3;
		break;
	}
	ibox = (jr-1)*3+kc;
	switch (ibox)
	{
	case 1:
		*(ptt+(i-1)*81)=0;
		*(ptt+(i-1)*81+1)=0;
		*(ptt+(i-1)*81+2)=0;
		*(ptt+(i-1)*81+9)=0;
		*(ptt+(i-1)*81+10)=0;
		*(ptt+(i-1)*81+11)=0;
		*(ptt+(i-1)*81+18)=0;
		*(ptt+(i-1)*81+19)=0;
		*(ptt+(i-1)*81+20)=0;
		break;
	case 2:
		*(ptt+(i-1)*81+3)=0;
		*(ptt+(i-1)*81+4)=0;
		*(ptt+(i-1)*81+5)=0;
		*(ptt+(i-1)*81+12)=0;
		*(ptt+(i-1)*81+13)=0;
		*(ptt+(i-1)*81+14)=0;
		*(ptt+(i-1)*81+21)=0;
		*(ptt+(i-1)*81+22)=0;
		*(ptt+(i-1)*81+23)=0;
		break;
	case 3:
		*(ptt+(i-1)*81+6)=0;
		*(ptt+(i-1)*81+7)=0;
		*(ptt+(i-1)*81+8)=0;
		*(ptt+(i-1)*81+15)=0;
		*(ptt+(i-1)*81+16)=0;
		*(ptt+(i-1)*81+17)=0;
		*(ptt+(i-1)*81+24)=0;
		*(ptt+(i-1)*81+25)=0;
		*(ptt+(i-1)*81+26)=0;
		break;
	case 4:
		*(ptt+(i-1)*81+27)=0;
		*(ptt+(i-1)*81+28)=0;
		*(ptt+(i-1)*81+29)=0;
		*(ptt+(i-1)*81+36)=0;
		*(ptt+(i-1)*81+37)=0;
		*(ptt+(i-1)*81+38)=0;
		*(ptt+(i-1)*81+45)=0;
		*(ptt+(i-1)*81+46)=0;
		*(ptt+(i-1)*81+47)=0;
		break;
	case 5:
		*(ptt+(i-1)*81+30)=0;
		*(ptt+(i-1)*81+31)=0;
		*(ptt+(i-1)*81+32)=0;
		*(ptt+(i-1)*81+39)=0;
		*(ptt+(i-1)*81+40)=0;
		*(ptt+(i-1)*81+41)=0;
		*(ptt+(i-1)*81+48)=0;
		*(ptt+(i-1)*81+49)=0;
		*(ptt+(i-1)*81+50)=0;
		break;
	case 6:
		*(ptt+(i-1)*81+33)=0;
		*(ptt+(i-1)*81+34)=0;
		*(ptt+(i-1)*81+35)=0;
		*(ptt+(i-1)*81+42)=0;
		*(ptt+(i-1)*81+43)=0;
		*(ptt+(i-1)*81+44)=0;
		*(ptt+(i-1)*81+51)=0;
		*(ptt+(i-1)*81+52)=0;
		*(ptt+(i-1)*81+53)=0;
		break;
	case 7:
		*(ptt+(i-1)*81+54)=0;
		*(ptt+(i-1)*81+55)=0;
		*(ptt+(i-1)*81+56)=0;
		*(ptt+(i-1)*81+63)=0;
		*(ptt+(i-1)*81+64)=0;
		*(ptt+(i-1)*81+65)=0;
		*(ptt+(i-1)*81+72)=0;
		*(ptt+(i-1)*81+73)=0;
		*(ptt+(i-1)*81+74)=0;
		break;
	case 8:
		*(ptt+(i-1)*81+57)=0;
		*(ptt+(i-1)*81+58)=0;
		*(ptt+(i-1)*81+59)=0;
		*(ptt+(i-1)*81+66)=0;
		*(ptt+(i-1)*81+67)=0;
		*(ptt+(i-1)*81+68)=0;
		*(ptt+(i-1)*81+75)=0;
		*(ptt+(i-1)*81+76)=0;
		*(ptt+(i-1)*81+77)=0;
		break;
	case 9:
		*(ptt+(i-1)*81+60)=0;
		*(ptt+(i-1)*81+61)=0;
		*(ptt+(i-1)*81+62)=0;
		*(ptt+(i-1)*81+69)=0;
		*(ptt+(i-1)*81+70)=0;
		*(ptt+(i-1)*81+71)=0;
		*(ptt+(i-1)*81+78)=0;
		*(ptt+(i-1)*81+79)=0;
		*(ptt+(i-1)*81+80)=0;
		break;
	}
	
	// set the value at given location
	*(ptt+9*9*(i-1)+9*j+k)=1;
	//tt[i-1][j][k]=1;
	return;
}