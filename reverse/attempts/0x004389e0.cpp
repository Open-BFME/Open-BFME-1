// ?d_004389e0@@YAXXZ
// partial score=0.48 date=2026-09-09
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB
// Scratch reconstruction for the generated 0x004389E0 GameTextManager init.
// The final source will keep the same TU-local ABI views and address-derived
// entry name; this file is intentionally outside Code/.

typedef unsigned short WideChar;
typedef bool Bool;

extern "C" int __cdecl _stricmp(const char *, const char *);
extern "C" __declspec(dllimport) int __stdcall SetWindowTextW(
    void *, const WideChar *);
extern const char *g_strFile;
extern const char *g_csfFile;
extern void *ApplicationHWnd;

template <class T> class StringBase
{
    friend class AsciiString;
    friend class UnicodeString;

private:
    struct Header
    {
        int references;
        unsigned short length;
        unsigned short capacity;
        T text[1];
    };

    StringBase() : m_data(0) {}
    StringBase(const T *text);
    StringBase(const StringBase<T> &other);
    ~StringBase();
    void releaseBuffer();

protected:
    Header *m_data;
};

class AsciiString : private StringBase<char>
{
public:
    AsciiString() : StringBase<char>() {}
    AsciiString(const char *text) : StringBase<char>(text) {}
    AsciiString(const AsciiString &other) : StringBase<char>(other) {}
    ~AsciiString() {}

    void format(AsciiString format, ...);

    const char *str() const
    {
        return m_data ? (const char *)m_data + 8 : (const char *)0x0107388b;
    }
};

class UnicodeString : private StringBase<WideChar>
{
public:
    UnicodeString() : StringBase<WideChar>() {}
    UnicodeString(const WideChar *text) : StringBase<WideChar>(text) {}
    UnicodeString(const UnicodeString &other) : StringBase<WideChar>(other) {}
    ~UnicodeString() {}

    const WideChar *str() const
    {
        return m_data ? (const WideChar *)((const char *)m_data + 8)
            : (const WideChar *)0x0107388c;
    }
};

struct StringInfo
{
    StringInfo();
    ~StringInfo();

    AsciiString label;
    UnicodeString text;
};

struct StringLookUp
{
    AsciiString *label;
    StringInfo *info;
};

class HeaderTemplateString
{
public:
    HeaderTemplateString() : m_text(0) {}
    HeaderTemplateString(const HeaderTemplateString &other);
    HeaderTemplateString(const char *text);
    ~HeaderTemplateString();

    const char *str() const
    {
        return m_text ? m_text + 8 : (const char *)0x0107388b;
    }

private:
    char *m_text;
};

HeaderTemplateString HeaderTemplateGetRegistryLanguage();

class File
{
public:
    virtual ~File();
    virtual Bool open(const char *filename, int access);
    virtual void close();
    virtual int read(void *buffer, int bytes) = 0;
    virtual int write(const void *buffer, int bytes) = 0;
    virtual int seek(int bytes) = 0;
    virtual void nextLine(char *buffer, int bufferSize) = 0;
    virtual Bool scanInt(int &value) = 0;
    virtual Bool scanReal(float &value) = 0;
    virtual Bool scanString(AsciiString &value) = 0;
    virtual Bool print(const char *format, ...) = 0;
    virtual int size();
    virtual int position();
    virtual char *readEntireAndClose() = 0;
    virtual File *convertToRAMFile() = 0;
    virtual void lock();
    virtual void unlock();

    void deleteOnClose()
    {
        *((unsigned char *)this + 0xd) = 1;
    }
};

class FileSystem
{
public:
    File *openFile(const char *filename, int access);
};

class Rva004389E0GameTextManager
{
public:
    virtual void slot00();
    virtual void init();
    virtual void slot02();
    virtual void slot03();
    virtual void slot04();
    virtual void slot05();
    virtual void slot06();
    virtual void slot07();
    virtual void slot08();
    virtual void slot09();
    virtual UnicodeString fetch(const char *label, Bool *exists = 0);
    virtual void slot11();
    virtual void slot12();
    virtual void deinit();

    void initStringFile(File *file, int *count);
    Bool parseStringFile(File *file);
    Bool parseCSF(const char *data);

private:
    unsigned char m_interfaceAndSubsystem[4];
    int m_textCount;
    unsigned char m_fileBuffers[0x7800];
    StringInfo *m_stringInfo;
    StringLookUp *m_stringLUT;
    Bool m_initialized;
    unsigned char m_padding7815[3];
    void *m_noStringList;
    int m_useStringFile;
    int m_language;
    UnicodeString m_failed;
    StringInfo *m_mapStringInfo;
    StringLookUp *m_mapStringLUT;
    int m_mapTextCount;
    void *m_vectorBegin;
    void *m_vectorEnd;
    void *m_vectorCapacity;
};

extern void j_0001efdd();
extern void j_00035175();
extern void j_0003ea77();
extern void j_000323f3();
extern void j_00034676();
extern void j_00045dea();

#pragma comment(linker, "/alternatename:?initStringFile@Rva004389E0GameTextManager@@QAEXPAVFile@@PAH@Z=?j_0001efdd@@YAXXZ")
#pragma comment(linker, "/alternatename:?parseStringFile@Rva004389E0GameTextManager@@QAE_NPAVFile@@@Z=?j_00035175@@YAXXZ")
#pragma comment(linker, "/alternatename:?parseCSF@Rva004389E0GameTextManager@@QAE_NPBD@Z=?j_0003ea77@@YAXXZ")

static void *const *const g_applicationWindow = (void **)0x012ed238;

struct StringLookUpCompare004389E0
{
    void *state;

    bool operator()(const StringLookUp &left,
        const StringLookUp &right) const
    {
        return _stricmp(left.label->str(), right.label->str()) < 0;
    }
};

static void sortStringLookUp(StringLookUp *first, StringLookUp *last,
    StringLookUpCompare004389E0 comp)
{
    if (first != last)
    {
        int n = last - first;
        int k;
        for (k = 0; n != 1; n >>= 1)
            ++k;

        typedef void (__cdecl *Intro)(StringLookUp *, StringLookUp *,
            StringLookUp *, int, StringLookUpCompare004389E0);
        union { void (*raw)(); Intro typed; } intro;
        intro.raw = j_000323f3;
        intro.typed(first, last, (StringLookUp *)0, k * 2, comp);

        typedef void (__cdecl *Insert)(StringLookUp *, StringLookUp *,
            StringLookUpCompare004389E0);
        union { void (*raw)(); Insert typed; } insert;
        insert.raw = j_00034676;

        if (last - first > 16)
        {
            StringLookUp *middle = first + 16;
            insert.typed(first, middle, comp);

            insert.raw = j_00045dea;
            insert.typed(middle, last, comp);
        }
        else
        {
            insert.typed(first, last, comp);
        }
    }
}

void Rva004389E0GameTextManager::init()
{
    AsciiString csfFile;
    csfFile.format(g_csfFile,
        HeaderTemplateGetRegistryLanguage().str());

    if (m_initialized)
        return;

    m_initialized = true;
    m_textCount = 0;

    File *file = 0;
    if (m_useStringFile)
    {
        file = ((FileSystem *)*((void **)0x0134cb48))->openFile(
            g_strFile, 0x21);
        if (file)
        {
            file->deleteOnClose();
            file = file->convertToRAMFile();
            if (file)
            {
                initStringFile(file, &m_textCount);
                if (m_textCount > 0)
                {
                    m_stringInfo = new StringInfo[m_textCount];
                    file->seek(0);
                    if (!parseStringFile(file))
                    {
                        deinit();
                        return;
                    }
                }
                file->close();
            }
        }
    }

    if (!m_textCount)
    {
        file = ((FileSystem *)*((void **)0x0134cb48))->openFile(
            csfFile.str(), 0);
        if (file)
        {
            file->deleteOnClose();
            char *data = file->readEntireAndClose();
            if (data)
            {
                if (!parseCSF(data))
                {
                    deinit();
                    return;
                }
                delete [] data;
            }
        }
    }

    m_stringLUT = new StringLookUp[m_textCount];
    StringLookUp *lut = m_stringLUT;
    StringInfo *info = m_stringInfo;
    for (int i = 0; i < m_textCount; ++i)
    {
        lut->info = info;
        lut->label = &info->label;
        ++lut;
        ++info;
    }

    sortStringLookUp(m_stringLUT, m_stringLUT + m_textCount,
        StringLookUpCompare004389E0());

    UnicodeString ourName = fetch("GUI:Command&ConquerGenerals");
    if (ApplicationHWnd)
    {
        SetWindowTextW(ApplicationHWnd, ourName.str());
    }
}
