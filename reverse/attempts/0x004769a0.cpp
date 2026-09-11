// ??0BfmeOwnCA@@QAE@XZ
// partial score=0.88 date=2026-09-11
// cl: /DNDEBUG /MD /EHsc /O2 /Ob2
//
// BfmeOwnCA::BfmeOwnCA, retail 0x004769A0, 205 bytes. Sibling of the already
// matched ??1BfmeOwnCA@@UAE@XZ (BfmeConv1763.cpp) and the BfmeMemACA/BfmeMemBCA
// dtor pins there: same class, same vtable pin (??_7BfmeOwnCA@@6B@).
//
// The two owned members are empty STLport red-black tree headers (allocate
// 0x18, self-link left/right, zero color/parent) -- the node size matches
// BfmeFontSizeMap = _STL::map<Int, UnsignedInt> already used by the sibling
// FontLibraryBFMERetail_getFont.cpp. SubsystemInterface's own name field at
// +4 is set to the literal "TheFontLibrary" via UnicodeString::set, which
// retail resolves to the shared StringBase<char>::set body -- UnicodeString
// here derives from BFMERetailAsciiString exactly as Rva0042F160Release.cpp
// already established.

namespace _STL {

class __new_alloc
{
public:
	static void *allocate(unsigned int n);
};

}

class BFMERetailAsciiString
{
public:
	BFMERetailAsciiString(const char *str);
	void set(const BFMERetailAsciiString &other);
	void releaseBuffer();
};

class UnicodeString : public BFMERetailAsciiString
{
public:
	UnicodeString(const char *str) : BFMERetailAsciiString(str) {}
	void set(const UnicodeString &other) { BFMERetailAsciiString::set(other); }
};

class SubsystemInterface
{
public:
	SubsystemInterface(void);
	virtual ~SubsystemInterface(void);

	UnicodeString m_bfmeName;					// +0x04
};

struct BfmeTreeHeaderCA
{
	unsigned char m_color;
	unsigned int m_parent;
	BfmeTreeHeaderCA *m_left;
	BfmeTreeHeaderCA *m_right;
};

class BfmeMemACA
{
public:
	__forceinline BfmeMemACA(void)
	{
		m_node = 0;
		m_node = (BfmeTreeHeaderCA *)_STL::__new_alloc::allocate(0x18);
		m_count = 0;
		m_node->m_color = 0;
		m_node->m_parent = 0;
		m_node->m_left = m_node;
		m_node->m_right = m_node;
	}
	~BfmeMemACA(void);

	BfmeTreeHeaderCA *m_node;					// +0x00
	unsigned int m_count;					// +0x04
	unsigned int m_bfmeCompareCA;					// +0x08 (stateless comparator, never written)
};

class BfmeMemBCA
{
public:
	__forceinline BfmeMemBCA(void)
	{
		m_node = 0;
		m_node = (BfmeTreeHeaderCA *)_STL::__new_alloc::allocate(0x18);
		m_count = 0;
		m_node->m_color = 0;
		m_node->m_parent = 0;
		m_node->m_left = m_node;
		m_node->m_right = m_node;
	}
	~BfmeMemBCA(void);

	BfmeTreeHeaderCA *m_node;					// +0x00
	unsigned int m_count;					// +0x04
};

class BfmeOwnCA : public SubsystemInterface
{
public:
	BfmeOwnCA(void);
	virtual ~BfmeOwnCA(void);
	virtual void bfmePureCA(void) = 0;

	unsigned int m_bfmeMidCA0;					// +0x08
	unsigned int m_bfmeMidCA1;					// +0x0c
	BfmeMemACA m_bfmeACA;					// +0x10, size 0xc
	BfmeMemBCA m_bfmeBCA;					// +0x1c
};

// ??0BfmeOwnCA@@QAE@XZ
BfmeOwnCA::BfmeOwnCA(void)
{
	m_bfmeMidCA0 = 0;
	m_bfmeMidCA1 = 0;

	UnicodeString *self = &m_bfmeName;
	UnicodeString name("TheFontLibrary");
	self->set(name);
	name.BFMERetailAsciiString::releaseBuffer();
}
