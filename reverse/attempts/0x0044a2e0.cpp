// ?d_0044a2e0@@YAXXZ
// partial score=0.2 date=2026-09-22
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/stringinline
// stlport
// Address-derived reconstruction of the embedded BFME cursor-animation owner.

#define _STLP_NO_EXCEPTIONS 1
#include <list>

typedef int Int;
typedef unsigned int UnsignedInt;
typedef float Real;

extern "C" double sqrt(double value);
extern Real g_bfmeDefaultBU;
extern const Real g_bfmeK1253;

template <typename T> struct Rva0044A2E0StringData
{
	int m_refCount;
	int m_length;
	T m_text[1];
};

template <typename T> class StringBase
{
	friend class AsciiString;

private:
	StringBase() : m_data(0) {}
	StringBase(const StringBase<T> &other);
	~StringBase();
	Rva0044A2E0StringData<T> *m_data;
};

class AsciiString : private StringBase<char>
{
public:
	AsciiString() : StringBase<char>() {}
	AsciiString(const AsciiString &other) : StringBase<char>(other) {}
	~AsciiString() {}
};

struct Rva0044A2E0Element
{
	Int m_frame;
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
	void addWorldAnimation(Anim2DTemplate *animTemplate,
		const struct Rva0044A2E0Coord *position, Int options,
		Real duration, Real zRisePerSecond);
};

struct Rva0044A2E0Coord
{
	Int x;
	Int y;
};

class GameClientRandomVariable
{
public:
	Real getValue() const;
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

namespace WWMath
{
	Real Random_Float();
}

class BfmeSinkBL;
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

class Rva0044A2E0Mouse
{
private:
	char m_pad0000[0x4D10];

public:
	Int m_x;
	Int m_y;
	char m_pad4D18[0x4DA8 - 0x4D18];
	Int m_cursor;
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

#define TheMouse (*(Rva0044A2E0Mouse **)0x012F4C5C)
#define TheAnim2DCollection (*(Anim2DCollection **)0x012F4CA8)
#define TheWritableGlobalData (*(void **)0x012ED5C8)
#define TheGameClient (*(ClientRoot4120 **)0x012F1464)
#define TheInGameUISink (*(BfmeSinkBL **)0x012F148C)
#define TheInGameUIAnimation (*(InGameUI **)0x012F148C)

#pragma comment(linker, "/alternatename:?findTemplate@Anim2DCollection@@QAEPAVAnim2DTemplate@@ABVAsciiString@@@Z=?j_0000c0ea@@YAXXZ")
#pragma comment(linker, "/alternatename:?getValue@GameClientRandomVariable@@QBEMXZ=?j_0000d7b5@@YAXXZ")
#pragma comment(linker, "/alternatename:?bfmeSubmitBL@BfmeSinkBL@@QAEXVAsciiStringBL@@HPAVBfmeBlobBL@@111@Z=?j_00039333@@YAXXZ")
#pragma comment(linker, "/alternatename:?addWorldAnimation@InGameUI@@QAEXPAVAnim2DTemplate@@PBURva0044A2E0Coord@@HMM@Z=?j_0003d230@@YAXXZ")

void Rva00449790Owner::rva0044a2e0()
{
	if (TheMouse == 0 || TheAnim2DCollection == 0 || TheMouse->m_cursor != 0x29)
		return;

	void *global = TheWritableGlobalData;
	TheInGameUISink->bfmeSubmitBL(
		*(AsciiStringBL *)((char *)global + 0xDD0),
		*(Int *)((char *)global + 0xDD4),
		(BfmeBlobBL *)((char *)global + 0xDEC),
		(BfmeBlobBL *)((char *)global + 0xDF8),
		(BfmeBlobBL *)((char *)global + 0xE04),
		(BfmeBlobBL *)((char *)global + 0xE10));

	Rva0044A2E0Coord mousePosition;
	mousePosition.x = TheMouse->m_x;
	mousePosition.y = TheMouse->m_y;
	UnsignedInt frame = TheGameClient->getFrame();

	for (Rva0044A2E0List::iterator it = m_animations.begin();
		it != m_animations.end();)
	{
		Rva0044A2E0Element &entry = *it;
		Anim2DTemplate *animTemplate = TheAnim2DCollection->findTemplate(entry.m_name);
		if (animTemplate == 0 || entry.m_frame > (Int)frame)
			break;

		if (m_previousX == -1)
		{
			Real zRise = 1.0f;
			TheInGameUIAnimation->addWorldAnimation(animTemplate, &mousePosition, 1,
				(*(GameClientRandomVariable *)((char *)TheWritableGlobalData + 0xDEC)).getValue(), zRise);
		}
		else
		{
			Int previousX = m_previousX;
			Int previousY = m_previousY;
			Int samples = *(Int *)((char *)TheWritableGlobalData + 0xDE8);
			Real deltaX = (Real)mousePosition.x - (Real)previousX;
			Real deltaY = (Real)mousePosition.y - (Real)previousY;
			Real distance = (Real)sqrt(deltaX * deltaX + deltaY * deltaY);
			Int divisor = previousY;
			if (samples <= 0)
				divisor = 1;
			Int count = (Int)(distance / (Real)divisor + g_bfmeDefaultBU);
			Real scale = g_bfmeDefaultBU / (Real)count;
			Real stepX = deltaX * scale;
			Real stepY = deltaY * scale;
			Real x = (Real)(*(Int *)((char *)TheWritableGlobalData + 0xE3C) + previousX);
			Real y = (Real)(*(Int *)((char *)TheWritableGlobalData + 0xE40) + previousY);
			Real zRise = 1.0f;
			Real zStep = (*(const Real *)0x01083BFC) / scale;

			while (count > 0)
			{
				x += stepX;
				y += stepY;
				Rva0044A2E0Coord position;
				position.x = (Int)(x + g_bfmeK1253);
				position.y = (Int)(y + g_bfmeK1253);
				if (count != 1 || WWMath::Random_Float() != *(Real *)((char *)TheWritableGlobalData + 0xDE4))
				{
					TheInGameUIAnimation->addWorldAnimation(animTemplate, &position, 1,
						(*(GameClientRandomVariable *)((char *)TheWritableGlobalData + 0xDEC)).getValue(), zRise);
				}
				zRise -= zStep;
				--count;
			}
		}

		it = m_animations.erase(it);
	}

	m_previousX = mousePosition.x;
	m_previousY = mousePosition.y;
}
