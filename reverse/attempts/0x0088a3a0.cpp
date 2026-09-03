// ?SimpleMatch@Debug@@SA_NPBD0@Z
// partial score=0.7 date=2026-09-03
// ?SimpleMatch@Debug@@SA_NPBD0@Z
// partial score=0.70 date=2026-09-04
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Oy- /O1
// Open-BFME5: Debug::SimpleMatch case-insensitive wildcard matcher, retail 0x0088A3A0, 132 bytes.
//
// for(;;)+breaks keeps the head str-first (while-shapes rotate pattern-first
// under /O1); /O1+/Oy- groups the prologue pushes (speed-opts interleave a
// deref between the param loads). Single shared star block via goto.
// Residue: entry falls through (retail pads+jumps to an aligned head),
// widened compare is movsx/movsx/add (retail movsx/add/movsx), star-loop
// cleanup is pop/pop (retail add esp,8). No single flag gives grouped
// prologue with add-esp: size-opts pop, speed-opts ungroup (all -G tried).
// Next: add-middle and add-esp walls; layout needs aligned-head trigger.

class Debug
{
public:
	static bool SimpleMatch(const char *str, const char *pattern);
};

// ?SimpleMatch@Debug@@SA_NPBD0@Z
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
		char s = *str;
		char p = *pattern;
		++pattern;
		++str;
		if (s >= 'A' && s <= 'Z')
		{
			if (s + ('a' - 'A') != p)
				return false;
		}
		else if (s != p)
			return false;
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
