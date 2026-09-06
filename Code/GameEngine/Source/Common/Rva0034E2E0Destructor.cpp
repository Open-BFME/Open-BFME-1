// cl: /DNDEBUG /MD /EHsc /O2
//
// Open-BFME5: retail 0x0034E2E0, 110 bytes. BfmeBaseVUQ destructor family:
// own vtable 0x010E7D00 stored at entry, a ThingTemplate-keyed _Rb_tree
// member at +0xC is destroyed and freed if present, an AsciiString member at
// +0x4 is released, then the base vtable 0x01073744 is restored.
//
// The _Rb_tree destructor (retail 0x0003D61D) and the operator delete
// (retail 0x00881EB0) are already pinned/landed callees; the class's real
// name is not recovered, so it keeps an address-derived name.

class BfmeBaseVUQ
{
public:
	virtual ~BfmeBaseVUQ() { }
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
public:
	~AsciiString(void) { releaseBuffer(); }
	void releaseBuffer(void);                                  ///< retail 0x00887940

private:
	void *m_bfmeData;                                          ///< +0x00
};

class ThingTemplate;

namespace _STL
{
template <class First, class Second>
struct pair
{
};

template <class Pair>
struct _Select1st
{
};

template <class Type>
struct less
{
};

template <class Type>
class allocator
{
};

template <class Key, class Value, class Select, class Compare, class Allocator>
class _Rb_tree
{
public:
	~_Rb_tree();
};
}

typedef _STL::_Rb_tree<ThingTemplate const *,
                        _STL::pair<ThingTemplate const *const, int>,
                        _STL::_Select1st<_STL::pair<ThingTemplate const *const, int> >,
                        _STL::less<ThingTemplate const *>,
                        _STL::allocator<_STL::pair<ThingTemplate const *const, int> > >
	ThingTemplateRbTree;

void __cdecl operator delete(void *block);

class Rva0034E2E0 : public BfmeBaseVUQ
{
public:
	~Rva0034E2E0();

private:
	AsciiString m_str;                                         ///< +0x04
	unsigned int m_pad08;                                      ///< +0x08 (untouched by this body)
	ThingTemplateRbTree *m_tree;                                ///< +0x0C
};

// @??1Rva0034E2E0@@UAE@XZ 0x0034E2E0
Rva0034E2E0::~Rva0034E2E0()
{
	ThingTemplateRbTree *tree = m_tree;

	if (tree != 0)
	{
		tree->~ThingTemplateRbTree();
		operator delete(tree);
	}

	m_tree = 0;
}
