class Rva006DAA70Accessor
{
public:
	int value() const;

private:
	char m_padding[4];
	int m_value;
};

int Rva006DAA70Accessor::value() const
{
	return m_value;
}

class Rva006DAA80Accessor
{
public:
	int value() const;

private:
	char m_padding[0x14];
	int m_value;
};

int Rva006DAA80Accessor::value() const
{
	return m_value;
}

class Rva006DAA90Accessor
{
public:
	int value() const;

private:
	char m_padding[0x1c];
	int m_value;
};

int Rva006DAA90Accessor::value() const
{
	return m_value;
}

class Rva006DAAA0Accessor
{
public:
	int value() const;

private:
	char m_padding[0x14];
	int m_value;
};

int Rva006DAAA0Accessor::value() const
{
	return m_value;
}

class Rva006DAAB0Accessor
{
public:
	unsigned char value() const;

private:
	char m_padding[0x44];
	unsigned char m_value;
};

unsigned char Rva006DAAB0Accessor::value() const
{
	return m_value;
}

class Rva006DAAC0Accessor
{
public:
	const char *address() const;

private:
	char m_padding[0x48];
	char m_value[1];
};

const char *Rva006DAAC0Accessor::address() const
{
	return m_value;
}

class Rva006DAAD0Accessor
{
public:
	float value() const;

private:
	char m_padding[0x54];
	float m_value;
};

float Rva006DAAD0Accessor::value() const
{
	return m_value;
}

class Rva006DAAE0Accessor
{
public:
	int value() const;

private:
	char m_padding[4];
	int m_value;
};

int Rva006DAAE0Accessor::value() const
{
	return m_value;
}

class Rva006DAAF0Accessor
{
public:
	const char *address() const;

private:
	char m_padding[0x14];
	char m_value[1];
};

const char *Rva006DAAF0Accessor::address() const
{
	return m_value;
}

class Rva006DAB00Accessor
{
public:
	unsigned char value() const;

private:
	char m_padding[0x10];
	unsigned char m_value;
};

unsigned char Rva006DAB00Accessor::value() const
{
	return m_value;
}

void __stdcall rva_006dad70_noop(int)
{
}

class Rva006DAEA0Accessor
{
public:
	int value() const;

private:
	char m_padding[0x10];
	int m_value;
};

int Rva006DAEA0Accessor::value() const
{
	return m_value;
}

class Rva006DAEB0Accessor
{
public:
	int value() const;

private:
	char m_padding[0xc];
	int m_value;
};

int Rva006DAEB0Accessor::value() const
{
	return m_value;
}

class Rva006DAEF0Accessor
{
public:
	int value() const;

private:
	char m_padding[4];
	int m_value;
};

int Rva006DAEF0Accessor::value() const
{
	return m_value;
}

class Rva006DAF00Identity
{
public:
	void *self();
};

void *Rva006DAF00Identity::self()
{
	return this;
}

int rva_006dafe0_identity(int value)
{
	return value;
}

class Rva006DB360Accessor
{
public:
	int value() const;

private:
	char m_padding[0x30];
	int m_value;
};

int Rva006DB360Accessor::value() const
{
	return m_value;
}

class Rva006DB580Accessor
{
public:
	int value() const;

private:
	char m_padding[4];
	int m_value;
};

int Rva006DB580Accessor::value() const
{
	return m_value;
}
