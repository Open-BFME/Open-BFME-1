// ?rva0044a2e0@Rva00449790Owner@@QAEXXZ
// partial score=0.88 date=2026-09-23
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/stringinline
// stlport
// Address-derived reconstruction of the embedded BFME cursor-animation owner.
// Retail 0x0044A2E0 (757 bytes), reached only through ILT 0x00045570 from
// 0x0044A6A0 with ecx = TheInGameUI + 0x12C8 -- the same object whose ctor is
// 0x00449790 (twelve ints, an STLport list at +0x30, two -1 ints at +0x34/+0x38).
// Only while TheMouse's cursor (+0x4DA8) is 0x29: submits the GlobalData
// +0xDD0 string block through 0x0044A240, then for every expired list entry
// spawns screen animations of that template along the segment from the last
// mouse position to the current one (count = length / spacing + 1).

#define _STLP_NO_EXCEPTIONS 1
#include <list>
#include "StringInline.h"

typedef int Int;
typedef unsigned int UnsignedInt;
typedef float Real;

extern "C" double __cdecl sqrt(double value);
#pragma intrinsic(sqrt)

struct Rva0044A2E0Coord
{
	Int x;
	Int y;
};

struct Rva0044A2E0Vector
{
	Real x;
	Real y;

	Real length() const { return (Real)sqrt(x * x + y * y); }
};


struct Rva0044A2E0Element
{
	UnsignedInt m_frame;
	AsciiString m_name;
};

typedef _STL::list<Rva0044A2E0Element,
	_STL::allocator<Rva0044A2E0Element> > Rva0044A2E0List;


class Anim2DTemplate;

class Anim2DCollection
{
public:
	Anim2DTemplate *findTemplate(const AsciiString &name);
};

class InGameUI
{
public:
	void rva00443910(Anim2DTemplate *animTemplate,
		const Rva0044A2E0Coord *position, Int options,
		Real duration, Real zRisePerSecond);
};

class GameClientRandomVariable
{
public:
	Real getValue() const;

private:
	char m_data[12];
};

class ClientRoot4120
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02();
	virtual void slot03(); virtual void slot04(); virtual void slot05();
	virtual void slot06(); virtual void slot07(); virtual void slot08();
	virtual void slot09(); virtual void slot10(); virtual void slot11();
	virtual void slot12(); virtual void slot13(); virtual void slot14();
	virtual void slot15(); virtual void slot16(); virtual void slot17();
	virtual void slot18(); virtual void slot19(); virtual void slot20();
	virtual void slot21(); virtual void slot22(); virtual void slot23();
	virtual void slot24(); virtual void slot25();
	virtual UnsignedInt getFrame();
};

class WWMath
{
public:
	static Real Random_Float();
};

class BfmeBlobBL
{
public:
	char m_data[12];
};

class StringBaseNarrowBL
{
protected:
	StringBaseNarrowBL(const StringBaseNarrowBL &other);
	~StringBaseNarrowBL();
	char *m_text;
};

class AsciiStringBL : public StringBaseNarrowBL
{
public:
	AsciiStringBL(const AsciiStringBL &other) : StringBaseNarrowBL(other) {}
	~AsciiStringBL() {}
};

class BfmeSinkBL
{
public:
	void bfmeSubmitBL(AsciiStringBL name, Int count, BfmeBlobBL *first,
		BfmeBlobBL *second, BfmeBlobBL *third, BfmeBlobBL *fourth);
};

struct Rva0044A2E0Mouse
{
	char m_pad0000[0x4D10];
	Int m_x;
	Int m_y;
	char m_pad4D18[0x4DA8 - 0x4D18];
	Int m_cursor;
};

struct Rva0044A2E0GlobalData
{
	char m_pad0000[0xDD0];
	AsciiString m_string_DD0;
	Int m_int_DD4;
	char m_pad0DD8[0xDE4 - 0xDD8];
	Real m_real_DE4;
	Int m_int_DE8;
	GameClientRandomVariable m_random_DEC;
	BfmeBlobBL m_blob_DF8;
	BfmeBlobBL m_blob_E04;
	BfmeBlobBL m_blob_E10;
	char m_pad0E1C[0xE3C - 0xE1C];
	Int m_int_E3C;
	Int m_int_E40;
};

class Rva00449790Owner
{
public:
	void rva0044a2e0();

private:
	Int m_f00;
	Int m_f04;
	Int m_f08;
	Int m_f0c;
	Int m_f10;
	Int m_f14;
	Int m_f18;
	Int m_f1c;
	Int m_f20;
	Int m_f24;
	Int m_f28;
	Int m_f2c;
	Rva0044A2E0List m_animations;
	Int m_previousX;
	Int m_previousY;
};

extern Rva0044A2E0Mouse *TheMouse;
extern Anim2DCollection *TheAnim2DCollection;
extern Rva0044A2E0GlobalData *TheWritableGlobalData;
extern ClientRoot4120 *TheGameClient;
extern InGameUI *TheInGameUI;

void Rva00449790Owner::rva0044a2e0()
{
	if (TheMouse == 0 || TheAnim2DCollection == 0 || TheMouse->m_cursor != 0x29)
		return;

	Rva0044A2E0GlobalData *global = TheWritableGlobalData;
	reinterpret_cast<BfmeSinkBL *>(TheInGameUI)->bfmeSubmitBL(
		*(AsciiStringBL *)&global->m_string_DD0,
		global->m_int_DD4,
		(BfmeBlobBL *)&global->m_random_DEC,
		&global->m_blob_DF8,
		&global->m_blob_E04,
		&global->m_blob_E10);

	Rva0044A2E0Coord mousePosition;
	mousePosition.x = TheMouse->m_x;
	mousePosition.y = TheMouse->m_y;
	UnsignedInt frame = TheGameClient->getFrame();

	for (Rva0044A2E0List::iterator it = m_animations.begin();
		it != m_animations.end();)
	{
		Anim2DTemplate *animTemplate =
			TheAnim2DCollection->findTemplate(TheWritableGlobalData->m_string_DD0);
		if (animTemplate == 0 || (*it).m_frame > frame)
		{
			++it;
			continue;
		}

		Int previousX = m_previousX;
		if (previousX == -1)
		{
			TheInGameUI->rva00443910(animTemplate, &mousePosition, 1,
				TheWritableGlobalData->m_random_DEC.getValue(), 1.0f);
		}
		else
		{
			Int previousY = m_previousY;
			Rva0044A2E0Vector current;
			current.x = (Real)mousePosition.x;
			current.y = (Real)mousePosition.y;
			Rva0044A2E0Vector point;
			point.x = current.x - (Real)previousX;
			point.y = current.y - (Real)previousY;
			Real distance = point.length();
			Int spacing = TheWritableGlobalData->m_int_DE8;
			if (spacing <= 0)
				spacing = 1;
			Int count = (Int)(distance / (Real)spacing + 1.0f);
			Real scale = 1.0f / (Real)count;
			Rva0044A2E0Vector step;
			step.x = point.x * scale;
			step.y = scale * point.y;
			point.x = (Real)(TheWritableGlobalData->m_int_E3C + previousX);
			point.y = (Real)(TheWritableGlobalData->m_int_E40 + previousY);
			Real zRise = 1.0f;
			Real zStep = 0.99f / (Real)count;

			for (Int i = 0; i < count; ++i)
			{
				point.x += step.x;
				point.y += step.y;
				Rva0044A2E0Coord position;
				position.x = (Int)(point.x + 0.5f);
				position.y = (Int)(point.y + 0.5f);
				if (count != 1 || !(WWMath::Random_Float() > TheWritableGlobalData->m_real_DE4))
				{
					TheInGameUI->rva00443910(animTemplate, &position, 1,
						TheWritableGlobalData->m_random_DEC.getValue(), zRise);
				}
				zRise -= zStep;
			}
		}

		it = m_animations.erase(it);
	}

	m_previousX = mousePosition.x;
	m_previousY = mousePosition.y;
}
