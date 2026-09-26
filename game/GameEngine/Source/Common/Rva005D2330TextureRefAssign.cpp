// cl: /O2
// A lazily allocated one-pointer holder.  Retail retains the incoming texture
// before releasing the old one, so assigning a holder to itself is safe.

class BfmeSharedBlock
{
public:
	void bfmeRelease();
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
			m_value->bfmeRelease();
		}
		m_value = source.m_value;
		return *this;
	}

	BfmeSharedBlock *m_value;
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
