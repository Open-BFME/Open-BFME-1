// cl: /GS

// EA FESL browser game reply handler at retail RVA 0x007F6890.
// The browser's vtable slot 21 looks up a game element, and the listener's
// slot 9 receives the game and lobby identifiers after the record is stored.

// Direct retail predicate at 0x007E88A0; receiver identity is opaque.
// See identity_evidence/0x007e88a0-predicate-owner-correction.md.
class Rva007E88A0
{
public:
	bool method();                                       // 0x007E88A0
};

class Rva007E8810Message
{
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

// 0x00802B30 is DEFINED in the ledger as
// ?bfmeFindZP@BfmeOwnerZP@@QAEXPAVBfmeKeyZP@@@Z (game/Libraries/.../
// BfmeConv1882.cpp), so the element the vtable hands back is spelled with the
// owner's real class and method name here. The record argument is passed
// through unchanged: only the pointee's cv-qualification differs from the
// ledger's BfmeKeyZP*, which is not part of the emitted code.
class BfmeKeyZP;

class BfmeOwnerZP
{
public:
	void bfmeFindZP(BfmeKeyZP *key);
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
	virtual BfmeOwnerZP *findGame(int lid);

	char m_head[0x18];
	Rva007F7980Listener *m_listener;

	void onGame(Rva007E8810Message *message);
};

void Rva007F7980Browser::onGame(Rva007E8810Message *message)
{
	Rva007FBEF0GameRecord record(message);
	int lid = record.m_lid;
	int gid = record.m_gid;
	if (((Rva007E88A0 *)message)->Rva007E88A0::method())
		return;
	BfmeOwnerZP *element = findGame(lid);
	if (element != 0)
		element->bfmeFindZP((BfmeKeyZP *)&record);
	m_listener->gameReady(lid, gid);
}
