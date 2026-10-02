// cl: /G7 -Igame/GameEngine/Source/Common/System -Igame/Libraries/Source/WWVegas/WWLib -Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include

// Open-BFME5 conversions.

extern char g_bfmeVft963[];

// bfmeBase963's body is the 16-byte constructor at 0x009A1A30, which the ledger
// carries as ??0SubsystemInterface@@QAE@XZ (source
// game/GameEngine/Source/Common/System/SubsystemInterface.cpp), so the base is
// declared by the real header instead of a TU-local address-derived stand-in and
// the base call mangles to the defining name. __declspec(novtable) keeps the
// compiler from emitting a vftable here: retail's own vtable for this class lives
// in g_bfmeVft963 and is stored by the explicit store in the body, so the derived
// subobject is still eight bytes -- a vptr plus the four-byte AsciiString m_name
// -- and every member keeps its retail offset.
#include "Lib/BaseType.h"
#include "subsystem_interface.h"

class __declspec(novtable) BfmeReg963 : public SubsystemInterface
{
public:
	BfmeReg963();

	volatile int m_bfme08;
	volatile int m_bfme0c;
	volatile int m_bfme10;
	volatile int m_bfme14;
	volatile int m_bfme18;
	volatile float m_bfme1c;
	volatile float m_bfme20;
	volatile float m_bfme24;
};

extern BfmeReg963 *g_bfmeReg963;

BfmeReg963::BfmeReg963()
{
	m_bfme08 = 0;
	m_bfme0c = 0;
	m_bfme10 = 0;
	m_bfme14 = 0;
	m_bfme18 = 0;
	// The base subobject's vptr slot: retail's vtable for this class is the
	// extern g_bfmeVft963, stored by the body rather than by the compiler
	// (__declspec(novtable) above keeps it from emitting one of its own).
	*reinterpret_cast<char *volatile *>(this) = g_bfmeVft963;
	m_bfme1c = 3.402823466e+38f;
	m_bfme20 = 3.402823466e+38f;
	m_bfme24 = 3.402823466e+38f;

	if (g_bfmeReg963 == 0)
		g_bfmeReg963 = this;
}
