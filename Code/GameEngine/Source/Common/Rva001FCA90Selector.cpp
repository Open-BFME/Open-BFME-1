// cl: /DNDEBUG /DWIN32 /MD /EHsc

// Retail 0x001FCA90, 151 bytes. Anonymous 1-site body (only caller is the
// generated d_004462d0 dump); no vtable install, string, or built emitter
// names an owner, so the class stays address-derived per docs/naming_evidence.md.
//
// Twin: Code/GameEngine/Source/GameLogic/ScriptEngine/ScriptActions_doSelectObject.cpp
// (SELECT_OBJECT, retail 0x002F0FD0) proves the InGameUI/MessageStream/Object
// virtual-slot layout used here -- same deselectAllDrawables()/appendMessage()/
// selectDrawable(getDrawable()) shape, just reached from a stored ObjectID
// (this+0x24) instead of a script parameter, and gated on the object's
// *controlling* player rather than a resolved player mask.

typedef bool Bool;
typedef unsigned int ObjectID;

class Drawable;

class Player
{
public:
	unsigned char m_beforeIndex[0x24];
};

class PlayerList
{
public:
	unsigned char m_beforeLocalPlayer[0x0c];
	Player *m_localPlayer;
};

class Object
{
public:
	virtual void slot00() = 0;
	virtual void slot01() = 0;
	virtual void slot02() = 0;
	virtual void slot03() = 0;
	virtual void slot04() = 0;
	virtual void slot05() = 0;
	virtual void slot06() = 0;
	virtual void slot07() = 0;
	virtual void slot08() = 0;
	virtual void slot09() = 0;
	virtual Drawable *getDrawable() = 0;

	Player *getControllingPlayer() const;
};

class GameLogic
{
public:
	Object *findObjectByID(int id);
};

class GameMessage
{
public:
	void appendBooleanArgument(Bool value);
	void appendObjectIDArgument(ObjectID id);
};

class MessageStream
{
public:
	virtual void slot00() = 0;
	virtual void slot01() = 0;
	virtual void slot02() = 0;
	virtual void slot03() = 0;
	virtual void slot04() = 0;
	virtual void slot05() = 0;
	virtual void slot06() = 0;
	virtual void slot07() = 0;
	virtual void slot08() = 0;
	virtual void slot09() = 0;
	virtual void slot10() = 0;
	virtual void slot11() = 0;
	virtual void slot12() = 0;
	virtual GameMessage *appendMessage(int type) = 0;
};

class InGameUI
{
public:
	virtual void slot00() = 0;
	virtual void slot01() = 0;
	virtual void slot02() = 0;
	virtual void slot03() = 0;
	virtual void slot04() = 0;
	virtual void slot05() = 0;
	virtual void slot06() = 0;
	virtual void slot07() = 0;
	virtual void slot08() = 0;
	virtual void slot09() = 0;
	virtual void slot10() = 0;
	virtual void slot11() = 0;
	virtual void slot12() = 0;
	virtual void slot13() = 0;
	virtual void slot14() = 0;
	virtual void slot15() = 0;
	virtual void slot16() = 0;
	virtual void slot17() = 0;
	virtual void slot18() = 0;
	virtual void slot19() = 0;
	virtual void slot20() = 0;
	virtual void slot21() = 0;
	virtual void slot22() = 0;
	virtual void slot23() = 0;
	virtual void slot24() = 0;
	virtual void slot25() = 0;
	virtual void slot26() = 0;
	virtual void slot27() = 0;
	virtual void slot28() = 0;
	virtual void slot29() = 0;
	virtual void slot30() = 0;
	virtual void slot31() = 0;
	virtual void slot32() = 0;
	virtual void slot33() = 0;
	virtual void slot34() = 0;
	virtual void slot35() = 0;
	virtual void slot36() = 0;
	virtual void slot37() = 0;
	virtual void slot38() = 0;
	virtual void slot39() = 0;
	virtual void slot40() = 0;
	virtual void slot41() = 0;
	virtual void slot42() = 0;
	virtual void slot43() = 0;
	virtual void slot44() = 0;
	virtual void slot45() = 0;
	virtual void slot46() = 0;
	virtual void slot47() = 0;
	virtual void slot48() = 0;
	virtual void slot49() = 0;
	virtual void slot50() = 0;
	virtual void slot51() = 0;
	virtual void slot52() = 0;
	virtual void slot53() = 0;
	virtual void slot54() = 0;
	virtual void slot55() = 0;
	virtual void selectDrawable(Drawable *drawable) = 0;
	virtual void slot57() = 0;
	virtual void deselectAllDrawables() = 0;
};

extern PlayerList *ThePlayerList;
extern InGameUI *TheInGameUI;
extern MessageStream *TheMessageStream;
extern GameLogic *TheGameLogic;

// Address-derived: no owning class or field name is provable, only the
// stored ObjectID at this+0x24 and the behavior below.
class Rva001FCA90Owner
{
public:
	Bool invoke();

private:
	unsigned char m_pad[0x24];
	ObjectID m_targetId;
};

Bool Rva001FCA90Owner::invoke()
{
	ObjectID id = m_targetId;
	if (id == 0)
		return false;

	Object *target = TheGameLogic->findObjectByID(id);
	if (!target)
		return false;

	Player *controller = target->getControllingPlayer();
	Player *local = ThePlayerList->m_localPlayer;
	if (!controller || !local || controller != local)
		return false;

	TheInGameUI->deselectAllDrawables();

	GameMessage *message = TheMessageStream->appendMessage(0x3ea);
	message->appendBooleanArgument(true);
	message->appendObjectIDArgument(m_targetId);

	Drawable *drawable = target->getDrawable();
	if (drawable)
		TheInGameUI->selectDrawable(drawable);

	return true;
}
