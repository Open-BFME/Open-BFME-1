// cl: /GS

// EA FESL browser player reply handler at retail RVA 0x007F6900.
//
// The dispatch thunk at 0x007F6FF0 passes (message, browser) to this
// __thiscall body.  The player record is the existing 0x98-byte
// Rva007F5010Player layout.  Its first two fields are opaque interned-key
// pointers (the base constructor stores BfmeThingRF::bfmeGoRF results), not
// integers; keeping them opaque also describes the BfmeThingAEA key ABI.

class Rva007E8810Message
{
public:
	bool hasError();

	char m_head[0x28];
	void *m_transaction;
};

class Rva007FBC30GameKey
{
public:
	Rva007FBC30GameKey(Rva007E8810Message *message);

	void *m_lid;
	void *m_gid;
};

class Rva007F5010Player : public Rva007FBC30GameKey
{
public:
	Rva007F5010Player(Rva007E8810Message *message);

	Rva007E8810Message *m_message;
	void *m_pid;
	char m_name[0x80];
	char m_uid[8];
};

struct BfmeKeyAEA
{
	unsigned char m_head[4];
	void *m_id;
};

class BfmeThingAEA
{
public:
	bool bfmeFindAEA(BfmeKeyAEA *key, void *extra);
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
	virtual void slot06(void *lid, void *gid);
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual void slot10(void *lid, void *gid, void *pid);
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
	virtual BfmeThingAEA *findByLid(void *lid);

	char m_head[0x18];
	Rva007F7980Listener *m_listener;

	void onPlayer(Rva007E8810Message *message);
};

void Rva007F7980Browser::onPlayer(Rva007E8810Message *message)
{
	Rva007F5010Player player(message);
	bool found = false;
	void *lid = player.m_lid;
	void *gid = player.m_gid;
	void *pid = player.m_pid;

	if (message->hasError())
		return;

	BfmeThingAEA *entry = findByLid(lid);
	if (entry != 0)
	{
		void *transaction = message->m_transaction;
		found = entry->bfmeFindAEA((BfmeKeyAEA *)&player, transaction);
	}
	m_listener->slot10(lid, gid, pid);
	if (found)
		m_listener->slot06(lid, gid);
}
