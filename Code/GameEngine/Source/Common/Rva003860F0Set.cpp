// cl: /O2 /Ob0

class Rva0036CA00Str
{
public:
	Rva0036CA00Str &operator=(const Rva0036CA00Str &other);
	void clear();

	struct Data
	{
		short a;
		short b;
		unsigned short first;
	};

	Data *m_item;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/GlobalData.h
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
		m_80 = *a;
		m_84 = *b;
		m_88 = *c;
		return;
	}
	m_6d = 0;
	m_80.clear();
	m_84.clear();
	m_88.clear();
}
