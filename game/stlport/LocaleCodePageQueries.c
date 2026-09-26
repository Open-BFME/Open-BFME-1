// STLport 4.5.3 Win32 locale code-page helpers.

typedef unsigned long LCID;
typedef unsigned int bfme_size_t;

#define LOCALE_IDEFAULTCODEPAGE 0x0000000b
#define LOCALE_IDEFAULTANSICODEPAGE 0x00001004

__declspec(dllimport) int __stdcall GetLocaleInfoA(
    LCID locale, unsigned long type, char *data, int count);
__declspec(dllimport) int __cdecl atoi(const char *text);
__declspec(dllimport) void *__cdecl malloc(unsigned int size);
__declspec(dllimport) void __cdecl free(void *memory);
__declspec(dllimport) char *__cdecl strcpy(char *destination, const char *source);
__declspec(dllimport) char *__cdecl strcat(char *destination, const char *source);
__declspec(dllimport) unsigned int __cdecl strlen(const char *text);
__declspec(dllimport) void *__cdecl memcpy(void *destination, const void *source,
    unsigned int count);
__declspec(dllimport) int __stdcall lstrcmpiA(const char *left, const char *right);
__declspec(dllimport) int __stdcall EnumSystemLocalesA(
    int (__stdcall *callback)(char *), unsigned long flags);
int __stdcall EnumLocalesProcA(char *locale);
__declspec(dllimport) int __stdcall MultiByteToWideChar(
    unsigned int codePage, unsigned long flags, const char *source, int sourceCount,
    unsigned short *destination, int destinationCount);
__declspec(dllimport) int __stdcall WideCharToMultiByte(
    unsigned int codePage, unsigned long flags, const unsigned short *source,
    int sourceCount, char *destination, int destinationCount,
    const char *defaultChar, int *usedDefaultChar);

typedef struct _LOCALECONV
{
    const char *name;
    const char *abbrev;
} LOCALECONV;

typedef struct _Locale_ctype_t
{
    LCID lcid;
    int cp;
} _Locale_ctype_t;

static int __FindFlag;
static LCID __FndLCID;
static const char *__FndLang;
static const char *__FndCtry;

static void my_ltoa(long value, char *buf)
{
    char reverse[64];
    char *ptr = reverse;
    if (value == 0)
        *ptr++ = '0';
    else
    {
        for (; value != 0; value /= 10)
            *ptr++ = (int)(value % 10) + '0';
    }
    while (ptr > reverse)
        *buf++ = *--ptr;
    *buf = '\0';
}

static int __intGetACP(LCID lcid);
static int __intGetOCP(LCID lcid);

int __intGetACP(LCID lcid)
{
    char cp[6];
    GetLocaleInfoA(lcid, LOCALE_IDEFAULTANSICODEPAGE, cp, 6);
    return atoi(cp);
}

int __intGetOCP(LCID lcid)
{
    char cp[6];
    GetLocaleInfoA(lcid, LOCALE_IDEFAULTCODEPAGE, cp, 6);
    return atoi(cp);
}

static int __GetDefaultCP(LCID lcid)
{
    int cp = __intGetACP(lcid);
    if (cp == 0)
        return __intGetOCP(lcid);
    return cp;
}

int __GetLCIDFromName(const char *name, LCID *lcid, char *cp);

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

static const char *__ConvertName(const char *lname, LOCALECONV *table, int tableSize)
{
    int i;
    int cmp = 1;
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

static void __ConvertFromACP(char *buf, int bufSize, const char *cp)
{
    unsigned short *wideBuffer;
    int wideSize = MultiByteToWideChar(0, 0, buf, -1, 0, 0);
    wideBuffer = (unsigned short *)malloc(sizeof(unsigned short) * (wideSize + 1));
    MultiByteToWideChar(0, 0, buf, -1, wideBuffer, wideSize);
    WideCharToMultiByte(atoi(cp), 0, wideBuffer, -1, buf, bufSize, 0, 0);
    free(wideBuffer);
}

static char *__ConvertToCP(int fromCP, int toCP, const char *from,
    bfme_size_t size, bfme_size_t *resultSize)
{
    int wideSize;
    int bufferSize;
    unsigned short *wideBuffer;
    char *buffer;

    wideSize = MultiByteToWideChar(fromCP, 1, from, size, 0, 0);
    wideBuffer = (unsigned short *)malloc(sizeof(unsigned short) * wideSize);
    MultiByteToWideChar(fromCP, 1, from, size, wideBuffer, wideSize);

    bufferSize = WideCharToMultiByte(toCP, 0x220, wideBuffer, wideSize,
        0, 0, 0, 0);
    buffer = (char *)malloc(bufferSize);
    WideCharToMultiByte(toCP, 0x220, wideBuffer, wideSize,
        buffer, bufferSize, 0, 0);

    free(wideBuffer);
    *resultSize = bufferSize;
    return buffer;
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

char *_Locale_common_default(char *buf)
{
    char cp[6];
    int codePage = __intGetACP(0x400);
    if (!codePage)
        codePage = __intGetOCP(0x400);
    my_ltoa(codePage, cp);
    return __GetLocaleName(0x400, cp, buf);
}

char *_Locale_ctype_name(const void *loc, char *buf)
{
    char cpBuf[6];
    _Locale_ctype_t *ctype = (_Locale_ctype_t *)loc;
    my_ltoa(ctype->cp, cpBuf);
    return __GetLocaleName(ctype->lcid, cpBuf, buf);
}

int Rva0084E5B0UseDefaultCPA(LCID lcid)
{
    return __GetDefaultCP(lcid);
}

int Rva0084E5B0UseDefaultCPB(LCID lcid)
{
    return __GetDefaultCP(lcid) + 1;
}

LCID Rva0084E1D0UseLocaleFromHexA(const char *locale)
{
    return LocaleFromHex(locale);
}

LCID Rva0084E1D0UseLocaleFromHexB(const char *locale)
{
    return LocaleFromHex(locale) + 1;
}

const char *Rva0084E070UseConvertNameA(const char *name, LOCALECONV *table, int count)
{
    return __ConvertName(name, table, count);
}

const char *Rva0084E070UseConvertNameB(const char *name, LOCALECONV *table, int count)
{
    const char *result = __ConvertName(name, table, count);
    return result ? result : name;
}

int Rva0084E310UseGetLCIDA(const char *lang, const char *ctry, LCID *lcid)
{
    return __GetLCID(lang, ctry, lcid);
}

int Rva0084E310UseGetLCIDB(const char *lang, const char *ctry, LCID *lcid)
{
    int result = __GetLCID(lang, ctry, lcid);
    return result == 0 ? 1 : result;
}

void Rva0084E4E0UseConvertFromACPA(char *buf, int size, const char *cp)
{
    __ConvertFromACP(buf, size, cp);
}

void Rva0084E4E0UseConvertFromACPB(char *buf, int size, const char *cp)
{
    if (buf)
        __ConvertFromACP(buf, size, cp);
}

char *Rva0084E600UseConvertToCPA(int fromCP, int toCP, const char *from,
    bfme_size_t size, bfme_size_t *resultSize)
{
    return __ConvertToCP(fromCP, toCP, from, size, resultSize);
}

char *Rva0084E600UseConvertToCPB(int fromCP, int toCP, const char *from,
    bfme_size_t size, bfme_size_t *resultSize)
{
    char *result = __ConvertToCP(fromCP, toCP, from, size, resultSize);
    return result ? result : fromCP ? (char *)from : result;
}

extern char locale_buffer_0084EED0[];

typedef struct LocaleCodePageObject_0084EED0
{
    LCID locale;
    char codePage[1];
} LocaleCodePageObject_0084EED0;

char *Rva0084EED0(LocaleCodePageObject_0084EED0 *object)
{
    LCID locale = object->locale;
    GetLocaleInfoA(locale, 0x28, locale_buffer_0084EED0, 9);
    {
        char *buffer = locale_buffer_0084EED0;
        __ConvertFromACP(buffer, 9, object->codePage);
        return buffer;
    }
}

extern char locale_buffer_0084EF00[];

char *Rva0084EF00(LocaleCodePageObject_0084EED0 *object)
{
    LCID locale = object->locale;
    GetLocaleInfoA(locale, 0x29, locale_buffer_0084EF00, 9);
    {
        char *buffer = locale_buffer_0084EF00;
        __ConvertFromACP(buffer, 9, object->codePage);
        return buffer;
    }
}

extern char *__cdecl Rva0084DE40Tail(char *buffer);

char *Rva0084ECA0(LocaleCodePageObject_0084EED0 *object)
{
    LCID locale = object->locale;
    GetLocaleInfoA(locale, 0x1f, locale_buffer_0084EED0, 0x104);
    {
        char *buffer = locale_buffer_0084EED0;
        __ConvertFromACP(buffer, 0x50, object->codePage);
        return Rva0084DE40Tail(buffer);
    }
}

char *Rva0084ECE0(LocaleCodePageObject_0084EED0 *object)
{
    LCID locale = object->locale;
    GetLocaleInfoA(locale, 0x20, locale_buffer_0084EF00, 0x104);
    {
        char *buffer = locale_buffer_0084EF00;
        __ConvertFromACP(buffer, 0x50, object->codePage);
        return Rva0084DE40Tail(buffer);
    }
}

extern char locale_buffer_008504C0[];
extern char locale_output_008504C0[];
extern unsigned short locale_separator_008504C0;
extern char *__cdecl Rva0084ED20Tail(LocaleCodePageObject_0084EED0 *object);

char *Rva008504C0(LocaleCodePageObject_0084EED0 *object)
{
    LCID locale = object->locale;
    GetLocaleInfoA(locale, 0x1f, locale_buffer_008504C0, 0x104);
    {
        char *buffer;
        char *converted;
        char *destination;
        char *suffix;
        char *suffixEnd;
        char ch;
        unsigned int suffixSize;

        buffer = locale_buffer_008504C0;
        __ConvertFromACP(buffer, 0x50, object->codePage);
        converted = Rva0084DE40Tail(buffer);
        strcpy(locale_output_008504C0, converted);

        destination = locale_output_008504C0;
        --destination;
        do
        {
            ch = destination[1];
            ++destination;
        } while (ch);
        *(unsigned short *)destination = locale_separator_008504C0;

        suffix = Rva0084ED20Tail(object);
        suffixSize = strlen(suffix);

        destination = locale_output_008504C0;
        --destination;
        do
        {
            ch = destination[1];
            ++destination;
        } while (ch);
        memcpy(destination, suffix, suffixSize);
        return locale_output_008504C0;
    }
}

extern char locale_buffer_00850560[];
extern char locale_output_00850560[];
extern unsigned short locale_separator_00850560;

char *Rva00850560(LocaleCodePageObject_0084EED0 *object)
{
    LCID locale = object->locale;
    GetLocaleInfoA(locale, 0x20, locale_buffer_00850560, 0x104);
    {
        char *buffer;
        char *converted;
        char *destination;
        char *suffix;
        char *suffixEnd;
        char ch;
        unsigned int suffixSize;

        buffer = locale_buffer_00850560;
        __ConvertFromACP(buffer, 0x50, object->codePage);
        converted = Rva0084DE40Tail(buffer);
        strcpy(locale_output_00850560, converted);

        destination = locale_output_00850560;
        --destination;
        do
        {
            ch = destination[1];
            ++destination;
        } while (ch);
        *(unsigned short *)destination = locale_separator_00850560;

        suffix = Rva0084ED20Tail(object);
        suffixSize = strlen(suffix);

        destination = locale_output_00850560;
        --destination;
        do
        {
            ch = destination[1];
            ++destination;
        } while (ch);
        memcpy(destination, suffix, suffixSize);
        return locale_output_00850560;
    }
}
