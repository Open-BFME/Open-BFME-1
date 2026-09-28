// ?placeAt001AD080@Rva001AD080TerrainLogic@@QAEXPBVThingTemplate@@PBUCoord3D@@PBVMatrix3D@@M@Z
// partial score=0.8249158249 date=2026-09-28
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
 Coord3D(const Coord3D &p):x(p.x),y(p.y),z(p.z){} ~Coord3D(){}
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
public:
 int count001AD080() const {return int(m_end-m_begin);}
 Rva001AD080Resource *resource001AD080(unsigned int i)const {
  if(i < (unsigned int)count001AD080()) return m_begin[i].resource;
  return 0;
 }

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
	virtual Rva001AD080DebugReport *slot00(const char *text);
	virtual Rva001AD080DebugReport *slot04(const char *text);
	virtual Rva001AD080DebugReport *slot08(const char *text);
	virtual Rva001AD080DebugReport *slot0c(const char *text);
	virtual Rva001AD080DebugReport *slot10(const char *text);
	virtual Rva001AD080DebugReport *slot14(const char *text);
	virtual Rva001AD080DebugReport *slot18(const char *text);
	virtual Rva001AD080DebugReport *slot1c(const char *text);
	virtual Rva001AD080DebugReport *slot20(const char *text);
	virtual Rva001AD080DebugReport *slot24(const char *text);
	virtual Rva001AD080DebugReport *slot28(const char *text);
	virtual Rva001AD080DebugReport *slot2c(const char *text);
	virtual Rva001AD080DebugReport *slot30(const char *text);
	virtual Rva001AD080DebugReport *slot34(const char *text);
	virtual Rva001AD080DebugReport *slot38(const char *text);
	virtual Rva001AD080DebugReport *slot3c(const char *text);
	virtual Rva001AD080DebugReport *slot40(const char *text);
	virtual Rva001AD080DebugReport *slot44(const char *text);
	virtual Rva001AD080DebugReport *slot48(const char *text);
	virtual Rva001AD080DebugReport *slot4c(Int kind);
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
	virtual virtual Rva001AD080DebugReport *slot6c(Int first, Int second);
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
	virtual void slot33(DrawableID, Coord3D, const Matrix3D *, Real,
		Int, void *, Int, const void *, const void *);
};

extern Rva001AD080TerrainVisual *g_bfmeTerrainVisual;

class Rva001AD080Record
{
public:
 Rva001AD080Record(const Coord3D &pos,int id,int value,const ThingTemplate *templ,int limit,unsigned char flag2c,unsigned char flag2d,unsigned short old)
 :m_field00(pos.x),m_field04(pos.y),m_field08(pos.z),m_field0c(id),m_field10(value),m_field14((int)templ),m_field18(0),m_field28(limit),m_field2c(flag2c),m_field2d(flag2d),m_field2e(old) {}

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

struct False001AD080 {False001AD080(){}};

struct Rva001AD080RecordVector
{
	Rva001AD080Record *begin;
	Rva001AD080Record *end;
	Rva001AD080Record *capacity;
 int size()const{return int(end-begin);}
	void insertOverflow(Rva001AD080Record *position, const Rva001AD080Record &value,
		const False001AD080 &, unsigned int first, bool second);
 void push_back(const Rva001AD080Record &record) {
		if (end != capacity)
		{
			if (end) ::new ((void *)end) Rva001AD080Record(record);
			++end;
		}
		else
		{
			insertOverflow(end, record, False001AD080(), 1, true);
		}
 }

};

class Frame001AD080 {char pad[0x3c]; public: unsigned int value; unsigned int frame()const{return value;} };
extern Frame001AD080 *g_Frame001AD080;
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
		m_value18f0 = g_Frame001AD080->frame();
		const ThingTemplate *templatePtr = thingTemplate;
        void *found=0;
        for(int i=0; i<templatePtr->count001AD080(); ++i) {
            Rva001AD080Resource *resource=templatePtr->resource001AD080(0);
            if(resource) {
                void *candidate=(void*)resource->getID();
                if(candidate) found=candidate;
            }
        }
		if (!found)
		{
			if (_bfme_debugReportingEnabled())
			{
				_bfme_debugRecordCallsite(1);
				TheBfmeAwakenDebug->slot60();
				Rva001AD080DebugReport *report = TheBfmeAwakenDebug->slot6c(0, 0);
				report=report->slot38((const char *)0x0109c3f0);
				void *name = *(void **)((const char *)templatePtr + 0x20);
				report=report->slot38(name ? (const char *)name + 8 : (const char *)0x0107388b);
				report=report->slot38((const char *)0x0109c358);
				report->slot4c(2);
			}
			return;
		}

		DrawableID id = TheGameClient->allocDrawableID();
		short index = gridIndex(position);
		short &bucket=m_words[index];
        UnsignedShort oldWord=(UnsignedShort)bucket;
        bucket=(short)m_records.size();
		Int candidateLimit = templatePtr->m_field46c;
        Int limit = *(Int *)((const char *)(*(void **)0x012ED5C8) + 0xb28);
        if (candidateLimit > 0) limit=candidateLimit;
		Int oldValue = m_value3c;
		++m_value3c;
        Rva001AD080Record record(*position,id,oldValue,templatePtr,limit,templatePtr->m_field48b,templatePtr->m_field48c,oldWord);
        m_records.push_back(record);
		g_bfmeTerrainVisual->slot33(id, *position, matrix, extra, 0, found,
			templatePtr->m_field482, (void *)((const char *)templatePtr + 0x4c),
			(void *)((const char *)templatePtr + 0x20));
	}
};


__declspec(noinline) void rva001ad080ForceEmit(Rva001AD080TerrainLogic *self,
	const ThingTemplate *thingTemplate, const Coord3D *position,
	const Matrix3D *matrix, Real extra)
{
	self->placeAt001AD080(thingTemplate, position, matrix, extra);
}
