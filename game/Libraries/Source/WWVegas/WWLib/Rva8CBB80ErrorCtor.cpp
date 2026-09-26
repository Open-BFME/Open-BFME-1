// ??0Rva8CBB80Derived@@QAE@XZ
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

class Rva899F00Base
{
public:
	Rva899F00Base(const char *id, int kind);
	virtual ~Rva899F00Base();

private:
	char _bfme_base_slice[0x1c];
};

class BfmeStrVKI
{
public:
	BfmeStrVKI()
	{
		bfmeSetVKI("Error");
	}
	~BfmeStrVKI();
	void bfmeSetVKI(const char *s);

private:
	void *m_data;
};

class Rva8CBB80Derived : public Rva899F00Base
{
public:
	Rva8CBB80Derived();

private:
	BfmeStrVKI m_first;
	BfmeStrVKI m_second;
};

Rva8CBB80Derived::Rva8CBB80Derived() :
	Rva899F00Base(reinterpret_cast<const char *>(0x29), 8),
	m_first(),
	m_second()
{
}
