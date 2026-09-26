// cl: /Igame/Libraries/Source/WWVegas/WWLib /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// The 0x00900E40 body is the alternate Rva00900FF0 constructor shape.  Its
// vtable, member offsets, and call-site stack layout are witnessed by the
// adjacent constructor/destructor and by d_00901b00.

#include <string.h>
#include <vector>

#include "wwstring.h"

class GenBase009EB7D0
{
public:
	GenBase009EB7D0();
	virtual ~GenBase009EB7D0();
	virtual void handle();

private:
	char m_pad[0x10];
};

class Rva00900FF0VecOfVec
{
public:
	Rva00900FF0VecOfVec(int allocator);
	Rva00900FF0VecOfVec(const Rva00900FF0VecOfVec &source);
	~Rva00900FF0VecOfVec();

	char *m_start;
	char *m_finish;
	char *m_endOfStorage;
};

#pragma comment(linker, "/alternatename:??0Rva00900FF0VecOfVec@@QAE@ABV0@@Z=?d_008ffb80@@YAXXZ")

struct ICoord2D
{
	int x;
	int y;
};

typedef _STL::vector<ICoord2D> Rva00900E40InnerVector;
typedef _STL::vector<Rva00900E40InnerVector> Rva00900E40VecOfVec;

struct Rva00900E40Elem4
{
	char m_bytes[4];
};

extern void *(__cdecl *bfmeMemCopy)(void *destination, const void *source, unsigned int bytes);

inline Rva00900E40Elem4 *Rva00900E40CopyRange(
	Rva00900E40Elem4 *destination,
	Rva00900E40Elem4 *first,
	Rva00900E40Elem4 *last)
{
	if (first == last)
		return destination;

	unsigned int bytes = (char *)last - (char *)first;
	return (Rva00900E40Elem4 *)((char *)bfmeMemCopy(destination, first, bytes) + bytes);
}

struct Rva00900E40VectorHolder
{
	Rva00900E40VectorHolder()
		: m_start(0), m_finish(0), m_endOfStorage(0)
	{
	}

	void clear(void)
	{
		m_finish = Rva00900E40CopyRange(m_start, m_finish, m_finish);
	}

	~Rva00900E40VectorHolder()
	{
		Rva00900E40Elem4 *start = m_start;
		if (start)
		{
			unsigned int bytes = (m_endOfStorage - start) * sizeof(Rva00900E40Elem4);
			_STL::__node_alloc<true, 0>::deallocate(start, bytes);
		}
	}

	Rva00900E40Elem4 *m_start;
	Rva00900E40Elem4 *m_finish;
	Rva00900E40Elem4 *m_endOfStorage;
};

class Rva00900FF0 : public GenBase009EB7D0
{
public:
	Rva00900FF0(
		const char *first,
		const char *second,
		int field64,
		int field68,
		Rva00900FF0VecOfVec vec1,
		Rva00900FF0VecOfVec vec2,
		Rva00900FF0VecOfVec vec3,
		int field6c);
	virtual ~Rva00900FF0();

private:
	StringClass m_str14;
	StringClass m_str18;
	Rva00900FF0VecOfVec m_vec1c;
	Rva00900FF0VecOfVec m_vec28;
	Rva00900FF0VecOfVec m_vec34;
	Rva00900E40VecOfVec m_vec40;
	Rva00900E40VecOfVec m_vec4c;
	Rva00900E40VectorHolder m_vector58;
	int m_field64;
	int m_field68;
	int m_field6c;
	void *m_countedPtr70;
};

Rva00900FF0::Rva00900FF0(
	const char *first,
	const char *second,
	int field64,
	int field68,
	Rva00900FF0VecOfVec vec1,
	Rva00900FF0VecOfVec vec2,
	Rva00900FF0VecOfVec vec3,
	int field6c)
	: GenBase009EB7D0(),
	  m_str14(first),
	  m_str18(second),
	  m_vec1c(vec1),
	  m_vec28(vec2),
	  m_vec34(vec3),
	  m_vec40(),
	  m_vec4c(),
	  m_vector58(),
	  m_field64(field64),
	  m_field68(field68),
	  m_field6c(field6c),
	  m_countedPtr70(0)
{
	m_vec40.clear();
	m_vec4c.clear();
	m_vector58.clear();
}
