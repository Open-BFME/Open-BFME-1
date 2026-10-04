// cl: /DNDEBUG /DWIN32 /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib

class Rva00491DB0Display
{
public:
	virtual void f00(); virtual void f01(); virtual void f02(); virtual void f03();
	virtual void f04(); virtual void f05(); virtual void f06(); virtual void f07();
	virtual void f08(); virtual void f09(); virtual void f10(); virtual void f11();
	virtual void f12(); virtual void f13(); virtual void f14(); virtual void f15();
	virtual void f16(); virtual void f17(); virtual void f18(); virtual void f19();
	virtual void f20(); virtual void f21(); virtual void f22(); virtual void f23();
	virtual void f24(); virtual void f25(); virtual void f26(); virtual void f27();
	virtual void f28(); virtual void f29(); virtual void f30(); virtual void f31();
	virtual void f32(); virtual void f33(); virtual void f34(); virtual void f35();
	virtual void f36(); virtual void f37(); virtual void f38(); virtual void f39();
	virtual void f40(); virtual void f41(); virtual void f42(); virtual void f43();
	virtual void f44(); virtual void f45(); virtual void f46(); virtual void f47();
	virtual void f48(); virtual void f49(); virtual void f50(); virtual void f51();
	virtual void f52(); virtual void f53(); virtual void f54(); virtual void f55();
	virtual void f56(); virtual void f57(); virtual void f58();
	virtual void releaseOwner(void);
};

// Retail's 0x012F1270 global is EA's `Display *TheDisplay`, defined once in
// game/GameEngine/Source/GameClient/Display.cpp.  The vtable slot reached here
// is observed through the local view class, so the cast happens at the use.
class Display;
extern Display *TheDisplay;

#include "ascii_string.h"

// Retail calls ILT 0x0004634E from the destructor tail, which routes to the
// 0x00490470 body the ledger owns as ??1Rva00490470@@UAE@XZ
// (game/GameEngine/Source/GameClient/GUI/Rva00490350LinkedCtorAndWindowDtor.cpp),
// so the base class is that class, not an address-derived view of it.
class Rva00490470
{
public:
	virtual ~Rva00490470();
private:
	unsigned char m_padding[0x10];
};

class Rva00491DB0DisplayOwner : public Rva00490470
{
public:
	virtual ~Rva00491DB0DisplayOwner();
private:
	// The +0x14 member is EA's AsciiString: retail calls 0x00887940 on it,
	// which is ?releaseBuffer@?$StringBase@D@@AAEXXZ, matched in
	// game/Libraries/Source/string/StringBase.cpp.
	AsciiString m_name;
};

Rva00491DB0DisplayOwner::~Rva00491DB0DisplayOwner()
{
	((Rva00491DB0Display *)TheDisplay)->releaseOwner();
}
