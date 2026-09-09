// cl: /DNDEBUG /MD /EHsc /ICode/GameEngine/Source/Common/System /ICode/Libraries/Source/WWVegas/WWLib
#include "xfer.h"
#include "ascii_string.h"

// Retail exposes these small StringBase operations inline at this caller.
template <typename T>
inline int StringBase<T>::getLength() const
{
    return m_data ? m_data->length : 0;
}

template <>
inline const char *StringBase<char>::str() const
{
    return m_data ? m_data->data : "";
}

template <typename T>
inline void StringBase<T>::clear()
{
    releaseBuffer();
}

class Rva009D6940TransferView
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

Xfer &Xfer::operator==(AsciiString &as)
{
    Rva009D6940TransferView *receiver = reinterpret_cast<Rva009D6940TransferView *>(this);
    if (receiver->isStoring())
    {
        int length = as.getLength();
        if (length >= 255)
        {
            unsigned char marker = 255;
            receiver->transfer(reinterpret_cast<void *>(0x61737472), &marker, 1);
            receiver->transfer(0, &length, 4);
        }
        else
            receiver->transfer(reinterpret_cast<void *>(0x61737472), &length, 1);
        receiver->transfer(0, as.str(), length);
    }
    else
    {
        int length = 0;
        receiver->transfer(reinterpret_cast<void *>(0x61737472), &length, 1);
        if (length == 255)
            receiver->transfer(0, &length, 4);
        if (length != 0)
        {
            receiver->transfer(0, reinterpret_cast<StringBase<char> *>(&as)->getBufferForRead(length), length);
            reinterpret_cast<StringBase<char> *>(&as)->getBufferForRead(length)[length] = 0;
        }
        else
            as.clear();
    }
    return *this;
}
