class Rva003C5E30FieldAddress
{
public:
	char *get() const;
};

char *Rva003C5E30FieldAddress::get() const
{
	return (char *)this + 0x8;
}

class Rva003C5E50FieldAddress
{
public:
	char *get() const;
};

char *Rva003C5E50FieldAddress::get() const
{
	return (char *)this + 0x28;
}

class Rva003C5E60FieldAddress
{
public:
	char *get() const;
};

char *Rva003C5E60FieldAddress::get() const
{
	return (char *)this + 0x30;
}

class Rva003C5E70FieldAddress
{
public:
	char *get() const;
};

char *Rva003C5E70FieldAddress::get() const
{
	return (char *)this + 0x3C;
}

class Rva003C5E80ByteField
{
public:
	unsigned char get() const;

private:
	char m_padding[0x74];
	unsigned char m_value;
};

unsigned char Rva003C5E80ByteField::get() const
{
	return m_value;
}

class Rva003C5F10DwordSlot
{
public:
	void set(unsigned int value);

private:
	char m_padding[0xAC];
	unsigned int m_value;
};

void Rva003C5F10DwordSlot::set(unsigned int value)
{
	m_value = value;
}

class Rva003C5F60Identity
{
public:
	void *get() const;
};

void *Rva003C5F60Identity::get() const
{
	return (void *)this;
}

class Rva003C5F70FieldAddress
{
public:
	char *get() const;
};

char *Rva003C5F70FieldAddress::get() const
{
	return (char *)this + 0x4;
}

class Rva003C5F90FieldAddress
{
public:
	char *get() const;
};

char *Rva003C5F90FieldAddress::get() const
{
	return (char *)this + 0x10;
}

class Rva003C5FA0FieldAddress
{
public:
	char *get() const;
};

char *Rva003C5FA0FieldAddress::get() const
{
	return (char *)this + 0x14;
}

class Rva003C5FB0DwordField
{
public:
	int get() const;

private:
	char m_padding[0x18];
	int m_value;
};

int Rva003C5FB0DwordField::get() const
{
	return m_value;
}

class Rva003C5FC0DwordField
{
public:
	int get() const;

private:
	char m_padding[0x1C];
	int m_value;
};

int Rva003C5FC0DwordField::get() const
{
	return m_value;
}

class Rva003C5FD0FieldAddress
{
public:
	char *get() const;
};

char *Rva003C5FD0FieldAddress::get() const
{
	return (char *)this + 0x30;
}

class Rva003C5FE0RealField
{
public:
	float get() const;

private:
	char m_padding[0x8];
	float m_value;
};

float Rva003C5FE0RealField::get() const
{
	return m_value;
}

class Rva003C5FF0DwordField
{
public:
	int get() const;

private:
	char m_padding[0x3C];
	int m_value;
};

int Rva003C5FF0DwordField::get() const
{
	return m_value;
}

class Rva003C6000FieldAddress
{
public:
	char *get() const;
};

char *Rva003C6000FieldAddress::get() const
{
	return (char *)this + 0x20;
}

class Rva003C6010DwordField
{
public:
	int get() const;

private:
	char m_padding[0x4C];
	int m_value;
};

int Rva003C6010DwordField::get() const
{
	return m_value;
}

class Rva003C6020DwordField
{
public:
	int get() const;

private:
	char m_padding[0x50];
	int m_value;
};

int Rva003C6020DwordField::get() const
{
	return m_value;
}

class Rva003C6040FieldAddress
{
public:
	char *get() const;
};

char *Rva003C6040FieldAddress::get() const
{
	return (char *)this + 0x40;
}

class Rva003C6420Identity
{
public:
	void *get() const;
};

void *Rva003C6420Identity::get() const
{
	return (void *)this;
}

class Rva003C6450Identity
{
public:
	void *get() const;
};

void *Rva003C6450Identity::get() const
{
	return (void *)this;
}

class Rva003C6470DwordField
{
public:
	int get() const;

private:
	int m_value;
};

int Rva003C6470DwordField::get() const
{
	return m_value;
}

class Rva003C64C0DwordField
{
public:
	int get() const;

private:
	char m_padding[0x4];
	int m_value;
};

int Rva003C64C0DwordField::get() const
{
	return m_value;
}

class Rva003C6510Ret4
{
public:
	void reset(int ignored);
};

void Rva003C6510Ret4::reset(int ignored)
{
}

class Rva003C6550Identity
{
public:
	void *get() const;
};

void *Rva003C6550Identity::get() const
{
	return (void *)this;
}
