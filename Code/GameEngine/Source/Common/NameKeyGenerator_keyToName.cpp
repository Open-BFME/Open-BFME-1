// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB
// stlport
// readable body of ?keyToName@NameKeyGenerator@@: Code/GameEngine/Source/Common/NameKeyGenerator.cpp
// readable body of ?keyToName@NameKeyGenerator@@QAE?AVAsciiString@@W4NameKeyType@@@Z: Code/GameEngine/Source/Common/NameKeyGenerator.cpp
// Open-BFME: NameKeyGenerator::keyToName, retail 0x0008FD30, 119 bytes.
//
// BFME replaced the reference's two nested loops over a fixed socket array
// with a single hash_map lookup, and the body is now the three lines that
// lookup takes. What is left of the reference is the shape of the answer:
// miss returns AsciiString::TheEmptyString, hit returns the bucket's
// m_nameString, and the return is by value into the hidden pointer.
//
// The map's placement and its instantiation both come off the bytes. It sits
// at this+0x2BF48, far enough out that MSVC materialises the address with an
// `add ecx`; the bucket vector's _M_start and _M_finish are the +4 and +8 the
// body loads, and the count is their difference over four. The key reaches the
// modulus in eax with no mixing at all -- `div edi` on the raw NameKeyType --
// so the hash is the identity, and the node it walks is next+0, key+4,
// mapped+8, the mapped value being the Bucket the name is then read out of.
//
// Bucket keeps the reference's layout: pool vptr at +0, m_nextInSocket at +4,
// m_key at +8 and m_nameString at +0xC, which is the `add ecx, 0xC` feeding
// the copy constructor.
#define _STLP_NO_EXCEPTIONS 1
#include <hash_map>

typedef int Int;
typedef unsigned int UnsignedInt;
typedef bool Bool;

enum NameKeyType
{
	NAMEKEY_INVALID = 0
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
public:
	AsciiString(const AsciiString &that);			// ??0AsciiString@@QAE@ABV0@@Z
	~AsciiString();

	static AsciiString TheEmptyString;			// retail 0x00F36E50

private:
	char *m_text;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/NameKeyGenerator.h
class Bucket
{
public:
	char m_bfme_poolVptr[4];				// this+0x00
	Bucket *m_nextInSocket;					// this+0x04
	NameKeyType m_key;					// this+0x08
	AsciiString m_nameString;				// this+0x0C
};

// `div edi` on the key itself: no mixing, so the hash is the identity.
struct NameKeyHashFn
{
	UnsignedInt operator()(NameKeyType key) const { return (UnsignedInt)key; }
};

typedef _STL::hash_map<NameKeyType, Bucket *, NameKeyHashFn, _STL::equal_to<NameKeyType> > NameKeyHash;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/NameKeyGenerator.h
class NameKeyGenerator
{
public:
	AsciiString keyToName(NameKeyType key);

private:
	char m_slice_pad[0x2BF48];				// retail this+0x00 .. +0x2BF47, untouched
	NameKeyHash m_bucketHash;				// this+0x2BF48
};

AsciiString NameKeyGenerator::keyToName(NameKeyType key)
{
	NameKeyHash::const_iterator it = m_bucketHash.find(key);
	if (it == m_bucketHash.end())
		return AsciiString::TheEmptyString;

	return (*it).second->m_nameString;
}
