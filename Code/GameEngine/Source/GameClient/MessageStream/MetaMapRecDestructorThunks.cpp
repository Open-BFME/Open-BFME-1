// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: MetaMapRec dtor. dual CountUpBuffer @+0x1c/+0x20.

void __cdecl operator delete(void *block) throw();

class CountUpBuffer
{
public:
	~CountUpBuffer();
private:
	unsigned char m_pad[4];
};

class MetaMapRec
{
public:
	~MetaMapRec();
	void *destroyAndMaybeDelete(unsigned int flags);
private:
	unsigned char m_gap[0x1c];
	CountUpBuffer m_a;
	CountUpBuffer m_b;
};

// ??1MetaMapRec@@QAE@XZ
MetaMapRec::~MetaMapRec()
{
}

// ??_GMetaMapRec@@QAEPAXI@Z
void *MetaMapRec::destroyAndMaybeDelete(unsigned int flags)
{
	this->~MetaMapRec();
	if (flags & 1)
		::operator delete(this);
	return this;
}
