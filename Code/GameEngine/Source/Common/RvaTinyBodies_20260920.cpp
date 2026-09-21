// Address-derived leaf bodies recovered from complete retail extents.

class Rva000FDB30Dword
{
public:
	unsigned int get() const;

private:
	char m_padding[8];
	unsigned int m_value;
};

// ?get@Rva000FDB30Dword@@QBEIXZ
unsigned int Rva000FDB30Dword::get() const
{
	return m_value;
}

class Rva00101B30Dword
{
public:
	unsigned int get() const;

private:
	char m_padding[0xC];
	unsigned int m_value;
};

// ?get@Rva00101B30Dword@@QBEIXZ
unsigned int Rva00101B30Dword::get() const
{
	return m_value;
}

// ?Rva00104740Store@@YAXPAI@Z
void Rva00104740Store(unsigned int *target)
{
	*target = 0x7FFu;
}

class Rva00106600Dword
{
public:
	unsigned int get() const;

private:
	char m_padding[0x20C];
	unsigned int m_value;
};

// ?get@Rva00106600Dword@@QBEIXZ
unsigned int Rva00106600Dword::get() const
{
	return m_value;
}

class Rva00106650Dword
{
public:
	unsigned int get() const;

private:
	char m_padding[4];
	unsigned int m_value;
};

// ?get@Rva00106650Dword@@QBEIXZ
unsigned int Rva00106650Dword::get() const
{
	return m_value;
}

class Rva0010A080Dword
{
public:
	unsigned int get() const;

	unsigned int m_value;
};

// ?get@Rva0010A080Dword@@QBEIXZ
unsigned int Rva0010A080Dword::get() const
{
	return m_value;
}

class Rva0010A710Dword
{
public:
	unsigned int get() const;

private:
	char m_padding[0xC];
	unsigned int m_value;
};

// ?get@Rva0010A710Dword@@QBEIXZ
unsigned int Rva0010A710Dword::get() const
{
	return m_value;
}

class Rva0010A750Dword
{
public:
	unsigned int get() const;

private:
	char m_padding[0x108];
	unsigned int m_value;
};

// ?get@Rva0010A750Dword@@QBEIXZ
unsigned int Rva0010A750Dword::get() const
{
	return m_value;
}

class Rva0010B650Byte
{
public:
	unsigned char get() const;

private:
	char m_padding[4];
	unsigned char m_value;
};

// ?get@Rva0010B650Byte@@QBEEXZ
unsigned char Rva0010B650Byte::get() const
{
	return m_value;
}

class Rva0010D2A0Self
{
public:
	void *get() const;
};

// ?get@Rva0010D2A0Self@@QBEPAXXZ
void *Rva0010D2A0Self::get() const
{
	return (void *)this;
}

class Rva0010D2C0Self
{
public:
	void *get() const;
};

// ?get@Rva0010D2C0Self@@QBEPAXXZ
void *Rva0010D2C0Self::get() const
{
	return (void *)this;
}

class Rva0010D300Self
{
public:
	void *get() const;
};

// ?get@Rva0010D300Self@@QBEPAXXZ
void *Rva0010D300Self::get() const
{
	return (void *)this;
}

class Rva0010D390Value
{
public:
	unsigned int get() const;

private:
	unsigned int m_value;
};

// ?get@Rva0010D390Value@@QBEIXZ
unsigned int Rva0010D390Value::get() const
{
	return m_value + 8;
}

class Rva00112940Dword
{
public:
	unsigned int get() const;

private:
	char m_padding[0x108];
	unsigned int m_value;
};

// ?get@Rva00112940Dword@@QBEIXZ
unsigned int Rva00112940Dword::get() const
{
	return m_value;
}

class Rva00115F20Self
{
public:
	void *get() const;
};

// ?get@Rva00115F20Self@@QBEPAXXZ
void *Rva00115F20Self::get() const
{
	return (void *)this;
}

// ?Rva0011A1A0False@@YA_NXZ
bool Rva0011A1A0False()
{
	return false;
}

// ?Rva0011A1B0False@@YA_NXZ
bool Rva0011A1B0False()
{
	return false;
}

// ?Rva0011A290Ret12@@YGXPAX00@Z
void __stdcall Rva0011A290Ret12(void *, void *, void *)
{
}

// ?Rva00121CD0Ret12@@YGXPAX00@Z
void __stdcall Rva00121CD0Ret12(void *, void *, void *)
{
}

// ?Rva00121CE0Zero@@YAHXZ
int Rva00121CE0Zero()
{
	return 0;
}

// ?Rva00121D00Zero@@YAHXZ
int Rva00121D00Zero()
{
	return 0;
}

class Rva00122270Self
{
public:
	void *get() const;
};

// ?get@Rva00122270Self@@QBEPAXXZ
void *Rva00122270Self::get() const
{
	return (void *)this;
}

// ?Rva00122280Noop@@YAXXZ
void Rva00122280Noop()
{
}

class Rva001222A0Self
{
public:
	void *get() const;
};

// ?get@Rva001222A0Self@@QBEPAXXZ
void *Rva001222A0Self::get() const
{
	return (void *)this;
}

class Rva001222C0Self
{
public:
	void *get() const;
};

// ?get@Rva001222C0Self@@QBEPAXXZ
void *Rva001222C0Self::get() const
{
	return (void *)this;
}

class Rva001222E0Self
{
public:
	void *get() const;
};

// ?get@Rva001222E0Self@@QBEPAXXZ
void *Rva001222E0Self::get() const
{
	return (void *)this;
}

// The carved boundary proves a one-byte ret-only body at 0x001222F0.
void Rva001222F0Noop()
{
}

// The carved boundary at 0x0040B1B0 contains only a return.
void Rva0040B1B0Noop()
{
}
