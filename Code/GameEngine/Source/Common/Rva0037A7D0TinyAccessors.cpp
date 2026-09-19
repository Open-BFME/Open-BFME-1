// cl: /DNDEBUG /MD
// Address-derived leaf accessors reconstructed from retail RVAs 0x0037A7D0-0x0037AEF0.

class Rva0037A7D0Object
{
public:
	unsigned char getByte() const;

private:
	char m_pad00[0x09];
	unsigned char m_value09;
};

class Rva0037A7E0Object
{
public:
	int getValue() const;

private:
	char m_pad00[0x10];
	int m_value10;
};

class Rva0037A800Object
{
public:
	int getValue() const;

private:
	char m_pad00[0x18];
	int m_value18;
};

class Rva0037A870Object
{
public:
	int getValue() const;

private:
	char m_pad00[0x30];
	int m_value30;
};

class Rva0037A880Object
{
public:
	int getValue() const;

private:
	char m_pad00[0x34];
	int m_value34;
};

class Rva0037A890Object
{
public:
	int getValue() const;

private:
	char m_pad00[0x38];
	int m_value38;
};

class Rva0037A8A0Object
{
public:
	int getValue() const;

private:
	char m_pad00[0x40];
	int m_value40;
};

class Rva0037A8B0Object
{
public:
	int getValue() const;

private:
	char m_pad00[0x48];
	int m_value48;
};

class Rva0037A8C0Object
{
public:
	unsigned char getByte() const;

private:
	char m_pad00[0x44];
	unsigned char m_value44;
};

class Rva0037A8D0Object
{
public:
	int getValue() const;

private:
	char m_pad00[0x50];
	int m_value50;
};

class Rva0037A8E0Object
{
public:
	char *member();

private:
	char m_pad00[0x54];
	char m_value54;
};

class Rva0037A910Object
{
public:
	char *member();

private:
	char m_pad00[0x7C];
	char m_value7C;
};

class Rva0037AAB0Object
{
public:
	char *member();

private:
	char *m_base;
};

class Rva0037AB10Object
{
public:
	Rva0037AB10Object *self();
};

class Rva0037AEF0Object
{
public:
	int getValue() const;

private:
	char m_pad00[4];
	int m_value04;
};

// ?getByte@Rva0037A7D0Object@@QBEEXZ
unsigned char Rva0037A7D0Object::getByte() const
{
	return m_value09;
}

// ?getValue@Rva0037A7E0Object@@QBEHXZ
int Rva0037A7E0Object::getValue() const
{
	return m_value10;
}

// ?getValue@Rva0037A800Object@@QBEHXZ
int Rva0037A800Object::getValue() const
{
	return m_value18;
}

// ?getValue@Rva0037A870Object@@QBEHXZ
int Rva0037A870Object::getValue() const
{
	return m_value30;
}

// ?getValue@Rva0037A880Object@@QBEHXZ
int Rva0037A880Object::getValue() const
{
	return m_value34;
}

// ?getValue@Rva0037A890Object@@QBEHXZ
int Rva0037A890Object::getValue() const
{
	return m_value38;
}

// ?getValue@Rva0037A8A0Object@@QBEHXZ
int Rva0037A8A0Object::getValue() const
{
	return m_value40;
}

// ?getValue@Rva0037A8B0Object@@QBEHXZ
int Rva0037A8B0Object::getValue() const
{
	return m_value48;
}

// ?getByte@Rva0037A8C0Object@@QBEEXZ
unsigned char Rva0037A8C0Object::getByte() const
{
	return m_value44;
}

// ?getValue@Rva0037A8D0Object@@QBEHXZ
int Rva0037A8D0Object::getValue() const
{
	return m_value50;
}

// ?member@Rva0037A8E0Object@@QAEPADXZ
char *Rva0037A8E0Object::member()
{
	return &m_value54;
}

// ?member@Rva0037A910Object@@QAEPADXZ
char *Rva0037A910Object::member()
{
	return &m_value7C;
}

// ?member@Rva0037AAB0Object@@QAEPADXZ
char *Rva0037AAB0Object::member()
{
	return m_base + 0x10;
}

// ?self@Rva0037AB10Object@@QAEPAV1@XZ
Rva0037AB10Object *Rva0037AB10Object::self()
{
	return this;
}

// ?getValue@Rva0037AEF0Object@@QBEHXZ
int Rva0037AEF0Object::getValue() const
{
	return m_value04;
}
