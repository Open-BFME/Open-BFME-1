// cl: /O2 /Ob0

#include "../../../Libraries/Source/WWVegas/WWLib/string_base.h"

// Retail calls the private StringBase release directly. Keep its native
// linkage and zero-argument thiscall ABI without defining another wrapper.
extern "C" void __identifier("?releaseBuffer@?$StringBase@D@@AAEXXZ")();

class Rva0036CA00Str
{
public:
	struct Data
	{
		short a;
		short b;
		unsigned short first;
	};

	Data *m_item;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/GlobalData.h
class GlobalData
{
public:
	char m_pad[0xA7D];
	unsigned char flag;
};

extern GlobalData *TheWritableGlobalData;

class Rva003860F0
{
	char m_pad0[0x6D];
	unsigned char m_6d;
	char m_pad1[0x12];
	Rva0036CA00Str m_80;
	Rva0036CA00Str m_84;
	Rva0036CA00Str m_88;

public:
	void set(Rva0036CA00Str *a, Rva0036CA00Str *b, Rva0036CA00Str *c);
};

void Rva003860F0::set(Rva0036CA00Str *a, Rva0036CA00Str *b, Rva0036CA00Str *c)
{
	if (a->m_item && a->m_item->first && !TheWritableGlobalData->flag)
	{
		m_6d = 1;
		((StringBase<char> *)&m_80)->set(*(const StringBase<char> *)a);
		((StringBase<char> *)&m_84)->set(*(const StringBase<char> *)b);
		((StringBase<char> *)&m_88)->set(*(const StringBase<char> *)c);
		return;
	}
	m_6d = 0;
	union { void (*raw)(); void (StringBase<char>::*member)(); } release;
	release.raw = __identifier("?releaseBuffer@?$StringBase@D@@AAEXXZ");
	(((StringBase<char> *)&m_80)->*release.member)();
	(((StringBase<char> *)&m_84)->*release.member)();
	(((StringBase<char> *)&m_88)->*release.member)();
}
