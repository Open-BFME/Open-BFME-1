// Retail 0x0063A7A0-0x0063B1E0 contains address-derived tiny accessors.
// Their owners and semantic field types remain unproven.

class Rva0063A7A0FieldAddress
{
public:
	char *get();

	char m_lead[ 4 ];
	char m_value;
};

// ?get@Rva0063A7A0FieldAddress@@QAEPADXZ
char *Rva0063A7A0FieldAddress::get()
{
	return &m_value;
}

class Rva0063A7C0ByteField
{
public:
	unsigned char get() const;

	char m_lead[ 0x51 ];
	unsigned char m_value;
};

// ?get@Rva0063A7C0ByteField@@QBEEXZ
unsigned char Rva0063A7C0ByteField::get() const
{
	return m_value;
}

class Rva0063A7E0DwordField
{
public:
	unsigned int get() const;

	char m_lead[ 0x54 ];
	unsigned int m_value;
};

// ?get@Rva0063A7E0DwordField@@QBEIXZ
unsigned int Rva0063A7E0DwordField::get() const
{
	return m_value;
}

class Rva0063A890DwordField
{
public:
	unsigned int get() const;

	char m_lead[ 0x64 ];
	unsigned int m_value;
};

// ?get@Rva0063A890DwordField@@QBEIXZ
unsigned int Rva0063A890DwordField::get() const
{
	return m_value;
}

class Rva0063AAF0DwordGetter
{
public:
	unsigned int get() const;

	unsigned int m_value;
};

// ?get@Rva0063AAF0DwordGetter@@QBEIXZ
unsigned int Rva0063AAF0DwordGetter::get() const
{
	return m_value;
}

class Rva0063AB30Identity
{
public:
	Rva0063AB30Identity *get();
};

// ?get@Rva0063AB30Identity@@QAEPAV1@XZ
Rva0063AB30Identity *Rva0063AB30Identity::get()
{
	return this;
}

class Rva0063AB80Identity
{
public:
	Rva0063AB80Identity *get();
};

// ?get@Rva0063AB80Identity@@QAEPAV1@XZ
Rva0063AB80Identity *Rva0063AB80Identity::get()
{
	return this;
}

class Rva0063ABE0DwordGetter
{
public:
	unsigned int get() const;

	unsigned int m_value;
};

// ?get@Rva0063ABE0DwordGetter@@QBEIXZ
unsigned int Rva0063ABE0DwordGetter::get() const
{
	return m_value;
}

class Rva0063AE00False
{
public:
	bool get() const;
};

// ?get@Rva0063AE00False@@QBE_NXZ
bool Rva0063AE00False::get() const
{
	return false;
}

class Rva0063AEE0False
{
public:
	bool get() const;
};

// ?get@Rva0063AEE0False@@QBE_NXZ
bool Rva0063AEE0False::get() const
{
	return false;
}

class Rva0063AEF0False
{
public:
	bool get() const;
};

// ?get@Rva0063AEF0False@@QBE_NXZ
bool Rva0063AEF0False::get() const
{
	return false;
}

class Rva0063AF00False
{
public:
	bool get() const;
};

// ?get@Rva0063AF00False@@QBE_NXZ
bool Rva0063AF00False::get() const
{
	return false;
}

class Rva0063AF80False
{
public:
	bool get() const;
};

// ?get@Rva0063AF80False@@QBE_NXZ
bool Rva0063AF80False::get() const
{
	return false;
}

class Rva0063B1E0DwordGetter
{
public:
	unsigned int get() const;

	unsigned int m_value;
};

// ?get@Rva0063B1E0DwordGetter@@QBEIXZ
unsigned int Rva0063B1E0DwordGetter::get() const
{
	return m_value;
}
