// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Igame/Libraries/Source/WWVegas/WWLib
// stlport
// BFME retail RVA 0x000EACD0, the object-count map transfer helper.

#include <map>

#include "../../../Include/Common/ScalarTypes.h"



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

#include "unicode_string.h"

#include "ascii_string.h"

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

// Retail calls ILT 0x00017111 -> 0x000EA510. Its ledger provider uses
// this address-scoped comparator spelling (zhstl_007.cpp); the default
// comparator's object-symbol is attached to a different body at 0x005D3380.
// Declare the existing provider without emitting another instantiation.
struct Gen_lt_000ea510 : public _STL::less<const ThingTemplate *> {};
typedef _STL::map<const ThingTemplate *, Int, Gen_lt_000ea510> Rva000EA510Map;
namespace _STL
{
	template <> Int &map<const ThingTemplate *, Int, Gen_lt_000ea510>::operator[](const ThingTemplate *const &key);
}

class ThingFactory;

// TU-local view of the singleton's findTemplate entry point.
class BfmeThingFactory
{
public:
	const ThingTemplate *findTemplate(const AsciiString &name);
};

extern ThingFactory *TheThingFactory;

static inline BfmeThingFactory *localTheThingFactory() { return (BfmeThingFactory *)TheThingFactory; }

class XferException
{
public:
	XferException(int tag, const char *format, ...);
	XferException(const XferException &that);
	~XferException(void);
	char *text;
	int tag;
};

class ScoreKeeper
{
public:
	void xferObjectCountMap(Xfer *xfer, ObjectCountMap *map);
};

// ?xferObjectCountMap@ScoreKeeper@@QAEXPAVXfer@@PAV?$map@PBVThingTemplate@@HU?$less@PBVThingTemplate@@@_STL@@V?$allocator@U?$pair@QBVThingTemplate@@H@_STL@@@3@@_STL@@@Z
void ScoreKeeper::xferObjectCountMap(Xfer *xfer, ObjectCountMap *map)
{
	XferVersion version(1);
	xfer->xferVersion(&version);

	UnsignedShort mapSize = map->size();
	xfer->xferUnsignedShort(&mapSize);

	Int count;
	AsciiString thingTemplateName;

	if (xfer->isStoring())
	{
		ObjectCountMap::iterator it;
		for (it = map->begin(); it != map->end(); ++it)
		{
			const ThingTemplate *thingTemplate = it->first;
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
			const ThingTemplate *thingTemplate = localTheThingFactory()->findTemplate(thingTemplateName);
			if (thingTemplate == 0)
			{
				throw XferException(5, 0);
			}

			xfer->xferInt(&count);
			(*reinterpret_cast<Rva000EA510Map *>(map))[thingTemplate] = count;
		}
	}
}
