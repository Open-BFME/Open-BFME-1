// W3DDisplay vtable slot 26 contains ILT 0x0000E88B, which routes here.
// The slot has no proven semantic name, so this method keeps its RVA token.
// The Ghidra boundary and RET at +0x98 establish the 153-byte extent.

class TextureClass
{
public:
	void Add_Ref();
	void Release_Ref();
};

class TextureReference006ECFE0
{
public:
	__forceinline TextureReference006ECFE0() : m_texture(0) {}
	__forceinline ~TextureReference006ECFE0()
	{
		if (m_texture != 0)
			m_texture->Release_Ref();
	}

	TextureReference006ECFE0 &operator=(const TextureReference006ECFE0 &other)
	{
		if (other.m_texture)
			other.m_texture->Add_Ref();
		if (m_texture)
			m_texture->Release_Ref();
		m_texture = other.m_texture;
		return *this;
	}

	__forceinline operator TextureClass *() const { return m_texture; }
	TextureClass *m_texture;
};

class Render2DClass
{
public:
	void Reset();

	void set(const TextureReference006ECFE0 &texture)
	{
		if (m_texture.m_texture != texture.m_texture)
		{
			m_texture = texture;
			m_currentBatch = m_texture ? -1 : 0;
		}
	}

	unsigned char m_unmodeled[0x4c];
	TextureReference006ECFE0 m_texture;
	int m_currentBatch;
};

class ItemSlot11At006ECFE0
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual void slot10();
	virtual void slot11();
};

// The second fastcall register carries this same table pointer in EDX.
typedef void (__fastcall *Rva006ECFE0Slot11)(ItemSlot11At006ECFE0 *, void *);

class W3DDisplay
{
public:
	virtual void slot00() = 0;
	virtual void slot01() = 0;
	virtual void slot02() = 0;
	virtual void slot03() = 0;
	virtual void slot04() = 0;
	virtual void slot05() = 0;
	virtual void slot06() = 0;
	virtual void slot07() = 0;
	virtual void slot08() = 0;
	virtual void slot09() = 0;
	virtual void slot10() = 0;
	virtual void slot11() = 0;
	virtual void slot12() = 0;
	virtual void slot13() = 0;
	virtual void slot14() = 0;
	virtual void slot15() = 0;
	virtual void slot16() = 0;
	virtual void slot17() = 0;
	virtual void slot18() = 0;
	virtual void slot19() = 0;
	virtual void slot20() = 0;
	virtual void slot21() = 0;
	virtual void slot22() = 0;
	virtual void slot23() = 0;
	virtual void slot24() = 0;
	virtual void slot25() = 0;
	virtual void rva006ECFE0();

	unsigned char m_unmodeled_004[0x160];
	Render2DClass *m_render2D;
	unsigned char m_unmodeled2[0x134];
	ItemSlot11At006ECFE0 **m_begin;
	ItemSlot11At006ECFE0 **m_end;
};

void W3DDisplay::rva006ECFE0()
{
	m_render2D->set(TextureReference006ECFE0());
	m_render2D->Reset();

	for (ItemSlot11At006ECFE0 **p = m_begin; p != m_end; p++)
	{
		ItemSlot11At006ECFE0 *item = *p;
		void **table = *(void ***)item;
		((Rva006ECFE0Slot11)table[11])(item, table);
	}
}
