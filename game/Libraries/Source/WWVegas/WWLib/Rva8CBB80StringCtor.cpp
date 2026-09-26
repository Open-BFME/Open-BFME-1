// ??0Rva8CBB80Derived@@QAE@VBfmeStrVKI@@@Z
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// readable by-value string constructor, retail 0x008CBBF0 (131 bytes).

class Rva899F00Base
{
public:
	Rva899F00Base(const char *id, int kind);
	virtual ~Rva899F00Base();

private:
	char _bfme_base_slice[0x1c];
};

struct BfmeHdrVKI
{
	unsigned short m_count;
};

extern void (__cdecl **Rva01337A30ReleaseTable)(void *);

class BfmeStrVKI
{
public:
	BfmeStrVKI()
	{
		bfmeSetVKI("Error");
	}
	BfmeStrVKI(const BfmeStrVKI &other)
	{
		BfmeHdrVKI *data = other.m_data;
		m_data = data;
		++data->m_count;
	}
	~BfmeStrVKI()
	{
		BfmeHdrVKI *data = m_data;
		--data->m_count;
		if (data->m_count == 0)
			Rva01337A30ReleaseTable[1](data);
	}
	void bfmeSetVKI(const char *s);

private:
	BfmeHdrVKI *m_data;
};

class Rva8CBB80Derived : public Rva899F00Base
{
public:
	Rva8CBB80Derived(BfmeStrVKI name);

private:
	BfmeStrVKI m_first;
	BfmeStrVKI m_second;
};

Rva8CBB80Derived::Rva8CBB80Derived(BfmeStrVKI name) :
	Rva899F00Base(reinterpret_cast<const char *>(0x29), 8),
	m_first(name),
	m_second()
{
}
