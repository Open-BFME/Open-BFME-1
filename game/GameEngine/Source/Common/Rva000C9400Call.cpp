// cl: /O2 /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD

class Rva000C9400S00
{
public:
	virtual void s00();
};

class Rva000C9400S04 : public Rva000C9400S00
{
public:
	virtual void s04();
};

class Rva000C9400S08 : public Rva000C9400S04
{
public:
	virtual void s08();
};

class Rva000C9400S0C : public Rva000C9400S08
{
public:
	virtual void s0C();
};

class Rva000C9400Pointee : public Rva000C9400S0C
{
public:
	virtual void dispatch(int, int, int, int);
};

class Rva000C9400
{
	char m_pad[0x220];
	Rva000C9400Pointee *m_pointee;

public:
	void call(int a, int b, int c, int d);
};

void Rva000C9400::call(int a, int b, int c, int d)
{
	if (m_pointee)
		m_pointee->dispatch(a, b, c, d);
}
