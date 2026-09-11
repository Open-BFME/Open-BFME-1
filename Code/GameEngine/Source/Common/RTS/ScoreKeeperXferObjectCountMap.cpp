// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// BFME retail RVA 0x000EACD0, the object-count map transfer helper.

#include <map>

typedef int Int;
typedef unsigned short UnsignedShort;
typedef unsigned char UnsignedByte;

struct XferVersion
{
	XferVersion(UnsignedByte value) : m_version(value), m_currentVersion(value) {}

	UnsignedByte m_version;
	UnsignedByte m_currentVersion;
};

class BFMERetailAsciiString
{
public:
	void releaseBuffer();
};

class UnicodeString
{
public:
	void set(const UnicodeString &other);
};

class AsciiString
{
public:
	AsciiString() : m_data(0) {}

	AsciiString &operator=(const AsciiString &other)
	{
		reinterpret_cast<UnicodeString *>(this)->set(
			*reinterpret_cast<const UnicodeString *>(&other));
		return *this;
	}

	~AsciiString()
	{
		reinterpret_cast<BFMERetailAsciiString *>(this)->releaseBuffer();
	}

private:
	void *m_data;
};

class Xfer
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual bool isStoring();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual void xferVersion(XferVersion *version);
	virtual void slot11();
	virtual void slot12();
	virtual void slot13();
	virtual void slot14();
	virtual void slot15();
	virtual void slot16();
	virtual void slot17();
	virtual void slot18();
	virtual void slot19();
	virtual void slot20();
	virtual void slot21();
	virtual void slot22();
	virtual void slot23();
	virtual void slot24();
	virtual void slot25();
	virtual void xferAsciiString(AsciiString *value);
	virtual void slot27();
	virtual void slot28();
	virtual void slot29();
	virtual void xferInt(Int *value);
	virtual void xferUnsignedShort(UnsignedShort *value);
};

class ThingTemplate
{
public:
	unsigned char m_unmodelled00[0x20];
	AsciiString m_name;
};

typedef _STL::map<const ThingTemplate *, Int> ObjectCountMap;

class BfmeThingFactory
{
public:
	const ThingTemplate *findTemplate(const AsciiString &name);
};

extern BfmeThingFactory *TheThingFactory;

struct XferException
{
	char *text;
	Int tag;
};

extern "C" XferException *__cdecl bfmeFormatText(
	XferException *result, Int tag, const char *format, ...);
extern void __declspec(noreturn) __stdcall _CxxThrowException(
	void *object, void *throwInfo);

class Rva000EACD0ScoreKeeper
{
public:
	void xferObjectCountMap(Xfer *xfer, ObjectCountMap *map);
};

// ?xferObjectCountMap@Rva000EACD0ScoreKeeper@@QAEXXZ absent-from-retail
void Rva000EACD0ScoreKeeper::xferObjectCountMap(Xfer *xfer, ObjectCountMap *map)
{
	XferVersion version(1);
	xfer->xferVersion(&version);

	UnsignedShort mapSize = map->size();
	xfer->xferUnsignedShort(&mapSize);

	Int count;
	const ThingTemplate *thingTemplate;
	AsciiString thingTemplateName;

	if (xfer->isStoring())
	{
		ObjectCountMap::iterator it;
		for (it = map->begin(); it != map->end(); ++it)
		{
			thingTemplate = it->first;
			thingTemplateName = thingTemplate->m_name;
			xfer->xferAsciiString(&thingTemplateName);

			count = it->second;
			xfer->xferInt(&count);
		}
	}
	else
	{
		for (UnsignedShort i = 0; i < mapSize; ++i)
		{
			xfer->xferAsciiString(&thingTemplateName);
			thingTemplate = TheThingFactory->findTemplate(thingTemplateName);
			if (thingTemplate == 0)
			{
				XferException error;
				bfmeFormatText(&error, 5, 0);
				_CxxThrowException(&error, (void *)0x011DFE5C);
			}

			xfer->xferInt(&count);
			(*map)[thingTemplate] = count;
		}
	}
}
