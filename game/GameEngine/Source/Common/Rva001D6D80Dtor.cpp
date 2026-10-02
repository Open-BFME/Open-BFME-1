// cl: /EHsc
// Destructor that destroys members at +8 then +4 (an Inner at +4) and stores
// a vftable at +0 last.
//
// Both members are narrow strings: the body calls the ONE narrow-string
// release, 0x00887940 (StringBase<char>::releaseBuffer, private, which is why
// the ledger spells it AAEXXZ), twice.  Spelled with AsciiString, whose inline
// destructor is that call, exactly as Bfme7NarrowStringChainDestructors.cpp
// does; a TU-local member spelled bfme* called nothing that existed.

#include "../../../Libraries/Source/WWVegas/WWLib/ascii_string.h"

struct Rva001D6D80Head
{
	virtual ~Rva001D6D80Head() {}
};

typedef AsciiString Rva001D6D80Elem;

struct Rva001D6D80Inner
{
	Rva001D6D80Elem m_first;
	Rva001D6D80Elem m_second;
};

struct Rva001D6D80
{
	Rva001D6D80Head m_head;
	Rva001D6D80Inner m_inner;
	~Rva001D6D80();
};

Rva001D6D80::~Rva001D6D80() {}
