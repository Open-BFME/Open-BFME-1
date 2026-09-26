// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
//
// The owner keeps an STLport map at +0x08.  Its values are owned objects: the
// destructor first visits the tree in key order and invokes each value's
// deleting destructor, then lets the map and SubsystemInterface subobjects
// unwind.  The +0x04 subsystem name field is what places the map at +0x08.
#include <map>

class SubsystemInterface
{
public:
	virtual ~SubsystemInterface();

private:
	void *m_name;
};

class Rva001B6F20Elem
{
public:
	virtual ~Rva001B6F20Elem();
};

typedef _STL::map<int, Rva001B6F20Elem *> Rva001B6F20Map;

class Rva001B6F20 : public SubsystemInterface
{
public:
	virtual ~Rva001B6F20();

private:
	Rva001B6F20Map m_values;
};

// ??1Rva001B6F20@@UAE@XZ
Rva001B6F20::~Rva001B6F20()
{
	for ( Rva001B6F20Map::iterator i = m_values.begin(); i != m_values.end(); ++i )
	{
		if ( i->second )
			delete i->second;
	}
	m_values.clear();
}
