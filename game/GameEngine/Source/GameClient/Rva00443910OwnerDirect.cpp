// Retail 0x00443910 (522 B) and its value constructor 0x0043BBC0 (39 B); owners are address-derived.
// The constructor's body must be visible here: with only a declaration the caller either gains an
// EH state (no throw()) or merges the allocation's null path (throw()), neither of which retail has.
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /DBFME_STLP_NODE_ALLOC /Iinputs/reference/shims/stlp_nodealloc /Iinputs/reference/shims/asciistringsetoutofline /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Igame/Libraries/Source/WWVegas/WWLib
// stlport

#include <list>
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
