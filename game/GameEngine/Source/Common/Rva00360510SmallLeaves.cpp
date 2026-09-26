// Address-derived leaves recovered from carved boundaries.
// The owning types remain unknown because no caller or vtable proves them.
// Each body models only the operation shown by retail instructions.

// cl: /O2 /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD

class Rva00360510FloatField
{
	char m_pad[ 0x8 ];
	float m_value;

public:
	float get() const;
};

float Rva00360510FloatField::get() const
{
	return m_value;
}

class Rva00360520DwordField
{
	char m_pad[ 0xC ];
	unsigned int m_value;

public:
	unsigned int get() const;
};

unsigned int Rva00360520DwordField::get() const
{
	return m_value;
}

class Rva00360570DwordField
{
	char m_pad[ 0x34 ];
	unsigned int m_value;

public:
	unsigned int get() const;
};

unsigned int Rva00360570DwordField::get() const
{
	return m_value;
}

class Rva00360580ByteField
{
	char m_pad[ 0x38 ];
	unsigned char m_value;

public:
	unsigned char get() const;
};

unsigned char Rva00360580ByteField::get() const
{
	return m_value;
}

class Rva00360590DwordField
{
	char m_pad[ 0x3C ];
	unsigned int m_value;

public:
	unsigned int get() const;
};

unsigned int Rva00360590DwordField::get() const
{
	return m_value;
}

class Rva003605A0DwordField
{
	char m_pad[ 0x44 ];
	unsigned int m_value;

public:
	unsigned int get() const;
};

unsigned int Rva003605A0DwordField::get() const
{
	return m_value;
}

class Rva003605B0DwordField
{
	char m_pad[ 0x48 ];
	unsigned int m_value;

public:
	unsigned int get() const;
};

unsigned int Rva003605B0DwordField::get() const
{
	return m_value;
}

class Rva003605F0FieldAddress
{
	char m_pad[ 0x78 ];
	char m_value;

public:
	char *get();
};

char *Rva003605F0FieldAddress::get()
{
	return &m_value;
}

class Rva00360620FieldAddress
{
	char m_pad[ 0x7C ];
	char m_value;

public:
	char *get();
};

char *Rva00360620FieldAddress::get()
{
	return &m_value;
}

class Rva00360660ByteField
{
	char m_pad[ 0x8 ];
	unsigned char m_value;

public:
	unsigned char get() const;
};

unsigned char Rva00360660ByteField::get() const
{
	return m_value;
}

class Rva003606A0DwordField
{
	char m_pad[ 0x24 ];
	unsigned int m_value;

public:
	unsigned int get() const;
};

unsigned int Rva003606A0DwordField::get() const
{
	return m_value;
}

class Rva003606B0FieldAddress
{
	char m_pad[ 0x48 ];
	char m_value;

public:
	char *get();
};

char *Rva003606B0FieldAddress::get()
{
	return &m_value;
}

class Rva003606D0FieldAddress
{
	char m_pad[ 0x30 ];
	char m_value;

public:
	char *get();
};

char *Rva003606D0FieldAddress::get()
{
	return &m_value;
}

class Rva00360750FieldAddress
{
	char m_pad[ 0x234 ];
	char m_value;

public:
	char *get();
};

char *Rva00360750FieldAddress::get()
{
	return &m_value;
}

class Rva00360A30DwordField
{
	unsigned int m_value;

public:
	unsigned int get() const;
};

unsigned int Rva00360A30DwordField::get() const
{
	return m_value;
}

class Rva00360A60DwordField
{
	char m_pad[ 0x4 ];
	unsigned int m_value;

public:
	unsigned int get() const;
};

unsigned int Rva00360A60DwordField::get() const
{
	return m_value;
}

class Rva00360B90
{
public:
	Rva00360B90 *self();
};

Rva00360B90 *Rva00360B90::self()
{
	return this;
}

class Rva00360BB0DwordField
{
	unsigned int m_value;

public:
	unsigned int get() const;
};

unsigned int Rva00360BB0DwordField::get() const
{
	return m_value;
}

class Rva00360BC0DwordField
{
	unsigned int m_value;

public:
	unsigned int get() const;
};

unsigned int Rva00360BC0DwordField::get() const
{
	return m_value;
}

bool Rva00360D50False()
{
	return false;
}

bool Rva00360D70False()
{
	return false;
}

bool Rva00360E30False()
{
	return false;
}

bool Rva00360EA0False()
{
	return false;
}
