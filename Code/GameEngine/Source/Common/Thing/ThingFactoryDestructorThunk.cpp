// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
//
// ??1ThingFactory@@UAE@XZ, retail 0x00137C90. tools/vtable_lookup.py 0x01090E6C
// shares this vtable with ThingFactory::ThingFactory (Thing/ThingFactory.cpp),
// so this row is ThingFactory's destructor, not the EmotionTrackerUpdateEntry
// near-twin an earlier size-only scan picked. The real ThingFactory.cpp already
// defines freeDatabase() and the destructor inline in the same TU, which lets
// the compiler inline freeDatabase's loop into the destructor and produce a
// much larger body (118B) than retail's 92B -- retail keeps freeDatabase as a
// genuine out-of-line call. This TU only declares freeDatabase (no body), so
// the call stays out-of-line and the implicit ~hash_map<AsciiString,
// ThingTemplate*> destructor for m_templateHashMap supplies the second call,
// matching retail's exact two-call shape.

#define _STLP_NO_EXCEPTIONS 1
#include <hash_map>

typedef unsigned short UnsignedShort;

class ThingTemplate;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
public:
	AsciiString();
	AsciiString(const AsciiString &other);
	~AsciiString();
	AsciiString &operator=(const AsciiString &other);

private:
	void *m_data;
};

inline bool operator==(const AsciiString &, const AsciiString &);

namespace rts
{
template <class T>
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/STLTypedefs.h
struct hash
{
	unsigned int operator()(T value) const;
};
}

typedef _STL::hash_map<AsciiString, ThingTemplate *, rts::hash<AsciiString>,
	_STL::equal_to<AsciiString> > ThingTemplateHashMap;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/SubsystemInterface.h
class SubsystemInterface
{
public:
	SubsystemInterface();
	virtual ~SubsystemInterface();
	virtual void init() = 0;
	virtual bool loadIniFilesFromLegend();
	virtual void reset() = 0;
	virtual void update() = 0;

private:
	void *m_name;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/ThingFactory.h
class ThingFactory : public SubsystemInterface
{
public:
	ThingFactory();
	virtual ~ThingFactory();
	virtual void init();
	virtual void postProcessLoad();
	virtual void reset();
	virtual void update();

private:
	void freeDatabase();		///< retail 0x00003A26 (still a dump)

	ThingTemplate *m_firstTemplate;
	UnsignedShort m_nextTemplateID;
	char m_pad0C[2];
	ThingTemplateHashMap m_templateHashMap;
};

ThingFactory::~ThingFactory()
{
	freeDatabase();
}
