// cl: /DNDEBUG /MD /EHsc
// readable body of ??0Keyboard@@: Code/GameEngine/Source/GameClient/Input/Keyboard.cpp
// Open-BFME5: Keyboard::Keyboard at retail 0x005A3AC0 (69B).
//
// Structure, unchanged from the earlier attempts: SubsystemInterface is eight
// bytes (vptr plus the AsciiString its constructor at 0x009A1A30 writes at
// +0x04), Keyboard is 0xE1C, and the write order is the three dwords at
// +0x0C/+0x10/+0x14, a 0x800 clear at +0x18, the word at +0x08 and byte at
// +0x0A, a 0x600 clear at +0x818, and the dword at +0xE18 last.
//
// TWO RECORDED BLOCKERS ON THIS ROW WERE BOTH MISREADINGS OF ONE FACT. The
// first was "MSVC writes the vftable pointer after the cleared fields"; the
// second was "xor eax,eax for the rep-stos fill is hoisted beside xor edx,edx
// where retail materialises it at its use". Written as eight plain statements
// in retail's order, MSVC 7.1 already emits all 69 bytes in retail's order
// except that it hoists the fill's xor eax,eax to the top -- one instruction
// out of place, and BOTH residues are that same one instruction, because the
// vptr store and the xor land on opposite sides of the same boundary.
//
// MSVC 7.1 sinks a constructor's vptr store forward until a barrier stops it,
// and it materialises a shared zero constant at the top of the region its uses
// live in. A member sub-object's construction is such a barrier, and it is
// emitted after the vptr store and before the constructor body. Grouping the
// three dwords at +0x0C..+0x18 into one sub-object therefore does both jobs at
// once: the vftable store is pinned ahead of them at the top, and the region
// that holds the two rep-stos fills now begins after them, so the fill's zero
// is materialised at the `lea` exactly as retail does. Nothing else moves.
//
// This replaces a spelling that used __declspec(novtable), an extern "C"
// vftable byte stored by hand, and volatile lvalues on all the scalars except
// the +0x08 word and +0x0A byte. That asymmetry -- "every store volatile
// overshoots, those two must stay plain" -- was the tell that the lever was
// store placement rather than volatile: volatile does not pin the compiler's
// own vptr store (probed directly; it orders only the volatile accesses among
// themselves), and the old spelling worked only because novtable had removed
// that store from the problem.

#include <string.h>

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/SubsystemInterface.h
class SubsystemInterface
{
public:
	virtual ~SubsystemInterface();
	void *m_name;
	SubsystemInterface();
};

// The three dwords at +0x0C..+0x18 are constructed, not assigned: retail's
// vftable store sits ahead of them and the array fill's zero is materialised
// after them, which is what a sub-object boundary at +0x0C..+0x18 produces and
// what eight plain statements do not.  The grouping is recovered from the
// bytes; the type name is not.
struct KeyboardShiftState
{
	int m_inputFrame;
	int m_shiftExKey;
	int m_shiftExCount;

	KeyboardShiftState()
	{
		m_inputFrame = 0;
		m_shiftExKey = 0;
		m_shiftExCount = 0;
	}
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/Keyboard.h
class Keyboard : public SubsystemInterface
{
public:
	unsigned short     m_modifiers;
	unsigned char      m_shift2Key;
	char               m_pad0b;
	KeyboardShiftState m_shiftState;
	int                m_keys[0x200];
	int                m_keyStatus[0x180];
	int                m_tail;

	Keyboard();
};

Keyboard::Keyboard()
{
	memset( m_keys, 0, sizeof( m_keys ) );
	m_modifiers = 0;
	m_shift2Key = 0;
	memset( m_keyStatus, 0, sizeof( m_keyStatus ) );
	m_tail = 0;
}
