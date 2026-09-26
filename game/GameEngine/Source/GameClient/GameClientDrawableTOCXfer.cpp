// ?xferDrawableTOC@GameClient@@AAEXPAVXfer@@@Z
// partial score=0.95 date=2026-09-22
// cl: /O2 /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Igame/Libraries/Source/WWVegas/WWLib /Igame/GameEngine/Source/Common/System
// stlport
// GameClient::xferDrawableTOC at retail 0x00431DC0, the Zero Hour twin in
// GameClient.cpp. Its caller 0x00432010 is GameClient's xfer. The TOC list
// at this+0xF0 is the one GameClient::findTOCEntryByName (0x00430B80) walks,
// and 0x00431C60 is GameClient::addTOCEntry: it builds a {name, id} entry and
// push_backs a 16-byte node onto this+0xF0 (ret 8).

#include <list>
#include "ascii_string.h"
#include "xfer.h"

typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;

class Overridable
{
public:
	const Overridable *getFinalOverride() const;

	void *m_vtable;
	Overridable *m_nextOverride;
};

class ThingTemplate : public Overridable
{
public:
	const AsciiString &getName() const
	{
		return *(const AsciiString *)((const char *)this + 0x20);
	}
};

class Drawable
{
public:
	void *m_vtable;
	ThingTemplate *m_template;
	char m_pad08[0xF4];
	void *m_object;
	char m_pad100[4];
	Drawable *m_nextDrawable;
	char m_pad108[8];
	unsigned char m_status[4];

	// Thing's OVERRIDE<ThingTemplate> read: null stays null, otherwise the
	// final override of the template.
	const ThingTemplate *getTemplate() const
	{
		if (m_template == 0)
			return 0;
		if (m_template->m_nextOverride != 0)
			return (const ThingTemplate *)m_template->m_nextOverride->getFinalOverride();
		return m_template;
	}
	void *getObject() const { return m_object; }
	bool testDrawableStatus(unsigned int status) const { return (m_status[0] & status) != 0; }
	Drawable *getNextDrawable() const { return m_nextDrawable; }
};

class GameClient
{
public:
	struct DrawableTOCEntry
	{
		AsciiString name;
		UnsignedShort id;
	};
	typedef std::list<DrawableTOCEntry> DrawableTOCList;
	typedef DrawableTOCList::iterator DrawableTOCListIterator;

	virtual void slot0() = 0;
	virtual void slot1() = 0;
	virtual void slot2() = 0;
	virtual void slot3() = 0;
	virtual void slot4() = 0;
	virtual void slot5() = 0;
	virtual void slot6() = 0;
	virtual void slot7() = 0;
	virtual void slot8() = 0;
	virtual void slot9() = 0;
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
	virtual Drawable *getDrawableList() = 0;

private:
	char m_pad04[0xEC];
	DrawableTOCList m_drawableTOC;

	void addTOCEntry(AsciiString name, UnsignedShort id);
	DrawableTOCEntry *findTOCEntryByName(AsciiString name);
	void xferDrawableTOC(Xfer *xfer);
};

static bool shouldSaveDrawable(const Drawable *draw)
{
	if (draw->testDrawableStatus(0x10) && draw->getObject() == 0)
		return false;
	return true;
}

void GameClient::xferDrawableTOC(Xfer *xfer)
{
	{
		Xfer::Version version;
		version.data[0] = 1;
		version.data[1] = 1;
		*xfer == version;
	}

	m_drawableTOC.clear();

	UnsignedInt tocCount = 0;
	if (xfer->IsStoring())
	{
		AsciiString templateName;

		for (Drawable *draw = getDrawableList(); draw; draw = draw->getNextDrawable())
		{
			if (!shouldSaveDrawable(draw))
				continue;

			templateName = draw->getTemplate()->getName();

			if (findTOCEntryByName(templateName) != 0)
				continue;

			addTOCEntry(draw->getTemplate()->getName(), ++tocCount);
		}

		*xfer == tocCount;

		DrawableTOCListIterator it;
		DrawableTOCEntry *tocEntry;
		for (it = m_drawableTOC.begin(); it != m_drawableTOC.end(); ++it)
		{
			tocEntry = &(*it);
			*xfer == tocEntry->name;
			*xfer == tocEntry->id;
		}
	}
	else
	{
		AsciiString templateName;
		UnsignedShort id;
		*xfer == tocCount;

		for (UnsignedInt i = 0; i < tocCount; ++i)
		{
			*xfer == templateName;
			*xfer == id;
			addTOCEntry(templateName, id);
		}
	}
}
