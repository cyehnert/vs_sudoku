#include <iostream>
using namespace std;

int str_to_digit(char chd)
{
	int digit;
	switch(chd) {
	case ('0'):
		digit = 0;
		break;
	case ('1'):
		digit = 1;
		break;
	case ('2'):
		digit = 2;
		break;
	case ('3'):
		digit = 3;
		break;
	case ('4'):
		digit = 4;
		break;
	case ('5'):
		digit = 5;
		break;
	case ('6'):
		digit = 6;
		break;
	case ('7'):
		digit = 7;
		break;
	case ('8'):
		digit = 8;
		break;
	case ('9'):
		digit = 9;
		break;
	default:
		exit (0);
	}
	return digit;
		
}