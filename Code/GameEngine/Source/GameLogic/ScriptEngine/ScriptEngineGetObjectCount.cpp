// cl: /DNDEBUG /MD /EHsc

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
private:
	void *m_data;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Player.h
class Player
{
public:
	bool isPlayerActive() const;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/PlayerList.h
class PlayerList
{
public:
	Player *getNthPlayer(int index);
};

extern PlayerList *ThePlayerList;

struct ObjectTypeCountNode
{
	void *m_links[4];
	AsciiString m_key;
	int m_value;
};

class ObjectTypeCount
{
public:
	ObjectTypeCountNode *find(const AsciiString &key) const;

	ObjectTypeCountNode *m_header;
	int m_count;
	void *m_compare;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/ScriptEngine.h
class ScriptEngine
{
public:
	int getObjectCount(int playerIndex, const AsciiString &objectTypeName) const;

private:
	char m_unknown[0x170E0];
	ObjectTypeCount m_objectCounts[32];
};

int ScriptEngine::getObjectCount(int playerIndex,
	const AsciiString &objectTypeName) const
{
	if (!ThePlayerList->getNthPlayer(playerIndex)->isPlayerActive())
		return 0;

	const ObjectTypeCount &counts = m_objectCounts[playerIndex];
	ObjectTypeCountNode *found = counts.find(objectTypeName);
	if (found == counts.m_header)
		return 0;
	return found->m_value;
}
