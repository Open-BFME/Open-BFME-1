// ?d_001ad080@@YAXXZ
// partial score=0.19 date=2026-09-23
// cl: /DNDEBUG /MD /EHsc- /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// Retail RVA 0x001AD080, 594 bytes. Address-derived placement helper.

#include <new>

typedef unsigned short UnsignedShort;
typedef unsigned int UnsignedInt;
typedef int Int;
typedef bool Bool;
typedef float Real;
typedef Int DrawableID;

struct Coord3D
{
	Real x;
	Real y;
	Real z;
};

class Matrix3D;

class Rva001AD080Resource
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
	virtual Int getID();
};

struct Rva001AD080Entry
{
	Int field00;
	Int field04;
	Rva001AD080Resource *resource;
	char pad0c[8];
};

class ThingTemplate
{
private:
	char m_pad00[0x2a0];

public:
	Rva001AD080Entry *m_begin;
	Rva001AD080Entry *m_end;
	char m_pad2a8[0x46c - 0x2a8];
	Int m_field46c;
	char m_pad470[0x482 - 0x470];
	UnsignedShort m_field482;
	char m_pad484[0x48b - 0x484];
	unsigned char m_field48b;
	unsigned char m_field48c;
};

class Rva001AD080GameClient
{
public:
	DrawableID allocDrawableID();
};

extern Rva001AD080GameClient *TheGameClient;
extern Bool _bfme_debugReportingEnabled();
extern void _bfme_debugRecordCallsite(Int kind);

class Rva001AD080DebugReport
{
public:
	Rva001AD080DebugReport *slot00(const char *text);
	Rva001AD080DebugReport *slot04(const char *text);
	Rva001AD080DebugReport *slot08(const char *text);
	Rva001AD080DebugReport *slot0c(const char *text);
	Rva001AD080DebugReport *slot10(const char *text);
	Rva001AD080DebugReport *slot14(const char *text);
	Rva001AD080DebugReport *slot18(const char *text);
	Rva001AD080DebugReport *slot1c(const char *text);
	Rva001AD080DebugReport *slot20(const char *text);
	Rva001AD080DebugReport *slot24(const char *text);
	Rva001AD080DebugReport *slot28(const char *text);
	Rva001AD080DebugReport *slot2c(const char *text);
	Rva001AD080DebugReport *slot30(const char *text);
	Rva001AD080DebugReport *slot34(const char *text);
	Rva001AD080DebugReport *slot38(const char *text);
	Rva001AD080DebugReport *slot3c(const char *text);
	Rva001AD080DebugReport *slot40(const char *text);
	Rva001AD080DebugReport *slot44(const char *text);
	Rva001AD080DebugReport *slot48(const char *text);
	Rva001AD080DebugReport *slot4c(Int kind);
};

class Rva001AD080DebugManager
{
public:
	virtual void slot00(); virtual void slot04(); virtual void slot08(); virtual void slot0c();
	virtual void slot10(); virtual void slot14(); virtual void slot18(); virtual void slot1c();
	virtual void slot20(); virtual void slot24(); virtual void slot28(); virtual void slot2c();
	virtual void slot30(); virtual void slot34(); virtual void slot38(); virtual void slot3c();
	virtual void slot40(); virtual void slot44(); virtual void slot48(); virtual void slot4c();
	virtual void slot50(); virtual void slot54(); virtual void slot58(); virtual void slot5c();
	virtual void slot60();
	virtual void slot64();
	virtual void slot68();
	virtual Rva001AD080DebugReport *slot6c(Int first, Int second);
};

extern Rva001AD080DebugManager *TheBfmeAwakenDebug;

class Rva001AD080TerrainVisual
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual void slot04(); virtual void slot05(); virtual void slot06(); virtual void slot07();
	virtual void slot08(); virtual void slot09(); virtual void slot10(); virtual void slot11();
	virtual void slot12(); virtual void slot13(); virtual void slot14(); virtual void slot15();
	virtual void slot16(); virtual void slot17(); virtual void slot18(); virtual void slot19();
	virtual void slot20(); virtual void slot21(); virtual void slot22(); virtual void slot23();
	virtual void slot24(); virtual void slot25(); virtual void slot26(); virtual void slot27();
	virtual void slot28(); virtual void slot29(); virtual void slot30(); virtual void slot31();
	virtual void slot32();
	virtual void slot33(class Rva001AD080TerrainLogic *, const Coord3D &, const Matrix3D *, Real,
		Int, void *, UnsignedShort, void *, void *);
};

extern Rva001AD080TerrainVisual *g_bfmeTerrainVisual;

class Rva001AD080Record
{
public:
	Rva001AD080Record(const Rva001AD080Record &other) throw();

	Real m_field00;
	Real m_field04;
	Real m_field08;
	Int m_field0c;
	Int m_field10;
	Int m_field14;
	unsigned char m_field18;
	unsigned char m_pad19[3];
	Int m_field1c;
	Int m_field20;
	Int m_field24;
	Int m_field28;
	unsigned char m_field2c;
	unsigned char m_field2d;
	UnsignedShort m_field2e;
};

struct Rva001AD080RecordVector
{
	Rva001AD080Record *begin;
	Rva001AD080Record *end;
	Rva001AD080Record *capacity;
	void insertOverflow(Rva001AD080Record *position, const Rva001AD080Record &value,
		Int first, Int second);
};

class Rva001AD080TerrainLogic
{
private:
	char m_pad00[0x3c];
	UnsignedInt m_value3c;
	char m_pad40[0x51c];
	Rva001AD080RecordVector m_records;
	short m_words[2500];
	UnsignedInt m_value18f0;

public:
	short gridIndex(const Coord3D *position);

	__declspec(noinline) void placeAt001AD080(const ThingTemplate *thingTemplate, const Coord3D *position,
		const Matrix3D *matrix, Real extra)
	{
		m_value18f0 = *(UnsignedInt *)((const char *)(*(void **)0x012F0898) + 0x3c);
		const ThingTemplate *templatePtr = thingTemplate;
		Int count = (Int)(templatePtr->m_end - templatePtr->m_begin);
		void *found = 0;
		Int i = 0;
		while (i < count)
		{
			if ((UnsignedInt)count > 0)
			{
				Rva001AD080Entry *entry = templatePtr->m_begin;
				Rva001AD080Resource *resource = entry->resource;
				if (resource)
				{
					found = (void *)resource->getID();
					if (found)
						break;
				}
			}
			count = (Int)(templatePtr->m_end - templatePtr->m_begin);
			++i;
		}
		if (!found)
		{
			if (_bfme_debugReportingEnabled())
			{
				_bfme_debugRecordCallsite(1);
				TheBfmeAwakenDebug->slot60();
				Rva001AD080DebugReport *report = TheBfmeAwakenDebug->slot6c(0, 0);
				report->slot38((const char *)0x0109c3f0);
				void *name = *(void **)((const char *)templatePtr + 0x20);
				report->slot38(name ? (const char *)name + 8 : (const char *)0x0107388b);
				report->slot38((const char *)0x0109c358);
				report->slot4c(2);
			}
			return;
		}

		DrawableID id = TheGameClient->allocDrawableID();
		short index = gridIndex(position);
		UnsignedShort oldWord = (UnsignedShort)m_words[index];
		Int recordCount = (Int)(m_records.end - m_records.begin);
		m_words[index] = (short)recordCount;
		Int oldValue = m_value3c;
		++m_value3c;
		Int limit = templatePtr->m_field46c;
		Int fallback = *(Int *)((const char *)(*(void **)0x012ED5C8) + 0xb28);
		if (limit <= 0)
			limit = fallback;
		char recordStorage[0x30];
		Rva001AD080Record &record = *(Rva001AD080Record *)recordStorage;
		record.m_field00 = position->x;
		record.m_field04 = position->y;
		record.m_field08 = position->z;
		record.m_field0c = id;
		record.m_field10 = oldValue;
		record.m_field14 = (Int)templatePtr;
		record.m_field18 = 0;
		record.m_field28 = limit;
		record.m_field2c = templatePtr->m_field48b;
		record.m_field2d = templatePtr->m_field48c;
		record.m_field2e = oldWord;
		if (m_records.end != m_records.capacity)
		{
			::new ((void *)m_records.end) Rva001AD080Record(record);
			++m_records.end;
		}
		else
		{
			m_records.insertOverflow(m_records.end, record, 1, 1);
		}
		g_bfmeTerrainVisual->slot33(this, *position, matrix, extra, id, found,
			templatePtr->m_field482, (void *)((const char *)templatePtr + 0x4c),
			*(void **)((const char *)templatePtr + 0x20));
	}
};


__declspec(noinline) void rva001ad080ForceEmit(Rva001AD080TerrainLogic *self,
	const ThingTemplate *thingTemplate, const Coord3D *position,
	const Matrix3D *matrix, Real extra)
{
	self->placeAt001AD080(thingTemplate, position, matrix, extra);
}
