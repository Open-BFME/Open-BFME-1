// cl: /O2
// A lazily allocated one-pointer holder.  Retail retains the incoming texture
// before releasing the old one, so assigning a holder to itself is safe.

// Retail releases through the shared counted-texture base leaf
// ?Release_Ref@TextureBaseClass@@QAEXXZ (0x009EB7A0); only the refcount word
// at +4 is touched here, so this keeps the address-derived holder layout.
class TextureBaseClass
{
public:
	void Release_Ref();
	char m_padding[4];
	unsigned short m_references;
};

struct Rva005D2330TextureRef
{
	Rva005D2330TextureRef() : m_value(0) {}
	Rva005D2330TextureRef &operator=(const Rva005D2330TextureRef &source)
	{
		if (source.m_value)
		{
			++source.m_value->m_references;
		}
		if (m_value)
		{
			m_value->Release_Ref();
		}
		m_value = source.m_value;
		return *this;
	}

	TextureBaseClass *m_value;
};

class Rva005D2330TextureRefOwner
{
public:
	void assign(const Rva005D2330TextureRef &source);

private:
	char m_padding[0x2c];
	Rva005D2330TextureRef *m_holder;
};

void Rva005D2330TextureRefOwner::assign(const Rva005D2330TextureRef &source)
{
	if (!m_holder)
	{
		m_holder = new Rva005D2330TextureRef;
	}
	*m_holder = source;
}
