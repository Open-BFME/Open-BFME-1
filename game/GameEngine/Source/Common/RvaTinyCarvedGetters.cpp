// Structural recoveries for carved nullary thiscall accessors.
// Owners and member names remain address-derived because no semantic owner is proven.
// cl: /O2 /DNDEBUG /MD /EHsc

class Rva000E69F0
{
public:
	void *get();
};

// ?get@Rva000E69F0@@QAEPAXXZ
void *Rva000E69F0::get()
{
	return this;
}

class Rva000E6CF0
{
public:
	void *get();
};

// ?get@Rva000E6CF0@@QAEPAXXZ
void *Rva000E6CF0::get()
{
	return this;
}

class Rva000E8B80
{
public:
	unsigned get() const;

private:
	char m_padding[4];
	unsigned m_value;
};

// ?get@Rva000E8B80@@QBEIXZ
unsigned Rva000E8B80::get() const
{
	return m_value;
}

class Rva000E8B90
{
public:
	void *get();
};

// ?get@Rva000E8B90@@QAEPAXXZ
void *Rva000E8B90::get()
{
	return this;
}

class Rva000E8BE0
{
public:
	unsigned get() const;

private:
	unsigned m_value;
};

// ?get@Rva000E8BE0@@QBEIXZ
unsigned Rva000E8BE0::get() const
{
	return m_value + 0x10;
}

class Rva000E9010
{
public:
	unsigned get() const;

private:
	char m_padding[4];
	unsigned m_value;
};

// ?get@Rva000E9010@@QBEIXZ
unsigned Rva000E9010::get() const
{
	return m_value;
}

class Rva000ED230
{
public:
	unsigned get() const;

private:
	char m_padding[4];
	unsigned m_value;
};

// ?get@Rva000ED230@@QBEIXZ
unsigned Rva000ED230::get() const
{
	return m_value;
}

class Rva000EDFF0
{
public:
	unsigned get() const;

private:
	char m_padding[0x10];
	unsigned m_value;
};

// ?get@Rva000EDFF0@@QBEIXZ
unsigned Rva000EDFF0::get() const
{
	return m_value;
}

class Rva000EE3D0
{
public:
	unsigned get() const;

private:
	char m_padding[4];
	unsigned m_value;
};

// ?get@Rva000EE3D0@@QBEIXZ
unsigned Rva000EE3D0::get() const
{
	return m_value;
}

class Rva000F8580
{
public:
	void *get();
};

// ?get@Rva000F8580@@QAEPAXXZ
void *Rva000F8580::get()
{
	return this;
}

class Rva000F91F0
{
public:
	unsigned get() const;

private:
	char m_padding[0x210];
	unsigned m_value;
};

// ?get@Rva000F91F0@@QBEIXZ
unsigned Rva000F91F0::get() const
{
	return m_value;
}

class Rva000F9230
{
public:
	float get() const;

private:
	char m_padding[0x0c];
	float m_value;
};

// ?get@Rva000F9230@@QBEMXZ
float Rva000F9230::get() const
{
	return m_value;
}

class Rva000F9240
{
public:
	unsigned get() const;

private:
	char m_padding[0x28];
	unsigned m_value;
};

// ?get@Rva000F9240@@QBEIXZ
unsigned Rva000F9240::get() const
{
	return m_value;
}

class Rva000F92F0
{
public:
	unsigned get() const;

private:
	unsigned m_value;
};

// ?get@Rva000F92F0@@QBEIXZ
unsigned Rva000F92F0::get() const
{
	return m_value;
}

class Rva000F9320
{
public:
	unsigned get() const;

private:
	char m_padding[4];
	unsigned m_value;
};

// ?get@Rva000F9320@@QBEIXZ
unsigned Rva000F9320::get() const
{
	return m_value;
}

class Rva000FB8D0
{
public:
	unsigned char get() const;

private:
	char m_padding[0x1c];
	unsigned char m_value;
};

// ?get@Rva000FB8D0@@QBEEXZ
unsigned char Rva000FB8D0::get() const
{
	return m_value;
}

class Rva000FB8E0
{
public:
	unsigned get() const;

private:
	char m_padding[0x24];
	unsigned m_value;
};

// ?get@Rva000FB8E0@@QBEIXZ
unsigned Rva000FB8E0::get() const
{
	return m_value;
}

class Rva000FBB40
{
public:
	void *get();
};

// ?get@Rva000FBB40@@QAEPAXXZ
void *Rva000FBB40::get()
{
	return this;
}

class Rva000FBDB0
{
public:
	float get() const;

private:
	char m_padding[0x14];
	float m_value;
};

// ?get@Rva000FBDB0@@QBEMXZ
float Rva000FBDB0::get() const
{
	return m_value;
}

class Rva000FC320
{
public:
	void *get();
};

// ?get@Rva000FC320@@QAEPAXXZ
void *Rva000FC320::get()
{
	return this;
}

class Rva000FC360
{
public:
	void *get();
};

// ?get@Rva000FC360@@QAEPAXXZ
void *Rva000FC360::get()
{
	return this;
}

class Rva000FC3A0
{
public:
	void *get();
};

// ?get@Rva000FC3A0@@QAEPAXXZ
void *Rva000FC3A0::get()
{
	return this;
}

class Rva000FC3C0
{
public:
	void *get();
};

// ?get@Rva000FC3C0@@QAEPAXXZ
void *Rva000FC3C0::get()
{
	return this;
}

class Rva000FC3E0
{
public:
	unsigned get() const;

private:
	unsigned m_value;
};

// ?get@Rva000FC3E0@@QBEIXZ
unsigned Rva000FC3E0::get() const
{
	return m_value + 8;
}

class Rva000FC410
{
public:
	unsigned get() const;

private:
	unsigned m_value;
};

// ?get@Rva000FC410@@QBEIXZ
unsigned Rva000FC410::get() const
{
	return m_value;
}
