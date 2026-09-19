// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// Leaf accessors at carved boundaries 0x003BC4F0 through 0x003BC820.

class Rva003BC4F0DwordField
{
public:
	int get() const;

private:
	char m_before[0x4];
	int m_value;
};

int Rva003BC4F0DwordField::get() const
{
	return m_value;
}

class Rva003BC520FieldAddress
{
public:
	void *address();

private:
	char m_before[0x8];
	char m_value;
};

void *Rva003BC520FieldAddress::address()
{
	return &m_value;
}

class Rva003BC540FieldAddress
{
public:
	void *address();

private:
	char m_before[0x40];
	char m_value;
};

void *Rva003BC540FieldAddress::address()
{
	return &m_value;
}

class Rva003BC550ByteField
{
public:
	unsigned char get() const;

private:
	char m_before[0x44];
	unsigned char m_value;
};

unsigned char Rva003BC550ByteField::get() const
{
	return m_value;
}

class Rva003BC560ByteField
{
public:
	unsigned char get() const;

private:
	char m_before[0x1E];
	unsigned char m_value;
};

unsigned char Rva003BC560ByteField::get() const
{
	return m_value;
}

class Rva003BC580ByteField
{
public:
	unsigned char get() const;

private:
	char m_before[0x18];
	unsigned char m_value;
};

unsigned char Rva003BC580ByteField::get() const
{
	return m_value;
}

class Rva003BC590ByteField
{
public:
	unsigned char get() const;

private:
	char m_before[0x50];
	unsigned char m_value;
};

unsigned char Rva003BC590ByteField::get() const
{
	return m_value;
}

class Rva003BC5B0FieldAddress
{
public:
	void *address();

private:
	char m_before[0x60];
	char m_value;
};

void *Rva003BC5B0FieldAddress::address()
{
	return &m_value;
}

class Rva003BC660DwordField
{
public:
	int get() const;

private:
	char m_before[0x8];
	int m_value;
};

int Rva003BC660DwordField::get() const
{
	return m_value;
}

class Rva003BC670DwordField
{
public:
	int get() const;

private:
	char m_before[0x34];
	int m_value;
};

int Rva003BC670DwordField::get() const
{
	return m_value;
}

class Rva003BC700DwordField
{
public:
	int get() const;

private:
	char m_before[0x4];
	int m_value;
};

int Rva003BC700DwordField::get() const
{
	return m_value;
}

class Rva003BC710ByteField
{
public:
	unsigned char get() const;

private:
	char m_before[0x8];
	unsigned char m_value;
};

unsigned char Rva003BC710ByteField::get() const
{
	return m_value;
}

class Rva003BC720DwordField
{
public:
	int get() const;

private:
	char m_before[0x8];
	int m_value;
};

int Rva003BC720DwordField::get() const
{
	return m_value;
}

class Rva003BC730ThisAccessor
{
public:
	int value() const;
};

int Rva003BC730ThisAccessor::value() const
{
	return (int)this;
}

class Rva003BC740FieldAddress
{
public:
	void *address();

private:
	char m_before[0xC];
	char m_value;
};

void *Rva003BC740FieldAddress::address()
{
	return &m_value;
}

class Rva003BC7E0ByteField
{
public:
	unsigned char get() const;

private:
	char m_before[0x44];
	unsigned char m_value;
};

unsigned char Rva003BC7E0ByteField::get() const
{
	return m_value;
}

class Rva003BC800ByteField
{
public:
	unsigned char get() const;

private:
	char m_before[0x1C];
	unsigned char m_value;
};

unsigned char Rva003BC800ByteField::get() const
{
	return m_value;
}

class Rva003BC820ByteField
{
public:
	unsigned char get() const;

private:
	char m_before[0x78];
	unsigned char m_value;
};

unsigned char Rva003BC820ByteField::get() const
{
	return m_value;
}
