// cl: /DNDEBUG /MD /EHsc /O2
//
// Open-BFME5: retail 0x0039B560, 134 bytes. Multiple-inheritance destructor:
// first base SubsystemInterface (real class, dtor pinned at 0x009A1A40),
// second base BfmeBaseVUQ (the shared folded trivial base, 0x01073744).
// Members destruct in reverse declared order: a 5-element/8-byte-stride
// array at +0x28 via the eh-vector-destructor-iterator helper (element dtor
// pinned to the retail thunk address 0x00048D42), a BFMERetailAsciiString at
// +0x1C, then a pinned "still a dump" member at +0x18
// (AttributeModifierAuraUpdateModuleDataMemberC, already pinned at
// 0x0001A401), before the two base subobjects unwind.

class BfmeBaseVUQ
{
public:
	virtual ~BfmeBaseVUQ() { }
};

class SubsystemInterface
{
public:
	virtual ~SubsystemInterface();                             ///< pinned 0x009A1A40

private:
	unsigned int m_pad04;
};

template <typename T>
class StringBase
{
public:
	~StringBase()
	{
		releaseBuffer();
	}

	void *m_data;

private:
	void releaseBuffer();
};

class BFMERetailAsciiString : private StringBase<char>
{
public:
	~BFMERetailAsciiString() { }
};

class AttributeModifierAuraUpdateModuleDataMemberC
{
public:
	~AttributeModifierAuraUpdateModuleDataMemberC();            ///< pinned 0x0001A401

private:
	unsigned int m_body;
};

class Rva0039B560Element
{
public:
	~Rva0039B560Element();                                      ///< pinned to retail thunk 0x00048D42

private:
	unsigned int m_words[2];
};

class Rva0039B560 : public SubsystemInterface, public BfmeBaseVUQ
{
public:
	~Rva0039B560();

private:
	unsigned char m_pad0C[0x18 - 0xC];                          ///< +0x0C, untouched by this body
	AttributeModifierAuraUpdateModuleDataMemberC m_memberC;     ///< +0x18
	BFMERetailAsciiString m_str;                                ///< +0x1C
	unsigned char m_pad20[0x28 - 0x20];                         ///< +0x20, untouched by this body
	Rva0039B560Element m_array[5];                              ///< +0x28
};

// @??1Rva0039B560@@UAE@XZ 0x0039B560
Rva0039B560::~Rva0039B560()
{
}
