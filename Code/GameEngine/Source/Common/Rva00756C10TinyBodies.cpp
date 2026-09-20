// Address-derived owners for complete tiny carved bodies.
// The declarations preserve only the ABI and field widths witnessed by retail.

class Rva00756C10Address
{
public:
	char *get();

private:
	char m_padding[0x18];
	char m_value;
};

// ?get@Rva00756C10Address@@QAEPADXZ
char *Rva00756C10Address::get()
{
	return &m_value;
}

class Rva00756C30ByteField
{
public:
	unsigned char get();

private:
	char m_padding[0x24];
	unsigned char m_value;
};

// ?get@Rva00756C30ByteField@@QAEEXZ
unsigned char Rva00756C30ByteField::get()
{
	return m_value;
}

class Rva00756C40FloatField
{
public:
	float get() const;

private:
	char m_padding[0x3C];
	float m_value;
};

// ?get@Rva00756C40FloatField@@QBEMXZ
float Rva00756C40FloatField::get() const
{
	return m_value;
}

class Rva00756D20Self
{
public:
	Rva00756D20Self *identity();
};

// ?identity@Rva00756D20Self@@QAEPAV1@XZ
Rva00756D20Self *Rva00756D20Self::identity()
{
	return this;
}

class Rva00756E30DwordField
{
public:
	int get() const;

private:
	char m_padding[4];
	int m_value;
};

// ?get@Rva00756E30DwordField@@QBEHXZ
int Rva00756E30DwordField::get() const
{
	return m_value;
}

class Rva00757B70Body
{
public:
	void body(int value);
};

// ?body@Rva00757B70Body@@QAEXH@Z
void Rva00757B70Body::body(int value)
{
}

class Rva00757B80Body
{
public:
	void body(int value);
};

// ?body@Rva00757B80Body@@QAEXH@Z
void Rva00757B80Body::body(int value)
{
}

class Rva00757B90Body
{
public:
	void body(int first, int second, int third);
};

// ?body@Rva00757B90Body@@QAEXHHH@Z
void Rva00757B90Body::body(int first, int second, int third)
{
}

class Rva00757BB0ByteConstant
{
public:
	unsigned char value() const;
};

// ?value@Rva00757BB0ByteConstant@@QBEEXZ
unsigned char Rva00757BB0ByteConstant::value() const
{
	return 1;
}

class Rva00758540Body
{
public:
	void body(int value);
};

// ?body@Rva00758540Body@@QAEXH@Z
void Rva00758540Body::body(int value)
{
}

class Rva00759300Body
{
public:
	void body(int value);
};

// ?body@Rva00759300Body@@QAEXH@Z
void Rva00759300Body::body(int value)
{
}

class Rva00759330Body
{
public:
	void body(int value);
};

// ?body@Rva00759330Body@@QAEXH@Z
void Rva00759330Body::body(int value)
{
}

class Rva00759450DwordField
{
public:
	int get() const;

private:
	char m_padding[4];
	int m_value;
};

// ?get@Rva00759450DwordField@@QBEHXZ
int Rva00759450DwordField::get() const
{
	return m_value;
}

class Rva00759840DwordField
{
public:
	int get() const;

private:
	char m_padding[4];
	int m_value;
};

// ?get@Rva00759840DwordField@@QBEHXZ
int Rva00759840DwordField::get() const
{
	return m_value;
}

class Rva00759F20Self
{
public:
	Rva00759F20Self *identity();
};

// ?identity@Rva00759F20Self@@QAEPAV1@XZ
Rva00759F20Self *Rva00759F20Self::identity()
{
	return this;
}

class Rva0075AF40DwordField
{
public:
	int get() const;

private:
	char m_padding[0x68];
	int m_value;
};

// ?get@Rva0075AF40DwordField@@QBEHXZ
int Rva0075AF40DwordField::get() const
{
	return m_value;
}

class Rva0075B170ByteField
{
public:
	void set(unsigned char value);

private:
	char m_padding[0x1AB];
	unsigned char m_value;
};

// ?set@Rva0075B170ByteField@@QAEXE@Z
void Rva0075B170ByteField::set(unsigned char value)
{
	m_value = value;
}

class Rva0075B1E0FloatField
{
public:
	float get() const;

private:
	char m_padding[0x0C];
	float m_value;
};

// ?get@Rva0075B1E0FloatField@@QBEMXZ
float Rva0075B1E0FloatField::get() const
{
	return m_value;
}

class Rva0075B1F0FloatField
{
public:
	float get() const;

private:
	char m_padding[0x10];
	float m_value;
};

// ?get@Rva0075B1F0FloatField@@QBEMXZ
float Rva0075B1F0FloatField::get() const
{
	return m_value;
}

class Rva0075B7F0Body
{
public:
	void body(int first, int second, int third);
};

// ?body@Rva0075B7F0Body@@QAEXHHH@Z
void Rva0075B7F0Body::body(int first, int second, int third)
{
}

class Rva0075B860Body
{
public:
	void body(int value);
};

// ?body@Rva0075B860Body@@QAEXH@Z
void Rva0075B860Body::body(int value)
{
}

class Rva0075B8A0IntConstant
{
public:
	int value() const;
};

// ?value@Rva0075B8A0IntConstant@@QBEHXZ
int Rva0075B8A0IntConstant::value() const
{
	return 0;
}

class Rva0075B900ByteField
{
public:
	unsigned char get() const;

private:
	char m_padding[0x30];
	unsigned char m_value;
};

// ?get@Rva0075B900ByteField@@QBEEXZ
unsigned char Rva0075B900ByteField::get() const
{
	return m_value;
}

class Rva0075C890Body
{
public:
	void body(int first, int second, int third);
};

// ?body@Rva0075C890Body@@QAEXHHH@Z
void Rva0075C890Body::body(int first, int second, int third)
{
}

class Rva0075E500Self
{
public:
	Rva0075E500Self *identity();
};

// ?identity@Rva0075E500Self@@QAEPAV1@XZ
Rva0075E500Self *Rva0075E500Self::identity()
{
	return this;
}
