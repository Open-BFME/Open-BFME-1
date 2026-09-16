// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport

// Open-BFME5: the asset walker at retail 0x0077F570, 252 bytes.
//
// What the body does is provable; who owns it is not. It takes a record, an
// AssetList and a context word, and it adds every asset the record names to
// the list. Two names go in through the inlined prototype insert, one through
// the out-of-line AssetList::operator<< at 0x00141D00, and one is looked up as
// a thing template first. Three sub-objects at +0x20, +0x24 and +0x50 each get
// the same two-pointer forwarder.
//
// The list is an AssetList because the body inserts through the same
// insert_unique thunk (ILT 0x00030413) the matched operator at 0x00141D00
// uses, sets the same changed flag at +0x10, and hands the same pointer to
// that operator. Nothing names the walker itself: the only thing that reaches
// it is the incremental thunk at 0x0003BDCC, and it has no vtable slot, no
// string of its own and no source emitter. Five earlier sessions stopped
// there. The symbol therefore keeps its address, which is what AGENTS.md asks
// for when the evidence proves the body but not its name.

#define _BFME_RETAIL_TREE_INSERT_LAYOUT
#include <set>

class AsciiString
{
public:
	const char *str() const
	{
		return m_data ? m_data + 8 : (const char *)0x0107388B;
	}
	bool isNotEmpty() const
	{
		return m_data != 0 && *(const unsigned short *)(m_data + 4) != 0;
	}

	const char *m_data;
};

struct Rva001408C0Target;

typedef Rva001408C0Target *Rva001408C0Key;
typedef _STL::set<Rva001408C0Key, _STL::less<Rva001408C0Key>,
	_STL::allocator<Rva001408C0Key> > Rva001408C0Set;

void *bfmeGoEMEb(void *);
typedef Rva001408C0Target *(__cdecl *FindPrototypeFn)(const char *name);

class AssetList
{
public:
	AssetList &operator <<(const AsciiString &name);

	Rva001408C0Set m_prototypes;
	unsigned int m_treeLayoutPad;
	bool m_changed;
};

class BfmeResGH
{
public:
	void bfmeTwoGH(void *list, void *context);
};

class ThingTemplate : public BfmeResGH
{
};

class BfmeThingFactory
{
public:
	const ThingTemplate *findTemplate(const AsciiString &name);
};

extern BfmeThingFactory *TheThingFactory;

class Gen_00429F60Target
{
public:
	void bfmeForward(void *list, void *context);
};

struct Record0077F570
{
	unsigned char m_pad00[8];
	AsciiString m_bfmeNameA;
	AsciiString m_bfmeNameB;
	unsigned char m_pad10[0x20 - 0x10];
	Gen_00429F60Target *m_bfmePartA;
	Gen_00429F60Target *m_bfmePartB;
	AsciiString m_bfmeNameC;
	unsigned char m_pad2C[0x48 - 0x2C];
	AsciiString m_bfmeTemplateName;
	unsigned char m_pad4C[4];
	Gen_00429F60Target *m_bfmePartC;
};

void collectAssets0077F570(Record0077F570 *record, AssetList *list, void *context)
{
	if (list->m_prototypes.insert(
		((FindPrototypeFn)bfmeGoEMEb)(record->m_bfmeNameA.str())).second)
	{
		list->m_changed = true;
	}

	if (list->m_prototypes.insert(
		((FindPrototypeFn)bfmeGoEMEb)(record->m_bfmeNameB.str())).second)
	{
		list->m_changed = true;
	}

	if (record->m_bfmePartA)
		record->m_bfmePartA->bfmeForward(list, context);

	if (record->m_bfmePartB)
		record->m_bfmePartB->bfmeForward(list, context);

	if (record->m_bfmeNameC.isNotEmpty())
		*list << record->m_bfmeNameC;

	if (record->m_bfmeTemplateName.isNotEmpty())
	{
		const ThingTemplate *found = TheThingFactory->findTemplate(record->m_bfmeTemplateName);
		if (found)
			const_cast<ThingTemplate *>(found)->bfmeTwoGH(list, context);
	}

	if (record->m_bfmePartC)
		record->m_bfmePartC->bfmeForward(list, context);
}
