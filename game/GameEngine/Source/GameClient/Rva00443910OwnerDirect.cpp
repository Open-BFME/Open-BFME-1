// Retail 0x00443910 (522 B) and its value constructor 0x0043BBC0 (39 B); owners are address-derived.
// The constructor's body must be visible here: with only a declaration the caller either gains an
// EH state (no throw()) or merges the allocation's null path (throw()), neither of which retail has.
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /DBFME_STLP_NODE_ALLOC /Iinputs/reference/shims/stlp_nodealloc /Iinputs/reference/shims/asciistringsetoutofline /Iinputs/reference/shims/zhcanonascii /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Igame/Libraries/Source/WWVegas/WWLib
// stlport

#include <list>
#include "ascii_string.h"
#include "GameClient/ClientRandomValue.h"

typedef int Int;
typedef unsigned int UnsignedInt;
typedef float Real;

class Anim2DTemplate;
class Anim2DCollection;

class Anim2D
{
public:
	Anim2D(Anim2DTemplate *, Anim2DCollection *);
	char m_storage[0x2c];
	Int m_tail2c;
	Int m_tail30;
};

struct Rva00443910Coord
{
	Int m_x;
	Int m_y;
};

class BfmeSubXW
{
public:
	Real bfmeScaleXW();
};

class Rva00443910Client
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
	static Real __fastcall Inv_Sqrt(Real);
};

struct Rva00442700Element
{
	Int m_body;
};

typedef _STL::list<Rva00442700Element, _STL::allocator<Rva00442700Element> >
	Rva00443910List;

struct Rva00443910GlobalDataDirect
{
	char m_padding[0xe04];
	GameClientRandomVariable m_xVelocity;
	GameClientRandomVariable m_yVelocity;
	GameClientRandomVariable m_zVelocity;
	BfmeSubXW m_randomFrame;
};

class GameClient;
class GlobalData;
extern Anim2DCollection *TheAnim2DCollection;
extern GameClient *TheGameClient;
extern GlobalData *TheWritableGlobalData;

class Rva0043BBC0
{
public:
	Rva0043BBC0();
	Int m_anim;
	Real m_x;
	Real m_y;
	Int m_expireFrame;
	Int m_options;
	Real m_xVelocity;
	Real m_yVelocity;
	Real m_zVelocity;
	Int m_randomFrame;
};

// @??0Rva0043BBC0@@QAE@XZ 0x0043BBC0
Rva0043BBC0::Rva0043BBC0()
{
	m_anim = 0;
	m_x = 0;
	m_y = 0;
	m_expireFrame = 0;
	m_xVelocity = 0;
	m_yVelocity = 0;
	m_zVelocity = 1.0f;
	m_options = 0;
	m_randomFrame = 0x20;
}

// Retail allocates 0x34 bytes and calls the Anim2D constructor itself.
typedef Anim2D Anim2DDirect;

struct Rva00443910RandomPair
{
	Real x;
	Real y;
};

class Rva00443910OwnerDirect
{
public:
	void addDirect(Anim2DTemplate *, const Rva00443910Coord *, Int, Real, Real);

private:
	char m_padding[0x12c4];
	Rva00443910List m_list;
};

extern Int GetGameClientRandomValue(Int, Int, char *, Int);

// @?addDirect@Rva00443910OwnerDirect@@QAEXPAVAnim2DTemplate@@PBURva00443910Coord@@HMM@Z 0x00443910
void Rva00443910OwnerDirect::addDirect(Anim2DTemplate *animTemplate,
	const Rva00443910Coord *position, Int options, Real duration,
	Real zRisePerSecond)
{
	register const Rva00443910Coord *pos = position;
	if (animTemplate == 0 || pos == 0 || duration <= 0.0f)
		return;

	Anim2DDirect *anim = new Anim2DDirect(animTemplate, TheAnim2DCollection);

	anim->m_tail2c = GetGameClientRandomValue(20, 30,
		"F:\\bfme\\Code\\gameengine\\Source\\GameClient\\InGameUI.cpp", 0x1ac4);
	anim->m_tail30 = anim->m_tail2c;

	Rva0043BBC0 *value = new Rva0043BBC0;
	if (value != 0)
	{
	value->m_anim = (Int)anim;
	value->m_expireFrame = (Int)(((Rva00443910Client *)TheGameClient)->getFrame() + duration * 5.0f);
	value->m_options = options;
	value->m_x = pos->m_x;
	value->m_y = pos->m_y;
	value->m_randomFrame = (Int)(((Rva00443910GlobalDataDirect *)TheWritableGlobalData)->m_randomFrame.bfmeScaleXW() +
		0.5f);

	Rva00443910RandomPair random;
	random.x = WWMath::Random_Float();
	random.x += random.x;
	random.x -= 1.0f;
	random.y = WWMath::Random_Float();
	random.y += random.y;
	random.y -= 1.0f;
	duration = random.y * random.y + random.x * random.x;
	if (duration == 0.0f)
	{
	}
	else
	{
		duration = WWMath::Inv_Sqrt(duration);
		random.x *= duration;
		random.y *= duration;
	}

	value->m_xVelocity = ((Rva00443910GlobalDataDirect *)TheWritableGlobalData)->m_xVelocity.getValue() * random.x;
	value->m_yVelocity = ((Rva00443910GlobalDataDirect *)TheWritableGlobalData)->m_yVelocity.getValue() * random.y;
	value->m_zVelocity = ((Rva00443910GlobalDataDirect *)TheWritableGlobalData)->m_zVelocity.getValue();
	value->m_x += zRisePerSecond * value->m_xVelocity;
	value->m_y += zRisePerSecond * value->m_yVelocity;

	m_list.push_front(reinterpret_cast<Rva00442700Element &>(value));
	}
}


// Address-derived reconstruction of the embedded cursor-animation owner built by
// the constructor at 0x00449790 (twelve ints, an STLport list at +0x30, two -1
// ints at +0x34/+0x38). Retail 0x0044A2E0 is reached only through ILT 0x00045570
// from 0x0044A6A0 with ecx = TheInGameUI + 0x12C8. It must follow addDirect in
// this unit: with addDirect's body visible, MSVC 7.1 knows the coordinate
// pointer does not escape, and schedules the client vtable load between the two
// mouse-coordinate stores as retail does.

typedef ICoord2D Rva0044A2E0Coord;
typedef Coord2D Rva0044A2E0Vector;

struct Rva0044A2E0Element
{
	UnsignedInt m_frame;
	AsciiString m_name;
};

typedef _STL::list<Rva0044A2E0Element,
	_STL::allocator<Rva0044A2E0Element> > Rva0044A2E0List;

class Anim2DCollection
{
public:
	Anim2DTemplate *findTemplate(const AsciiString &name);
};

// AsciiStringBL, BfmeBlobBL and BfmeSinkBL as declared beside their matched
// body in game/GameEngine/Source/Common/BfmeSinkSubmitBL.cpp (0x0044A240).
class AsciiStringBL : public AsciiString
{
public:
	AsciiStringBL(const AsciiStringBL &other) throw() : AsciiString(other)
	{
	}

	~AsciiStringBL(void) throw()
	{
	}
};

class BfmeBlobBL
{
public:
	char m_bfmePadBBL[12];
};

class Rva004488B0FourBlockRecord
{
};

class BfmeSinkBL
{
public:
	void bfmeSubmitBL(AsciiStringBL name, int count, BfmeBlobBL *first,
		BfmeBlobBL *second, BfmeBlobBL *third, BfmeBlobBL *fourth);

private:
	char m_bfmePad[0x12c8];
	Rva004488B0FourBlockRecord m_bfmeRecord;
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

class Mouse;
class InGameUI;
extern Mouse *TheMouse;
extern InGameUI *TheInGameUI;

// @?rva0044a2e0@Rva00449790Owner@@QAEXXZ 0x0044A2E0
void Rva00449790Owner::rva0044a2e0()
{
	Rva0044A2E0Mouse *mouse = (Rva0044A2E0Mouse *)TheMouse;
	if (mouse == 0 || TheAnim2DCollection == 0 || mouse->m_cursor != 0x29)
		return;

	Rva0044A2E0GlobalData *global = (Rva0044A2E0GlobalData *)TheWritableGlobalData;
	reinterpret_cast<BfmeSinkBL *>(TheInGameUI)->bfmeSubmitBL(
		*(AsciiStringBL *)&global->m_string_DD0,
		global->m_int_DD4,
		(BfmeBlobBL *)&global->m_random_DEC,
		&global->m_blob_DF8,
		&global->m_blob_E04,
		&global->m_blob_E10);

	Rva0044A2E0Coord mousePosition;
	mousePosition.x = ((Rva0044A2E0Mouse *)TheMouse)->m_x;
	mousePosition.y = ((Rva0044A2E0Mouse *)TheMouse)->m_y;
	UnsignedInt frame = ((Rva00443910Client *)TheGameClient)->getFrame();

	for (Rva0044A2E0List::iterator it = m_animations.begin();
		it != m_animations.end();)
	{
		Anim2DTemplate *animTemplate = TheAnim2DCollection->findTemplate(
			((Rva0044A2E0GlobalData *)TheWritableGlobalData)->m_string_DD0);
		if (animTemplate == 0 || (*it).m_frame > frame)
		{
			++it;
			continue;
		}

		Int previousX = m_previousX;
		if (previousX == -1)
		{
			((Rva00443910OwnerDirect *)TheInGameUI)->addDirect(animTemplate,
				(const Rva00443910Coord *)&mousePosition, 1,
				((Rva0044A2E0GlobalData *)TheWritableGlobalData)->m_random_DEC.getValue(), 1.0f);
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
			Int spacing = ((Rva0044A2E0GlobalData *)TheWritableGlobalData)->m_int_DE8;
			if (spacing <= 0)
				spacing = 1;
			Int count = (Int)(distance / (Real)spacing + 1.0f);
			Real scale = 1.0f / (Real)count;
			Rva0044A2E0Vector step;
			step.x = point.x * scale;
			step.y = scale * point.y;
			point.x = (Real)(((Rva0044A2E0GlobalData *)TheWritableGlobalData)->m_int_E3C + previousX);
			point.y = (Real)(((Rva0044A2E0GlobalData *)TheWritableGlobalData)->m_int_E40 + previousY);
			Real zRise = 1.0f;
			Real zStep = 0.99f * zRise / (Real)count;

			for (Int i = 0; i < count; ++i)
			{
				point.x += step.x;
				point.y += step.y;
				Rva0044A2E0Coord position;
				position.x = (Int)(point.x + 0.5f);
				position.y = (Int)(point.y + 0.5f);
				if (count != 1 || !(WWMath::Random_Float() >
					((Rva0044A2E0GlobalData *)TheWritableGlobalData)->m_real_DE4))
				{
					((Rva00443910OwnerDirect *)TheInGameUI)->addDirect(animTemplate,
						(const Rva00443910Coord *)&position, 1,
						((Rva0044A2E0GlobalData *)TheWritableGlobalData)->m_random_DEC.getValue(), zRise);
				}
				zRise -= zStep;
			}
		}

		it = m_animations.erase(it);
	}

	m_previousX = mousePosition.x;
	m_previousY = mousePosition.y;
}
