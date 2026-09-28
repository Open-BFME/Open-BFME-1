// cl: /DNDEBUG /MD /EHsc /O2 /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB
// stlport

#define _STLP_NO_EXCEPTIONS 1
#include <map>

typedef unsigned char UnsignedByte;
typedef unsigned short UnsignedShort;
typedef int Int;
typedef bool Bool;

struct BfmeAsciiStringData
{
	UnsignedShort m_refCount;
	UnsignedShort m_numCharsAllocated;
	UnsignedShort m_numChars;
	UnsignedShort m_unreconstructed_06;
};

template <class T> class StringBase
{
	friend class AsciiString;

private:
	StringBase(const StringBase &);
	~StringBase();
	void set(const StringBase &);
	void releaseBuffer();
};

class AsciiString
{
public:
	AsciiString(void) : m_data(0) {}
	AsciiString(const AsciiString &that)
	{
		((StringBase<char> *)this)->StringBase<char>::StringBase(
			*(const StringBase<char> *)&that);
	}
	~AsciiString() { ((StringBase<char> *)this)->releaseBuffer(); }
	AsciiString &operator=(const AsciiString &that)
	{
		((StringBase<char> *)this)->set(
			*(const StringBase<char> *)&that);
		return *this;
	}

private:
	BfmeAsciiStringData *m_data;
};

struct XferVersion
{
	XferVersion(UnsignedByte version) :
		m_version(version), m_currentVersion(version)
	{
	}

	UnsignedByte m_version;
	UnsignedByte m_currentVersion;
	UnsignedByte m_pad[2];
};

struct XferException
{
	char *m_text;
	Int m_tag;
};

extern "C" XferException *__cdecl bfmeFormatText(
	XferException *result, Int tag, const char *format, ...);
extern void __declspec(noreturn) __stdcall _CxxThrowException(
	void *object, void *throwInfo);
extern int g_guardTargetTypeThrowInfo;

class Snapshot;

class Xfer
{
public:
	virtual void slot00();
	virtual Bool IsLoading() const;
	virtual Bool IsStoring() const;
	virtual void slot03();
	virtual Bool IsLightCRC() const;
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual void xferVersion(XferVersion *version);
	virtual void slot11();
	virtual void xferSnapshot(Snapshot *snapshot);
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
	virtual void xferUnsignedInt(unsigned int *value);
	virtual void xferInt(Int *value);
	virtual void xferUnsignedShort(UnsignedShort *value);
	virtual void slot32();
	virtual void slot33();
	virtual void slot34();
	virtual void xferBool(Bool *value);
};

class ThingTemplate
{
public:
	unsigned char m_unreconstructed_00[0x20];
	AsciiString m_name;

	const AsciiString &getName(void) const { return m_name; }
};

typedef std::map<const ThingTemplate *, Int> AttackPriorityMap;

class ThingFactory
{
public:
	ThingTemplate *findTemplate(const AsciiString &name);
};

extern ThingFactory *TheThingFactory;

class AttackPriorityInfo
{
public:
	void setPriority(const ThingTemplate *thing, Int priority);

protected:
	virtual void xfer(Xfer *xfer);

private:
	AsciiString m_name;
	Int m_defaultPriority;
	AttackPriorityMap *m_priorityMap;
};

// ?xfer@AttackPriorityInfo@@MAEXPAVXfer@@@Z
void AttackPriorityInfo::xfer(Xfer *xfer)
{
	if (xfer->IsLightCRC())
		return;

	XferVersion version(1);
	xfer->xferVersion(&version);
	xfer->xferAsciiString(&m_name);
	xfer->xferInt(&m_defaultPriority);

	UnsignedShort priorityMapCount;
	if (m_priorityMap)
		priorityMapCount = m_priorityMap->size();
	else
		priorityMapCount = 0;
	xfer->xferUnsignedShort(&priorityMapCount);

	AsciiString thingTemplateName;
	const ThingTemplate *thingTemplate;
	Int priority;
	XferException error;
	if (xfer->IsStoring())
	{
		if (m_priorityMap)
		{
			AttackPriorityMap::const_iterator it;
			for (it = m_priorityMap->begin(); it != m_priorityMap->end(); ++it)
			{
				thingTemplate = (*it).first;
				thingTemplateName = thingTemplate->getName();
				xfer->xferAsciiString(&thingTemplateName);
				priority = (*it).second;
				xfer->xferInt(&priority);
			}
		}
	}
	else
	{
		for (UnsignedShort i = 0; i < priorityMapCount; ++i)
		{
			xfer->xferAsciiString(&thingTemplateName);
			thingTemplate = TheThingFactory->findTemplate(thingTemplateName);
			if (thingTemplate == 0)
			{
				bfmeFormatText(&error, 5, 0);
				_CxxThrowException(&error, &g_guardTargetTypeThrowInfo);
			}
			xfer->xferInt(&priority);
			setPriority(thingTemplate, priority);
		}
	}
}
