// Open-BFME5: retail RVA 0x00615D50, 513 bytes.
//
// The matched caller at 0x003BF3C0 (Rva003BF3C0.cpp) names this body
// ?lookup@Glo012F706CType@@QAEPAURva00615D50Object@@PBUICoord2D@@H@Z through
// ILT 0x0002934D and calls it twice with categories 1 and 0.  It walks the
// same AsciiString hash_map at manager+0x224 that the landed 0x00615CB0
// lookup walks, so begin() and the bucket helper reach the same two bodies
// through ILT 0x00036412 and ILT 0x0001F843.
//
// Two shapes that the byte diff pins down.  The screen distance has no named
// float variable at all: the repeated (float)sqrt(...) cast is what forces the
// store-and-reload through the temporary at esp+0x14 that the second candidate
// then compares against.  And the world position getter takes no argument and
// returns Coord3D by value, so its ret 4 pops only the hidden result pointer;
// the surviving push is the second argument of the projection call that
// consumes it.
//
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib
// stlport

#define _STLP_NO_EXCEPTIONS 1
#include "Common/STLTypedefs.h"
#include <hash_map>
#include <math.h>

// ICoord2D and Coord3D come from Lib/BaseType.h through STLTypedefs.h.

class BfmeSubBIA
{
public:
	int ask();													///< ILT 0x000022BB
};

class Rva00615D50Type
{
public:
	void *m_at00;
	BfmeSubBIA *m_override;
	void *m_at08;
	int m_category;
};

struct Rva00615D50Object
{
	bool rva0004a444(const ICoord2D *point);					///< ILT 0x0004A444
	Coord3D rva0001895d();						///< ILT 0x0001895D

	void *m_at00;
	const Rva00615D50Type *m_type;
	int m_id;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/Display.h
class Display
{
public:
	virtual void d00();
	virtual void d04();
	virtual void d08();
	virtual void d0C();
	virtual void d10();
	virtual void d14();
	virtual void d18();
	virtual void d1C();
	virtual void d20();
	virtual void d24();
	virtual void d28();
	virtual unsigned int getWidth();
};

extern Display *TheDisplay;

class Gen_00609320
{
public:
	virtual void s00();
	virtual void s04();
	virtual void s08();
	virtual void s0C();
	virtual void s10();
	virtual void s14();
	virtual void s18();
	virtual void s1C();
	virtual void s20();
	virtual bool s24(const Coord3D &world, ICoord2D *screen);
};

extern Gen_00609320 *g_bfmeStateDF;

typedef _STL::hash_map<AsciiString, Rva00615D50Object *,
	rts::hash<AsciiString>, _STL::equal_to<AsciiString> > Rva00615D50Map;

class Glo012F706CType
{
public:
	Rva00615D50Object *lookup(const ICoord2D *position, int category);

private:
	unsigned char m_prefix[0x224];
	Rva00615D50Map m_objects;
};

Rva00615D50Object *Glo012F706CType::lookup(const ICoord2D *position, int category)
{
	float base = 1.0f;
	if (TheDisplay != 0)
		base = (float)TheDisplay->getWidth() * 0.0009765625f;
	float limit = base * 70.0f;
	Rva00615D50Object *best = 0;

	for (Rva00615D50Map::iterator it = m_objects.begin();
		it != m_objects.end(); ++it)
	{
		Rva00615D50Object *object = it->second;

		if (category != 5)
		{
			const Rva00615D50Type *type = object->m_type;
			if (type != 0 && type->m_override != 0)
				type = (const Rva00615D50Type *)type->m_override->ask();
			if (category != type->m_category)
				continue;
		}

		if (!object->rva0004a444(position))
			continue;

		ICoord2D screen;
		if (!g_bfmeStateDF->s24(object->rva0001895d(), &screen))
			continue;

		float dx = (float)(position->x - screen.x);
		float dy = (float)(position->y - screen.y);
		if ((float)sqrt(dx * dx + dy * dy) < limit)
		{
			if (best == 0)
			{
				best = object;
				continue;
			}

			ICoord2D bestScreen;
			if (!g_bfmeStateDF->s24(best->rva0001895d(), &bestScreen))
				continue;

			float bx = (float)(position->x - bestScreen.x);
			float by = (float)(position->y - bestScreen.y);
			if (sqrt(by * by + bx * bx) > (float)sqrt(dx * dx + dy * dy))
				best = object;
		}
	}

	return best;
}
