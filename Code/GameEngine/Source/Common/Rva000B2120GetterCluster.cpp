// Three independently carved accessors reached only through anonymous ILT
// thunks. Their address-qualified types deliberately make no owner claim.

class Rva000B2120DwordField
{
public:
	int get() const;

private:
	char m_padding00[0x4C];
	int m_value;
};

int Rva000B2120DwordField::get() const
{
	return m_value;
}

class Rva000B2140DwordField
{
public:
	int get() const;

private:
	char m_padding00[0x6C];
	int m_value;
};

int Rva000B2140DwordField::get() const
{
	return m_value;
}

class Rva000B2150EmbeddedField
{
public:
	void *get();

private:
	char m_padding00[0x0C];
	char m_value;
};

void *Rva000B2150EmbeddedField::get()
{
	return &m_value;
}
