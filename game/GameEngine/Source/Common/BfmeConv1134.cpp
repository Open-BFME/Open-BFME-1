// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
// Open-BFME5 conversions.

// The base is the real SubsystemInterface, not a TU-local stand-in: retail runs
// 0x009A1A30 here, which is ??0SubsystemInterface@@QAE@XZ, and the header's
// `AsciiString m_name` at +0x04 is the same four bytes the old
// `char *m_bfme00 / int m_bfme04` placeholder pair stood for. The paired
// destructor TU (BfmeConv1134Destructor.cpp) already spells BfmeA1134 that way.
#include "string_base.h"

#include "ascii_string.h"

typedef bool Bool;
#include "System/subsystem_interface.h"

// Retail's constructor stores 0x010F0AE0 over the base's vptr at +0x0A. That
// address is this class's own vftable, `??_7BfmeA1134@@6B@`, which no C++
// spelling can name and which the only emitter, the paired destructor TU
// (BfmeConv1134Destructor.cpp), already defines as a COMDAT. The old
// `extern "C" char g_bfmeV1134[]` stood in for it with a name nothing defines,
// so this object never linked.
//
// Declaring a virtual member here and taking its address makes MSVC 7.1 emit
// the standard *external-vftable reference* `??_9@$BBI@AE` instead of a local
// copy, and link.exe rewrites it to whatever `??_7BfmeA1134@@6B@` resolves to in
// the TU that defines the vftable. The store then stays where retail has it.
// Letting the compiler place the implicit vptr store itself does not work: the
// `volatile` members make /O2 sink it to the end of the ctor (byte-identical
// everything else, but the store lands at +0xB4 instead of +0x0A).
//
// bfmeSlot0 is this class's first vftable slot; its body is not recovered, and
// nothing here needs it: the address is taken only to name the vftable, and
// no definition, ledger row or second definition of the vftable is added.
class BfmeA1134 : public SubsystemInterface
{
public:
	BfmeA1134(void);
	virtual void bfmeSlot0();
	volatile int m_bfme08;
	volatile int m_bfme0c;
	volatile int m_bfme10;
	volatile int m_bfme14;
	volatile int m_bfme18;
	volatile char m_bfme1c;
	char m_bfmePad1d[3];
	volatile int m_bfme20;
	volatile int m_bfme24;
	volatile int m_bfme28;
	volatile int m_bfme2c;
	volatile int m_bfme30;
	volatile int m_bfme34;
	volatile int m_bfme38;
	volatile int m_bfme3c;
	volatile int m_bfme40;
	volatile int m_bfme44;
	volatile float m_bfme48;
	volatile char m_bfme4c;
	char m_bfmePad4d[3];
	volatile int m_bfme50;
	volatile int m_bfme54;
	volatile int m_bfme58;
	volatile int m_bfme5c;
	volatile int m_bfme60;
	volatile int m_bfme64;
	volatile int m_bfme68;
	volatile int m_bfme6c;
	volatile int m_bfme70;
	volatile int m_bfme74;
	volatile int m_bfme78;
	volatile int m_bfme7c;
	volatile char m_bfme80;
	volatile char m_bfme81;
	char m_bfmePad82[2];
	volatile int m_bfme84;
	volatile int m_bfme88;
	volatile int m_bfme8c;
	volatile int m_bfme90;
	volatile int m_bfme94;
	volatile int m_bfme98;
	volatile int m_bfme9c;
	volatile int m_bfmea0;
	volatile int m_bfmea4;
	volatile int m_bfmea8;
};

BfmeA1134::BfmeA1134(void)
{
	// this class's own vftable goes over the base's, at the same slot (+0x00).
	// The union is this repo's convention for naming a __thiscall entity from a
	// raw address; here it names the vftable, through the external-vftable
	// reference described above.
	typedef void (BfmeA1134::*Slot0)();
	union { void (*raw)(void); Slot0 member; } fn;
	fn.member = &BfmeA1134::bfmeSlot0;
	*(void *volatile *)this = (void *)fn.raw;
	m_bfme08 = 0;
	m_bfme0c = 0;
	m_bfme10 = 0;
	m_bfme14 = 0;
	m_bfme18 = 0;
	m_bfme1c = 0;
	m_bfme20 = 0;
	m_bfme24 = 0;
	m_bfme28 = 0;
	m_bfme38 = 0;
	m_bfme3c = 0;
	m_bfme40 = 0;
	m_bfme44 = 0;
	m_bfme4c = 0;
	m_bfme50 = 0;
	m_bfme60 = 0;
	m_bfme48 = 1.0f;
	m_bfme64 = 0;
	m_bfme68 = 0;
	m_bfme6c = 0;
	m_bfme70 = 0;
	m_bfme74 = 0;
	m_bfme78 = 0;
	m_bfme7c = 0;
	m_bfme80 = 0;
	m_bfme81 = 0;
	m_bfme84 = 0;
	m_bfme88 = 0;
	m_bfme8c = 0;
	m_bfme90 = 0;
	m_bfme94 = 0;
	m_bfme98 = 0;
	m_bfme9c = 0;
	m_bfmea0 = 0;
	m_bfmea4 = 0;
	m_bfmea8 = 0;
	m_bfme34 = 0;
	m_bfme30 = 0;
	m_bfme2c = 0;
	m_bfme5c = 0;
	m_bfme58 = 0;
	m_bfme54 = 0;
}
