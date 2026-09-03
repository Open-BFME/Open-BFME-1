// cl: /DNDEBUG /MD /EHsc

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	unsigned char m_pad[0x88];
	Object *m_nextObject;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/GameLogic.h
class GameLogic
{
public:
	Object *getFirstObject();
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
public:
	AsciiString &operator=(const AsciiString &other);
	void set(const char *text, int length);
private:
	char *m_data;
};

extern GameLogic *TheGameLogic;
extern const char g_Rva0107301CEmptyString[];

class BfmeObjectReferenceStore
{
public:
	void configure(int mode, const int &value, const Object *player,
		const AsciiString &name, int trailingValue);
	void updateObjectReference(Object *object, bool adding);
	void clearObjectEntries();

private:
	unsigned char m_pad[0x14];
	int m_mode;
	unsigned char m_pad2[4];
	AsciiString m_name;
	int m_value;
	unsigned short m_mask;
};

void BfmeObjectReferenceStore::clearObjectEntries()
{
	Object *object = TheGameLogic->getFirstObject();
	while (object != 0) {
		updateObjectReference(object, true);
		object = object->m_nextObject;
	}
	m_mode = 0;
	m_name.set(g_Rva0107301CEmptyString, 0);
	m_value = 0;
	m_mask = 0;
}

void BfmeObjectReferenceStore::configure(int mode, const int &value,
		const Object *player, const AsciiString &name, int trailingValue)
{
	clearObjectEntries();
	m_mode = mode;
	*(int *)(m_pad2) = value;
	m_name = name;
	m_value = trailingValue;
	m_mask = (unsigned short)(1 << *(const int *)((const unsigned char *)player + 0x24));

	Object *object = TheGameLogic->getFirstObject();
	while (object != 0) {
		updateObjectReference(object, false);
		object = object->m_nextObject;
	}
}
