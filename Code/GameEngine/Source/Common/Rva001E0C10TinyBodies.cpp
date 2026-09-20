// cl: /O2
// Address-derived leaf bodies from the carved 0x001E0C10-0x001F03A0 batch.

class Rva001E0C10FloatField
{
public:
	float get(void) const;

	char m_padding[0x2C];
	float m_value;
};

// ?get@Rva001E0C10FloatField@@QBEMXZ
float Rva001E0C10FloatField::get(void) const
{
	return m_value;
}

class Rva001E0DE0DwordField
{
public:
	unsigned int get(void) const;

	char m_padding[0x30];
	unsigned int m_value;
};

// ?get@Rva001E0DE0DwordField@@QBEIXZ
unsigned int Rva001E0DE0DwordField::get(void) const
{
	return m_value;
}

class Rva001E1050ByteField
{
public:
	unsigned char get(void) const;

	char m_padding[0x54];
	unsigned char m_value;
};

// ?get@Rva001E1050ByteField@@QBEEXZ
unsigned char Rva001E1050ByteField::get(void) const
{
	return m_value;
}

class Rva001E1070DwordField
{
public:
	unsigned int get(void) const;

	char m_padding[0x70];
	unsigned int m_value;
};

// ?get@Rva001E1070DwordField@@QBEIXZ
unsigned int Rva001E1070DwordField::get(void) const
{
	return m_value;
}

class Rva001E1D60Self
{
public:
	Rva001E1D60Self *self(void);
};

// ?self@Rva001E1D60Self@@QAEPAV1@XZ
Rva001E1D60Self *Rva001E1D60Self::self(void)
{
	return this;
}

class Rva001E1DD0Self
{
public:
	Rva001E1DD0Self *self(void);
};

// ?self@Rva001E1DD0Self@@QAEPAV1@XZ
Rva001E1DD0Self *Rva001E1DD0Self::self(void)
{
	return this;
}

class Rva001E1E30Self
{
public:
	Rva001E1E30Self *self(void);
};

// ?self@Rva001E1E30Self@@QAEPAV1@XZ
Rva001E1E30Self *Rva001E1E30Self::self(void)
{
	return this;
}

// ?Rva001E1EA0Pop4@@YGXPAX@Z
void __stdcall Rva001E1EA0Pop4(void *)
{
}

class Rva001E1EB0DwordField
{
public:
	unsigned int get(void) const;

	unsigned int m_value;
};

// ?get@Rva001E1EB0DwordField@@QBEIXZ
unsigned int Rva001E1EB0DwordField::get(void) const
{
	return m_value;
}

class Rva001E1F30DwordField
{
public:
	unsigned int get(void) const;

	unsigned int m_value;
};

// ?get@Rva001E1F30DwordField@@QBEIXZ
unsigned int Rva001E1F30DwordField::get(void) const
{
	return m_value;
}

class Rva001EAB80DwordField
{
public:
	unsigned int get(void) const;

	char m_padding[0x4C];
	unsigned int m_value;
};

// ?get@Rva001EAB80DwordField@@QBEIXZ
unsigned int Rva001EAB80DwordField::get(void) const
{
	return m_value;
}

class Rva001EB020DwordField
{
public:
	unsigned int get(void) const;

	unsigned int m_value;
};

// ?get@Rva001EB020DwordField@@QBEIXZ
unsigned int Rva001EB020DwordField::get(void) const
{
	return m_value;
}

class Rva001EB030FieldAddress
{
public:
	char *get(void);

	char m_padding[4];
	char m_value;
};

// ?get@Rva001EB030FieldAddress@@QAEPADXZ
char *Rva001EB030FieldAddress::get(void)
{
	return &m_value;
}

class Rva001ECEE0DwordField
{
public:
	unsigned int get(void) const;

	char m_padding[4];
	unsigned int m_value;
};

// ?get@Rva001ECEE0DwordField@@QBEIXZ
unsigned int Rva001ECEE0DwordField::get(void) const
{
	return m_value;
}

class Rva001EE800False
{
public:
	bool value(void) const;
};

// ?value@Rva001EE800False@@QBE_NXZ
bool Rva001EE800False::value(void) const
{
	return false;
}

class Rva001EE8C0DwordField
{
public:
	unsigned int get(void) const;

	char m_padding[4];
	unsigned int m_value;
};

// ?get@Rva001EE8C0DwordField@@QBEIXZ
unsigned int Rva001EE8C0DwordField::get(void) const
{
	return m_value;
}

class Rva001EF460FloatField
{
public:
	float get(void) const;

	char m_padding[0x5C];
	float m_value;
};

// ?get@Rva001EF460FloatField@@QBEMXZ
float Rva001EF460FloatField::get(void) const
{
	return m_value;
}

class Rva001EF470FloatField
{
public:
	float get(void) const;

	char m_padding[0x60];
	float m_value;
};

// ?get@Rva001EF470FloatField@@QBEMXZ
float Rva001EF470FloatField::get(void) const
{
	return m_value;
}

class Rva001EF480ByteField
{
public:
	unsigned char get(void) const;

	char m_padding[0x64];
	unsigned char m_value;
};

// ?get@Rva001EF480ByteField@@QBEEXZ
unsigned char Rva001EF480ByteField::get(void) const
{
	return m_value;
}

class Rva001EF4E0IntFloat
{
public:
	float get(void) const;

	char m_padding[0x34];
	int m_value;
};

// ?get@Rva001EF4E0IntFloat@@QBEMXZ
float Rva001EF4E0IntFloat::get(void) const
{
	return (float)m_value;
}

class Rva001EF540DwordField
{
public:
	unsigned int get(void) const;

	char m_padding[8];
	unsigned int m_value;
};

// ?get@Rva001EF540DwordField@@QBEIXZ
unsigned int Rva001EF540DwordField::get(void) const
{
	return m_value;
}

class Rva001EF560DwordField
{
public:
	unsigned int get(void) const;

	char m_padding[4];
	unsigned int m_value;
};

// ?get@Rva001EF560DwordField@@QBEIXZ
unsigned int Rva001EF560DwordField::get(void) const
{
	return m_value;
}

class Rva001F0390True
{
public:
	bool value(void) const;
};

// ?value@Rva001F0390True@@QBE_NXZ
bool Rva001F0390True::value(void) const
{
	return true;
}

class Rva001F03A0DwordField
{
public:
	unsigned int get(void) const;

	char m_padding[8];
	unsigned int m_value;
};

// ?get@Rva001F03A0DwordField@@QBEIXZ
unsigned int Rva001F03A0DwordField::get(void) const
{
	return m_value;
}
