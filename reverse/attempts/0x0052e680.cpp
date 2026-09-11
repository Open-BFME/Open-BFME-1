// ?bfmeAddSavedIgnoreFromEntryE6B@@YGXPAVGameWindow@@@Z
// partial score=0.975 date=2026-09-11
#include "../../../../reference/shims/stringinline/StringInline.h"

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

BfmeUStrEBA __cdecl bfmeFormatEBA(int value);

class BfmeRecEBA
{
public:
	unsigned char m_bfmeHeadEBA[4];
	AsciiString m_bfmeNameEBA;
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
	virtual void addToSavedIgnoreListE6B(int id, AsciiString name) = 0;
	virtual void removeFromSavedIgnoreListE7B(int id);
};

extern GameSpyInfo *TheGameSpyInfo;

class GameSpyConfigInterface
{
public:
	virtual void bfmeSlot00E6B();
	virtual void bfmeSlot01E6B();
	virtual void bfmeSlot02E6B();
	virtual void bfmeSlot03E6B();
	virtual void bfmeSlot04E6B();
	virtual void bfmeSlot05E6B();
	virtual void bfmeSlot06E6B();
	virtual void bfmeSlot07E6B();
	virtual void bfmeSlot08E6B();
	virtual void bfmeSlot09E6B();
	virtual void bfmeSlot10E6B();
	virtual bool bfmeRejectE6B(int id);
};

extern GameSpyConfigInterface *TheGameSpyConfig;

void __stdcall bfmeRequestBuddyFromEntryEBA(GameWindow *entry)
{
	BfmeUStrEBA text;

	text.bfmeSetEBA(bfmeFormatEBA((int)entry));

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

// The original callback spelling is not exposed by any named caller.  Its
// GameSpyInfo receiver and slot are fixed by the matched family at 0052E4C0.
void __stdcall bfmeRemoveBuddyFromEntryE5B(GameWindow *entry)
{
	BfmeUStrEBA text;

	text.bfmeSetEBA(bfmeFormatEBA((int)entry));

	if (text.m_bfmeDataEBA != 0 && text.m_bfmeDataEBA->m_bfmeLenEBA != 0)
	{
		BfmeRecEBA *rec = bfmeLookupEBA(&text);

		if (rec != 0)
			TheGameSpyInfo->removeBuddyE5B(rec->m_bfmeIdEBA);
	}
}

// The 0x0052E680 callback additionally rejects the current room and records
// filtered by the GameSpy configuration before forwarding the copied room.
void __stdcall bfmeAddSavedIgnoreFromEntryE6B(GameWindow *entry)
{
	BfmeUStrEBA text;

	text.bfmeSetEBA(bfmeFormatEBA((int)entry));

	if (text.m_bfmeDataEBA != 0 && text.m_bfmeDataEBA->m_bfmeLenEBA != 0)
	{
		BfmeRecEBA *rec = bfmeLookupEBA(&text);

		if (rec != 0 && rec->m_bfmeIdEBA != TheGameSpyInfo->getLocalProfileIDEBA() &&
			(rec->m_bfmeFlagsEBA & 0x20) == 0 &&
			(TheGameSpyConfig == 0 || !TheGameSpyConfig->bfmeRejectE6B(rec->m_bfmeIdEBA)))
		{
			TheGameSpyInfo->addToSavedIgnoreListE6B(rec->m_bfmeIdEBA,
				rec->m_bfmeNameEBA);
		}
	}
}

// The 0x0052E7B0 callback is the same Unicode lookup path as E5B above,
// dispatching through the next same-signature GameSpyInfo selector at slot 74.
// Its original callback spelling is likewise not exposed by a named caller.
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
