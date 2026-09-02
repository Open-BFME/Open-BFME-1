// cl: /DNDEBUG /MD /EHsc

class AsciiString
{
private:
	void *m_data;
};

class Player
{
public:
	bool isPlayerActive() const;
};

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
