// cl: /O2 /MD /EHsc-
// Address-derived accessors for complete carved bodies with no direct callees.

class Rva00097E50Identity
{
public:
	void *identity();
};

// ?identity@Rva00097E50Identity@@QAEPAXXZ
void *Rva00097E50Identity::identity()
{
	return this;
}

class Rva00098F40False
{
public:
	static bool get();
};

// ?get@Rva00098F40False@@SA_NXZ
bool Rva00098F40False::get()
{
	return false;
}

class Rva0009C1C0Dword
{
	char m_padding[0x0C];
	unsigned int m_value;
public:
	unsigned int get() const;
};

// ?get@Rva0009C1C0Dword@@QBEIXZ
unsigned int Rva0009C1C0Dword::get() const
{
	return m_value;
}

class Rva0009C1D0Dword
{
	char m_padding[0x14];
	unsigned int m_value;
public:
	unsigned int get() const;
};

// ?get@Rva0009C1D0Dword@@QBEIXZ
unsigned int Rva0009C1D0Dword::get() const
{
	return m_value;
}

class Rva0009EC30Identity
{
public:
	void *identity();
};

// ?identity@Rva0009EC30Identity@@QAEPAXXZ
void *Rva0009EC30Identity::identity()
{
	return this;
}

class Rva0009FEE0Dword
{
	char m_padding[0x1C];
	unsigned int m_value;
public:
	unsigned int get() const;
};

// ?get@Rva0009FEE0Dword@@QBEIXZ
unsigned int Rva0009FEE0Dword::get() const
{
	return m_value;
}

class Rva0009FEF0Dword
{
	char m_padding[4];
	unsigned int m_value;
public:
	unsigned int get() const;
};

// ?get@Rva0009FEF0Dword@@QBEIXZ
unsigned int Rva0009FEF0Dword::get() const
{
	return m_value;
}

class Rva000A0140Identity
{
public:
	void *identity();
};

// ?identity@Rva000A0140Identity@@QAEPAXXZ
void *Rva000A0140Identity::identity()
{
	return this;
}

class Rva000A01C0Identity
{
public:
	void *identity();
};

// ?identity@Rva000A01C0Identity@@QAEPAXXZ
void *Rva000A01C0Identity::identity()
{
	return this;
}

class Rva000A03A0Address
{
public:
	char *get() const;
};

// ?get@Rva000A03A0Address@@QBEPADXZ
char *Rva000A03A0Address::get() const
{
	return (char *)this + 0x38;
}

class Rva000A1A40NoOp
{
public:
	void noop(int unused);
};

// ?noop@Rva000A1A40NoOp@@QAEXH@Z
void Rva000A1A40NoOp::noop(int unused)
{
	(void)unused;
}

class Rva000A1A70False
{
public:
	static bool get();
};

// ?get@Rva000A1A70False@@SA_NXZ
bool Rva000A1A70False::get()
{
	return false;
}

class Rva000A1A90False
{
public:
	static bool get();
};

// ?get@Rva000A1A90False@@SA_NXZ
bool Rva000A1A90False::get()
{
	return false;
}

class Rva000A1AA0False
{
public:
	static bool get();
};

// ?get@Rva000A1AA0False@@SA_NXZ
bool Rva000A1AA0False::get()
{
	return false;
}

class Rva000A1AB0Byte
{
	char m_padding[0x20];
	unsigned char m_value;
public:
	unsigned char get() const;
};

// ?get@Rva000A1AB0Byte@@QBEEXZ
unsigned char Rva000A1AB0Byte::get() const
{
	return m_value;
}

class Rva000A1AC0False
{
public:
	static bool get();
};

// ?get@Rva000A1AC0False@@SA_NXZ
bool Rva000A1AC0False::get()
{
	return false;
}

class Rva000A1AD0False
{
public:
	static bool get();
};

// ?get@Rva000A1AD0False@@SA_NXZ
bool Rva000A1AD0False::get()
{
	return false;
}

class Rva000A2140Dword
{
	char m_padding[4];
	unsigned int m_value;
public:
	unsigned int get() const;
};

// ?get@Rva000A2140Dword@@QBEIXZ
unsigned int Rva000A2140Dword::get() const
{
	return m_value;
}

class Rva000A21C0Address
{
public:
	char *get() const;
};

// ?get@Rva000A21C0Address@@QBEPADXZ
char *Rva000A21C0Address::get() const
{
	return (char *)this + 0x28;
}

class Rva000A21D0Address
{
public:
	char *get() const;
};

// ?get@Rva000A21D0Address@@QBEPADXZ
char *Rva000A21D0Address::get() const
{
	return (char *)this + 0x48;
}

class Rva000A3030Address
{
public:
	char *get() const;
};

// ?get@Rva000A3030Address@@QBEPADXZ
char *Rva000A3030Address::get() const
{
	return (char *)this + 8;
}

class Rva000A3050Dword
{
	char m_padding[0x18];
	unsigned int m_value;
public:
	unsigned int get() const;
};

// ?get@Rva000A3050Dword@@QBEIXZ
unsigned int Rva000A3050Dword::get() const
{
	return m_value;
}

class Rva000A3060Dword
{
	char m_padding[0x24];
	unsigned int m_value;
public:
	unsigned int get() const;
};

// ?get@Rva000A3060Dword@@QBEIXZ
unsigned int Rva000A3060Dword::get() const
{
	return m_value;
}

class Rva000A3070Dword
{
	char m_padding[0x3C];
	unsigned int m_value;
public:
	unsigned int get() const;
};

// ?get@Rva000A3070Dword@@QBEIXZ
unsigned int Rva000A3070Dword::get() const
{
	return m_value;
}

class Rva000A30B0Byte
{
	char m_padding[0x0E];
	unsigned char m_value;
public:
	unsigned char get() const;
};

// ?get@Rva000A30B0Byte@@QBEEXZ
unsigned char Rva000A30B0Byte::get() const
{
	return m_value;
}
