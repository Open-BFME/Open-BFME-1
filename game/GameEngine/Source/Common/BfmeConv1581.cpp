// Open-BFME5 conversions.

#include "../../../Libraries/Source/WWVegas/WWLib/string_base.h"

class Object;
enum UpdateSleepTime;
extern "C" void __identifier("?setWakeFrame@UpdateModule@@IAEXPAVObject@@W4UpdateSleepTime@@@Z")();

class BfmeStrVSI
{
public:
	char *m_bfme00;
};

class BfmeArgVSI
{
public:
	char m_bfmePad00[0xc];
	BfmeStrVSI m_bfme0c;
	char m_bfmePad10[0x148];
	char m_bfme158;
};

class BfmeOwnVSI
{
public:
	void bfmeApplyVSI(BfmeArgVSI *arg);
	char m_bfmePad00[8];
	int m_bfme08;
	char m_bfmePad0c[0x14];
	BfmeStrVSI m_bfme20;
};

void BfmeOwnVSI::bfmeApplyVSI(BfmeArgVSI *arg)
{
	union
	{
		void (*raw)();
		void (BfmeOwnVSI::*member)(Object *, UpdateSleepTime);
	} wake;
	wake.raw = __identifier("?setWakeFrame@UpdateModule@@IAEXPAVObject@@W4UpdateSleepTime@@@Z");
	if (arg != 0 && arg->m_bfme158 != 0 &&
		((const StringBase<char> *)&arg->m_bfme0c)->compare(*(const StringBase<char> *)&m_bfme20) != 0)
	{
		((StringBase<char> *)&m_bfme20)->set(*(const StringBase<char> *)&arg->m_bfme0c);
		(this->*wake.member)((Object *)m_bfme08, (UpdateSleepTime)1);
	}
	else
	{
		((StringBase<char> *)&m_bfme20)->set("", 0);
		(this->*wake.member)((Object *)m_bfme08, (UpdateSleepTime)0x3fffffff);
	}
}
