// ?d_003d28d0@@YAXXZ
// partial score=0.255 date=2026-09-23
// cl: /O2 /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /ICode/GameEngine/Include/Precompiled
// stlport

#include "PreRTS.h"
#include <vector>

extern "C" __declspec(dllimport) double __cdecl ceil(double value);

extern const float g_bfmeDefaultBU;
extern const float g_bfmeK1253;

class Rva003D2B80Source
{
public:
	char m_pad00[0x0c];
	float m_step;
	char m_pad10[0x90];
	float m_0a0;
	float m_0a4;
};

struct Gen003D1380Elem
{
	float m_00;
	float m_04;
	void *m_08;
	void *m_0c;
	unsigned int m_10;
	unsigned int m_14;
	unsigned int m_18;
	unsigned int m_1c;
	unsigned int m_20;
	unsigned int m_24;
	unsigned int m_28;
	unsigned int m_2c;
	unsigned int m_30;
	unsigned int m_34;
	unsigned char m_38;
	unsigned char m_39;
	unsigned char m_3a[2];

	__forceinline Gen003D1380Elem()
	{
	}
	Gen003D1380Elem(const Gen003D1380Elem &other);
	~Gen003D1380Elem();
};

#pragma comment(linker, "/alternatename:??0Gen003D1380Elem@@QAE@ABU0@@Z=?j_00042316@@YAXXZ")
#pragma comment(linker, "/alternatename:??1Gen003D1380Elem@@QAE@XZ=?j_00036a9d@@YAXXZ")
#pragma comment(linker, "/alternatename:?reserve@?$vector@UGen003D1380Elem@@V?$allocator@UGen003D1380Elem@@@_STL@@@_STL@@QAEXI@Z=?j_0000e642@@YAXXZ")
#pragma comment(linker, "/alternatename:?_M_insert_overflow@?$vector@UGen003D1380Elem@@V?$allocator@UGen003D1380Elem@@@_STL@@@_STL@@IAEXPAUGen003D1380Elem@@ABU2@ABU__false_type@2@I_N@Z=?j_000382bc@@YAXXZ")

typedef _STL::vector<Gen003D1380Elem> Rva003D2B80Entries;

struct Rva003D2B80Coord
{
	float m_00;
	float m_04;

	Rva003D2B80Coord(float *corner)
		: m_00(corner[0]), m_04(corner[1])
	{
	}
};

class Rva003D2B80Child
{
public:
	Rva003D2B80Child(Rva003D2B80Source *source, float *corner);

private:
	Rva003D2B80Coord m_pad00;
	Rva003D2B80Entries m_entries;
	Rva003D2B80Source *m_source;
	int m_count;
};

Rva003D2B80Child::Rva003D2B80Child(Rva003D2B80Source *source,
	float *corner)
	: m_pad00(corner), m_entries()
{
	float scale = g_bfmeDefaultBU;
	m_source = source;
	float step = source->m_step;
	scale /= step;

	float first = (float)ceil((double)((source->m_0a0 - corner[0]) * scale));
	int firstCount = fast_float2long_round(first);
	m_count = firstCount;
	float second = (float)ceil((double)((source->m_0a4 - corner[1]) * scale));
	int secondCount = fast_float2long_round(second);

	m_entries.reserve(firstCount * secondCount);

	float halfStep = step * g_bfmeK1253;
	for (int y = 0; y < secondCount; ++y)
	{
		float yPosition = (float)y * step + corner[1] + halfStep;
		for (int x = 0; x < m_count; ++x)
		{
			float xPosition = (float)x * step + halfStep + corner[0];
			Gen003D1380Elem element;
			element.m_00 = xPosition;
			element.m_04 = yPosition;
			element.m_08 = source;
			element.m_0c = 0;
			element.m_10 = 0;
			element.m_14 = 0;
			element.m_18 = 0;
			element.m_1c = 0;
			element.m_20 = 0;
			element.m_24 = 0;
			element.m_28 = 0;
			element.m_2c = 0;
			element.m_30 = 0;
			element.m_34 = 0;
			element.m_38 = 0;
			element.m_39 = 8;
			m_entries.push_back(element);
		}
	}
}
