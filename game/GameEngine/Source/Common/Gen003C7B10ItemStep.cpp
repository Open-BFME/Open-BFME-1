// Open-BFME5: retail RVA 0x006199D0, 108 bytes.
//
// Gen003C7B10Owner::step at 0x003C7B10 walks a vector of these items and
// calls the existing ILT 0x000484FA, whose canonical decorated signature is
// Gen003C7B10Item::step(Gen003C7B10Context *).  This body walks the item's
// embedded vector at +0x9c/+0xa0, whose elements are 0x24 bytes, and routes
// each element/context pair through existing ILT 0x0002C403.  The item and
// element semantic names are retained only where the caller/ILT proves them;
// the element payload remains address-derived.

// cl: /DNDEBUG /MD /EHsc /O2 /Ob2

#include <vector>

class Gen003C7B10Context
{
};

class Gen003C7B10Element
{
private:
	unsigned char m_unmodelled[0x24];
};

struct Gen003C7B10Vector
{
	Gen003C7B10Element *m_begin;
	Gen003C7B10Element *m_finish;

	unsigned int size() const
	{
		return (unsigned int)(m_finish - m_begin);
	}

	Gen003C7B10Element &operator[](unsigned int index)
	{
		return m_begin[index];
	}
};

extern void j_0002c403();

class Gen003C7B10Item
{
public:
	void step(Gen003C7B10Context *context);

private:
	unsigned char m_unmodelled00[0x9c];
	Gen003C7B10Vector m_elements;
};

// ?step@Gen003C7B10Item@@QAEXPAVGen003C7B10Context@@@Z
void Gen003C7B10Item::step(Gen003C7B10Context *context)
{
	for (unsigned int index = 0; index < m_elements.size(); ++index)
	{
		typedef void (Gen003C7B10Element::*Apply)(Gen003C7B10Context *);
		union { void (*raw)(); Apply member; } apply;
		apply.raw = j_0002c403;
		(m_elements[index].*apply.member)(context);
	}
}
