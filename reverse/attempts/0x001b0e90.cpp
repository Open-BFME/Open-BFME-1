// ?d_001b0e90@@YAXXZ
// partial score=0.22 date=2026-09-22
// cl: /DNDEBUG /MD /EHsc
// Address-qualified reconstruction of retail 0x001B0E90.

typedef int Int;

class BFMERetailAsciiString
{
public:
	BFMERetailAsciiString() : m_data(0) {}
	BFMERetailAsciiString(const char *text);
	~BFMERetailAsciiString() { releaseBuffer(); }
	void __cdecl format(BFMERetailAsciiString format, ...);
	void releaseBuffer();
	const char *str() const
	{
		return m_data ? (const char *)m_data + 8 : (const char *)0x0107388B;
	}

	void *m_data;
};

class Rva001B0E90EntryObject
{
public:
	virtual void slot00() = 0;
	virtual void slot01() = 0;
	virtual void slot02() = 0;
	virtual void slot03() = 0;
	virtual void slot04() = 0;
	virtual void slot05() = 0;
	virtual void slot06() = 0;
	virtual void slot07() = 0;
	virtual void slot08() = 0;
	virtual void slot09() = 0;
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
	int size() const { return m_end - m_begin; }
};

class Rva001B0E90Owner
{
public:
	char m_prefix[0x20];
	BFMERetailAsciiString m_name;
	char m_padding[0x27C];
	Rva001B0E90Range m_records;
};

class BfmeAwakenLog
{
public:
	virtual BfmeAwakenLog *slot00() = 0;
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
	virtual Int slot90(void *, void *) = 0;
};

extern BfmeAwakenDebug *TheBfmeAwakenDebug;
extern void _bfme_debugRecordCallsite(Int kind);
extern bool _bfme_debugReportingEnabled(void);
extern "C" Rva001B0E90TerrainVisual *g_bfmeTerrainVisual;

Int __stdcall Rva001B0E90Dispatch(Rva001B0E90Owner *self, void *context)
{
	if (self->m_records.size() == 0)
		goto warning;
	if (self->m_records.begin()->m_object != 0)
		goto success;

warning:
	{
		BFMERetailAsciiString message;
		message.format(BFMERetailAsciiString((const char *)0x0109C918),
			(int)((char *)self->m_records.m_end -
				(char *)self->m_records.m_begin), self->m_name.str());
	}
	return 0;

success:
	{
		void *result = self->m_records.begin()->m_object->slot28();
		if (result == 0)
		{
			if (_bfme_debugReportingEnabled())
			{
				_bfme_debugRecordCallsite(1);
				TheBfmeAwakenDebug->slot60();
				BfmeAwakenLog *report = TheBfmeAwakenDebug->slot6C(0, 0);
				report = report->slot38((const char *)0x0109C910);
				report = report->slot38(self->m_name.str());
				report = report->slot38((const char *)0x0109C8E8);
				report->slot4C(2);
			}
			return 0;
		}
		return g_bfmeTerrainVisual->slot90(context, result);
	}
	return 0;
}
