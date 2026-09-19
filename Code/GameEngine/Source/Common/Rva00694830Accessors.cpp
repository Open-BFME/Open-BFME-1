// The carved bodies have only anonymous thunk callers. Each type therefore
// keeps its RVA while expressing the field access proven by retail bytes.
class Rva00694830FloatField
{
public:
	float get() const;

private:
	char m_padding[0x24];
	float m_value;
};

float Rva00694830FloatField::get() const
{
	return m_value;
}

class Rva00694870FloatField
{
public:
	float get() const;

private:
	char m_padding[0x70];
	float m_value;
};

float Rva00694870FloatField::get() const
{
	return m_value;
}

class Rva006948B0DwordField
{
public:
	unsigned int get() const;

private:
	char m_padding[0x2C];
	unsigned int m_value;
};

unsigned int Rva006948B0DwordField::get() const
{
	return m_value;
}

class Rva006948C0FieldAddress
{
public:
	char *get();

private:
	char m_padding[8];
};

char *Rva006948C0FieldAddress::get()
{
	return m_padding + 8;
}

class Rva006948D0ByteField
{
public:
	unsigned char get() const;

private:
	char m_padding[0x42];
	unsigned char m_value;
};

unsigned char Rva006948D0ByteField::get() const
{
	return m_value;
}

class Rva00694910GuardedFieldAddress
{
public:
	char *get();

private:
	char *m_value;
};

char *Rva00694910GuardedFieldAddress::get()
{
	if (m_value != 0)
		return m_value + 8;
	return 0;
}
