// ?Rva0005DC70CompareWideLengths@@YAHPBGH0H@Z
// partial score=0.97 date=2026-08-31
typedef unsigned short WCHAR;

int __cdecl Rva0005DC70CompareWideLengths(const WCHAR *s1, int len1, const WCHAR *s2, int len2)
{
	int minLen = len1;
	if (minLen >= len2)
	{
		minLen = len2;
	}

	if (minLen > 0)
	{
		do
		{
			if (*s1 != *s2)
			{
				int diff = (int)(unsigned int)*s1 - (int)(unsigned int)*s2;
				if (diff != 0)
				{
					return diff;
				}
				break;
			}
			++s1;
			++s2;
			--minLen;
		} while (minLen > 0);
	}

	return len1 - len2;
}
