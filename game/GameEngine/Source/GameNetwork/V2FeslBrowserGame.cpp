// cl: /GS

// EA FESL browser game reply handler at retail RVA 0x007F6890.
// The browser's vtable slot 21 looks up a game element, and the listener's
// slot 9 receives the game and lobby identifiers after the record is stored.

class Rva007E8810Message
{
public:
	bool hasError();
};

class Rva007FBEF0GameRecord
{
public:
	Rva007FBEF0GameRecord(Rva007E8810Message *message);

	int m_lid;
	int m_gid;
	Rva007E8810Message *m_message;
	char m_ugid[0x25];
};

class Rva00802B30Element
{
public:
	void store(const Rva007FBEF0GameRecord *record);
};

class Rva007F7980Listener
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
	virtual void gameReady(int lid, int gid);
};

class Rva007F7980Browser
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
	virtual void slot19();
	virtual void slot20();
	virtual Rva00802B30Element *findGame(int lid);

	char m_head[0x18];
	Rva007F7980Listener *m_listener;

	void onGame(Rva007E8810Message *message);
};

void Rva007F7980Browser::onGame(Rva007E8810Message *message)
{
	Rva007FBEF0GameRecord record(message);
	int lid = record.m_lid;
	int gid = record.m_gid;
	if (message->hasError())
		return;
	Rva00802B30Element *element = findGame(lid);
	if (element != 0)
		element->store(&record);
	m_listener->gameReady(lid, gid);
}
