// cl: /O2 /MD
bool __stdcall isLeapYear(int year);
class Rva008B6580Date { public: int daysInMonth(unsigned int month, int year); };

// Open BFME 2 Code/Libraries/Source/Apt/AptDate.cpp.
int Rva008B6580Date::daysInMonth( unsigned int month, int year )
{
	int days = 31;
	switch( month )
	{
	case 0: case 2: case 4: case 6: case 7: case 9: case 11:
		days = 31;
		break;
	case 1:
		{
		typedef bool (Rva008B6580Date::*LeapMember)(int);
		union { bool (__stdcall *entry)(int); LeapMember member; } native;
		typedef char SamePointerWidth[sizeof(native.entry) == sizeof(native.member) ? 1 : -1];
		native.entry = isLeapYear;
		days = 28 + ((this->*native.member)(year) ? 1 : 0);
		}
		break;
	case 3: case 5: case 8: case 10:
		days = 30;
		break;
	}
	return days;
}
