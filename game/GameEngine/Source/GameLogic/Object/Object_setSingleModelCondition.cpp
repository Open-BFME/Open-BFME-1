// cl: /DNDEBUG /MD /Gy /O2 /Ob1
// Object helper at 0x000F2150 (71B): BitFlags local, set one bit, forward.
//
// The local flag set here is NINETY-SIX bits and model conditions are not.
// This body reserves exactly 0x0C, zeroes three dwords, sets bit `bit` in them,
// passes the buffer and releases 0x0C -- three dwords, no more. BFME's model
// condition names are a NUL-terminated pointer array at file offset 0x00EA6918
// holding 304 of them, TOPPLED and FRONTCRUSHED and BACKCRUSHED through to
// EMOTION_UNCONTROLLABLY_AFRAID, so a ModelConditionFlags is ten dwords, and
// the ledger's ModelConditionFlags family agrees: it decorates as
// V?$BitFlags@$0BDA@@, which is 0x130 = 304 bits. That family is right, and a
// three-dword buffer could not carry it -- handing ten dwords' worth of flags
// to a callee through twelve bytes of stack would overrun.
//
// So the 304-bit family is not what is wrong here; this typedef was, and it is
// renamed to say only what is measured. The callee behind ILT 0x0002181E is
// now identified: it is Object::rva001CD540 at 0x001CD540, whose three
// outgoing Object::setStatus calls take the 86-bit mask family ($0FG@) and a
// Bool, so the local flag set is 86 bits and the second argument is a bool.
// That is still three dwords, so this body reserves exactly 0x0C as before. The
// row name ?setSingleModelCondition@Object@@QAEXH@Z is left alone for the same
// reason -- nothing here supplies a better one, and the width is
// mangling-neutral because a typedef name never reaches the decoration.

typedef int Int;
typedef unsigned int UnsignedInt;
#include <string.h>

template<int NUMBITS>
class BitFlags
{
public:
	BitFlags()
	{
		memset(m_bits, 0, sizeof(m_bits));
	}

	void set(Int idx)
	{
		m_bits[(unsigned)idx >> 5] |= 1u << (idx & 31);
	}

	UnsignedInt m_bits[(NUMBITS + 31) / 32];
};

typedef BitFlags<86> ObjectStatusMaskType;   // NOT ModelConditionFlags: those are 304 bits

class Object
{
public:
	void rva001CD540(const ObjectStatusMaskType &flags, bool arg);
	void setSingleModelCondition(Int bit);
};

void Object::setSingleModelCondition(Int bit)
{
	ObjectStatusMaskType flags;
	flags.set(bit);
	rva001CD540(flags, false);
}
