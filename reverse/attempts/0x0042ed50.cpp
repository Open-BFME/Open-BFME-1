// ?bfmeStartZF@@YAHPAXD@Z (identity unknown)
// partial score=0.72 date=2026-09-06
// 82/87. The middle third is byte-exact (both global loads, the 0xbb6 byte
// guard, the je to the shared 5-exit, and the Display virtual at +0xe8).
// This is the EA logo path: literal "EALogoMovie" at 0x010F361C.
// Two residues:
//   1. retail hoists the constant 5 into esi (`mov esi,5` before the first
//      virtual call, `mov eax,esi` at the shared exit, `pop esi` in both
//      epilogues); MSVC folds it to `mov eax,5` at each exit. No source form
//      of the local reproduces the hoist.
//   2. retail constructs the AsciiString temporary IN the argument area
//      (push 8, push 0, push ecx for space, esp marker, `mov ecx,esp`, push
//      the literal, call the ctor); MSVC builds a local, calls the ctor on
//      it, then copies the dword into the slot.
// Combination map measured here:
//   ctor+dtor both declared, no throw()  -> full SEH frame, 89+ bytes
//   ctor throw() + dtor throw()          -> 82 bytes, no marker, local+copy
//   + inline copy ctor                   -> 82 bytes, unchanged
//   /Os, /O1 -> 76; /G7 -> 80; /Og -> 82
// Guard polarity is settled: `if (enabled == 0) return 7;` first puts the
// mov eax,7 block last, matching retail.
class BFMERetailAsciiString
{
public:
	BFMERetailAsciiString(const char *text);
	~BFMERetailAsciiString() throw() {}

	int m_bfmeDataZF;
};

class GameEngine
{
public:
	virtual void bfmeGeSlot00ZF(void);
	virtual void bfmeGeSlot01ZF(void);
	virtual void bfmeGeSlot02ZF(void);
	virtual void bfmeGeSlot03ZF(void);
	virtual void bfmeGeSlot04ZF(void);
	virtual void bfmeGeSlot05ZF(void);
	virtual void bfmeGeSlot06ZF(void);
	virtual void bfmeGeSlot07ZF(void);
	virtual void bfmeGeSlot08ZF(void);
	virtual void bfmeGeSlot09ZF(void);
	virtual void bfmeGeSlot10ZF(void);
	virtual void bfmeGeSlot11ZF(void);
	virtual void bfmeGeSlot12ZF(void);
	virtual void bfmeGeSlot13ZF(void);
	virtual void bfmeGeSlot14ZF(void);
	virtual void bfmeGeSlot15ZF(void);
	virtual void bfmeStartupZF(void);
};

class Glo012ED5C8Type
{
public:
	unsigned char m_bfmeHeadZF[0xbb6];
	char m_bfmeFlagZF;
};

class Display
{
public:
	virtual void bfmeDpSlot00ZF(void);
	virtual void bfmeDpSlot01ZF(void);
	virtual void bfmeDpSlot02ZF(void);
	virtual void bfmeDpSlot03ZF(void);
	virtual void bfmeDpSlot04ZF(void);
	virtual void bfmeDpSlot05ZF(void);
	virtual void bfmeDpSlot06ZF(void);
	virtual void bfmeDpSlot07ZF(void);
	virtual void bfmeDpSlot08ZF(void);
	virtual void bfmeDpSlot09ZF(void);
	virtual void bfmeDpSlot10ZF(void);
	virtual void bfmeDpSlot11ZF(void);
	virtual void bfmeDpSlot12ZF(void);
	virtual void bfmeDpSlot13ZF(void);
	virtual void bfmeDpSlot14ZF(void);
	virtual void bfmeDpSlot15ZF(void);
	virtual void bfmeDpSlot16ZF(void);
	virtual void bfmeDpSlot17ZF(void);
	virtual void bfmeDpSlot18ZF(void);
	virtual void bfmeDpSlot19ZF(void);
	virtual void bfmeDpSlot20ZF(void);
	virtual void bfmeDpSlot21ZF(void);
	virtual void bfmeDpSlot22ZF(void);
	virtual void bfmeDpSlot23ZF(void);
	virtual void bfmeDpSlot24ZF(void);
	virtual void bfmeDpSlot25ZF(void);
	virtual void bfmeDpSlot26ZF(void);
	virtual void bfmeDpSlot27ZF(void);
	virtual void bfmeDpSlot28ZF(void);
	virtual void bfmeDpSlot29ZF(void);
	virtual void bfmeDpSlot30ZF(void);
	virtual void bfmeDpSlot31ZF(void);
	virtual void bfmeDpSlot32ZF(void);
	virtual void bfmeDpSlot33ZF(void);
	virtual void bfmeDpSlot34ZF(void);
	virtual void bfmeDpSlot35ZF(void);
	virtual void bfmeDpSlot36ZF(void);
	virtual void bfmeDpSlot37ZF(void);
	virtual void bfmeDpSlot38ZF(void);
	virtual void bfmeDpSlot39ZF(void);
	virtual void bfmeDpSlot40ZF(void);
	virtual void bfmeDpSlot41ZF(void);
	virtual void bfmeDpSlot42ZF(void);
	virtual void bfmeDpSlot43ZF(void);
	virtual void bfmeDpSlot44ZF(void);
	virtual void bfmeDpSlot45ZF(void);
	virtual void bfmeDpSlot46ZF(void);
	virtual void bfmeDpSlot47ZF(void);
	virtual void bfmeDpSlot48ZF(void);
	virtual void bfmeDpSlot49ZF(void);
	virtual void bfmeDpSlot50ZF(void);
	virtual void bfmeDpSlot51ZF(void);
	virtual void bfmeDpSlot52ZF(void);
	virtual void bfmeDpSlot53ZF(void);
	virtual void bfmeDpSlot54ZF(void);
	virtual void bfmeDpSlot55ZF(void);
	virtual void bfmeDpSlot56ZF(void);
	virtual void bfmeDpSlot57ZF(void);
	virtual void bfmePlayZF(class BFMERetailAsciiString name, int first, int second);
};

extern GameEngine *TheGameEngine;
extern Glo012ED5C8Type *TheWritableGlobalData;
extern Display *TheDisplay;

int __cdecl bfmeStartZF(void *unused, char enabled)
{
	int result = 5;

	TheGameEngine->bfmeStartupZF();

	if (enabled == 0)
		return 7;

	if (TheWritableGlobalData->m_bfmeFlagZF == 0)
		return result;

	TheDisplay->bfmePlayZF(BFMERetailAsciiString("EALogoMovie"), 0, 8);

	return result;
}
