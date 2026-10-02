// cl: /O2 /DNDEBUG /MD
// The call at +0x0E is Bfme5's allocate-and-fill factory at 0x007F4810, whose
// real body and mangled name live in
// game/GameEngine/Source/Common/Bfme5FactoryStubs.cpp
// (`?bfme5MakeObj70@@YAPAUBfme5Obj70@@H@Z`).  Retail passes the owning object
// in the factory's one argument slot, so this file declares that factory
// rather than a bfmeMakeBZA of its own that nothing defines.

struct Bfme5Obj70;
Bfme5Obj70 *__cdecl bfme5MakeObj70(int arg);

class BfmeCacheBZA;

class BfmeThingBZA
{
public:
	BfmeCacheBZA *bfmeGetBZA();
	unsigned char m_bfmeHead[0x244];
	BfmeCacheBZA *m_bfmeCache;
};

BfmeCacheBZA *BfmeThingBZA::bfmeGetBZA()
{
	if (m_bfmeCache == 0)
		m_bfmeCache = (BfmeCacheBZA *)bfme5MakeObj70((int)this);
	return m_bfmeCache;
}