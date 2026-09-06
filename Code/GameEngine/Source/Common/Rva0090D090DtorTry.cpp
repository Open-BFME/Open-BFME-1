// ??1Rva0090D090@@UAE@XZ
// experiment: reuse twin's exact base-class shape (9-slot vtable + virtual
// dtor) instead of the simpler BfmeThingUB placeholder, to test whether the
// richer base layout is what gives retail's push-ecx/push-esi 2-word frame.
// cl: /DNDEBUG /MD /EHsc

class StringClass
{
public:
	~StringClass();
	char *m_buffer;
};

class Rva009EB810TailBase
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0C();
	virtual void slot10();
	virtual void slot14();
	virtual void slot18();
	virtual void slot1C();
	virtual void slot20();
	virtual ~Rva009EB810TailBase();

private:
	char m_pad[0x10];
};

class Rva0090D090Owned
{
public:
	virtual void slot0();
	virtual void slot1(int);
};

class Rva0090D090 : public Rva009EB810TailBase
{
public:
	virtual ~Rva0090D090();

private:
	Rva0090D090Owned *m_owned;
	StringClass m_str;
};

// ?d_0090d090@@YAXXZ
Rva0090D090::~Rva0090D090()
{
	if (m_owned)
		m_owned->slot1(1);
}
