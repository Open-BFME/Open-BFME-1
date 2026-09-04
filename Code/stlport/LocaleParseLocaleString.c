// cl: /O2 /MD
// STLport 4.5.3 __ParseLocaleString, retail 0x0084E0C0, 259 bytes.
// First argument arrives in EAX (same-TU private convention). Keep a
// stack-calling wrapper so the static stays live and the body is not inlined.
// Separator set is "_.,". A leading '.' copies the rest into page (max 5)
// and clears lang/ctry. Otherwise fields fill lang, ctry, page in order.

__declspec(dllimport) unsigned int __cdecl strcspn(const char *s, const char *reject);
__declspec(dllimport) char *__cdecl strncpy(char *destination, const char *source, unsigned int count);
__declspec(dllimport) unsigned int __cdecl strlen(const char *s);
__declspec(dllimport) char *__cdecl strcpy(char *destination, const char *source);

static int __ParseLocaleString(const char *lname, char *lang, char *ctry, char *page)
{
	int param = 0;
	unsigned int len;
	char sep;

	if (lname[0] == 0)
		return 0;

	if (lname[0] == '.')
	{
		const char *src = lname + 1;

		if (strlen(src) > 5)
			return -1;
		strcpy(page, src);
		lang[0] = 0;
		ctry[0] = 0;
		return 0;
	}

	for (;;)
	{
		len = strcspn(lname, "_.,");
		sep = lname[len];

		if (param == 0)
		{
			if (len >= 0x40)
				return -1;
			if (sep != '.')
				strncpy(lang, lname, len);
			else
			{
				char *langDest = lang;
				char *ctryDest = ctry;

				ctryDest[0] = 0;
				strncpy(langDest, lname, len);
				param = 1;
			}
		}
		else if (param == 1)
		{
			if (len >= 0x40)
				return -1;
			if (sep == '_')
				return -1;
			strncpy(ctry, lname, len);
		}
		else if (param == 2)
		{
			if (len >= 5)
				return -1;
			if (sep != 0 && sep != ',')
				return -1;
			strncpy(page, lname, len);
		}
		else
			return -1;

		if (sep == ',')
			return 0;
		++param;
		lname += len + 1;
		if (sep == 0)
			return 0;
	}
}

int ParseLocaleStringKeep(const char *lname, char *lang, char *ctry, char *page)
{
	return __ParseLocaleString(lname, lang, ctry, page);
}
