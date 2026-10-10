// Open-BFME5 conversions.

#include "../../../Libraries/Source/WWVegas/WWLib/string_base.h"

class Object;
enum UpdateSleepTime;
extern "C" void __identifier("?setWakeFrame@UpdateModule@@IAEXPAVObject@@W4UpdateSleepTime@@@Z")();

class BfmeStrVSJ
{
public:
	char *m_bfme00;
};

class BfmeArgVSJ
{
public:
	char m_bfmePad00[0xc];
	BfmeStrVSJ m_bfme0c;
};

class BfmeOwnVSJ
{
public:
	void bfmeApplyVSJ(BfmeArgVSJ *arg, char force);
	char m_bfmePad00[8];
	int m_bfme08;
	char m_bfmePad0c[0x14];
	BfmeStrVSJ m_bfme20;
};

void BfmeOwnVSJ::bfmeApplyVSJ(BfmeArgVSJ *arg, char force)
{
	union
	{
		void (*raw)();
		void (BfmeOwnVSJ::*member)(Object *, UpdateSleepTime);
	} wake;
	wake.raw = __identifier("?setWakeFrame@UpdateModule@@IAEXPAVObject@@W4UpdateSleepTime@@@Z");
	if (arg != 0 &&
		((const StringBase<char> *)&arg->m_bfme0c)->compare(*(const StringBase<char> *)&m_bfme20) == 0 && force == 0)
	{
		((StringBase<char> *)&m_bfme20)->set("", 0);
		(this->*wake.member)((Object *)m_bfme08, (UpdateSleepTime)0x3fffffff);
	}
	else
	{
		((StringBase<char> *)&m_bfme20)->set(*(const StringBase<char> *)&arg->m_bfme0c);
		(this->*wake.member)((Object *)m_bfme08, (UpdateSleepTime)1);
	}
}
