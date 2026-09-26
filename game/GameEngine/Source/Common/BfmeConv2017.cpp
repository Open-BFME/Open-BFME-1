class GameWindow;

struct BfmeUHdrEBA
{
	unsigned short m_bfmeRefEBA;
	unsigned short m_bfmeCapEBA;
	unsigned short m_bfmeLenEBA;
	unsigned short m_bfmeFlagsEBA;
};

class BfmeUStrEBA
{
public:
	BfmeUStrEBA() { m_bfmeDataEBA = 0; }
	~BfmeUStrEBA();

	void bfmeSetEBA(const BfmeUStrEBA &other);

	BfmeUHdrEBA *m_bfmeDataEBA;
};

// This TU-local spelling is pinned to GadgetTextEntryGetText's ILT. Keeping
// the one-word parameter here preserves the already-proven call relocation;
// each public callback below exposes the real GameWindow* ABI.
BfmeUStrEBA __cdecl bfmeFormatEBA(int value);

class BfmeRecEBA
{
public:
	unsigned char m_bfmeHeadEBA[4];
	void *m_bfmeNameEBA;
	unsigned char m_bfmePadEBA[0x0c];
	int m_bfmeIdEBA;
	unsigned int m_bfmeFlagsEBA;
};

BfmeRecEBA *__cdecl bfmeLookupEBA(BfmeUStrEBA *text);

class GameSpyInfo
{
public:
	virtual void bfmeSlot00EBA();
	virtual void bfmeSlot01EBA();
	virtual void bfmeSlot02EBA();
	virtual void bfmeSlot03EBA();
	virtual void bfmeSlot04EBA();
	virtual void bfmeSlot05EBA();
	virtual void bfmeSlot06EBA();
	virtual void bfmeSlot07EBA();
	virtual void bfmeSlot08EBA();
	virtual void bfmeSlot09EBA();
	virtual void bfmeSlot10EBA();
	virtual void bfmeSlot11EBA();
	virtual void bfmeSlot12EBA();
	virtual void bfmeSlot13EBA();
	virtual void bfmeSlot14EBA();
	virtual void bfmeSlot15EBA();
	virtual void bfmeSlot16EBA();
	virtual void bfmeSlot17EBA();
	virtual void bfmeSlot18EBA();
	virtual void bfmeSlot19EBA();
	virtual void bfmeSlot20EBA();
	virtual void bfmeSlot21EBA();
	virtual void bfmeSlot22EBA();
	virtual void bfmeSlot23EBA();
	virtual void bfmeSlot24EBA();
	virtual void bfmeSlot25EBA();
	virtual void bfmeSlot26EBA();
	virtual void bfmeSlot27EBA();
	virtual int getLocalProfileIDEBA();
	virtual void bfmeSlot29EBA();
	virtual void bfmeSlot30EBA();
	virtual void bfmeSlot31EBA();
	virtual void bfmeSlot32EBA();
	virtual void bfmeSlot33EBA();
	virtual void bfmeSlot34EBA();
	virtual void bfmeSlot35EBA();
	virtual void bfmeSlot36EBA();
	virtual void bfmeSlot37EBA();
	virtual void bfmeSlot38EBA();
	virtual void bfmeSlot39EBA();
	virtual void bfmeSlot40EBA();
	virtual void bfmeSlot41EBA();
	virtual void bfmeSlot42EBA();
	virtual void bfmeSlot43EBA();
	virtual void bfmeSlot44EBA();
	virtual void bfmeSlot45EBA();
	virtual void bfmeSlot46EBA();
	virtual void bfmeSlot47EBA();
	virtual void bfmeSlot48EBA();
	virtual void bfmeSlot49EBA();
	virtual void bfmeSlot50EBA();
	virtual void bfmeSlot51EBA();
	virtual void bfmeSlot52EBA();
	virtual void bfmeSlot53EBA();
	virtual void bfmeSlot54EBA();
	virtual void bfmeSlot55EBA();
	virtual void bfmeSlot56EBA();
	virtual void bfmeSlot57EBA();
	virtual void bfmeSlot58EBA();
	virtual void bfmeSlot59EBA();
	virtual void bfmeSlot60EBA();
	virtual void bfmeSlot61EBA();
	virtual void bfmeSlot62EBA();
	virtual void bfmeSlot63EBA();
	virtual void bfmeSlot64EBA();
	virtual void bfmeSlot65EBA();
	virtual void bfmeSlot66EBA();
	virtual void bfmeSlot67EBA();
	virtual void bfmeSlot68EBA();
	virtual void bfmeSlot69EBA();
	virtual void bfmeSlot70EBA();
	virtual void requestBuddyAddEBA(int id);
	virtual void removeBuddyE5B(int id);
	virtual void bfmeSlot73E6B();
	virtual void removeFromSavedIgnoreListE7B(int id);
};

extern GameSpyInfo *TheGameSpyInfo;

// Read a player name from the entry, resolve its PlayerInfo record, and issue
// a buddy request unless it names the local profile (slots 28 and 71). The
// historical neutral callback spelling keeps its one-word argument opaque;
// GadgetTextEntryGetText proves that word carries a GameWindow pointer.
void __stdcall bfmeSelectByNameEBA(int entryHandle)
{
	BfmeUStrEBA text;

	text.bfmeSetEBA(bfmeFormatEBA(entryHandle));

	if (text.m_bfmeDataEBA != 0 && text.m_bfmeDataEBA->m_bfmeLenEBA != 0)
	{
		BfmeRecEBA *rec = bfmeLookupEBA(&text);

		if (rec != 0)
		{
			int id = rec->m_bfmeIdEBA;

			if (id != TheGameSpyInfo->getLocalProfileIDEBA())
				TheGameSpyInfo->requestBuddyAddEBA(id);
		}
	}
}

// The original callback spelling is not exposed by any named caller. The
// GameSpyInfo vtable fixes slot 72 as removeBuddy.
void __stdcall bfmeSelectByNameE5B(int entryHandle)
{
	BfmeUStrEBA text;

	text.bfmeSetEBA(bfmeFormatEBA(entryHandle));

	if (text.m_bfmeDataEBA != 0 && text.m_bfmeDataEBA->m_bfmeLenEBA != 0)
	{
		BfmeRecEBA *rec = bfmeLookupEBA(&text);

		if (rec != 0)
			TheGameSpyInfo->removeBuddyE5B(rec->m_bfmeIdEBA);
	}
}

// The 0x0052E7B0 callback is the same Unicode lookup path as E5B above,
// dispatching to GameSpyInfo::removeFromSavedIgnoreList at slot 74. Its
// original callback spelling is likewise not exposed by a named caller.
void __stdcall bfmeRemoveSavedIgnoreFromEntryE7B(GameWindow *entry)
{
	BfmeUStrEBA text;

	text.bfmeSetEBA(bfmeFormatEBA((int)entry));

	if (text.m_bfmeDataEBA != 0 && text.m_bfmeDataEBA->m_bfmeLenEBA != 0)
	{
		BfmeRecEBA *rec = bfmeLookupEBA(&text);

		if (rec != 0)
			TheGameSpyInfo->removeFromSavedIgnoreListE7B(rec->m_bfmeIdEBA);
	}
}
