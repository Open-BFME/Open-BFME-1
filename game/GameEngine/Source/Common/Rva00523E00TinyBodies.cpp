// Address-derived tiny bodies recovered from complete carved retail extents.
// Each declaration keeps only the fields and ABI proven by the body bytes.

class Rva00523E00Self
{
public:
	Rva00523E00Self *self();
};

// ?self@Rva00523E00Self@@QAEPAV1@XZ
Rva00523E00Self *Rva00523E00Self::self()
{
	return this;
}

class Rva0052B140Self
{
public:
	Rva0052B140Self *self();
};

// ?self@Rva0052B140Self@@QAEPAV1@XZ
Rva0052B140Self *Rva0052B140Self::self()
{
	return this;
}

class Rva0052CF70Self
{
public:
	Rva0052CF70Self *self();
};

// ?self@Rva0052CF70Self@@QAEPAV1@XZ
Rva0052CF70Self *Rva0052CF70Self::self()
{
	return this;
}

// ?Rva0052D310False@@YA_NXZ
bool Rva0052D310False()
{
	return false;
}

// ?Rva0052D320False@@YA_NXZ
bool Rva0052D320False()
{
	return false;
}

// ?Rva0052D340False@@YA_NXZ
bool Rva0052D340False()
{
	return false;
}

// ?Rva0052D350False@@YA_NXZ
bool Rva0052D350False()
{
	return false;
}

// ?Rva0052D360False@@YA_NXZ
bool Rva0052D360False()
{
	return false;
}

class Rva00537530ByteFlag
{
public:
	void apply();

private:
	char m_padding[ 0x50 ];
	unsigned char m_value;
};

// ?apply@Rva00537530ByteFlag@@QAEXXZ
void Rva00537530ByteFlag::apply()
{
	m_value = 1;
}

class Rva00537610DwordExchange
{
public:
	int replace( int value );

private:
	char m_padding[ 0x18 ];
	int m_value;
};

// ?replace@Rva00537610DwordExchange@@QAEHH@Z
int Rva00537610DwordExchange::replace( int value )
{
	int old = m_value;
	m_value = value;
	return old;
}

class Rva00537620DwordExchange
{
public:
	int replace( int value );

private:
	char m_padding[ 0x1C ];
	int m_value;
};

// ?replace@Rva00537620DwordExchange@@QAEHH@Z
int Rva00537620DwordExchange::replace( int value )
{
	int old = m_value;
	m_value = value;
	return old;
}

class Rva00537660DwordGetter
{
public:
	unsigned int get() const;

private:
	char m_padding[ 8 ];
	unsigned int m_value;
};

// ?get@Rva00537660DwordGetter@@QBEIXZ
unsigned int Rva00537660DwordGetter::get() const
{
	return m_value;
}

class Rva005376F0DwordGetter
{
public:
	unsigned int get() const;

private:
	char m_padding[ 0x40 ];
	unsigned int m_value;
};

// ?get@Rva005376F0DwordGetter@@QBEIXZ
unsigned int Rva005376F0DwordGetter::get() const
{
	return m_value;
}

class Rva00537DF0ByteExchange
{
public:
	unsigned char replace( unsigned char value );

private:
	char m_padding[ 0x54 ];
	unsigned char m_value;
};

// ?replace@Rva00537DF0ByteExchange@@QAEEE@Z
unsigned char Rva00537DF0ByteExchange::replace( unsigned char value )
{
	unsigned char old = m_value;
	m_value = value;
	return old;
}

class Rva00537EA0PointerOffset
{
public:
	char *get() const;

private:
	char *m_base;
};

// ?get@Rva00537EA0PointerOffset@@QBEPADXZ
char *Rva00537EA0PointerOffset::get() const
{
	return m_base + 8;
}

class Rva00537F40DwordGetter
{
public:
	unsigned int get() const;
};

// ?get@Rva00537F40DwordGetter@@QBEIXZ
unsigned int Rva00537F40DwordGetter::get() const
{
	return *( (const unsigned int *)this );
}

// ?Rva00537FF0False@@YA_NXZ
bool Rva00537FF0False()
{
	return false;
}

class Rva00538220DwordGetter
{
public:
	unsigned int get() const;

private:
	char m_padding[ 0x58 ];
	unsigned int m_value;
};

// ?get@Rva00538220DwordGetter@@QBEIXZ
unsigned int Rva00538220DwordGetter::get() const
{
	return m_value;
}

class Rva00549F80Self
{
public:
	Rva00549F80Self *self();
};

// ?self@Rva00549F80Self@@QAEPAV1@XZ
Rva00549F80Self *Rva00549F80Self::self()
{
	return this;
}

class Rva00549F90Self
{
public:
	Rva00549F90Self *self();
};

// ?self@Rva00549F90Self@@QAEPAV1@XZ
Rva00549F90Self *Rva00549F90Self::self()
{
	return this;
}

class Rva00549FA0Self
{
public:
	Rva00549FA0Self *self();
};

// ?self@Rva00549FA0Self@@QAEPAV1@XZ
Rva00549FA0Self *Rva00549FA0Self::self()
{
	return this;
}

class Rva00549FC0Self
{
public:
	Rva00549FC0Self *self();
};

// ?self@Rva00549FC0Self@@QAEPAV1@XZ
Rva00549FC0Self *Rva00549FC0Self::self()
{
	return this;
}

class Rva0054B300Self
{
public:
	Rva0054B300Self *self();
};

// ?self@Rva0054B300Self@@QAEPAV1@XZ
Rva0054B300Self *Rva0054B300Self::self()
{
	return this;
}

class Rva0054BA10DwordGetter
{
public:
	unsigned int get() const;

private:
	unsigned int m_padding;
	unsigned int m_value;
};

// ?get@Rva0054BA10DwordGetter@@QBEIXZ
unsigned int Rva0054BA10DwordGetter::get() const
{
	return m_value;
}
