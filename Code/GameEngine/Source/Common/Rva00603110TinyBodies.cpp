// cl: /O2 /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHs-c-
// Address-derived owners retain the incomplete identities of this carved batch.

class Rva00603110False
{
public:
	unsigned char get() const;
};

// ?get@Rva00603110False@@QBEEXZ
unsigned char Rva00603110False::get() const
{
	return 0;
}

class Rva00603900Field
{
public:
	unsigned int get() const;

private:
	char m_padding[8];
	unsigned int m_value;
};

// ?get@Rva00603900Field@@QBEIXZ
unsigned int Rva00603900Field::get() const
{
	return m_value;
}

class Rva00604CB0Self
{
public:
	void *get();
};

// ?get@Rva00604CB0Self@@QAEPAXXZ
void *Rva00604CB0Self::get()
{
	return this;
}

class Rva00604CE0Pointer
{
public:
	char *get() const;

private:
	char *m_value;
};

// ?get@Rva00604CE0Pointer@@QBEPADXZ
char *Rva00604CE0Pointer::get() const
{
	return m_value + 4;
}

class Rva00604E50Field
{
public:
	unsigned int get() const;

private:
	char m_padding[4];
	unsigned int m_value;
};

// ?get@Rva00604E50Field@@QBEIXZ
unsigned int Rva00604E50Field::get() const
{
	return m_value;
}

class Rva00606990Field
{
public:
	unsigned int get() const;

private:
	char m_padding[4];
	unsigned int m_value;
};

// ?get@Rva00606990Field@@QBEIXZ
unsigned int Rva00606990Field::get() const
{
	return m_value;
}

class Rva00607DD0FieldAddress
{
public:
	char *get() const;
};

// ?get@Rva00607DD0FieldAddress@@QBEPADXZ
char *Rva00607DD0FieldAddress::get() const
{
	return (char *)this + 8;
}

class Rva00609F60Byte
{
public:
	unsigned char get() const;

private:
	char m_padding[0x14];
	unsigned char m_value;
};

// ?get@Rva00609F60Byte@@QBEEXZ
unsigned char Rva00609F60Byte::get() const
{
	return m_value;
}

class Rva00609F70Byte
{
public:
	unsigned char get() const;

private:
	char m_padding[0x15];
	unsigned char m_value;
};

// ?get@Rva00609F70Byte@@QBEEXZ
unsigned char Rva00609F70Byte::get() const
{
	return m_value;
}

class Rva0060A160Field
{
public:
	unsigned int get() const;

private:
	char m_padding[8];
	unsigned int m_value;
};

// ?get@Rva0060A160Field@@QBEIXZ
unsigned int Rva0060A160Field::get() const
{
	return m_value;
}

class Rva0060A6E0Self
{
public:
	void *get();
};

// ?get@Rva0060A6E0Self@@QAEPAXXZ
void *Rva0060A6E0Self::get()
{
	return this;
}

class Rva0060C190Field
{
public:
	unsigned int get() const;

private:
	char m_padding[4];
	unsigned int m_value;
};

// ?get@Rva0060C190Field@@QBEIXZ
unsigned int Rva0060C190Field::get() const
{
	return m_value;
}

class AsciiString;
class BfmeGameCW;

struct Rva00612430Item
{
	char m_padding[4];
	void *m_value;
};

class Rva00612430Owner
{
public:
	Rva00612430Item *find(const AsciiString &name);
};

extern BfmeGameCW *g_bfmeGameCW;

// ?Rva0060C1B0@@YGXPAXPBVAsciiString@@@Z
void __stdcall Rva0060C1B0(void *out, const AsciiString *name)
{
	Rva00612430Item *item = reinterpret_cast<Rva00612430Owner *>(g_bfmeGameCW)->find(*name);
	if (item != 0)
		*(void **)out = item->m_value;
}

class Rva0060C320Self
{
public:
	void *get();
};

// ?get@Rva0060C320Self@@QAEPAXXZ
void *Rva0060C320Self::get()
{
	return this;
}

class Rva0060D220Float
{
public:
	float get() const;

private:
	char m_padding[0x90];
	float m_value;
};

// ?get@Rva0060D220Float@@QBEMXZ
float Rva0060D220Float::get() const
{
	return m_value;
}

class Rva0060D250Field
{
public:
	unsigned int get() const;

private:
	char m_padding[0x0C];
	unsigned int m_value;
};

// ?get@Rva0060D250Field@@QBEIXZ
unsigned int Rva0060D250Field::get() const
{
	return m_value;
}

class Rva0060D270FieldAddress
{
public:
	char *get() const;
};

// ?get@Rva0060D270FieldAddress@@QBEPADXZ
char *Rva0060D270FieldAddress::get() const
{
	return (char *)this + 0x18;
}

class Rva0060D280Byte
{
public:
	unsigned char get() const;

private:
	char m_padding[0x11];
	unsigned char m_value;
};

// ?get@Rva0060D280Byte@@QBEEXZ
unsigned char Rva0060D280Byte::get() const
{
	return m_value;
}

class Rva0060D290FieldAddress
{
public:
	char *get() const;
};

// ?get@Rva0060D290FieldAddress@@QBEPADXZ
char *Rva0060D290FieldAddress::get() const
{
	return (char *)this + 0x1C;
}

class Rva0060D2A0FieldAddress
{
public:
	char *get() const;
};

// ?get@Rva0060D2A0FieldAddress@@QBEPADXZ
char *Rva0060D2A0FieldAddress::get() const
{
	return (char *)this + 4;
}

class Rva0060D700Self
{
public:
	void *get();
};

// ?get@Rva0060D700Self@@QAEPAXXZ
void *Rva0060D700Self::get()
{
	return this;
}

class Rva0060D760Self
{
public:
	void *get();
};

// ?get@Rva0060D760Self@@QAEPAXXZ
void *Rva0060D760Self::get()
{
	return this;
}

class Rva0060D790Self
{
public:
	void *get();
};

// ?get@Rva0060D790Self@@QAEPAXXZ
void *Rva0060D790Self::get()
{
	return this;
}
