// ?d_0048fc90@@YAXXZ
// partial score=0.9911 date=2026-09-28
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// Retail 0x0048FC90 (898 bytes): word-wraps a UnicodeString into the lines of
// the timed text object whose clear (0x0048FA30, Bfme5DestroyRangeClear.cpp)
// is its fifth virtual. Reached through ILT 0x000198B2 from the forwarder at
// 0x0043BC10 (`if (m_81C) m_81C->...(text, seconds)`); no string or caller
// names the method, so it keeps an address-derived name.
//
// Read from the retail body: it clears the object, copies the text and lets
// the target (+0x08) prepare; empty text ends there. Timing: the frame from
// TheGameClient slot +0x68 goes to +0x18, and with a duration in seconds
// +0x1C/+0x20 get frame + 30*seconds and 30 frames before that, otherwise
// 0 and frame + 450. A new display string takes the target's font, and a
// whitespace state machine feeds words to the flush helper 0x0048FAC0 and
// line breaks to 0x0048F8C0 through a line record on the stack. Each line is
// then placed: x advances by 1.5 font heights from 100, elements get running
// offsets from 0x14, and the 0x0048E730 functor walk stacks them from the
// +0x18 value in steps of 30. The display string is freed at the end.

#define _STLP_NO_EXCEPTIONS 1
#include <vector>
#include <algorithm>

typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;
typedef float Real;
typedef bool Bool;
typedef unsigned short WideChar;

#define NULL 0

// MSVCR71 import (IAT VA 0x01359438); the CRT header's inline wrapper would
// call iswctype instead.
extern "C" __declspec(dllimport) int __cdecl iswspace(WideChar c);

template <typename T>
struct StringBaseData
{
	UnsignedShort m_refCount;
	UnsignedShort m_numCharsAllocated;
	UnsignedShort m_length;
	UnsignedShort m_pad06;
	T m_text[1];
};

template <typename T>
class StringBase
{
	friend class UnicodeString;

public:
	void concat(const T *text, Int length);

private:
	StringBase(void) : m_data(0) {}
	StringBase(const StringBase<T> &other);
	~StringBase(void) { releaseBuffer(); }

	void releaseBuffer(void);

	StringBaseData<T> *m_data;
};

class UnicodeString : private StringBase<WideChar>
{
public:
	UnicodeString(void) : StringBase<WideChar>() {}
	UnicodeString(const UnicodeString &other) : StringBase<WideChar>(other) {}
	~UnicodeString(void) {}

	Int getLength(void) const { return m_data ? m_data->m_length : 0; }
	WideChar getCharAt(Int index) const { return m_data ? m_data->m_text[index] : 0; }
	void concat(WideChar c) { StringBase<WideChar>::concat(&c, 1); }
	void clear(void) { releaseBuffer(); }
};

class DisplayString
{
public:
	virtual void slot00(void);
	virtual void slot01(void);
	virtual void slot02(void);
	virtual void slot03(void);
	virtual void slot04(void);
	virtual void slot05(void);
	virtual void setFont(void *font);					// +0x18
};

// Retail global at VA 0x012F12CC: slot +0x24 hands out a display string and
// +0x28 takes it back.
class Rva0048EC80Manager
{
public:
	virtual void slot00(void);
	virtual void slot01(void);
	virtual void slot02(void);
	virtual void slot03(void);
	virtual void slot04(void);
	virtual void slot05(void);
	virtual void slot06(void);
	virtual void slot07(void);
	virtual void slot08(void);
	virtual DisplayString *newDisplayString(void);		// +0x24
	virtual void freeDisplayString(DisplayString *string);	// +0x28
};
extern Rva0048EC80Manager *Rva0048EC80TheManager;
typedef Rva0048EC80Manager BfmeDisplayManagerFC;
#define TheDisplayStringManager Rva0048EC80TheManager

class Display
{
public:
	virtual void slot00(void);
	virtual void slot01(void);
	virtual void slot02(void);
	virtual void slot03(void);
	virtual void slot04(void);
	virtual void slot05(void);
	virtual void slot06(void);
	virtual void slot07(void);
	virtual void slot08(void);
	virtual void slot09(void);
	virtual void slot10(void);
	virtual UnsignedInt displaySlot2C(void);			// +0x2C
};
extern Display *TheDisplay;

class GameClient
{
public:
#define GAME_CLIENT_SLOT(n) virtual void slot##n(void);
	GAME_CLIENT_SLOT(00) GAME_CLIENT_SLOT(01) GAME_CLIENT_SLOT(02) GAME_CLIENT_SLOT(03)
	GAME_CLIENT_SLOT(04) GAME_CLIENT_SLOT(05) GAME_CLIENT_SLOT(06) GAME_CLIENT_SLOT(07)
	GAME_CLIENT_SLOT(08) GAME_CLIENT_SLOT(09) GAME_CLIENT_SLOT(10) GAME_CLIENT_SLOT(11)
	GAME_CLIENT_SLOT(12) GAME_CLIENT_SLOT(13) GAME_CLIENT_SLOT(14) GAME_CLIENT_SLOT(15)
	GAME_CLIENT_SLOT(16) GAME_CLIENT_SLOT(17) GAME_CLIENT_SLOT(18) GAME_CLIENT_SLOT(19)
	GAME_CLIENT_SLOT(20) GAME_CLIENT_SLOT(21) GAME_CLIENT_SLOT(22) GAME_CLIENT_SLOT(23)
	GAME_CLIENT_SLOT(24) GAME_CLIENT_SLOT(25)
#undef GAME_CLIENT_SLOT
	virtual Int getFrame(void);							// +0x68
};
extern GameClient *TheGameClient;

// Elements of a line, as the matched 0x0048E730 walk sees them; this body
// also writes +0x10/+0x14 and reads +0x0C.
struct Rva0048E730Element
{
	void *m_measure;
	Int m_unused;
	Int m_offset;										// +0x08
	Int m_extra0c;										// +0x0C
	Int m_extra10;										// +0x10
	Int m_extra14;										// +0x14
};

typedef Rva0048E730Element BfmeLayoutElementFC;

class Rva0048E730Layout
{
public:
	Rva0048E730Layout(Int offset) : m_offset(offset) {}

	Int m_offset;
};

Rva0048E730Layout layoutRva0048E730(Rva0048E730Element **first,
	Rva0048E730Element **last, Rva0048E730Layout layout);

struct BfmeLayoutRangeFC
{
	_STL::vector<Rva0048E730Element *> m_elements;
};

typedef _STL::vector<BfmeLayoutRangeFC *> BfmeVecL;

// Lays one line's elements out left to right from offset 0x14 at column x.
class Rva0048FC90Place
{
public:
	Rva0048FC90Place(Int x) : m_offset(0x14), m_x(x) {}
	void operator()(BfmeLayoutElementFC *element)
	{
		element->m_extra10 = m_offset;
		m_offset += element->m_extra0c;
		element->m_extra14 = m_x;
	}

	Int m_offset;
	Int m_x;
};

// The stack record the two helpers take.
struct BfmeLineInfoFC
{
	BfmeLineInfoFC(Int width, Int halfWidth, BfmeVecL *lines,
		DisplayString *displayString)
		: m_width(width), m_halfWidth(halfWidth), m_lines(lines),
		  m_displayString(displayString), m_extra14(0)
	{
	}

	Int m_width;										// +0x00
	Int m_halfWidth;									// +0x04
	BfmeVecL *m_lines;						// +0x08
	DisplayString *m_displayString;						// +0x0C
	UnicodeString m_text;								// +0x10
	Int m_extra14;										// +0x14
};

struct Rva0048FC90Font
{
	UnsignedInt m_unmodelled00[4];
	Int m_height;										// +0x10
};

class BfmeTargetL
{
public:
	virtual void slot00(void);
	virtual void slot01(void);							// +0x04

	void setColour(Int colour) { m_bfmeColour = colour; }
	Rva0048FC90Font *getFont(void) const { return m_font; }

	Rva0048FC90Font *m_font;							// +0x04
	Int m_unmodelled08[4];
	Int m_bfmeColour;									// +0x18
};

class Gen_0048FA30
{
public:
	virtual void slot00(void);
	virtual void slot01(void);
	virtual void slot02(void);
	virtual void slot03(void);
	virtual void bfmeClearVirtual(void);				// +0x10, body 0x0048FA30

	void bfmeForward(const UnicodeString &source, Int seconds);
	void bfmeAddLine(BfmeLineInfoFC *info);
	void bfmeFlushLine(BfmeLineInfoFC *info, Int spaces, UnicodeString *word);

private:
	Int m_bfmeHead4;									// +0x04
	BfmeTargetL *m_bfmeTarget;							// +0x08
	BfmeVecL m_bfmeVector;					// +0x0C
	Int m_bfmeCount;									// +0x18
	Int m_bfmeIndex;									// +0x1C
	Int m_bfmeState;									// +0x20
};

// ?bfmeForward@Gen_0048FA30@@QAEXABVUnicodeString@@H@Z
void Gen_0048FA30::bfmeForward(const UnicodeString &source, Int seconds)
{
	bfmeClearVirtual();
	UnicodeString text(source);
	m_bfmeTarget->slot01();
	Int length = text.getLength();
	if (length == 0)
		return;

	Real halfWidth = (Real)(TheDisplay->displaySlot2C() / 2);
	Int width = (Int)((Real)TheDisplay->displaySlot2C() * 0.8333333f);
	m_bfmeCount = TheGameClient->getFrame();
	if (seconds)
	{
		m_bfmeIndex = m_bfmeCount + seconds * 30;
		m_bfmeState = m_bfmeIndex - 30;
	}
	else
	{
		m_bfmeState = m_bfmeCount + 450;
		m_bfmeIndex = 0;
	}
	m_bfmeTarget->setColour(0xFF000000);

	DisplayString *displayString = TheDisplayStringManager->newDisplayString();
	if (displayString == NULL)
		return;
	displayString->setFont(m_bfmeTarget->getFont());

	{
		BfmeVecL lines;
		{
			BfmeLineInfoFC info(width, (Int)halfWidth, &lines, displayString);
			Int spaces = 0;
			UnicodeString word;
			Int index = 0;
			Bool atSpace = true;
			WideChar ch = text.getCharAt(0);
			for (;;)
			{
				if (atSpace)
				{
					if (!iswspace(ch))
					{
						atSpace = false;
						continue;
					}
					if (ch == L' ')
					{
						++spaces;
					}
					else if (ch == L'\n')
					{
						bfmeAddLine(&info);
						spaces = 0;
					}
				}
				else
				{
					if (iswspace(ch))
					{
						bfmeFlushLine(&info, spaces, &word);
						spaces = 0;
						word.clear();
						atSpace = true;
						continue;
					}
					word.concat(ch);
				}
				if (++index >= length)
					break;
				ch = text.getCharAt(index);
			}
			if (!atSpace)
				bfmeFlushLine(&info, spaces, &word);
			bfmeAddLine(&info);
		}

		Int fontHeight = m_bfmeTarget->getFont()->m_height;
		Int x = 100;
		Int y = m_bfmeCount;
		for (BfmeVecL::iterator it = m_bfmeVector.begin();
			it != m_bfmeVector.end(); ++it)
		{
			Int lineX = x;
			x = (Int)((Real)x + (Real)fontHeight * 1.5f);
			_STL::for_each((*it)->m_elements.begin(), (*it)->m_elements.end(),
				Rva0048FC90Place(lineX));
			layoutRva0048E730((*it)->m_elements.begin(), (*it)->m_elements.end(),
				Rva0048E730Layout(y));
			y += 30;
		}

		TheDisplayStringManager->freeDisplayString(displayString);
	}
}
