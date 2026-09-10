// ?rva001FE910@GettingBuiltBehavior@@QAEXXZ
// partial score=0.95 date=2026-09-09
// Retail 0x001FE910, 76 bytes.  The neighboring matched methods, constructor
// at 0x001FE380, and object fields at +0x08 and +0x24 identify this helper as
// GettingBuiltBehavior.  The two pinned calls and the audio vtable slot match
// the retail body without a generated instruction sequence.

typedef unsigned int UnsignedInt;

class Object
{
public:
	char m_pad00[0x78];
	UnsignedInt m_objectID;

	__forceinline UnsignedInt getID() const
	{
		return m_objectID;
	}
};

class BfmeY982
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0c();
	virtual void slot10();
	virtual void slot14();

	BfmeY982 *bfmeConv982B();
};

class GameLogic
{
public:
	Object *findObjectByID(int id);
};

class Rva00367E30Logic;
extern Rva00367E30Logic *TheBfmeGameLogic;

class AudioClientUpdate
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0c();
	virtual void slot10();
	virtual void slot14();
	virtual void slot18();
	virtual void slot1c();
	virtual void slot20();
	virtual void slot24();
	virtual void slot28();
	virtual void slot2c();
	virtual void slot30();
	virtual void slot34();
	virtual void slot38();
	virtual void slot3c();
	virtual void slot40();
	virtual void slot44();
	virtual void slot48();
	virtual void removeAudioEvent(UnsignedInt audioEvent);
};

extern AudioClientUpdate *TheAudioClientUpdate;

class GettingBuiltBehavior
{
public:
	void rva001FE910();

private:
	char m_pad00[8];
	Object *m_object;
	char m_pad0c[0x18];
	UnsignedInt m_audioHandle;
};

void GettingBuiltBehavior::rva001FE910()
{
	Object *object = m_object;
	if (BfmeY982 *target = (BfmeY982 *)((GameLogic *)TheBfmeGameLogic)->findObjectByID(
		(int)object->getID()))
	{
		BfmeY982 *production = target->bfmeConv982B();
		if (production != 0)
			production->slot14();
	}

	if (TheAudioClientUpdate != 0 && m_audioHandle >= 5)
	{
		TheAudioClientUpdate->removeAudioEvent(m_audioHandle);
		m_audioHandle = 1;
	}
}
