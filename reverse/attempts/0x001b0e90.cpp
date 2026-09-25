// ?Rva001B0E90Dispatch@@YGHPAVRva001B0E90Owner@@PAX@Z
// partial score=0.2876 date=2026-09-25
// ?Rva001B0E90Dispatch@@YGHPAVRva001B0E90Owner@@PAX@Z
// cl: /DNDEBUG /MD /EHsc

typedef int Int;

template <typename T>
class StringBase;

template <>
class StringBase<char>
{
	friend class BFMERetailAsciiString;

private:
	struct Header
	{
		int ref_count;
		unsigned short length;
		unsigned short capacity;
		char data[1];
	};

	StringBase() : m_data(0) {}
	StringBase(const char *text);
	StringBase(const StringBase<char> &other);
	~StringBase();
	void releaseBuffer();
	Header *m_data;
};

class BFMERetailAsciiString : private StringBase<char>
{
public:
	BFMERetailAsciiString() : StringBase<char>() {}
	BFMERetailAsciiString(const char *text) : StringBase<char>(text) {}
	BFMERetailAsciiString(const BFMERetailAsciiString &other)
		: StringBase<char>(other) {}
	~BFMERetailAsciiString() { releaseBuffer(); }
	void __cdecl format(BFMERetailAsciiString format, ...);
	const char *str() const
	{
		return m_data ? m_data->data : (const char *)0x0107388B;
	}
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
	if ((int)(self->m_records.m_end - self->m_records.m_begin) != 0)
	{
		if (self->m_records.m_begin->m_object != 0)
			goto success;
	}

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
		void *result = self->m_records.m_begin->m_object->slot28();
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
