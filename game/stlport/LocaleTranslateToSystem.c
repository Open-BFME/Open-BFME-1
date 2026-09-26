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

/* Retail 0x0084E0C0 — keep body non-trivial so the call is not inlined; first
 * arg arrives in EAX under the same-TU private convention. */
static int __ParseLocaleString(const char *lname, char *lang, char *ctry, char *page)
{
    int param = 0;
    unsigned int len;
    unsigned int tmpLen;

    if (lname[0] == 0)
        return 0;

    len = strcspn(lname, "_");
    if (lname[len] == '_') {
        if (len == 0 || len > 64)
            return -1;
        strncpy(lang, lname, len);
        lang[len] = 0;
        lname += len + 1;
        ++param;
    }

    len = (unsigned int)-1;
    tmpLen = strcspn(lname, ".");
    while (lname[tmpLen] == '.') {
        len = tmpLen;
        ++tmpLen;
        tmpLen += strcspn(lname + tmpLen, ".");
    }
    if (len != (unsigned int)-1) {
        if (param == 0) {
            if (len > 64)
                return -1;
            if (len == 0)
                ++param;
            else {
                strncpy(lang, lname, len);
                lang[len] = 0;
            }
            ++param;
        } else {
            if (len == 0 || len > 64)
                return -1;
            strncpy(ctry, lname, len);
            ctry[len] = 0;
        }
        ++param;
        lname += len + 1;
    }

    len = strcspn(lname, ",");
    switch (param) {
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
    /* Retail stack: ctry @ +0x10, lang @ +0x58, page @ +0x08 — declare so
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

/* Keep both statics live. */
char *TranslateToSystemKeep(const char *lname, char *buf)
{
    return __TranslateToSystem(lname, buf);
}

int GetLCIDFromNameKeep(const char *lname, LCID *lcid, char *cp)
{
    return __GetLCIDFromName(lname, lcid, cp);
}
