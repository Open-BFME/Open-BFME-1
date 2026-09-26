// cl: /DNDEBUG /MD /EHsc /O2

class Rva0078AFC0Ref
{
public:
	virtual void bfmeReleaseFinal(void);
	int m_references;
};

class Rva0078AFC0Owned
{
public:
	void bfmeDestroy(void);
};

class Rva0078AFC0OwnedPtr
{
public:
	~Rva0078AFC0OwnedPtr()
	{
		Rva0078AFC0Owned *pointer = m_pointer;
		if (pointer != 0)
			pointer->bfmeDestroy();
	}

	Rva0078AFC0Owned *m_pointer;
};

class Rva0078AFC0RefPtr
{
public:
	~Rva0078AFC0RefPtr()
	{
		Rva0078AFC0Ref *pointer = m_pointer;
		if (pointer != 0) {
			if (--pointer->m_references == 0)
				pointer->bfmeReleaseFinal();
			m_pointer = 0;
		}
	}

	Rva0078AFC0Ref *m_pointer;
};

class Rva0078AFC0Holder
{
public:
	~Rva0078AFC0Holder();

	void *m_table;
	Rva0078AFC0OwnedPtr m_owned;
	char m_pad08[0xc8];
	Rva0078AFC0RefPtr m_reference;
};

// @??1Rva0078AFC0Holder@@QAE@XZ 0x0078AFC0
Rva0078AFC0Holder::~Rva0078AFC0Holder()
{
}
