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

// Retain the legacy per-unit identity hint. The array below is represented
// independently by its measured stride and original ILT callback.
class ThingRef
{
public:
	~ThingRef();                                               ///< ILT 0x00048D42

private:
	unsigned int m_words[2];
};

// Address-only ILT declaration. The CRT supplies the callback's original thiscall ABI.
extern "C" void __cdecl __identifier("?j_00048d42@@YAXXZ")();
extern "C" void __cdecl __identifier("??_M@YGXPAXIHP6EX0@Z@Z")(void *, unsigned, int, void *) throw(...);
// Calling through the actual stdcall ABI avoids a spurious @16 linker suffix
// on VC7.1's already decorated CRT identifier.
typedef void (__stdcall *BfmeArrayDtorABI)(void *, unsigned, int, void *);
class Rva0039B560 : public SubsystemInterface, public Snapshot
{
public:
	~Rva0039B560();

private:
	unsigned char m_pad0C[0x18 - 0xC];                          ///< +0x0C, untouched by this body
	AttributeHandleStandIn m_memberC;                          ///< +0x18
	AsciiString m_str;                                         ///< +0x1C
	unsigned char m_pad20[0x28 - 0x20];                         ///< +0x20, untouched by this body
	    // Preserve the established element type and count while spelling the
    // original ILT callbacks explicitly. This is a local lifetime adapter,
    // not a replacement identity for the element class.
    template<class Element, unsigned Count>
    struct ElementArrayLifetime
    {
        typedef char RetainedElementWidth[(sizeof(Element) == 8 && sizeof(unsigned) == 4) ? 1 : -1];
        unsigned m_words[(sizeof(Element) * Count) / sizeof(unsigned)];

        __declspec(dllimport) __forceinline ~ElementArrayLifetime()
        {
            reinterpret_cast<BfmeArrayDtorABI>(&__identifier("??_M@YGXPAXIHP6EX0@Z@Z"))(
                this, sizeof(Element), Count,
                reinterpret_cast<void *>(&__identifier("?j_00048d42@@YAXXZ")));
        }
    };

    ElementArrayLifetime<ThingRef, 5> m_array;                                       ///< +0x28, eight-byte stride
};

// @??1Rva0039B560@@UAE@XZ 0x0039B560
Rva0039B560::~Rva0039B560()
{
}
