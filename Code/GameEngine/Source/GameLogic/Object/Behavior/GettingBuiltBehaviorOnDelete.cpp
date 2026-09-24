// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
//
// Retail 0x001FE910, 76 bytes: GettingBuiltBehavior::onDelete.
// GettingBuiltBehavior's vtable 0x00CA46F4 (installed by the constructor at
// 0x001FE380) holds ILT 0x00044AC6 -> 0x001FE910 in slot 8.  Slot 8 is
// onDelete in the landed HordeContain (vtable 0x010AF2C8) and OpenContain
// tables, and slots 5, 6, 7 and 10 are the same shared Module defaults in both
// tables.  The body finds the producer by Object+0x78 (m_producerID in the
// layout witness), pokes its slot-0x14 interface and releases the looping
// audio handle at +0x24 (the constructor stores 1 there).
//
// Read the producer ID straight off m_object: an Object local or an inline
// ID accessor lets VC7.1 reuse EAX for the ID and hoist the GameLogic load
// above the push, where retail loads the ID into ECX.

typedef unsigned int UnsignedInt;

#include "../object.h"

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

extern GameLogic *TheBfmeGameLogic;

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
	virtual ~GettingBuiltBehavior();
	virtual void vslot04();
	virtual void vslot08();
	virtual void vslot0c();
	virtual void vslot10();
	virtual void vslot14();
	virtual void vslot18();
	virtual void vslot1c();
	virtual void onDelete();

private:
	char m_pad04[4];
	Object *m_object;
	char m_pad0c[0x18];
	UnsignedInt m_audioHandle;
};

void GettingBuiltBehavior::onDelete()
{
	if (BfmeY982 *target = (BfmeY982 *)TheBfmeGameLogic->findObjectByID(
		(int)m_object->m_producerID))
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
