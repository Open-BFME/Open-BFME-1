// ?create001B0E90@EffectFactory0040A260@@QAEPAUSnapshot0040A260@@PBVThingTemplate@@PAX@Z
// partial score=0.1632 date=2026-10-01
// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
// ?create001B0E90@EffectFactory0040A260@@QAEPAUSnapshot0040A260@@PBVThingTemplate@@PAX@Z
// The matched call in BuffTransfer0040A260 names this body at RVA 0x001B0E90.
#include "ascii_string.h"

typedef int Int;

class ThingTemplate;
struct Snapshot0040A260;

class EffectFactory0040A260
{
public:
	Snapshot0040A260 *create001B0E90(const ThingTemplate *thingTemplate, void *context);
};

class Rva001B0E90EntryObject
{
public:
	virtual void slot00() = 0;
	virtual void slot04() = 0;
	virtual void slot08() = 0;
	virtual void slot0C() = 0;
	virtual void slot10() = 0;
	virtual void slot14() = 0;
	virtual void slot18() = 0;
	virtual void slot1C() = 0;
	virtual void slot20() = 0;
	virtual void slot24() = 0;
	virtual void *slot28() = 0;
};

struct Rva001B0E90Record
{
	char m_prefix[8];
	Rva001B0E90EntryObject *m_object;
	char m_suffix[8];
};

struct Rva001B0E90Range
{
	Rva001B0E90Record *m_begin;
	Rva001B0E90Record *m_end;
	Rva001B0E90Record *begin() const { return m_begin; }
	int size() const { return (int)(m_end - m_begin); }
};

struct Rva001B0E90ThingTemplateView
{
	char m_prefix[0x20];
	AsciiString m_name;
	char m_padding[0x27C];
	Rva001B0E90Range m_records;
};

class BfmeAwakenLog
{
public:
	virtual void slot00() = 0;
	virtual void slot04() = 0;
	virtual void slot08() = 0;
	virtual void slot0C() = 0;
	virtual void slot10() = 0;
	virtual void slot14() = 0;
	virtual void slot18() = 0;
	virtual void slot1C() = 0;
	virtual void slot20() = 0;
	virtual void slot24() = 0;
	virtual void slot28() = 0;
	virtual void slot2C() = 0;
	virtual void slot30() = 0;
	virtual void slot34() = 0;
	virtual BfmeAwakenLog *slot38(const char *) = 0;
	virtual void slot3C() = 0;
	virtual void slot40() = 0;
	virtual void slot44() = 0;
	virtual void slot48() = 0;
	virtual void slot4C(Int) = 0;
};

class BfmeAwakenDebug
{
public:
	virtual void slot00() = 0;
	virtual void slot04() = 0;
	virtual void slot08() = 0;
	virtual void slot0C() = 0;
	virtual void slot10() = 0;
	virtual void slot14() = 0;
	virtual void slot18() = 0;
	virtual void slot1C() = 0;
	virtual void slot20() = 0;
	virtual void slot24() = 0;
	virtual void slot28() = 0;
	virtual void slot2C() = 0;
	virtual void slot30() = 0;
	virtual void slot34() = 0;
	virtual void slot38() = 0;
	virtual void slot3C() = 0;
	virtual void slot40() = 0;
	virtual void slot44() = 0;
	virtual void slot48() = 0;
	virtual void slot4C() = 0;
	virtual void slot50() = 0;
	virtual void slot54() = 0;
	virtual void slot58() = 0;
	virtual void slot5C() = 0;
	virtual void slot60() = 0;
	virtual void slot64() = 0;
	virtual void slot68() = 0;
	virtual BfmeAwakenLog *slot6C(Int, Int) = 0;
};

class Rva001B0E90TerrainVisual
{
public:
	virtual void slot00() = 0;
	virtual void slot04() = 0;
	virtual void slot08() = 0;
	virtual void slot0C() = 0;
	virtual void slot10() = 0;
	virtual void slot14() = 0;
	virtual void slot18() = 0;
	virtual void slot1C() = 0;
	virtual void slot20() = 0;
	virtual void slot24() = 0;
	virtual void slot28() = 0;
	virtual void slot2C() = 0;
	virtual void slot30() = 0;
	virtual void slot34() = 0;
	virtual void slot38() = 0;
	virtual void slot3C() = 0;
	virtual void slot40() = 0;
	virtual void slot44() = 0;
	virtual void slot48() = 0;
	virtual void slot4C() = 0;
	virtual void slot50() = 0;
	virtual void slot54() = 0;
	virtual void slot58() = 0;
	virtual void slot5C() = 0;
	virtual void slot60() = 0;
	virtual void slot64() = 0;
	virtual void slot68() = 0;
	virtual void slot6C() = 0;
	virtual void slot70() = 0;
	virtual void slot74() = 0;
	virtual void slot78() = 0;
	virtual void slot7C() = 0;
	virtual void slot80() = 0;
	virtual void slot84() = 0;
	virtual void slot88() = 0;
	virtual void slot8C() = 0;
	virtual Snapshot0040A260 *slot90(void *, void *) = 0;
};

extern void *g_Rva00F36E5C;
extern void _bfme_debugRecordCallsite(Int kind);
extern bool _bfme_debugReportingEnabled(void);
class TerrainVisual;
extern TerrainVisual *TheTerrainVisual;

Snapshot0040A260 *EffectFactory0040A260::create001B0E90(const ThingTemplate *thingTemplate, void *context)
{
	const Rva001B0E90ThingTemplateView *self = (const Rva001B0E90ThingTemplateView *)thingTemplate;
	if (self->m_records.size() == 0 || !self->m_records.begin()->m_object)
	{
		AsciiString message;
		message.format(AsciiString((const char *)0x0109C918),
			self->m_name.str());
		return 0;
	}

	void *result = self->m_records.begin()->m_object->slot28();
	if (result == 0)
	{
		if (_bfme_debugReportingEnabled())
		{
			_bfme_debugRecordCallsite(1);
			reinterpret_cast<BfmeAwakenDebug *>(g_Rva00F36E5C)->slot60();
			reinterpret_cast<BfmeAwakenDebug *>(g_Rva00F36E5C)->slot6C(0, 0)
				->slot38((const char *)0x0109C910)
				->slot38(self->m_name.str())
				->slot38((const char *)0x0109C8E8)
				->slot4C(2);
		}
		return 0;
	}
	return reinterpret_cast<Rva001B0E90TerrainVisual *>(TheTerrainVisual)->slot90(context, result);
}
