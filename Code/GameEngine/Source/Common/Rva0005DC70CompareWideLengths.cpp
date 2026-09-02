// cl: /DNDEBUG /MD
//
// Retail 0x0005DC70: lexicographic compare of two wide-char runs by length.
// Returns the first differing code-unit delta, else len1 - len2.
//
// Register-order levers (docs/lessons.md): retail loads s2 into esi and s1
// into edx BEFORE the minLen guard, so the parameters are copied into locals
// after the min computation and before the guard -- and s2's local is
// defined first, because MSVC 7.1 hands out registers in definition order.

typedef unsigned short WCHAR;

int __cdecl Rva0005DC70CompareWideLengths( const WCHAR *s1, int len1, const WCHAR *s2, int len2 )
{
	int minLen = len1;
	if (minLen >= len2)
		minLen = len2;

	const WCHAR *q = s2;
	const WCHAR *p = s1;
	if (minLen > 0)
	{
		do
		{
			if (*p != *q)
			{
				int diff = (int)(unsigned int)*p - (int)(unsigned int)*q;
				if (diff != 0)
					return diff;
				break;
			}
			++p;
			++q;
			--minLen;
		} while (minLen > 0);
	}
	return len1 - len2;
}
