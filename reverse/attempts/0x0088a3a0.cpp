// ?SimpleMatch@Debug@@SA_NPBD0@Z
// partial score=0.72 date=2026-09-03
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Oy- /O1

class Debug
{
public:
	static bool SimpleMatch(const char *str, const char *pattern);
};

bool Debug::SimpleMatch(const char *str, const char *pattern)
{
	for (;;)
	{
		if (*str == 0)
			break;
		if (*pattern == 0)
			break;
		if (*pattern == '*')
			goto match_star;

		if (*str >= 'A' && *str <= 'Z')
		{
			if ((*str++ + ('a' - 'A')) != *pattern++)
				return false;
		}
		else
		{
			if (*str++ != *pattern++)
				return false;
		}
	}

	if (*pattern != '*')
		return *str == *pattern;

match_star:
	++pattern;
	while (*str)
	{
		if (SimpleMatch(str++, pattern))
			return true;
	}
	return *str == *pattern;
}
