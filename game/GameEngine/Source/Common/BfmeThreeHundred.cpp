// cl: /Oy-
// The record's own name written out with its length measured in place, then a
// number written after it in the record's own base. The name-writer is pinned
// by address; the number is turned into text by the runtime.

extern "C" unsigned int __cdecl strlen(const char *at);
#pragma intrinsic(strlen)

extern "C" __declspec(dllimport) char *__cdecl _itoa(int value, char *out, int base);

// The name-writer is Debug::AddOutput, not a member of this record: retail at
// 0x0088C1F0 makes one direct call to 0x0088A8F0, which is
// ?AddOutput@Debug@@AAEXPBDI@Z, and its only other direct call is the IAT
// slot for _itoa (tools/callees.py 0x0088C1F0 80).  The mangled access code
// AAE is retail's, so the member stays in Debug's private section; Debug's
// upstream header game/Libraries/Source/WWVegas/WWDebug/debug_debug.h:1109
// declares it there and befriends only unrelated classes, and a friend
// declaration cannot be added from this TU, so this file carries the same
// TU-local ABI view the matched defining body does
// (game/Libraries/Source/debug/Debug_AddOutput_0088A8F0.cpp:47).  Only the
// name is needed here: nothing is called on the result, so no member layout
// is asserted and none of Debug's own members are touched.  BfmeThingQQ is
// befriended purely so the private member can be named; that does not add
// any inheritance, layout or vftable.
class Debug
{
	friend class BfmeThingQQ;
	void AddOutput(const char *at, unsigned int many);
};

class BfmeThingQQ
{
public:
	virtual void bfmeSpare000QQ(void) = 0;
	virtual void bfmeSpare001QQ(void) = 0;
	virtual void bfmeSpare002QQ(void) = 0;
	virtual void bfmeSpare003QQ(void) = 0;
	virtual void bfmeSpare004QQ(void) = 0;
	virtual void bfmeSpare005QQ(void) = 0;
	virtual void bfmeSpare006QQ(void) = 0;
	virtual void bfmeSpare007QQ(void) = 0;
	virtual void bfmeSpare008QQ(void) = 0;
	virtual void bfmeSpare009QQ(void) = 0;
	virtual void bfmeSpare010QQ(void) = 0;
	virtual void bfmeSpare011QQ(void) = 0;
	virtual void bfmeSpare012QQ(void) = 0;
	virtual void bfmeSpare013QQ(void) = 0;
	virtual void bfmeAddQQ(const char *text) = 0;

	void bfmeShowQQ(short what);

	unsigned char m_bfmeHead[0x9e6c];	// 0x0004
	char m_bfmeName[0x10];			// 0x9e70
	int m_bfmeBase;				// 0x9e80
};

void BfmeThingQQ::bfmeShowQQ(short what)
{
	char tmp[0x14];

	((Debug *)this)->AddOutput(m_bfmeName, strlen(m_bfmeName));

	bfmeAddQQ(_itoa(what, tmp, m_bfmeBase));
}