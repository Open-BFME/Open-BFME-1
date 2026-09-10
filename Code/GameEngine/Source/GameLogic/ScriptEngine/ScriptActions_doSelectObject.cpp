// cl: /DNDEBUG /DWIN32 /MD /EHsc
// SELECT_OBJECT at retail RVA 0x002F0FD0.

typedef bool Bool;
typedef unsigned short PlayerMaskType;
typedef unsigned int ObjectID;

class AsciiString
{
};

class Parameter
{
public:
	unsigned char m_beforeInt[8];
	int m_int;
	float m_real;
	AsciiString m_string;
};

class Object;

class ScriptEngine
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
	virtual Object *getUnitNamed(Parameter *parameter) = 0;

	int resolvePlayerMask(void *parameter, int flags);
};

class Player
{
public:
	unsigned char m_beforeIndex[0x24];
	int m_playerIndex;
};

class PlayerList
{
public:
	Player *getEachPlayerFromMask(PlayerMaskType &mask);

	unsigned char m_beforeLocalPlayer[0x0c];
	Player *m_localPlayer;
};

class Drawable
{
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

	unsigned char m_beforeID[0x70];
	ObjectID m_id;
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

class GameLogic
{
public:
	void selectObject(Object *object, Bool createNewSelection,
		PlayerMaskType playerMask, Bool affectClient);
};

class ScriptActions
{
protected:
	void doSelectObject(Parameter *player, Parameter *object);
};

extern ScriptEngine *TheScriptEngine;
extern PlayerList *ThePlayerList;
extern MessageStream *TheMessageStream;
extern InGameUI *TheInGameUI;
extern GameLogic *TheGameLogic;

// ?doSelectObject@ScriptActions@@IAEXPAVParameter@@0@Z
void ScriptActions::doSelectObject(Parameter *player, Parameter *object)
{
	Object *selectedObject = TheScriptEngine->getUnitNamed(object);
	if (selectedObject)
	{
		PlayerMaskType playerMask = (PlayerMaskType)
			TheScriptEngine->resolvePlayerMask(&player->m_string, 0);
		if (playerMask)
		{
			do
			{
				Player *selectedPlayer =
					ThePlayerList->getEachPlayerFromMask(playerMask);
				if (selectedPlayer)
				{
					if (selectedPlayer == ThePlayerList->m_localPlayer)
					{
						TheInGameUI->deselectAllDrawables();
						GameMessage *message =
							TheMessageStream->appendMessage(1001);
						message->appendBooleanArgument(true);
						message->appendObjectIDArgument(selectedObject->m_id);
						TheInGameUI->selectDrawable(
							selectedObject->getDrawable());
					}

					TheGameLogic->selectObject(selectedObject, true,
						(PlayerMaskType)(1 << selectedPlayer->m_playerIndex),
						false);
				}
			} while (playerMask);
		}
	}
}
