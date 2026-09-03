// ?daysInMonth@@YGHIH@Z
// partial score=0.7 date=2026-09-02
// cl: /O2 /DNDEBUG /MD

bool __stdcall isLeapYear(int year);

int __stdcall daysInMonth(unsigned int month, int year)
{
	int days = 31;
	unsigned int m = month;
	if (m > 11)
		return days;
	switch (m)
	{
	case 0:
	case 2:
	case 4:
	case 6:
	case 7:
	case 9:
	case 11:
		return days;
	case 1:
		return 28 + isLeapYear(year);
	case 3:
	case 5:
	case 8:
	case 10:
		return 30;
	default:
		return days;
	}
}
