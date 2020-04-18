#include <iostream>
using namespace std;

char digit_to_str(int digit)
{
	char s;
	switch(digit) {
	case (0):
		s = '0';
		break;
	case (1):
		s = '1';
		break;
	case (2):
		s = '2';
		break;
	case (3):
		s = '3';
		break;
	case (4):
		s = '4';
		break;
	case (5):
		s = '5';
		break;
	case (6):
		s = '6';
		break;
	case (7):
		s = '7';
		break;
	case (8):
		s = '8';
		break;
	case (9):
		s = '9';
		break;
	default:
		exit (0);
	}
	return s;
		
}