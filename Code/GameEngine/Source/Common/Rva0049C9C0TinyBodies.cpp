// Address-derived owners for the complete carved bodies in this batch.
// Their callers and vtable ownership do not prove semantic names.

class Rva0049C9C0Dword
{
public:
	unsigned int get() const;

private:
	char m_pad[0x144];
};

// ?get@Rva0049C9C0Dword@@QBEIXZ
unsigned int Rva0049C9C0Dword::get() const
{
	return *(const unsigned int *)((const char *)this + 0x144);
}

class Rva0049C9D0Dword
{
public:
	unsigned int get() const;

private:
	char m_pad[0x14];
};

// ?get@Rva0049C9D0Dword@@QBEIXZ
unsigned int Rva0049C9D0Dword::get() const
{
	return *(const unsigned int *)((const char *)this + 0x14);
}

class Rva0049CA00Dword
{
public:
	unsigned int get() const;

private:
	char m_pad[0x14];
};

// ?get@Rva0049CA00Dword@@QBEIXZ
unsigned int Rva0049CA00Dword::get() const
{
	return *(const unsigned int *)((const char *)this + 0x14);
}

class Rva0049D5C0False
{
public:
	bool get() const;
};

// ?get@Rva0049D5C0False@@QBE_NXZ
bool Rva0049D5C0False::get() const
{
	return false;
}

class Rva0049D630False
{
public:
	bool get() const;
};

// ?get@Rva0049D630False@@QBE_NXZ
bool Rva0049D630False::get() const
{
	return false;
}

class Rva0049D640False
{
public:
	bool get() const;
};

// ?get@Rva0049D640False@@QBE_NXZ
bool Rva0049D640False::get() const
{
	return false;
}

class UnicodeString
{
public:
	void set(const UnicodeString &value);
};

class Rva004A3A70Owner
{
public:
	void set(const UnicodeString &value);

private:
	char m_pad[0x68];
	UnicodeString m_string;
};

// ?set@Rva004A3A70Owner@@QAEXABVUnicodeString@@@Z
void Rva004A3A70Owner::set(const UnicodeString &value)
{
	m_string.set(value);
}

class Rva004A6600Self
{
public:
	Rva004A6600Self *get();
};

// ?get@Rva004A6600Self@@QAEPAV1@XZ
Rva004A6600Self *Rva004A6600Self::get()
{
	return this;
}

class Rva004AAD20Self
{
public:
	Rva004AAD20Self *get();
};

// ?get@Rva004AAD20Self@@QAEPAV1@XZ
Rva004AAD20Self *Rva004AAD20Self::get()
{
	return this;
}

class Rva004AB7C0Dword
{
public:
	unsigned int get() const;

private:
	char m_pad[0x20];
};

// ?get@Rva004AB7C0Dword@@QBEIXZ
unsigned int Rva004AB7C0Dword::get() const
{
	return *(const unsigned int *)((const char *)this + 0x20);
}

class Rva004AB830DwordSlot
{
public:
	void set(int value);

private:
	char m_pad[0x2bc];
};

// ?set@Rva004AB830DwordSlot@@QAEXH@Z
void Rva004AB830DwordSlot::set(int value)
{
	*(int *)((char *)this + 0x2bc) = value;
}

class Rva004AB8C0Self
{
public:
	Rva004AB8C0Self *get();
};

// ?get@Rva004AB8C0Self@@QAEPAV1@XZ
Rva004AB8C0Self *Rva004AB8C0Self::get()
{
	return this;
}

// ?Rva004AB8D0NoOp@@YAXXZ
void Rva004AB8D0NoOp()
{
}

class Rva004AB8E0Self
{
public:
	Rva004AB8E0Self *get();
};

// ?get@Rva004AB8E0Self@@QAEPAV1@XZ
Rva004AB8E0Self *Rva004AB8E0Self::get()
{
	return this;
}

class Rva004AB900Self
{
public:
	Rva004AB900Self *get();
};

// ?get@Rva004AB900Self@@QAEPAV1@XZ
Rva004AB900Self *Rva004AB900Self::get()
{
	return this;
}

// ?Rva004AB910NoOp@@YAXXZ
void Rva004AB910NoOp()
{
}

class Rva004AFB10RootDword
{
public:
	unsigned int get() const;
};

// ?get@Rva004AFB10RootDword@@QBEIXZ
unsigned int Rva004AFB10RootDword::get() const
{
	return *(const unsigned int *)this;
}

class Rva004B2F10Dword
{
public:
	unsigned int get() const;

private:
	char m_pad[8];
};

// ?get@Rva004B2F10Dword@@QBEIXZ
unsigned int Rva004B2F10Dword::get() const
{
	return *(const unsigned int *)((const char *)this + 8);
}

class Rva004B59E0RootDword
{
public:
	unsigned int get() const;
};

// ?get@Rva004B59E0RootDword@@QBEIXZ
unsigned int Rva004B59E0RootDword::get() const
{
	return *(const unsigned int *)this;
}

class Rva004BE030Dword
{
public:
	unsigned int get() const;

private:
	char m_pad[8];
};

// ?get@Rva004BE030Dword@@QBEIXZ
unsigned int Rva004BE030Dword::get() const
{
	return *(const unsigned int *)((const char *)this + 8);
}

class Rva004C10A0Address
{
public:
	void *get() const;
};

// ?get@Rva004C10A0Address@@QBEPAXXZ
void *Rva004C10A0Address::get() const
{
	return (void *)((const char *)this + 0x5c);
}

class Rva004C10B0Address
{
public:
	void *get() const;
};

// ?get@Rva004C10B0Address@@QBEPAXXZ
void *Rva004C10B0Address::get() const
{
	return (void *)((const char *)this + 0x60);
}

class Rva004C10C0Address
{
public:
	void *get() const;
};

// ?get@Rva004C10C0Address@@QBEPAXXZ
void *Rva004C10C0Address::get() const
{
	return (void *)((const char *)this + 0x64);
}

class Rva004C11E0RootDword
{
public:
	unsigned int get() const;
};

// ?get@Rva004C11E0RootDword@@QBEIXZ
unsigned int Rva004C11E0RootDword::get() const
{
	return *(const unsigned int *)this;
}

class Rva004C11F0RootDword
{
public:
	unsigned int get() const;
};

// ?get@Rva004C11F0RootDword@@QBEIXZ
unsigned int Rva004C11F0RootDword::get() const
{
	return *(const unsigned int *)this;
}

class Rva004C9050Dword
{
public:
	unsigned int get() const;

private:
	char m_pad[8];
};

// ?get@Rva004C9050Dword@@QBEIXZ
unsigned int Rva004C9050Dword::get() const
{
	return *(const unsigned int *)((const char *)this + 8);
}

class Rva004CAE70Byte
{
public:
	unsigned char get() const;

private:
	char m_pad[8];
};

// ?get@Rva004CAE70Byte@@QBEEXZ
unsigned char Rva004CAE70Byte::get() const
{
	return *(const unsigned char *)((const char *)this + 8);
}
