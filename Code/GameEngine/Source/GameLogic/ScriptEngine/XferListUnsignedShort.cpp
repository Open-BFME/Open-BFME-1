// Open-BFME5: typed STL list transfer helper, retail 0x000D0D50.
// The retail body is the list serializer twin of xferListInt, with a
// two-byte element transfer through the BFME Xfer slot at +0x7c.
// cl: /O2 /MD /EHsc /D_STLP_USE_STATIC_LIB /ICode/Libraries/Source/WWVegas/WWLib
// stlport

#define _STLP_NO_EXCEPTIONS 1
#include <list>
#include "string_base.h"

typedef unsigned char UnsignedByte;
typedef unsigned short UnsignedShort;
typedef bool Bool;

struct XferVersion
{
    UnsignedByte m_version;
    UnsignedByte m_currentVersion;
};

class Xfer
{
public:
    virtual ~Xfer(void);
    virtual Bool isLoading(void);
    virtual Bool isSaving(void);
    virtual void slot03(void);
    virtual void slot04(void);
    virtual void slot05(void);
    virtual void slot06(void);
    virtual void slot07(void);
    virtual void slot08(void);
    virtual void slot09(void);
    virtual Xfer &xferVersion(XferVersion *version);
    virtual Xfer &xferTypeName(const char *const &name);
    virtual void slot12(void);
    virtual void slot13(void);
    virtual void slot14(void);
    virtual void slot15(void);
    virtual void slot16(void);
    virtual void slot17(void);
    virtual void slot18(void);
    virtual void slot19(void);
    virtual void slot20(void);
    virtual void slot21(void);
    virtual void slot22(void);
    virtual void slot23(void);
    virtual void slot24(void);
    virtual void slot25(void);
    virtual Xfer &xferAsciiString(void *value);
    virtual void slot27(void);
    virtual void slot28(void);
    virtual Xfer &xferUnsignedShort(unsigned int *value);
    virtual void slot30(void);
    virtual Xfer &xferShort(UnsignedShort *value);
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

typedef _STL::list<UnsignedShort> ListUnsignedShort;

// ?xferListUnsignedShort@@YAPAVXfer@@PAV1@PAV?$list@GV?$allocator@G@_STL@@@_STL@@@Z
Xfer *xferListUnsignedShort(Xfer *xfer, ListUnsignedShort *list)
{
    struct XferListLocals
    {
        unsigned int count;
        XferVersion version;
    } locals;

    locals.version.m_version = 1;
    locals.version.m_currentVersion = 1;
    xfer->xferVersion(&locals.version);

    locals.count = list->size();
    xfer->xferTypeName("std::list").xferUnsignedShort(&locals.count);

    if (xfer->isSaving())
    {
        ListUnsignedShort::_Node *sentinel = list->_M_node._M_data;
        ListUnsignedShort::_Node *node =
            (ListUnsignedShort::_Node *)sentinel->_M_next;
        while (node != sentinel)
        {
            xfer->xferShort(&node->_M_data);
            node = (ListUnsignedShort::_Node *)node->_M_next;
        }
    }
    else
    {
        if (!list->empty())
        {
            XferException error;
            bfmeFormatText(&error, 4, "List must be empty on load");
            _CxxThrowException(&error, &g_guardTargetTypeThrowInfo);
        }

        UnsignedShort value;
        while (locals.count != 0)
        {
            --locals.count;
            xfer->xferShort(&value);
            list->push_back(value);
        }
        --locals.count;
    }
    return xfer;
}
