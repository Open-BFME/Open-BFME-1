// ?bfmeStop@BfmeStopF@@QAEXXZ
// partial score=0.75 date=2026-09-14
// cl: /DNDEBUG /DWIN32 /MD /EHsc /ICode/Libraries/Source/WWVegas/WWLib
// BfmeStopF::bfmeStop — retail 0x0037C600 (508B). Called by the clear
// bodies in Bfme5ClearsWithTails.cpp and Bfme5GuardedStopClear.cpp through
// ILT 0x00015E2E.

#include "ascii_string.h"

// map<int,int>::operator[] resolves through ILT 0x00033AA (??AEmotionMap);
// map<unsigned short,int>::operator[] through ILT 0x00028D0D.
class EmotionMap
{
public:
	int &operator[]( const int &key );

	unsigned int m_head;
	unsigned int m_count;
	unsigned int m_compare;
};

class EmotionShortMap
{
public:
	int &operator[]( const unsigned short &key );

	unsigned int m_head;
	unsigned int m_count;
	unsigned int m_compare;
};

class Object;

// ILT 0x0002BE77: the object's related-pointer getter (retail 0x001CF980).
class BfmeRes920D
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual void slot10();
	virtual void slot11();
	virtual void slot12();
	virtual void slot13();
	virtual void slot14();
	virtual void slot15();
	virtual void slot16();
	virtual void slot17();
	virtual void slot18();
	virtual void *slot19();
};

class BfmeX920D
{
public:
	BfmeRes920D *bfmeGet920D();
};

// ILT 0x000486FD: module preload wrapper (retail 0x0026FD50).
class BfmeAI956
{
public:
	void j_000486fd();
};

// ILT 0x00011F77 / 0x00022BBA: FXList predicate and object-effect call.
class FXList
{
public:
	bool bfmeIsBlocked() const;
	void doFXObj( const Object *a, const Object *b ) const;
};

// ILT 0x000095ED: the !related apply path (retail 0x001C7720).
class BfmeThingVKP
{
public:
	void bfmeSetVKP( short a, short b );
};

class BfmeStrShell
{
public:
	void *m_bfmeData;
	void releaseBuffer() const;
};

class BfmeBridgeStr
{
public:
	void *m_bfmeData;
	~BfmeBridgeStr() { releaseBuffer(); }
	void releaseBuffer() const;
};

class RvaStopState
{
public:
	BfmeStrShell getBridgeModelNameDamagedFirst();
	BfmeBridgeStr getBridgeModelNameDamaged();	// ILT 0x00041BF0 -> 0x0037B0D0

	char m_pad00[0x10];
	unsigned int m_bfme10;
	unsigned int m_bfme14;
	unsigned int m_bfme18;
	char m_pad1C[0x1C];
	FXList *m_bfme38;
	unsigned int m_bfme3C;
	unsigned int m_bfme40;
	unsigned char m_bfme44;
	char m_pad45[3];
	unsigned int m_bfme48;
	int m_bfme4C;
	char m_pad50[0x2C];
	int m_bfme7C;
	char m_pad80[0x4C];
	int m_bfmeCC;
};

class ModelConditionFlags
{
};

class Object
{
public:
	bool applyAttributeModifier( const AsciiString &name, int value );
	void rva001CD300( const int &a, const int &b );
	void clearAndSetModelConditionFlags( const ModelConditionFlags &a, const ModelConditionFlags &b );
	void notifyModelConditionChanged();

	char m_pad00[0x124];
	unsigned int m_bfmeFlags124;
	char m_pad128[0x204 - 0x128];
	BfmeAI956 *m_bfmeModule;			// +0x204
};

class GameLogic
{
public:
	Object *findObjectByID( int id );

	char m_pad00[0x3C];
	unsigned int m_bfmeFrame;				// +0x3C
};

extern GameLogic *volatile TheGameLogic;				// retail [0x012F0898]

class BfmeStopF
{
public:
	void bfmeStop();

	Object *m_bfmeObject;					// +0x00
	RvaStopState *m_bfmeState;				// +0x04
	int m_bfme08;						// +0x08
	unsigned short m_bfme0C;				// +0x0C
	unsigned short m_bfme0E;
	unsigned int m_bfme10;					// +0x10
	EmotionMap m_bfme14;					// +0x14
	EmotionShortMap m_bfme20;				// +0x20
	char m_pad2C[4];
	unsigned int m_bfme30;					// +0x30
};

// ?bfmeStop@BfmeStopF@@QAEXXZ
void BfmeStopF::bfmeStop()
{
	Object *found;
	FXList *fx;
	Object *target;
	if (m_bfmeState->m_bfme10)
	{
		m_bfme10 = m_bfmeState->m_bfme10 + TheGameLogic->m_bfmeFrame;
	}

	if (m_bfmeState->m_bfme14 && m_bfme08)
	{
		unsigned int frame = TheGameLogic->m_bfmeFrame;
		m_bfme14[m_bfme08] = m_bfmeState->m_bfme14 + frame;
	}

	if (m_bfmeState->m_bfme18 && m_bfme0C)
	{
		unsigned int frame = TheGameLogic->m_bfmeFrame;
		m_bfme20[m_bfme0C] = m_bfmeState->m_bfme18 + frame;
	}

	if (m_bfmeState->m_bfme38)
	{
		target = m_bfmeObject;
		BfmeRes920D *related = ((BfmeX920D *)m_bfmeObject)->bfmeGet920D();
		if (related)
		{
			target = (Object *)related->slot19();
		}

		found = TheGameLogic->findObjectByID(m_bfme08);
		if (found || !m_bfme08)
		{
			if (!target)
			{
				target = m_bfmeObject;
			}
			fx = m_bfmeState->m_bfme38;
			if (fx && !fx->bfmeIsBlocked())
			{
				fx->doFXObj(target, found);
			}
		}
	}

	if (m_bfmeObject->m_bfmeModule)
	{
		if (m_bfmeState->m_bfme4C == 0 ||
			(m_bfmeState->m_bfme4C > 1 && m_bfmeState->m_bfme4C <= 5))
		{
			m_bfmeObject->m_bfmeModule->j_000486fd();
		}

		Object *related = (Object *)((BfmeX920D *)m_bfmeObject)->bfmeGet920D();
		if (related)
		{
			m_bfmeObject->rva001CD300(
				m_bfmeState->m_bfme7C, m_bfmeState->m_bfmeCC);
		}
		else
		{
			m_bfmeObject->clearAndSetModelConditionFlags(
				(const ModelConditionFlags &)m_bfmeState->m_bfme7C,
				(const ModelConditionFlags &)m_bfmeState->m_bfmeCC);
		}

		if (m_bfmeObject->m_bfmeFlags124 & 0x40000000)
		{
			m_bfmeObject->m_bfmeFlags124 &= 0xBFFFFFFF;
			m_bfmeObject->notifyModelConditionChanged();
		}
	}

	BfmeStrShell first = m_bfmeState->getBridgeModelNameDamagedFirst();
	void *firstData = first.m_bfmeData;
	bool ready;
	if (firstData &&
		*(unsigned short *)((char *)firstData + 4) &&
		TheGameLogic->m_bfmeFrame >= m_bfme30 + m_bfmeState->m_bfme40 &&
		m_bfmeState->m_bfme44)
	{
		ready = true;
	}
	else
	{
		ready = false;
	}
	first.releaseBuffer();
	if (ready)
	{
		m_bfmeObject->applyAttributeModifier(
			(const AsciiString &)m_bfmeState->getBridgeModelNameDamaged(),
			m_bfmeState->m_bfme48);
	}
}
