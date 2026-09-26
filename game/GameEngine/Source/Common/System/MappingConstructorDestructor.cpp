// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib

class MemoryPoolObject
{
public:
	virtual void memoryPoolAnchor();
};

#include "ascii_string.h"

class Mapping : public MemoryPoolObject
{
public:
	Mapping();

protected:
	virtual ~Mapping();

private:
	Mapping *m_next;
	AsciiString m_name;
};

Mapping::Mapping()
{
}

Mapping::~Mapping()
{
}
