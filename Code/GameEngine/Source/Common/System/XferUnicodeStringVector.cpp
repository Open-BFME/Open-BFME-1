// cl: /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /MD /EHsc /Ireference/shims/stlp_nodealloc /Ireference/shims/asciistring_thin /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWSaveLoad
// stlport

#define BFME_STLP_NODE_ALLOC
#include <vector>

typedef unsigned char UnsignedByte;
typedef unsigned int UnsignedInt;
typedef bool Bool;

template <typename T>
class StringBase
{
    friend class UnicodeString;

private:
    StringBase() : m_data(0) {}
    StringBase(const StringBase<T> &source);
    ~StringBase();

    void *m_data;
};

class UnicodeString : private StringBase<unsigned short>
{
public:
    UnicodeString() : StringBase<unsigned short>() {}
    UnicodeString(const UnicodeString &source) : StringBase<unsigned short>(source) {}
    ~UnicodeString() {}
};

struct XferVersion
{
    UnsignedByte m_version;
    UnsignedByte m_currentVersion;
};

class Xfer
{
public:
    virtual ~Xfer();
    virtual Bool isLoading();
    virtual Bool isSaving();
    virtual void slot03();
    virtual void slot04();
    virtual void slot05();
    virtual void slot06();
    virtual void slot07();
    virtual void slot08();
    virtual void slot09();
    virtual Xfer &xferVersion(XferVersion &version);
    virtual Xfer &xferTypeName(const char *const &name);
    virtual void slot12();
    virtual void slot13();
    virtual void slot14();
    virtual void slot15();
    virtual void slot16();
    virtual void slot17();
    virtual void slot18();
    virtual void slot19();
    virtual void slot20();
    virtual void slot21();
    virtual void slot22();
    virtual void slot23();
    virtual void slot24();
    virtual void xferUnicodeString(UnicodeString &value);
    virtual void slot26();
    virtual void slot27();
    virtual void slot28();
    virtual Xfer &xferUnsignedInt(UnsignedInt &value);
};

struct XferException
{
    char *text;
    int tag;
};

extern "C" XferException *__cdecl bfmeFormatText(
    XferException *result, int tag, const char *format, ...);
extern int g_guardTargetTypeThrowInfo;
extern void __declspec(noreturn) __stdcall _CxxThrowException(
    void *object, void *throwInfo);

typedef _STL::vector<UnicodeString> UnicodeStringVector;

// ?xferUnicodeStringVector@@YAPAVXfer@@PAV1@PAV?$vector@VUnicodeString@@V?$allocator@VUnicodeString@@@_STL@@@_STL@@@Z
Xfer *xferUnicodeStringVector(Xfer *xfer, UnicodeStringVector *vector)
{
    XferVersion version;
    version.m_version = 1;
    version.m_currentVersion = 1;
    xfer->xferVersion(version);

    UnsignedInt count = vector->size();
    xfer->xferTypeName("std::vector").xferUnsignedInt(count);

    if (xfer->isSaving())
    {
        UnicodeString *end = vector->end();
        UnicodeString *current = vector->begin();
        while (current != end)
        {
            xfer->xferUnicodeString(*current);
            ++current;
        }
    }
    else
    {
        if (!vector->empty())
        {
            XferException error;
            bfmeFormatText(&error, 4, "Vector must be empty on load");
            _CxxThrowException(&error, &g_guardTargetTypeThrowInfo);
        }

        vector->reserve(count);
        UnicodeString value;
        while (count != 0)
        {
            --count;
            xfer->xferUnicodeString(value);
            vector->push_back(value);
        }
        --count;
    }
    return xfer;
}
