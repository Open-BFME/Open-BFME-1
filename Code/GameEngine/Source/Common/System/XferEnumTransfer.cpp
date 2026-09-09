// cl: /DNDEBUG /MD /EHsc /ICode/GameEngine/Source/Common/System
#include "xfer.h"

// Local dispatch view preserves the retail +0x94 transfer slot.
// The shared header still gives that slot the older XferEnum label.
class Rva009D67B0XferView
{
public:
    virtual void slot00();
    virtual void slot01();
    virtual void slot02();
    virtual void slot03();
    virtual void slot04();
    virtual void slot05();
    virtual void slot06();
    virtual void slot07();
    virtual void slot08();
    virtual void slot09();
    virtual void slot10();
    virtual void slot11();
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
    virtual void slot25();
    virtual void slot26();
    virtual void slot27();
    virtual void slot28();
    virtual void slot29();
    virtual void slot30();
    virtual void slot31();
    virtual void slot32();
    virtual void slot33();
    virtual void slot34();
    virtual void slot35();
    virtual void slot36();
    virtual void transfer(void *context, const void *data, unsigned int size);
};

class XferException
{
public:
    XferException(int tag, const char *format, ...);
    XferException(const XferException &that);
    ~XferException();
    char *text;
    int tagValue;
};

// Retail 0x009D67B0 includes the complete four-entry switch table.
Xfer &Xfer::XferEnum(const char *name, void *data, unsigned int size)
{
    Rva009D67B0XferView *receiver = reinterpret_cast<Rva009D67B0XferView *>(this);
    if (size == 0 || size > 4)
        throw XferException(4, 0);
    switch (size)
    {
    case 1:
        receiver->transfer(reinterpret_cast<void *>(0x656E7531), data, 1);
        break;
    case 2:
        receiver->transfer(reinterpret_cast<void *>(0x656E7532), data, 2);
        break;
    case 3:
        receiver->transfer(reinterpret_cast<void *>(0x656E7533), data, 3);
        break;
    case 4:
        receiver->transfer(reinterpret_cast<void *>(0x656E7534), data, 4);
        break;
    }
    return *this;
}
