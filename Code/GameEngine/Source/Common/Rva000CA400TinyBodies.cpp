// These carved leaf bodies are reached only through anonymous thunks. Their
// names therefore describe the proven instruction behavior and keep each RVA.
void Rva000CA400Noop() {}
void Rva000CA410Noop() {}

class Rva000CA420Self
{
public:
	void *getSelf();
};

void *Rva000CA420Self::getSelf()
{
	return this;
}

void Rva000CA430Noop() {}

class Rva000CA440DwordGetter
{
public:
	unsigned int get() const;

private:
	char m_padding[0x10];
	unsigned int m_value;
};

unsigned int Rva000CA440DwordGetter::get() const
{
	return m_value;
}

void Rva000CA470Noop() {}
void Rva000CA4A0Noop() {}

class Rva000CA4B0DwordGetter
{
public:
	unsigned int get() const;

private:
	char m_padding[0x10];
	unsigned int m_value;
};

unsigned int Rva000CA4B0DwordGetter::get() const
{
	return m_value;
}

class Rva000CA4C0Self
{
public:
	void *getSelf();
};

void *Rva000CA4C0Self::getSelf()
{
	return this;
}

void Rva000CA4D0Noop() {}
void Rva000CA4E0Noop() {}
