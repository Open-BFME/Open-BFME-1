// cl: /DNDEBUG /MD /EHsc /ICode/GameEngine/Source/Common/System
#include "xfer.h"

class Rva009D63C0TransferView
{
public:
    virtual void slot00();
    virtual void slot01();
    virtual bool isStoring() const;
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

Xfer &Xfer::XferRawBytes(void *data, unsigned int size)
{
    Rva009D63C0TransferView *receiver = reinterpret_cast<Rva009D63C0TransferView *>(this);
    if (size == 0 || data != 0)
    {
        receiver->transfer(reinterpret_cast<void *>(0x726177), &size, 4);
        receiver->transfer(0, data, size);
    }
    return *this;
}
