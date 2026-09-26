// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
#include "ascii_string.h"

// Retail 0x003C7F40, 184 bytes. Its only caller, reached through ILT
// 0x00029B31, is the landed Rva003C7F40Owner::rva003C8030 (0x003C8030); no
// name is proven, so the owner stays address-qualified. Retail cleans up
// three stack arguments (ret 12). The caller passes its incoming ECX straight
// through, so this is a __thiscall member that never reads this. Its direct
// calls copy an AsciiString, join two AsciiStrings with the literal ".", then
// release the temporary buffer.
inline AsciiString::~AsciiString()
{
    ((StringBase<char> *)this)->releaseBuffer();
}

// Retail dispatches through the receiver's vtable at +0x7C. Neither the
// receiver's class nor that slot's semantic name has independent evidence.
class Rva003C7F40Receiver
{
public:
    virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
    virtual void slot04(); virtual void slot05(); virtual void slot06(); virtual void slot07();
    virtual void slot08(); virtual void slot09(); virtual void slot0A(); virtual void slot0B();
    virtual void slot0C(); virtual void slot0D(); virtual void slot0E(); virtual void slot0F();
    virtual void slot10(); virtual void slot11(); virtual void slot12(); virtual void slot13();
    virtual void slot14(); virtual void slot15(); virtual void slot16(); virtual void slot17();
    virtual void slot18(); virtual void slot19(); virtual void slot1A(); virtual void slot1B();
    virtual void slot1C(); virtual void slot1D(); virtual void slot1E();
    virtual void *slot1F(const char *name, int flags);
};

class Rva003C7F40Owner
{
public:
	void *rva003C7F40(Rva003C7F40Receiver *receiver, const AsciiString &left, const AsciiString &right);
};

void *Rva003C7F40Owner::rva003C7F40(
    Rva003C7F40Receiver *receiver,
    const AsciiString &left,
    const AsciiString &right)
{
    if (receiver == 0)
        return 0;

    AsciiString joined = left + "." + right;
    // StringBase<char>'s one-pointer layout has eight header bytes before text.
    const char *header = *(const char *const *)&joined;
    return receiver->slot1F(header ? header + 8 : "", 0);
}
