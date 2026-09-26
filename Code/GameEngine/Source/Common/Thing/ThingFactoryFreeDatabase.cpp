// cl: /DNDEBUG /MD /EHsc /ICode/Libraries/Source/WWVegas/WWLib
//
// Retail 0x00137BE0, 59 bytes: Zero Hour's ThingFactory::freeDatabase, reached
// through ILT 0x00003A26 from the ThingFactory destructor.  Advancing through
// m_firstTemplate rather than tmpl is what keeps retail's null test before the
// virtual delete.  The body ends by tail-calling bfmeGoEBL.
#include "ascii_string.h"

// Only the clear call is needed; these declarations give it STLport's mangling.
namespace _STL
{
	template <class T1, class T2> struct pair;
	template <class T> struct _Select1st;
	template <class T> struct equal_to;
	template <class T> class allocator;

	template <class V, class K, class HF, class ExK, class EqK, class A>
	class hashtable
	{
	public:
		void clear();

	private:
		char m_unmodelled00[0x14];
	};
}

namespace rts
{
	template <class T> struct hash;
}

class ThingTemplate;

typedef _STL::pair<const AsciiString, ThingTemplate *> ThingTemplateHashPair;
typedef _STL::hashtable< ThingTemplateHashPair, AsciiString, rts::hash<AsciiString>,
	_STL::_Select1st<ThingTemplateHashPair>, _STL::equal_to<AsciiString>,
	_STL::allocator<ThingTemplateHashPair> > ThingTemplateHashMap;

class ThingTemplate
{
public:
	virtual ~ThingTemplate();
	ThingTemplate *friend_getNextTemplate() const { return m_nextThingTemplate; }

private:
	char m_unmodelled04[0x388];
	ThingTemplate *m_nextThingTemplate;
};

void bfmeGoEBL();

class ThingFactory
{
private:
	void freeDatabase();

	void *m_vptr;
	int m_unmodelled04;
	ThingTemplate *m_firstTemplate;
	int m_unmodelled0C;
	ThingTemplateHashMap m_templateHashMap;
};

void ThingFactory::freeDatabase()
{
	while (m_firstTemplate)
	{
		ThingTemplate *tmpl = m_firstTemplate;
		m_firstTemplate = m_firstTemplate->friend_getNextTemplate();
		delete tmpl;
	}
	m_templateHashMap.clear();
	bfmeGoEBL();
}
