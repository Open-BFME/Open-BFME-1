// ??0Rva0039B450@@QAE@XZ
// partial score=0.75 date=2026-09-06
// cl: /DNDEBUG /MD /EHsc /O2
//
// Open-BFME5: retail 0x0039B450, 140 bytes. BfmeBaseVUQ CONSTRUCTOR family
// (paired with the already-landed sibling destructor at 0x0039B560, same
// layout): bases SubsystemInterface (ctor matched at 0x009A1A30) and
// BfmeBaseVUQ (shared trivial base, vtable 0x01073744); members an
// HRBMD_Buffer at +0x18 (ctor still a dump, pinned 0x0003747A), a
// BFMERetailAsciiString at +0x1C (default-constructed empty), and a
// 5-element/8-byte-stride array at +0x28 built through the eh-vector
// constructor iterator (??_L, element ctor pinned 0x0003C0BA, element dtor
// pinned 0x00048D42 for the exception unwind path -- the same address the
// landed destructor uses for that array's element destructor).

class BfmeBaseVUQ
{
public:
	virtual ~BfmeBaseVUQ() { }
};

class SubsystemInterface
{
public:
	SubsystemInterface();                                       ///< matched 0x009A1A30
	virtual ~SubsystemInterface();                               ///< pinned 0x009A1A40

private:
	unsigned int m_pad04;
};

class HRBMD_Buffer
{
public:
	HRBMD_Buffer();                                              ///< pinned 0x0003747A

private:
	unsigned int m_body;
};

template <typename T>
class StringBase
{
public:
	StringBase() : m_data(0) { }

	void *m_data;
};

class BFMERetailAsciiString : private StringBase<char>
{
public:
	BFMERetailAsciiString() { }
};

class Rva0039B450Element
{
public:
	Rva0039B450Element();                                        ///< pinned 0x0003C0BA
	~Rva0039B450Element();                                       ///< pinned 0x00048D42

private:
	unsigned int m_words[2];
};

class Rva0039B450 : public SubsystemInterface, public BfmeBaseVUQ
{
public:
	Rva0039B450();
	virtual ~Rva0039B450();

private:
	unsigned int m_at0C;
	unsigned int m_at10;
	unsigned int m_at14;
	HRBMD_Buffer m_buffer;                                       ///< +0x18
	BFMERetailAsciiString m_str;                                 ///< +0x1C
	unsigned int m_at20;
	unsigned int m_at24;                                         ///< +0x24, untouched by this ctor
	Rva0039B450Element m_array[5];                               ///< +0x28
};

// @??0Rva0039B450@@QAE@XZ 0x0039B450
Rva0039B450::Rva0039B450()
	: m_at0C(0)
	, m_at10(1)
	, m_at14(0)
	, m_at20(0)
{
}
