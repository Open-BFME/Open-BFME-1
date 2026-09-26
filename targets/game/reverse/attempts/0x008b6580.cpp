// ?d_008b6580@@YAXXZ
// partial score=0.93 date=2026-09-26
// cl: /DNDEBUG /DWIN32 /MD /EHsc /O2 /Ob2
// ?daysInMonth@@YGHIH@Z
bool __stdcall isLeapYear( int year );

int __stdcall daysInMonth( unsigned int month, int year )
{
	int days = 31;
	switch( month )
	{
	case 0: case 2: case 4: case 6: case 7: case 9: case 11:
		days = 31;
		break;
	case 1:
		days = isLeapYear( year ) ? 29 : 28;
		break;
	case 3: case 5: case 8: case 10:
		days = 30;
		break;
	}
	return days;
}
