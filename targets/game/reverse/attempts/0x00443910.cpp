// ?addDirect@Rva00443910OwnerDirect@@QAEXPAVAnim2DTemplate@@PBURva00443910Coord@@HMM@Z
// partial score=0.97 date=2026-09-27
// ?rva00443910@Rva00443910Owner@@QAEXPAVAnim2DTemplate@@PBURva00443910Coord@@HMM@Z
// Retail 0x00443910, address-derived owner. The receiver is witnessed by the caller.
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
	virtual Int getFrame();
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

#define TheAnim2DCollection (*(Anim2DCollection **)0x012f4ca8)
#define TheGameClient (*(Rva00443910Client **)0x012f1464)
#define TheWritableGlobalData (*(Rva00443910GlobalDataDirect **)0x012ed5c8)

class Rva0043BBC0
{
public:
	Rva0043BBC0() throw();
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

class Anim2DDirect
{
public:
	Anim2DDirect(Anim2DTemplate *, Anim2DCollection *);
	char m_storage[0x2c];
	Int m_tail2c;
	Int m_tail30;
};

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

void Rva00443910OwnerDirect::addDirect(Anim2DTemplate *animTemplate,
	const Rva00443910Coord *position, Int options, Real duration,
	Real zRisePerSecond)
{
	register const Rva00443910Coord *pos = position;
	if (animTemplate == 0 || pos == 0 || duration <= *(const Real *)0x01075350)
		return;

	Anim2DDirect *anim = new Anim2DDirect(animTemplate, TheAnim2DCollection);

	anim->m_tail2c = GetGameClientRandomValue(20, 30,
		(char *)0x010f5978, 0x1ac4);
	anim->m_tail30 = anim->m_tail2c;

	Rva0043BBC0 *value = new Rva0043BBC0;
	if (value != 0)
	{
	value->m_anim = (Int)anim;
	UnsignedInt frame = TheGameClient->getFrame();
	value->m_expireFrame = (Int)(frame + duration * *(const Real *)0x01075344);
	value->m_options = options;
	value->m_x = pos->m_x;
	value->m_y = pos->m_y;
	value->m_randomFrame = (Int)(TheWritableGlobalData->m_randomFrame.bfmeScaleXW() +
		*(const Real *)0x0107533c);

	Rva00443910RandomPair random;
	random.x = WWMath::Random_Float();
	random.x += random.x;
	random.x -= *(const Real *)0x01075334;
	random.y = WWMath::Random_Float();
	random.y += random.y;
	random.y -= *(const Real *)0x01075334;
	duration = random.y * random.y + random.x * random.x;
	if (duration == *(const Real *)0x01075350)
	{
	}
	else
	{
		duration = WWMath::Inv_Sqrt(duration);
		random.x *= duration;
		random.y *= duration;
	}

	value->m_xVelocity = TheWritableGlobalData->m_xVelocity.getValue() * random.x;
	value->m_yVelocity = TheWritableGlobalData->m_yVelocity.getValue() * random.y;
	value->m_zVelocity = TheWritableGlobalData->m_zVelocity.getValue();
	value->m_x += zRisePerSecond * value->m_xVelocity;
	value->m_y += zRisePerSecond * value->m_yVelocity;

	m_list.push_front(reinterpret_cast<Rva00442700Element &>(value));
	}
}
