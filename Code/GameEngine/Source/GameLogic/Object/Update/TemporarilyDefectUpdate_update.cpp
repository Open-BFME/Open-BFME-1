// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: TemporarilyDefectUpdate::update, retail 0x002B0D40.
// The update interface vtable at 0x010C4CF8 routes its first slot through
// ILT 0x0002E48D. The object completion callback uses Object vtable slot 18,
// which is the matched body at 0x001CBC20.

typedef unsigned int UnsignedInt;

enum UpdateSleepTime
{
	UPDATE_SLEEP_10 = 10,
	UPDATE_SLEEP_FOREVER = 0x3FFFFFFF
};

class Drawable;
class Player;
class GameMessage;

class Object
{
public:
	virtual void slot00() = 0;
	virtual void slot04() = 0;
	virtual void slot08() = 0;
	virtual void slot0C() = 0;
	virtual void slot10() = 0;
	virtual void slot14() = 0;
	virtual void slot18() = 0;
	virtual void slot1C() = 0;
	virtual void slot20() = 0;
	virtual void slot24() = 0;
	virtual Drawable *getDrawable() const = 0;
	virtual void slot2C() = 0;
	virtual void slot30() = 0;
	virtual void slot34() = 0;
	virtual void slot38() = 0;
	virtual void slot3C() = 0;
	virtual void slot40() = 0;
	virtual void slot44() = 0;
	virtual void rva001CBC20() = 0;

	Player *getControllingPlayer() const;
	UnsignedInt getID() const
	{
		return *(const UnsignedInt *)((const char *)this + 0x74);
	}

	unsigned char m_pad004[0x210];
	UnsignedInt m_completionState;
};

class GameLogic
{
public:
	Object *findObjectByID(int id);

	unsigned char m_pad000[0x3C];
	UnsignedInt m_frame;
};

class PlayerList
{
public:
	unsigned char m_pad000[0x0C];
	Player *m_localPlayer;
};

class GameMessage
{
public:
	enum Type
	{
		MSG_REMOVE_FROM_SELECTED_GROUP = 0x3EC
	};

	void appendObjectIDArgument(UnsignedInt id);
};

class MessageStream
{
public:
	virtual void slot00() = 0;
	virtual void slot04() = 0;
	virtual void slot08() = 0;
	virtual void slot0C() = 0;
	virtual void slot10() = 0;
	virtual void slot14() = 0;
	virtual void slot18() = 0;
	virtual void slot1C() = 0;
	virtual void slot20() = 0;
	virtual void slot24() = 0;
	virtual void slot28() = 0;
	virtual void slot2C() = 0;
	virtual void slot30() = 0;
	virtual GameMessage *appendMessage(GameMessage::Type type) = 0;
};

class InGameUI
{
public:
	virtual void slot00() = 0;
	virtual void slot04() = 0;
	virtual void slot08() = 0;
	virtual void slot0C() = 0;
	virtual void slot10() = 0;
	virtual void slot14() = 0;
	virtual void slot18() = 0;
	virtual void slot1C() = 0;
	virtual void slot20() = 0;
	virtual void slot24() = 0;
	virtual void slot28() = 0;
	virtual void slot2C() = 0;
	virtual void slot30() = 0;
	virtual void slot34() = 0;
	virtual void slot38() = 0;
	virtual void slot3C() = 0;
	virtual void slot40() = 0;
	virtual void slot44() = 0;
	virtual void slot48() = 0;
	virtual void slot4C() = 0;
	virtual void slot50() = 0;
	virtual void slot54() = 0;
	virtual void slot58() = 0;
	virtual void slot5C() = 0;
	virtual void slot60() = 0;
	virtual void slot64() = 0;
	virtual void slot68() = 0;
	virtual void slot6C() = 0;
	virtual void slot70() = 0;
	virtual void slot74() = 0;
	virtual void slot78() = 0;
	virtual void slot7C() = 0;
	virtual void slot80() = 0;
	virtual void slot84() = 0;
	virtual void slot88() = 0;
	virtual void slot8C() = 0;
	virtual void slot90() = 0;
	virtual void slot94() = 0;
	virtual void slot98() = 0;
	virtual void slot9C() = 0;
	virtual void slotA0() = 0;
	virtual void slotA4() = 0;
	virtual void slotA8() = 0;
	virtual void slotAC() = 0;
	virtual void slotB0() = 0;
	virtual void slotB4() = 0;
	virtual void slotB8() = 0;
	virtual void slotBC() = 0;
	virtual void slotC0() = 0;
	virtual void slotC4() = 0;
	virtual void slotC8() = 0;
	virtual void slotCC() = 0;
	virtual void slotD0() = 0;
	virtual void slotD4() = 0;
	virtual void slotD8() = 0;
	virtual void slotDC() = 0;
	virtual void slotE0() = 0;
	virtual void deselectDrawable(Drawable *draw) = 0;
};

extern GameLogic *TheGameLogic;
extern PlayerList *ThePlayerList;
extern MessageStream *TheMessageStream;
extern InGameUI *TheInGameUI;

#pragma comment(linker, "/alternatename:?getControllingPlayer@Object@@QBEPAVPlayer@@XZ=?j_00020824@@YAXXZ")
#pragma comment(linker, "/alternatename:?findObjectByID@GameLogic@@QAEPAVObject@@H@Z=?j_0001f253@@YAXXZ")
#pragma comment(linker, "/alternatename:?appendObjectIDArgument@GameMessage@@QAEXI@Z=?j_0002bcec@@YAXXZ")

class TemporarilyDefectUpdate
{
public:
	virtual UpdateSleepTime update();

	private:
	unsigned char m_pad004[0x0C];
	UnsignedInt m_endFrame;
	UnsignedInt m_startFrame;
	UnsignedInt m_defectorID;
	unsigned char m_fxFired;
};

// ?update@TemporarilyDefectUpdate@@UAE?AW4UpdateSleepTime@@XZ
UpdateSleepTime TemporarilyDefectUpdate::update()
{
	Object *object = *(Object **)((char *)this - 8);
	Drawable *drawable = object->getDrawable();
	UnsignedInt zero = 0;

	if (m_fxFired != 0)
	{
		m_startFrame = zero;
		m_endFrame = zero;
		m_fxFired = (unsigned char)zero;
		if (drawable != 0)
		{
			Player *localPlayer = ThePlayerList->m_localPlayer;
			if (object->getControllingPlayer() == localPlayer)
			{
				GameMessage *message = TheMessageStream->appendMessage(
					GameMessage::MSG_REMOVE_FROM_SELECTED_GROUP);
				message->appendObjectIDArgument(object->getID());
				TheInGameUI->deselectDrawable(drawable);
			}
		}
		return UPDATE_SLEEP_FOREVER;
	}

	GameLogic *logic = TheGameLogic;
	if (logic->m_frame < m_endFrame)
	{
		if (m_defectorID != zero)
		{
			Object *defector = logic->findObjectByID(m_defectorID);
			if (defector == 0 || (*(const unsigned char *)((const char *)defector + 0x344) & 1) != 0)
				m_defectorID = zero;
			else
				return UPDATE_SLEEP_10;
		}
		else
			return UPDATE_SLEEP_10;
	}

	m_startFrame = zero;
	m_endFrame = zero;
	m_fxFired = (unsigned char)zero;
	if (drawable != 0)
	{
		Player *localPlayer = ThePlayerList->m_localPlayer;
		if (object->getControllingPlayer() == localPlayer)
		{
			GameMessage *message = TheMessageStream->appendMessage(
				GameMessage::MSG_REMOVE_FROM_SELECTED_GROUP);
			message->appendObjectIDArgument(object->getID());
			TheInGameUI->deselectDrawable(drawable);
		}
	}

	if (object->m_completionState == zero)
		object->rva001CBC20();
	return UPDATE_SLEEP_FOREVER;
}
