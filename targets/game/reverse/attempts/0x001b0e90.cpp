// ?create001B0E90@EffectFactory0040A260@@QAEPAUSnapshot0040A260@@PBVThingTemplate@@PAX@Z
// partial score=0.704 date=2026-09-28
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

struct Rva001B0E90StringData
{
	int m_refCount;
	unsigned short m_length;
	unsigned short m_capacity;
	char m_text[1];
};

struct Rva001B0E90StringStorage
{
	Rva001B0E90StringData *m_data;
};

inline const char *Rva001B0E90StringText(const AsciiString &string)
{
	const Rva001B0E90StringStorage *storage = (const Rva001B0E90StringStorage *)&string;
	return storage->m_data ? storage->m_data->m_text : (const char *)0x0107388B;
}

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
	virtual Snapshot0040A260 *slot90(void *, void *) = 0;
};

extern BfmeAwakenDebug *TheBfmeAwakenDebug;
extern void _bfme_debugRecordCallsite(Int kind);
extern bool _bfme_debugReportingEnabled(void);
extern "C" Rva001B0E90TerrainVisual *g_bfmeTerrainVisual;

Snapshot0040A260 *EffectFactory0040A260::create001B0E90(const ThingTemplate *thingTemplate, void *context)
{
	const Rva001B0E90ThingTemplateView *self = (const Rva001B0E90ThingTemplateView *)thingTemplate;
	if (self->m_records.size() == 0 || !self->m_records.begin()->m_object)
	{
		AsciiString message;
		message.format(AsciiString((const char *)0x0109C918),
			(int)((char *)self->m_records.m_end - (char *)self->m_records.m_begin),
			Rva001B0E90StringText(self->m_name));
		return 0;
	}

	void *result = self->m_records.begin()->m_object->slot28();
	if (result == 0)
	{
		if (_bfme_debugReportingEnabled())
		{
			_bfme_debugRecordCallsite(1);
			TheBfmeAwakenDebug->slot60();
			TheBfmeAwakenDebug->slot6C(0, 0)
				->slot38((const char *)0x0109C910)
				->slot38(Rva001B0E90StringText(self->m_name))
				->slot38((const char *)0x0109C8E8)
				->slot4C(2);
		}
		return 0;
	}
	return g_bfmeTerrainVisual->slot90(context, result);
}
