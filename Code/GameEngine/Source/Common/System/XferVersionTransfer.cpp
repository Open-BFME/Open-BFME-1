// cl: /DNDEBUG /MD /EHsc /ICode/GameEngine/Source/Common/System
#include "xfer.h"

class Rva009D6430XferView
{
public:
    virtual ~Rva009D6430XferView(void);
    virtual void slot01(void);
    virtual bool isStoring(void) const;              // +08
    virtual void slot03(void);
    virtual void slot04(void);
    virtual void slot05(void);
    virtual void slot06(void);
    virtual void slot07(void);
    virtual void slot08(void);
    virtual void slot09(void);
    virtual void slot10(void);
    virtual void slot11(void);
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
    virtual void slot26(void);
    virtual void slot27(void);
    virtual void slot28(void);
    virtual void slot29(void);
    virtual void slot30(void);
    virtual void slot31(void);
    virtual void slot32(void);
    virtual void slot33(void);
    virtual void slot34(void);
    virtual void slot35(void);
    virtual void slot36(void);
    virtual void transfer(void *context, const void *data, unsigned int size); // +94
};

class XferException
{
public:
    XferException(int tag, const char *format, ...);
    XferException(const XferException &that);
    ~XferException(void);
    char *text;
    int tagValue;
};

Xfer &Xfer::operator==(Version &v)
{
    Rva009D6430XferView *receiver =
        reinterpret_cast<Rva009D6430XferView *>(this);

    if (receiver->isStoring())
    {
        receiver->transfer(reinterpret_cast<void *>(0x00766572),
                            &v.data[1], 1);
    }
    else
    {
        unsigned char previousVersion;
        unsigned char loadedVersion;
        unsigned char earliestVersion;
        {
            previousVersion = v.data[1];
            receiver->transfer(reinterpret_cast<void *>(0x00766572), &v.data[1], 1);
            loadedVersion = v.data[1];
            earliestVersion = v.data[0];
        }
        if (loadedVersion < earliestVersion)
            throw XferException(2, "Found version %i but the earliest supported is %i",
                                loadedVersion, earliestVersion);
        if (loadedVersion > previousVersion)
            throw XferException(3, "Don't know how to load version %i (most recent is %i)",
                                loadedVersion, previousVersion);
    }
    return *this;
}
