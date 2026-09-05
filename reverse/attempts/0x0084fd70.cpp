// __Locale_monetary_create
// partial score=0.5 date=2026-09-05
// cl: /O2 /MD
// STLport 4.5.3 _Locale_numeric_create (0x0084F700) and _Locale_monetary_create
// (0x0084FD70). Both parse a composite "LC_xxx=name;..." string (needle
// "LC_NUMERIC="/"LC_MONETARY=", delimiter ";") or take a plain locale name,
// resolve it with the shared file-static helper __GetLCIDFromName
// (0x0084F020, see LocaleTranslateToSystem.c) and fill their facet struct
// with GetLocaleInfoA fields converted through the shared file-static helper
// __ConvertFromACP (0x0084E4E0, see LocaleCodePageQueries.c).
//
// Both helpers are file-static (internal linkage) in their own retail
// translation units, so they cannot be called across a TU boundary; this file
// carries faithful local copies instead. The two target bodies' own bytes are
// what gets matched -- the call sites into these local replicas -- not the
// replica bodies themselves, so their internal tables are placeholders.
//
// The needle/delimiter string literals below are read from the retail image
// at the DIR32 slots this dump references: 0x012C83A8 -> "LC_NUMERIC",
// 0x012C83A4 -> "LC_MONETARY", 0x011176E8 -> ";".

typedef unsigned long LCID;

extern "C" {

__declspec(dllimport) int __stdcall GetLocaleInfoA(
    LCID locale, unsigned long type, char *data, int count);
__declspec(dllimport) int __stdcall lstrcmpiA(const char *left, const char *right);
__declspec(dllimport) char *__cdecl strncpy(char *destination, const char *source, unsigned int count);
__declspec(dllimport) unsigned int __cdecl strcspn(const char *s, const char *reject);
__declspec(dllimport) char *__cdecl strstr(const char *s, const char *needle);
__declspec(dllimport) char *__cdecl strchr(const char *s, int ch);
__declspec(dllimport) void *__cdecl memset(void *dst, int value, unsigned int size);
__declspec(dllimport) int __cdecl atoi(const char *text);
__declspec(dllimport) void *__cdecl malloc(unsigned int size);
__declspec(dllimport) void __cdecl free(void *memory);
__declspec(dllimport) int __stdcall EnumSystemLocalesA(
    int (__stdcall *callback)(char *), unsigned long flags);
__declspec(dllimport) int __stdcall MultiByteToWideChar(
    unsigned int codePage, unsigned long flags, const char *source, int sourceCount,
    unsigned short *destination, int destinationCount);
__declspec(dllimport) int __stdcall WideCharToMultiByte(
    unsigned int codePage, unsigned long flags, const unsigned short *source,
    int sourceCount, char *destination, int destinationCount,
    const char *defaultChar, int *usedDefaultChar);

int __stdcall EnumLocalesProcA(char *locale);

} // extern "C"

class Rva0084E030Buffer
{
public:
    void squash();
    char m_chars[1];
};

extern "C" {

typedef struct _LOCALECONV2
{
    const char *name;
    const char *abbrev;
} LOCALECONV2;

/* Placeholders: the real tables (0x012C80D0/0x012C82D8) live in the retail
 * TU this helper originally shared with __GetLCIDFromName; this copy only
 * needs to induce the same call-site codegen in the two target bodies. */
static LOCALECONV2 s_language[1] = { { "c", "C" } };
static LOCALECONV2 s_country[1] = { { "us", "US" } };

static int s_FindFlag;
static LCID s_FndLCID;
static const char *s_FndLang;
static const char *s_FndCtry;

static const char *localConvertName(const char *lname, LOCALECONV2 *table, int tableSize)
{
    int i;
    int cmp;
    int low = 0;
    int high = tableSize - 1;
    while (low <= high)
    {
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

static int localParseLocaleString(const char *lname, char *lang, char *ctry, char *page)
{
    int param = 0;
    unsigned int len;
    unsigned int tmpLen;

    if (lname[0] == 0)
        return 0;

    len = strcspn(lname, "_");
    if (lname[len] == '_')
    {
        if (len == 0 || len > 64)
            return -1;
        strncpy(lang, lname, len);
        lang[len] = 0;
        lname += len + 1;
        ++param;
    }

    len = (unsigned int)-1;
    tmpLen = strcspn(lname, ".");
    while (lname[tmpLen] == '.')
    {
        len = tmpLen;
        ++tmpLen;
        tmpLen += strcspn(lname + tmpLen, ".");
    }
    if (len != (unsigned int)-1)
    {
        if (param == 0)
        {
            if (len > 64)
                return -1;
            if (len == 0)
                ++param;
            else
            {
                strncpy(lang, lname, len);
                lang[len] = 0;
            }
            ++param;
        }
        else
        {
            if (len == 0 || len > 64)
                return -1;
            strncpy(ctry, lname, len);
            ctry[len] = 0;
        }
        ++param;
        lname += len + 1;
    }

    len = strcspn(lname, ",");
    switch (param)
    {
    case 0:
        if (len > 64)
            return -1;
        strncpy(lang, lname, len);
        lang[len] = 0;
        break;
    case 1:
        if (len > 64)
            return -1;
        strncpy(ctry, lname, len);
        ctry[len] = 0;
        break;
    default:
        if (len > 5)
            return -1;
        strncpy(page, lname, len);
        page[len] = 0;
        break;
    }
    return 0;
}

static int localGetLCID(const char *lang, const char *ctry, LCID *lcid)
{
    s_FindFlag = 0;
    s_FndLang = lang;
    s_FndCtry = ctry;
    EnumSystemLocalesA(EnumLocalesProcA, 1);
    if (s_FindFlag == 0)
        return -1;
    *lcid = s_FndLCID;
    return 0;
}

static void localMyLtoa(long value, char *buf)
{
    char reverse[64];
    char *ptr = reverse;
    if (value == 0)
        *ptr++ = '0';
    else
    {
        for (; value != 0; value /= 10)
            *ptr++ = (char)(value % 10) + '0';
    }
    while (ptr > reverse)
        *buf++ = *--ptr;
    *buf = '\0';
}

static int localIntGetACP(LCID lcid)
{
    char cp[6];
    GetLocaleInfoA(lcid, 0x1004, cp, 6);
    return atoi(cp);
}

static int localIntGetOCP(LCID lcid)
{
    char cp[6];
    GetLocaleInfoA(lcid, 0x0b, cp, 6);
    return atoi(cp);
}

static int localGetLCIDFromName(const char *lname, LCID *lcid, char *cp)
{
    char ctry[65];
    char lang[65];
    char page[6];
    int result = 0;

    if (lname == 0 || lname[0] == 0)
    {
        *lcid = 0x400;
        return 0;
    }

    memset(lang, 0, 65);
    memset(ctry, 0, 65);
    memset(page, 0, 6);
    if (localParseLocaleString(lname, lang, ctry, page) == -1)
        return -1;

    if (lang[0] == 0 && ctry[0] == 0)
        *lcid = 0x400;
    else if (ctry[0] == 0)
        result = localGetLCID(localConvertName(lang, s_language, 1), 0, lcid);
    else
        result = localGetLCID(
            localConvertName(lang, s_language, 1),
            localConvertName(ctry, s_country, 1),
            lcid);

    if (result == 0)
    {
        if (lstrcmpiA(page, "ACP") == 0 || page[0] == 0)
            localMyLtoa(localIntGetACP(*lcid), cp);
        else if (lstrcmpiA(page, "OCP") == 0)
            localMyLtoa(localIntGetOCP(*lcid), cp);
        else
            strncpy(cp, page, 5);
    }
    return result;
}

static void localConvertFromACP(char *buf, int bufSize, const char *cp)
{
    unsigned short *wideBuffer;
    int wideSize = MultiByteToWideChar(0, 0, buf, -1, 0, 0);
    wideBuffer = (unsigned short *)malloc(sizeof(unsigned short) * (wideSize + 1));
    MultiByteToWideChar(0, 0, buf, -1, wideBuffer, wideSize);
    WideCharToMultiByte(atoi(cp), 0, wideBuffer, -1, buf, bufSize, 0, 0);
    free(wideBuffer);
}

/* 0x0084F700 -- _Locale_numeric_create: 24-byte facet (lcid, cp, decimal
 * point, thousands separator, grouping digit string after squash). */
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
    Locale_numeric_t *obj = (Locale_numeric_t *)malloc(0x18);
    char lname[256];
    char *buf;
    int len;

    if (obj == 0)
        return 0;

    if (name[0] == 'L' && name[1] == 'C' && name[2] == '_')
    {
        char *p = strstr(name, "LC_NUMERIC");
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

    if (localGetLCIDFromName(lname, &obj->lcid, obj->cp) == -1)
    {
        free(obj);
        return 0;
    }

    GetLocaleInfoA(obj->lcid, 0x0e, obj->decimal_point, 4);
    localConvertFromACP(obj->decimal_point, 4, obj->cp);

    GetLocaleInfoA(obj->lcid, 0x0f, obj->thousands_sep, 4);
    localConvertFromACP(obj->thousands_sep, 4, obj->cp);

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

/* 0x0084FD70 -- _Locale_monetary_create: 56-byte facet. */
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

    if (name[0] == 'L' && name[1] == 'C' && name[2] == '_')
    {
        char *p = strstr(name, "LC_MONETARY");
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

    if (localGetLCIDFromName(lname, &obj->lcid, obj->cp) == -1)
    {
        free(obj);
        return 0;
    }

    GetLocaleInfoA(obj->lcid, 0x0e, obj->decimal_point, 4);
    localConvertFromACP(obj->decimal_point, 4, obj->cp);

    GetLocaleInfoA(obj->lcid, 0x0f, obj->thousands_sep, 4);
    localConvertFromACP(obj->thousands_sep, 4, obj->cp);

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
    localConvertFromACP(obj->curr_symbol, 6, obj->cp);

    GetLocaleInfoA(obj->lcid, 0x51, obj->positive_sign, 5);
    localConvertFromACP(obj->positive_sign, 5, obj->cp);

    GetLocaleInfoA(obj->lcid, 0x50, obj->negative_sign, 5);
    localConvertFromACP(obj->negative_sign, 5, obj->cp);

    GetLocaleInfoA(obj->lcid, 0x19, digits, 3);
    obj->frac_digits = atoi(digits);

    GetLocaleInfoA(obj->lcid, 0x1a, digits, 3);
    obj->int_frac_digits = atoi(digits);

    GetLocaleInfoA(obj->lcid, 0x15, obj->frac_digits_raw, 5);
    return obj;
}

} // extern "C"
