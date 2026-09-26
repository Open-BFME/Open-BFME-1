// Address-derived leaf accessors from the 0x0014FED0-0x00150690 carved family.
// The bodies prove offsets and return widths, but no semantic owner or field names.

class Rva0014FED0FieldAddress
{
public:
	char *get();

private:
	char m_lead[0xC];
	char m_value;
};

// ?get@Rva0014FED0FieldAddress@@QAEPADXZ
char *Rva0014FED0FieldAddress::get()
{
	return &m_value;
}

class Rva0014FEE0DwordField
{
public:
	int get() const;

private:
	char m_lead[0x8];
	int m_value;
};

// ?get@Rva0014FEE0DwordField@@QBEHXZ
int Rva0014FEE0DwordField::get() const
{
	return m_value;
}

class Rva0014FEF0DwordField
{
public:
	int get() const;

private:
	char m_lead[0x4];
	int m_value;
};

// ?get@Rva0014FEF0DwordField@@QBEHXZ
int Rva0014FEF0DwordField::get() const
{
	return m_value;
}

class Rva0014FF00DwordField
{
public:
	int get() const;

private:
	char m_lead[0x8];
	int m_value;
};

// ?get@Rva0014FF00DwordField@@QBEHXZ
int Rva0014FF00DwordField::get() const
{
	return m_value;
}

class Rva00150030DwordField
{
public:
	int get() const;

private:
	char m_lead[0x21C];
	int m_value;
};

// ?get@Rva00150030DwordField@@QBEHXZ
int Rva00150030DwordField::get() const
{
	return m_value;
}

class Rva00150040ByteField
{
public:
	unsigned char get() const;

private:
	char m_lead[0x338];
	unsigned char m_value;
};

// ?get@Rva00150040ByteField@@QBEEXZ
unsigned char Rva00150040ByteField::get() const
{
	return m_value;
}

class Rva00150060ByteField
{
public:
	unsigned char get() const;

private:
	char m_lead[0x532];
	unsigned char m_value;
};

// ?get@Rva00150060ByteField@@QBEEXZ
unsigned char Rva00150060ByteField::get() const
{
	return m_value;
}

class Rva00150070DwordField
{
public:
	int get() const;

private:
	char m_lead[0x18];
	int m_value;
};

// ?get@Rva00150070DwordField@@QBEHXZ
int Rva00150070DwordField::get() const
{
	return m_value;
}

class Rva001501D0NoOp
{
public:
	void invoke(int first, int second, int third);
};

// ?invoke@Rva001501D0NoOp@@QAEXHHH@Z
void Rva001501D0NoOp::invoke(int first, int second, int third)
{
}

class Rva001501E0Constant
{
public:
	int get() const;
};

// ?get@Rva001501E0Constant@@QBEHXZ
int Rva001501E0Constant::get() const
{
	return -1;
}

class Rva00150230Self
{
public:
	void *getSelf();
};

// ?getSelf@Rva00150230Self@@QAEPAXXZ
void *Rva00150230Self::getSelf()
{
	return this;
}

class Rva00150270Offset
{
public:
	void *get() const;

private:
	void *m_value;
};

// ?get@Rva00150270Offset@@QBEPAXXZ
void *Rva00150270Offset::get() const
{
	return static_cast<char *>(m_value) + 8;
}

class Rva00150290DwordField
{
public:
	int get() const;

private:
	char m_lead[0x4];
	int m_value;
};

// ?get@Rva00150290DwordField@@QBEHXZ
int Rva00150290DwordField::get() const
{
	return m_value;
}

class Rva00150690DwordField
{
public:
	int get() const;

private:
	char m_lead[0x4];
	int m_value;
};

// ?get@Rva00150690DwordField@@QBEHXZ
int Rva00150690DwordField::get() const
{
	return m_value;
}
