// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD
// Tiny leaf accessors recovered from their complete retail extents.

class Rva000EC260DwordGetter
{
public:
	int get() const;

private:
	char m_pad[0x0C];
	int m_value;
};

int Rva000EC260DwordGetter::get() const
{
	return m_value;
}

class Rva000EC3C0DwordGetter
{
public:
	int get() const;

private:
	char m_pad[0x04];
	int m_value;
};

int Rva000EC3C0DwordGetter::get() const
{
	return m_value;
}

class Rva000EC3E0ByteGetter
{
public:
	unsigned char get() const;

private:
	char m_pad[0x31];
	unsigned char m_value;
};

unsigned char Rva000EC3E0ByteGetter::get() const
{
	return m_value;
}

class Rva000EC3F0AddressGetter
{
public:
	char *get();

private:
	char m_pad[0x10];
	char m_value;
};

char *Rva000EC3F0AddressGetter::get()
{
	return &m_value;
}

class Rva000EC640DwordGetter
{
public:
	int get() const;

private:
	char m_pad[0x28];
	int m_value;
};

int Rva000EC640DwordGetter::get() const
{
	return m_value;
}

class Rva000EC650DwordGetter
{
public:
	int get() const;

private:
	char m_pad[0x10];
	int m_value;
};

int Rva000EC650DwordGetter::get() const
{
	return m_value;
}

class Rva000EC660ByteGetter
{
public:
	unsigned char get() const;

private:
	char m_pad[0x14];
	unsigned char m_value;
};

unsigned char Rva000EC660ByteGetter::get() const
{
	return m_value;
}

class Rva000EC680ByteGetter
{
public:
	unsigned char get() const;

private:
	char m_pad[0x18];
	unsigned char m_value;
};

unsigned char Rva000EC680ByteGetter::get() const
{
	return m_value;
}

class Rva000EC690ByteGetter
{
public:
	unsigned char get() const;

private:
	char m_pad[0x19];
	unsigned char m_value;
};

unsigned char Rva000EC690ByteGetter::get() const
{
	return m_value;
}

class Rva000EC6A0ByteGetter
{
public:
	unsigned char get() const;

private:
	char m_pad[0x1A];
	unsigned char m_value;
};

unsigned char Rva000EC6A0ByteGetter::get() const
{
	return m_value;
}

class Rva000EC6B0DwordGetter
{
public:
	int get() const;

private:
	char m_pad[0x20];
	int m_value;
};

int Rva000EC6B0DwordGetter::get() const
{
	return m_value;
}

class Rva000EC720DwordGetter
{
public:
	int get() const;

private:
	char m_pad[0x1C];
	int m_value;
};

int Rva000EC720DwordGetter::get() const
{
	return m_value;
}

class Rva000EC730DwordGetter
{
public:
	int get() const;

private:
	char m_pad[0x04];
	int m_value;
};

int Rva000EC730DwordGetter::get() const
{
	return m_value;
}

class Rva000EC740AddressGetter
{
public:
	char *get();

private:
	char m_pad[0x0C];
	char m_value;
};

char *Rva000EC740AddressGetter::get()
{
	return &m_value;
}

class Rva000EC8E0FloatGetter
{
public:
	float get() const;

private:
	char m_pad[0x10];
	float m_value;
};

float Rva000EC8E0FloatGetter::get() const
{
	return m_value;
}

class Rva000ECAA0OffsetAddressGetter
{
public:
	char *get() const;

private:
	char *m_base;
};

char *Rva000ECAA0OffsetAddressGetter::get() const
{
	return m_base + 0x10;
}

class Rva000ECB50OffsetAddressGetter
{
public:
	char *get() const;

private:
	char *m_base;
};

char *Rva000ECB50OffsetAddressGetter::get() const
{
	return m_base + 0x08;
}

class Rva000ECB60AddressGetter
{
public:
	char *get() const;

private:
	char *m_base;
};

char *Rva000ECB60AddressGetter::get() const
{
	return m_base;
}

class Rva000ECB70AddressGetter
{
public:
	char *get();
};

char *Rva000ECB70AddressGetter::get()
{
	return (char *)this;
}

class Rva000ECBE0DwordGetter
{
public:
	int get() const;

private:
	char m_pad[0x04];
	int m_value;
};

int Rva000ECBE0DwordGetter::get() const
{
	return m_value;
}

class Rva000ECBF0IdentityGetter
{
public:
	char *get();
};

char *Rva000ECBF0IdentityGetter::get()
{
	return (char *)this;
}

class Rva000ECC20IdentityGetter
{
public:
	char *get();
};

char *Rva000ECC20IdentityGetter::get()
{
	return (char *)this;
}
