// ?placeAt001AD080@Rva001AD080TerrainLogic@@QAEXPBVThingTemplate@@PBUCoord3D@@PBVMatrix3D@@M@Z
// partial score=0.8266 date=2026-09-28
// cl: /DNDEBUG /MD /EHsc- /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Iinputs/reference/shims/stringinline
// stlport
// Retail RVA 0x001AD080, 594 bytes. Tree placement: needs a W3DTreeDrawModule, links the record into its bucket.
// Residue: retail keeps this in EBX and position in EDI; this form swaps them (see build/r1ad080 in the seat).

#include <vector>

#include "StringInline.h"

typedef unsigned short UnsignedShort;
typedef unsigned int UnsignedInt;
typedef int Int;
typedef bool Bool;
typedef float Real;
enum DrawableID { INVALID_DRAWABLE_ID = 0 };

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
	char m_pad00[0x20];

public:
	AsciiString m_nameString;

private:
	char m_pad24[0x4c - 0x24];

public:
	AsciiString m_shadowTextureName;

private:
	char m_pad50[0x2a0 - 0x50];

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

class GameClient
{
	friend class Rva001AD080TerrainLogic;

protected:
	DrawableID allocDrawableID();	///< landed at 0x0042E520
};

extern GameClient *TheGameClient;
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

class BfmeAwakenDebug
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

extern BfmeAwakenDebug *TheBfmeAwakenDebug;

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
	virtual void slot33(DrawableID, Coord3D, Real, const Matrix3D *,
		Int, void *, Int, const AsciiString &, const AsciiString &);
};

extern "C" Rva001AD080TerrainVisual *g_bfmeTerrainVisual;

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

class GameLogic
{
	char pad[0x3c];

public:
	UnsignedInt m_frame;
	UnsignedInt getFrame() const { return m_frame; }
};

extern GameLogic *TheGameLogic;

class GlobalData
{
	char m_pad00[0xb28];

public:
	Int m_fieldB28;
};

extern GlobalData *TheWritableGlobalData;

// Landed at 0x001A3060; the receiver is this object (ecx = this at the call).
class Rva001A3060
{
public:
	int getBucket(const Coord3D &position) const;
};
class Rva001AD080TerrainLogic
{
private:
	char m_pad00[0x3c];
	UnsignedInt m_value3c;
	char m_pad40[0x51c];
	std::vector<Rva001AD080Record> m_records;
	short m_words[2500];
	UnsignedInt m_value18f0;

public:

	void placeAt001AD080(const ThingTemplate *thingTemplate, const Coord3D *position,
		const Matrix3D *matrix, Real extra);
};

void Rva001AD080TerrainLogic::placeAt001AD080(const ThingTemplate *thingTemplate, const Coord3D *position,
		const Matrix3D *matrix, Real extra)
{
	m_value18f0 = TheGameLogic->getFrame();
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
			report=report->slot38("Tree ");
			report=report->slot38(templatePtr->m_nameString.str());
			report=report->slot38(" requires a W3DTreeDrawModule.\n");
			report->slot4c(2);
		}
		return;
	}

	DrawableID id = TheGameClient->allocDrawableID();
	short index = ((const Rva001A3060 *)this)->getBucket(*position);
	short &bucket=m_words[index];
	UnsignedShort oldWord=(UnsignedShort)bucket;
	bucket=(short)m_records.size();
	Int candidateLimit = templatePtr->m_field46c;
	Int limit = TheWritableGlobalData->m_fieldB28;
	if (candidateLimit > 0) limit=candidateLimit;
	Int oldValue = m_value3c;
	++m_value3c;
	unsigned char f2c=templatePtr->m_field48b; unsigned char f2d=templatePtr->m_field48c;
	Rva001AD080Record record(*position,id,oldValue,templatePtr,limit,f2c,f2d,oldWord);
	m_records.push_back(record);
	g_bfmeTerrainVisual->slot33(id, *position, extra, matrix, 0, found,
		templatePtr->m_field482, templatePtr->m_shadowTextureName,
		templatePtr->m_nameString);
}
