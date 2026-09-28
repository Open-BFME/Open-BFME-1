// ?d_009f63d0@@YAXXZ
// partial score=0.946 date=2026-09-28
// cl: /O2 /Ob2 /FAsc /Fabuild/Rva009F63D0Probe.cod /DNDEBUG /DWIN32 /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport


#define _STLP_NO_EXCEPTIONS 1
#include <vector>

struct Rva009F39F0Pair
{
	int first;
	int second;
};

struct Rva009F39F0Payload
{
	_STL::vector<Rva009F39F0Pair> m_items;
	void *m_cursor;
	int m_refCount;
};

struct Rva009F39F0Result
{
	Rva009F39F0Payload *m_value;
	Rva009F39F0Result();
};

struct BfmeWideResult : private Rva009F39F0Result
{
	__forceinline BfmeWideResult() : Rva009F39F0Result() {}
	__forceinline BfmeWideResult(const BfmeWideResult &that)
		: Rva009F39F0Result(*(const Rva009F39F0Result *)&that)
	{
		++m_value->m_refCount;
	}
	__forceinline ~BfmeWideResult()
	{
		Rva009F39F0Payload *&value = m_value;
		if (--value->m_refCount == 0)
		{
			value->m_items.~vector();
			::operator delete(value);
		}
	}
};

struct Rva009F4130NodeList
{
	int hasChildren;
	void *head;
};

struct Rva009F4130Range
{
	float x0, y0, unused08, x1, y1;
};

struct Rva009F4130Node;
struct Rva009F4130DistanceContext;
class BfmeThingEQ;
typedef float (__cdecl *Rva009F4130Distance)(void *, void *, float);

class Rva009F4130Owner
{
public:
	void query(Rva009F39F0Result *, Rva009F4130NodeList *, unsigned int,
		int, int, int, int, int, int, int, void *, float,
		const Rva009F4130Range *, Rva009F4130Distance, BfmeThingEQ *);
};

class Rva009F2AB0Mask
{
public:
	int getMask(void);
};

class BfmeHostER
{
public:
	unsigned int bfmeIndexER(float);
};

class BfmeHostES
{
public:
	unsigned int bfmeIndexES(float);
};

class BfmeThingVJX
{
public:
	void bfmeGoVJX(int);
};

typedef _STL::vector<Rva009F4130NodeList> Rva009F63D0NodeVector;
class Rva009F63D0
{
public:
	float m_field00;
	float m_field04;
	unsigned char m_pad08[0x10];
	Rva009F63D0NodeVector m_vectors[17];
	unsigned char m_padE4[4];
	float m_fieldE8;
	unsigned int m_fieldEC;
	BfmeWideResult method(int a, int b, int c, int d, int e, int f);
};

BfmeWideResult Rva009F63D0::method(int position, int radius, int bounds,
	int distanceType, int filters, int sortMode)
{
	BfmeWideResult result;
	if (distanceType != 0 && distanceType != 2 && distanceType != 1 &&
		distanceType != 3 && distanceType != 4)
		distanceType = 0;
	int filterMask;
	if (filters != 0)
		filterMask = ((Rva009F2AB0Mask *)filters)->getMask() * 2 + 1;
	else
		filterMask = -1;

	const float *point = (const float *)position;
	Rva009F4130Range *range = (Rva009F4130Range *)bounds;
	int xMin, xMax, yMin, yMax;
	if (point != 0)
	{
		float r = *(float *)&radius;
		xMin = ((BfmeHostER *)this)->bfmeIndexER(point[0] - r);
		xMax = ((BfmeHostER *)this)->bfmeIndexER(point[0] + r);
		yMin = ((BfmeHostES *)this)->bfmeIndexES(point[1] - r);
		yMax = ((BfmeHostES *)this)->bfmeIndexES(point[1] + r);
	}
	else
	{
		xMin = ((BfmeHostER *)this)->bfmeIndexER(range->x0);
		xMax = ((BfmeHostER *)this)->bfmeIndexER(range->x1);
		yMin = ((BfmeHostES *)this)->bfmeIndexES(range->y0);
		yMax = ((BfmeHostES *)this)->bfmeIndexES(range->y1);
	}

	float radiusSquared = *(float *)&radius;
	radiusSquared *= radiusSquared;
	Rva009F63D0NodeVector *nodes = m_vectors;
	int remaining = 17;
	do
	{
		if ((filterMask & 1) != 0)
		{
			((Rva009F4130Owner *)this)->query(
				(Rva009F39F0Result *)&result, nodes->begin(),
				nodes->size() / 4,
				xMin, yMin, xMax, yMax, 0, 0, m_fieldEC,
				(void *)point, radiusSquared, range,
				((Rva009F4130Distance *)0x012DBD60)[distanceType],
				(BfmeThingEQ *)filters);
		}
		filterMask >>= 1;
		++nodes;
	} while (--remaining != 0);

	if (sortMode != 0)
		((BfmeThingVJX *)&result)->bfmeGoVJX(sortMode);
	return result;
}

class BfmeWideForwardA
{
	char m_pad[0x0C];
	Rva009F63D0 *m_source;

public:
	BfmeWideResult bfmeForwardWideA(int a, int b, int c, int d);
};

class BfmeWideForwardB
{
	char m_pad[0x0C];
	Rva009F63D0 *m_source;

public:
	BfmeWideResult bfmeForwardWideB(int a, int b, int c, int d);
};

class BfmeWideForwardC
{
	char m_pad[0x0C];
	Rva009F63D0 *m_source;

public:
	BfmeWideResult bfmeForwardWideC(int a, int b, int c, int d, int e);
};

class BfmeWideForward009F29A0
{
	char m_pad[0x0C];
	Rva009F63D0 *m_source;

public:
	BfmeWideResult forward009F29A0(int a, int b, int c);
};

BfmeWideResult BfmeWideForward009F29A0::forward009F29A0(int a, int b, int c)
{
	return m_source->method(0, 0, a, b, 0, c);
}

BfmeWideResult BfmeWideForwardA::bfmeForwardWideA(int a, int b, int c, int d)
{
	return m_source->method(a, b, 0, c, 0, d);
}

BfmeWideResult BfmeWideForwardB::bfmeForwardWideB(int a, int b, int c, int d)
{
	return m_source->method(0, 0, a, b, c, d);
}

BfmeWideResult BfmeWideForwardC::bfmeForwardWideC(int a, int b, int c, int d, int e)
{
	return m_source->method(a, b, 0, c, d, e);
}
