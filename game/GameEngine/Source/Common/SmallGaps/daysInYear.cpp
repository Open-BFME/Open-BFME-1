// ?daysInYear@@YGHH@Z
int __stdcall daysInYear(int year)
{
	if (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0))
		return 366;
	return 365;
}
