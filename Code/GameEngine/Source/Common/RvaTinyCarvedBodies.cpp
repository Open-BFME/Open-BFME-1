// cl: /DNDEBUG /DWIN32 /MD /EHs-c-

extern "C" int __cdecl memcmp(const void *, const void *, unsigned int);
#pragma intrinsic(memcmp)

class Rva0005C180Field
{
public:
	int get(void) const;

private:
	char m_pad[4];
	int m_value;
};

// ?get@Rva0005C180Field@@QBEHXZ
int Rva0005C180Field::get(void) const
{
	return m_value;
}

class Rva0005C1C0Field
{
public:
	int get(void) const;

private:
	char m_pad[8];
	int m_value;
};

// ?get@Rva0005C1C0Field@@QBEHXZ
int Rva0005C1C0Field::get(void) const
{
	return m_value;
}

class Rva0005C210Field
{
public:
	int get(void) const;

private:
	char m_pad[0x10];
	int m_value;
};

// ?get@Rva0005C210Field@@QBEHXZ
int Rva0005C210Field::get(void) const
{
	return m_value;
}

class Rva0005C230Field
{
public:
	int get(void) const;

private:
	char m_pad[0x0c];
	int m_value;
};

// ?get@Rva0005C230Field@@QBEHXZ
int Rva0005C230Field::get(void) const
{
	return m_value;
}

// ?Rva0005C480Compare@@YGHPBD0H@Z
int __stdcall Rva0005C480Compare(const char *left, const char *right, int count)
{
	return memcmp(left, right, count);
}

class Rva0005C6A0Field
{
public:
	int get(void) const;

private:
	int m_value;
};

// ?get@Rva0005C6A0Field@@QBEHXZ
int Rva0005C6A0Field::get(void) const
{
	return m_value;
}

class Rva0005CBC0Field
{
public:
	char *field(void);

private:
	char m_prefix[8];
	char m_field[1];
};

// ?field@Rva0005CBC0Field@@QAEPADXZ
char *Rva0005CBC0Field::field(void)
{
	return m_field;
}

class Rva0005D7D0Field
{
public:
	int get(void) const;

private:
	int m_value;
};

// ?get@Rva0005D7D0Field@@QBEHXZ
int Rva0005D7D0Field::get(void) const
{
	return m_value;
}

class Rva0005D800Field
{
public:
	int get(void) const;

private:
	int m_value;
};

// ?get@Rva0005D800Field@@QBEHXZ
int Rva0005D800Field::get(void) const
{
	return m_value;
}

class Rva0005DC10Field
{
public:
	char *field(void);

private:
	char m_prefix[8];
	char m_field[1];
};

// ?field@Rva0005DC10Field@@QAEPADXZ
char *Rva0005DC10Field::field(void)
{
	return m_field;
}

class Rva0005DC20Field
{
public:
	char *field(void);

private:
	char m_prefix[8];
	char m_field[1];
};

// ?field@Rva0005DC20Field@@QAEPADXZ
char *Rva0005DC20Field::field(void)
{
	return m_field;
}

class Rva000607C0Flag
{
public:
	void enable(void);

private:
	unsigned char m_flag;
};

// ?enable@Rva000607C0Flag@@QAEXXZ
void Rva000607C0Flag::enable(void)
{
	m_flag = 1;
}

class Rva00061630Field
{
public:
	int get(void) const;

private:
	char m_pad[4];
	int m_value;
};

// ?get@Rva00061630Field@@QBEHXZ
int Rva00061630Field::get(void) const
{
	return m_value;
}

class Rva000616B0Field
{
public:
	int get(void) const;

private:
	char m_pad[4];
	int m_value;
};

// ?get@Rva000616B0Field@@QBEHXZ
int Rva000616B0Field::get(void) const
{
	return m_value;
}

class Rva00061700Opaque
{
public:
	Rva00061700Opaque *self(void);
};

// ?self@Rva00061700Opaque@@QAEPAV1@XZ
Rva00061700Opaque *Rva00061700Opaque::self(void)
{
	return this;
}

class Rva00061CA0Owner
{
public:
	int *field(void) const;

private:
	int *m_base;
};

// ?field@Rva00061CA0Owner@@QBEPAHXZ
int *Rva00061CA0Owner::field(void) const
{
	return m_base + 4;
}

class Rva00061CC0Opaque
{
public:
	void invoke(int value);
};

// ?invoke@Rva00061CC0Opaque@@QAEXH@Z
void Rva00061CC0Opaque::invoke(int value)
{
}

class Rva00063DF0FloatField
{
public:
	float get(void) const;

private:
	char m_pad[0x0c];
	float m_value;
};

// ?get@Rva00063DF0FloatField@@QBEMXZ
float Rva00063DF0FloatField::get(void) const
{
	return m_value;
}

class Rva00063E00Field
{
public:
	int get(void) const;

private:
	char m_pad[0x18];
	int m_value;
};

// ?get@Rva00063E00Field@@QBEHXZ
int Rva00063E00Field::get(void) const
{
	return m_value;
}

class Rva000644D0Field
{
public:
	int get(void) const;

private:
	char m_pad[4];
	int m_value;
};

// ?get@Rva000644D0Field@@QBEHXZ
int Rva000644D0Field::get(void) const
{
	return m_value;
}

class Rva00065290Field
{
public:
	int get(void) const;

private:
	char m_pad[0x3c];
	int m_value;
};

// ?get@Rva00065290Field@@QBEHXZ
int Rva00065290Field::get(void) const
{
	return m_value;
}

class Rva00065360Opaque
{
public:
	Rva00065360Opaque *self(void);
};

// ?self@Rva00065360Opaque@@QAEPAV1@XZ
Rva00065360Opaque *Rva00065360Opaque::self(void)
{
	return this;
}
