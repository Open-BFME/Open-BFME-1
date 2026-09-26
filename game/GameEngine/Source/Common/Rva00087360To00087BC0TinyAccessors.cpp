// cl: /DNDEBUG /MD /O2 /Ob0

// Each body is an address-derived leaf. The decoded offsets prove the access shape, not an owner name.

struct Rva00087360DwordGetter
{
	char m_pad[4];
	unsigned int m_value;

	unsigned int get(void) const;
};

// ?get@Rva00087360DwordGetter@@QBEIXZ
unsigned int Rva00087360DwordGetter::get(void) const
{
	return m_value;
}

struct Rva000873A0AddressGetter
{
	void *field(void) const;
};

// ?field@Rva000873A0AddressGetter@@QBEPAXXZ
void *Rva000873A0AddressGetter::field(void) const
{
	return reinterpret_cast<char *>(const_cast<Rva000873A0AddressGetter *>(this)) + 0x24;
}

struct Rva000873B0AddressGetter
{
	void *field(void) const;
};

// ?field@Rva000873B0AddressGetter@@QBEPAXXZ
void *Rva000873B0AddressGetter::field(void) const
{
	return reinterpret_cast<char *>(const_cast<Rva000873B0AddressGetter *>(this)) + 0x24;
}

struct Rva000873C0AddressGetter
{
	void *field(void) const;
};

// ?field@Rva000873C0AddressGetter@@QBEPAXXZ
void *Rva000873C0AddressGetter::field(void) const
{
	return reinterpret_cast<char *>(const_cast<Rva000873C0AddressGetter *>(this)) + 8;
}

struct Rva000873D0FloatGetter
{
	char m_pad[0x1c];
	float m_value;

	float get(void) const;
};

// ?get@Rva000873D0FloatGetter@@QBEMXZ
float Rva000873D0FloatGetter::get(void) const
{
	return m_value;
}

struct Rva00087510AddressGetter
{
	void *field(void) const;
};

// ?field@Rva00087510AddressGetter@@QBEPAXXZ
void *Rva00087510AddressGetter::field(void) const
{
	return reinterpret_cast<char *>(const_cast<Rva00087510AddressGetter *>(this)) + 8;
}

struct Rva00087840DwordGetter
{
	unsigned int m_value;

	unsigned int get(void) const;
};

// ?get@Rva00087840DwordGetter@@QBEIXZ
unsigned int Rva00087840DwordGetter::get(void) const
{
	return m_value;
}

struct Rva00087960DwordGetter
{
	unsigned int m_value;

	unsigned int get(void) const;
};

// ?get@Rva00087960DwordGetter@@QBEIXZ
unsigned int Rva00087960DwordGetter::get(void) const
{
	return m_value;
}

struct Rva00087970Self
{
	void *self(void);
};

// ?self@Rva00087970Self@@QAEPAXXZ
void *Rva00087970Self::self(void)
{
	return this;
}

// ?Rva00087B00False@@YA_NXZ
bool Rva00087B00False(void)
{
	return false;
}

// ?Rva00087B10False@@YA_NXZ
bool Rva00087B10False(void)
{
	return false;
}

struct Rva00087BA0AddressGetter
{
	void *field(void) const;
};

// ?field@Rva00087BA0AddressGetter@@QBEPAXXZ
void *Rva00087BA0AddressGetter::field(void) const
{
	return reinterpret_cast<char *>(const_cast<Rva00087BA0AddressGetter *>(this)) + 8;
}

struct Rva00087BB0AddressGetter
{
	void *field(void) const;
};

// ?field@Rva00087BB0AddressGetter@@QBEPAXXZ
void *Rva00087BB0AddressGetter::field(void) const
{
	return reinterpret_cast<char *>(const_cast<Rva00087BB0AddressGetter *>(this)) + 0x20;
}

struct Rva00087BC0AddressGetter
{
	void *field(void) const;
};

// ?field@Rva00087BC0AddressGetter@@QBEPAXXZ
void *Rva00087BC0AddressGetter::field(void) const
{
	return reinterpret_cast<char *>(const_cast<Rva00087BC0AddressGetter *>(this)) + 0x60;
}
