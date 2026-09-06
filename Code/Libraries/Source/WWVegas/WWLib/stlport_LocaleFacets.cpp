// cl: /O2 /MD
// STLport 4.5.3 numeric and monetary locale facets.
// Resolver, Windows enumeration callback and all three facets share actual
// file-static lookup state. Real facet callers keep private helper ABIs.

typedef unsigned long LCID;

extern const char *g_Rva012C83A8;
extern const char *g_Rva012C83A4;

extern "C" {

__declspec(dllimport) int __cdecl atoi(const char *text);
__declspec(dllimport) void *__cdecl malloc(unsigned int size);
__declspec(dllimport) void __cdecl free(void *memory);
__declspec(dllimport) char *__cdecl strstr(const char *s, const char *needle);
__declspec(dllimport) char *__cdecl strchr(const char *s, int ch);

__declspec(dllimport) int __stdcall MultiByteToWideChar(
    unsigned int codePage, unsigned long flags, const char *source, int sourceCount,
    unsigned short *destination, int destinationCount);
__declspec(dllimport) int __stdcall WideCharToMultiByte(
    unsigned int codePage, unsigned long flags, const unsigned short *source,
    int sourceCount, char *destination, int destinationCount,
    const char *defaultChar, int *usedDefaultChar);

}

extern "C" {

static void __ConvertFromACP(char *buf, int bufSize, const char *cp)
{
    unsigned short *wideBuffer;
    int wideSize = MultiByteToWideChar(0, 0, buf, -1, 0, 0);
    wideBuffer = (unsigned short *)malloc(sizeof(unsigned short) * (wideSize + 1));
    MultiByteToWideChar(0, 0, buf, -1, wideBuffer, wideSize);
    WideCharToMultiByte(atoi(cp), 0, wideBuffer, -1, buf, bufSize, 0, 0);
    free(wideBuffer);
}

// cl: /O2 /MD
// STLport 4.5.3 __TranslateToSystem (edx-in wrapper) + sibling statics.
// Retail 0x0084F190 calls file-static __GetLCIDFromName (0x0084F020) with the
// MSVC private register convention (lname=edx, lcid*=ebx, cp on stack).

typedef unsigned long LCID;

__declspec(dllimport) int __stdcall GetLocaleInfoA(
    LCID locale, unsigned long type, char *data, int count);
__declspec(dllimport) int __stdcall lstrcmpiA(const char *left, const char *right);
__declspec(dllimport) char *__cdecl strcpy(char *destination, const char *source);
__declspec(dllimport) char *__cdecl strcat(char *destination, const char *source);
__declspec(dllimport) char *__cdecl strncpy(char *destination, const char *source, unsigned int count);
__declspec(dllimport) unsigned int __cdecl strcspn(const char *s, const char *reject);
__declspec(dllimport) void *__cdecl memset(void *dst, int value, unsigned int size);
__declspec(dllimport) int __cdecl atoi(const char *text);
__declspec(dllimport) int __stdcall EnumSystemLocalesA(
    int (__stdcall *callback)(char *), unsigned long flags);
int __stdcall EnumLocalesProcA(char *);

typedef struct _LOCALECONV {
    const char *name;
    const char *abbrev;
} LOCALECONV;

/* Retail tables at 0x012C80D0 (65) and 0x012C82D8 (23). */
extern LOCALECONV __rg_language[];
extern LOCALECONV __rg_country[];

static int __FindFlag;
static LCID __FndLCID;
static const char *__FndLang;
static const char *__FndCtry;

#pragma auto_inline(off)

static void my_ltoa(long value, char *buf)
{
    char reverse[64];
    char *ptr = reverse;
    if (value == 0)
        *ptr++ = '0';
    else {
        for (; value != 0; value /= 10)
            *ptr++ = (char)(value % 10) + '0';
    }
    while (ptr > reverse)
        *buf++ = *--ptr;
    *buf = '\0';
}

static int __intGetACP(LCID lcid)
{
    char cp[6];
    GetLocaleInfoA(lcid, 0x1004, cp, 6);
    return atoi(cp);
}

static int __intGetOCP(LCID lcid)
{
    char cp[6];
    GetLocaleInfoA(lcid, 0x0b, cp, 6);
    return atoi(cp);
}

static const char *__ConvertName(const char *lname, LOCALECONV *table, int tableSize)
{
    int i;
    int cmp;
    int low = 0;
    int high = tableSize - 1;
    while (low <= high) {
        i = (low + high) / 2;
        if ((cmp = lstrcmpiA(lname, table[i].name)) == 0)
            return table[i].abbrev;
        else if (cmp < 0)
            high = i - 1;
        else
            low = i + 1;
    }
    return lname;
}

/* Retail 0x0084E0C0 -- keep body non-trivial so the call is not inlined; first
 * arg arrives in EAX under the same-TU private convention. */
__declspec(dllimport) unsigned int __cdecl strlen(const char *s);
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

static LCID LocaleFromHex(const char *locale)
{
    unsigned long result = 0;
    int digit;
    while (*locale)
    {
        result <<= 4;
        digit = (*locale >= '0' && *locale <= '9') ? *locale - '0' :
            (*locale >= 'A' && *locale <= 'F') ? (*locale - 'A') + 10 :
            (*locale - 'a') + 10;
        result += digit;
        locale++;
    }
    return (LCID)result;
}

static char __LocaleLanguageBuffer[65];
static char __LocaleCountryBuffer[65];

int __stdcall EnumLocalesProcA(char *locale)
{
    LCID lcid = LocaleFromHex(locale);
    int foundLanguage = 0;
    int foundCountry = (__FndCtry == 0);
    GetLocaleInfoA(lcid, 0x1001, __LocaleLanguageBuffer, 64);
    if (lstrcmpiA(__LocaleLanguageBuffer, __FndLang) == 0)
        foundLanguage = 1;
    else {
        GetLocaleInfoA(lcid, 3, __LocaleLanguageBuffer, 64);
        if (lstrcmpiA(__LocaleLanguageBuffer, __FndLang) == 0)
            foundLanguage = 1;
    }
    if (__FndCtry != 0) {
        GetLocaleInfoA(lcid, 0x1002, __LocaleCountryBuffer, 64);
        if (lstrcmpiA(__LocaleCountryBuffer, __FndCtry) == 0)
            foundCountry = 1;
        else {
            GetLocaleInfoA(lcid, 7, __LocaleCountryBuffer, 64);
            if (lstrcmpiA(__LocaleCountryBuffer, __FndCtry) == 0)
                foundCountry = 1;
        }
    }
    if (foundLanguage && foundCountry) {
        __FndLCID = lcid;
        __FindFlag = 1;
        return 0;
    }
    return 1;
}
static int __GetLCID(const char *lang, const char *ctry, LCID *lcid)
{
    __FindFlag = 0;
    __FndLang = lang;
    __FndCtry = ctry;
    EnumSystemLocalesA(EnumLocalesProcA, 1);
    if (__FindFlag == 0)
        return -1;
    *lcid = __FndLCID;
    return 0;
}

static int __GetLCIDFromName(const char *lname, LCID *lcid, char *cp)
{
    /* Retail stack: ctry @ +0x10, lang @ +0x58, page @ +0x08 -- declare so
     * first-use memset hits lang (high) then ctry (low). */
    char ctry[65];
    char lang[65];
    char page[6];
    int result = 0;

    if (lname == 0 || lname[0] == 0) {
        *lcid = 0x400;
        return 0;
    }

    memset(lang, 0, 65);
    memset(ctry, 0, 65);
    memset(page, 0, 6);
    if (__ParseLocaleString(lname, lang, ctry, page) == -1)
        return -1;

    if (lang[0] == 0 && ctry[0] == 0)
        *lcid = 0x400;
    else if (ctry[0] == 0) {
        result = __GetLCID(__ConvertName(lang, __rg_language, 0x41), 0, lcid);
    } else {
        result = __GetLCID(
            __ConvertName(lang, __rg_language, 0x41),
            __ConvertName(ctry, __rg_country, 0x17),
            lcid);
    }

    if (result == 0) {
        if (lstrcmpiA(page, "ACP") == 0 || page[0] == 0)
            my_ltoa(__intGetACP(*lcid), cp);
        else if (lstrcmpiA(page, "OCP") == 0)
            my_ltoa(__intGetOCP(*lcid), cp);
        else
            strncpy(cp, page, 5);
    }
    return result;
}

static char *__GetLocaleName(LCID lcid, const char *cp, char *buf)
{
    char lang[65];
    char country[65];
    GetLocaleInfoA(lcid, 0x1001, lang, 64);
    GetLocaleInfoA(lcid, 0x1002, country, 64);
    strcpy(buf, lang);
    strcat(buf, "_");
    strcat(buf, country);
    strcat(buf, ".");
    return strcat(buf, cp);
}

static char *__TranslateToSystem(const char *lname, char *buf)
{
    LCID lcid;
    char cp[6];
    if (__GetLCIDFromName(lname, &lcid, cp) != 0)
        return 0;
    return __GetLocaleName(lcid, cp, buf);
}

#undef TranslateToSystemKeep
#undef GetLCIDFromNameKeep

}

class Rva0084E030Buffer
{
public:
    void squash();
    char m_chars[1];
};

extern "C" {

typedef struct
{
    LCID lcid;
    char cp[6];
    char decimal_point[4];
    char thousands_sep[4];
    char *grouping;
} Locale_numeric_t;

void *_Locale_numeric_create(const char *name)
{
    char lname[256];
    char *buf;
    int len;
    Locale_numeric_t *obj = (Locale_numeric_t *)malloc(0x18);

    if (obj == 0)
        return 0;

    lname[0] = 0;

    if (name[0] == 'L' && name[1] == 'C' && name[2] == '_')
    {
        char *p = strstr(name, g_Rva012C83A8);
        if (p != 0)
        {
            char *q = strchr(p, '=');
            if (q != 0)
            {
                unsigned int matchLen;
                ++q;
                matchLen = strcspn(q, ";");
                if (matchLen > 0x100)
                    matchLen = 0x100;
                strncpy(lname, q, matchLen);
                lname[matchLen] = 0;
            }
        }
    }
    else
    {
        strncpy(lname, name, 0x100);
    }

    if (__GetLCIDFromName(lname, &obj->lcid, obj->cp) == -1)
    {
        free(obj);
        return 0;
    }

    GetLocaleInfoA(obj->lcid, 0x0e, obj->decimal_point, 4);
    __ConvertFromACP(obj->decimal_point, 4, obj->cp);

    GetLocaleInfoA(obj->lcid, 0x0f, obj->thousands_sep, 4);
    __ConvertFromACP(obj->thousands_sep, 4, obj->cp);

    len = GetLocaleInfoA(obj->lcid, 0x10, 0, 0);
    buf = (char *)malloc(len);
    if (buf == 0)
    {
        obj->grouping = 0;
        return obj;
    }

    GetLocaleInfoA(obj->lcid, 0x10, buf, len);
    ((Rva0084E030Buffer *)buf)->squash();
    obj->grouping = buf;
    return obj;
}

typedef struct
{
    LCID lcid;
    char cp[6];
    char decimal_point[4];
    char thousands_sep[4];
    char *grouping;
    char frac_digits_raw[5];
    char curr_symbol[6];
    char positive_sign[5];
    char negative_sign[5];
    int frac_digits;
    int int_frac_digits;
} Locale_monetary_t;

void *_Locale_monetary_create(const char *name)
{
    Locale_monetary_t *obj = (Locale_monetary_t *)malloc(0x38);
    char lname[256];
    char *buf;
    int len;
    char digits[4];

    if (obj == 0)
        return 0;

    memset(obj, 0, 0x38);
    lname[0] = 0;

    if (name[0] == 'L' && name[1] == 'C' && name[2] == '_')
    {
        char *p = strstr(name, g_Rva012C83A4);
        if (p != 0)
        {
            char *q = strchr(p, '=');
            if (q != 0)
            {
                unsigned int matchLen;
                ++q;
                matchLen = strcspn(q, ";");
                if (matchLen > 0x100)
                    matchLen = 0x100;
                strncpy(lname, q, matchLen);
                lname[matchLen] = 0;
            }
        }
    }
    else
    {
        strncpy(lname, name, 0x100);
    }

    if (__GetLCIDFromName(lname, &obj->lcid, obj->cp) == -1)
    {
        free(obj);
        return 0;
    }

    GetLocaleInfoA(obj->lcid, 0x0e, obj->decimal_point, 4);
    __ConvertFromACP(obj->decimal_point, 4, obj->cp);

    GetLocaleInfoA(obj->lcid, 0x0f, obj->thousands_sep, 4);
    __ConvertFromACP(obj->thousands_sep, 4, obj->cp);

    len = GetLocaleInfoA(obj->lcid, 0x10, 0, 0);
    buf = (char *)malloc(len);
    if (buf == 0)
    {
        obj->grouping = 0;
        return obj;
    }

    GetLocaleInfoA(obj->lcid, 0x10, buf, len);
    ((Rva0084E030Buffer *)buf)->squash();
    obj->grouping = buf;

    GetLocaleInfoA(obj->lcid, 0x14, obj->curr_symbol, 6);
    __ConvertFromACP(obj->curr_symbol, 6, obj->cp);

    GetLocaleInfoA(obj->lcid, 0x51, obj->positive_sign, 5);
    __ConvertFromACP(obj->positive_sign, 5, obj->cp);

    GetLocaleInfoA(obj->lcid, 0x50, obj->negative_sign, 5);
    __ConvertFromACP(obj->negative_sign, 5, obj->cp);

    GetLocaleInfoA(obj->lcid, 0x19, digits, 3);
    obj->frac_digits = atoi(digits);

    GetLocaleInfoA(obj->lcid, 0x1a, digits, 3);
    obj->int_frac_digits = atoi(digits);

    GetLocaleInfoA(obj->lcid, 0x15, obj->frac_digits_raw, 5);
    return obj;
}

}

extern const char *g_Rva012C839C;
typedef struct
{
    LCID lcid;
    char cp[6];
} Locale_collate_t;

extern "C" void *_Locale_collate_create(const char *name)
{
    Locale_collate_t *obj = (Locale_collate_t *)malloc(0xc);
    char lname[256];

    if (obj == 0)
        return 0;

    memset(obj, 0, 0xc);
    lname[0] = 0;

    if (name[0] == 'L' && name[1] == 'C' && name[2] == '_')
    {
        char *p = strstr(name, g_Rva012C839C);
        if (p != 0)
        {
            char *q = strchr(p, '=');
            if (q != 0)
            {
                unsigned int matchLen;
                ++q;
                matchLen = strcspn(q, ";");
                if (matchLen > 0x100)
                    matchLen = 0x100;
                strncpy(lname, q, matchLen);
                lname[matchLen] = 0;
            }
        }
    }
    else
    {
        strncpy(lname, name, 0x100);
    }

    if (__GetLCIDFromName(lname, &obj->lcid, obj->cp) == -1)
    {
        free(obj);
        return 0;
    }
    return obj;
}
