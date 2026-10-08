// cl: /DNDEBUG /MD /EHsc /O2
//
// Open-BFME5: retail 0x0039B560, 134 bytes. Multiple-inheritance destructor:
// first base SubsystemInterface (real class, dtor pinned at 0x009A1A40),
// second base BfmeBaseVUQ (the shared folded trivial base, 0x01073744).
// Members destruct in reverse declared order: a 5-element/8-byte-stride
// array at +0x28 via the eh-vector-destructor-iterator helper (ThingRef dtor
// through ILT 0x00048D42 -> 0x0039B060), an AsciiString at +0x1C, then an
// AttributeHandleStandIn at +0x18 (ILT 0x0001A401 -> 0x0039D550), before
// the two base subobjects unwind.

#include "../../../Libraries/Source/WWVegas/WWLib/ascii_string.h"

// Second base: cleanup funclet 0x00C1CA48 destroys this+8 through ILT
// 0x00001C80, the PE-exported Snapshot destructor.
#include "System/snapshot.h"

class SubsystemInterface
{
public:
	virtual ~SubsystemInterface();                             ///< pinned 0x009A1A40

private:
	unsigned int m_name;
};

class AttributeHandleStandIn
{
public:
	~AttributeHandleStandIn();                                 ///< ILT 0x0001A401

private:
	unsigned int m_body;
};

class ThingRef
{
public:
	~ThingRef();                                               ///< ILT 0x00048D42

private:
	unsigned int m_words[2];
};

class Rva0039B560 : public SubsystemInterface, public Snapshot
{
public:
	~Rva0039B560();

private:
	unsigned char m_pad0C[0x18 - 0xC];                          ///< +0x0C, untouched by this body
	AttributeHandleStandIn m_memberC;                          ///< +0x18
	AsciiString m_str;                                         ///< +0x1C
	unsigned char m_pad20[0x28 - 0x20];                         ///< +0x20, untouched by this body
	ThingRef m_array[5];                                       ///< +0x28, eight-byte stride
};

// @??1Rva0039B560@@UAE@XZ 0x0039B560
Rva0039B560::~Rva0039B560()
{
}
