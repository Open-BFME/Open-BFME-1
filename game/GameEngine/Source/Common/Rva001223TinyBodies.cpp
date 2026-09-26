// cl: /O2 /MD /EHsc-

struct Rva00122300Owner
{
	Rva00122300Owner *self();
};

// ?self@Rva00122300Owner@@QAEPAU1@XZ
Rva00122300Owner *Rva00122300Owner::self()
{
	return this;
}

struct Rva00122320Owner
{
	Rva00122320Owner *self();
};

// ?self@Rva00122320Owner@@QAEPAU1@XZ
Rva00122320Owner *Rva00122320Owner::self()
{
	return this;
}

struct Rva00122350Owner
{
	void *m_value;
	void *get();
};

// ?get@Rva00122350Owner@@QAEPAXXZ
void *Rva00122350Owner::get()
{
	return static_cast<unsigned char *>(m_value) + 0x10;
}

struct Rva00122400Owner
{
	void *m_value;
	void *get();
};

// ?get@Rva00122400Owner@@QAEPAXXZ
void *Rva00122400Owner::get()
{
	return static_cast<unsigned char *>(m_value) + 0x10;
}

struct Rva00122AD0Owner
{
	unsigned char m_padding[4];
	unsigned int m_value;
	unsigned int get();
};

// ?get@Rva00122AD0Owner@@QAEIXZ
unsigned int Rva00122AD0Owner::get()
{
	return m_value;
}

struct Gen_001273e0
{
	void *m(int value);
};

struct Rva00127AC0Owner
{
	void *invoke();
};

// ?invoke@Rva00127AC0Owner@@QAEPAXXZ
void *Rva00127AC0Owner::invoke()
{
	char local[4];
	return reinterpret_cast<Gen_001273e0 *>(this)->m((int)&local[3]);
}

struct Rva0012B000Owner
{
	Rva0012B000Owner *self();
};

// ?self@Rva0012B000Owner@@QAEPAU1@XZ
Rva0012B000Owner *Rva0012B000Owner::self()
{
	return this;
}

struct Rva00131D60Owner
{
	unsigned char m_padding[0x0C];
	float m_value;
	float get() const;
};

// ?get@Rva00131D60Owner@@QBEMXZ
float Rva00131D60Owner::get() const
{
	return m_value;
}

struct Rva00131D70Owner
{
	unsigned char m_padding[0x1C];
	float m_value;
	float get() const;
};

// ?get@Rva00131D70Owner@@QBEMXZ
float Rva00131D70Owner::get() const
{
	return m_value;
}

struct Rva00132110Owner
{
	int get() const;
};

// ?get@Rva00132110Owner@@QBEHXZ
int Rva00132110Owner::get() const
{
	return 0;
}

struct Rva00133090Owner
{
	Rva00133090Owner *self();
};

// ?self@Rva00133090Owner@@QAEPAU1@XZ
Rva00133090Owner *Rva00133090Owner::self()
{
	return this;
}

struct Rva001339F0Owner
{
	bool get() const;
};

// ?get@Rva001339F0Owner@@QBE_NXZ
bool Rva001339F0Owner::get() const
{
	return false;
}

struct Rva00133AB0Owner
{
	bool get() const;
};

// ?get@Rva00133AB0Owner@@QBE_NXZ
bool Rva00133AB0Owner::get() const
{
	return false;
}

struct Rva00133AC0Owner
{
	bool get() const;
};

// ?get@Rva00133AC0Owner@@QBE_NXZ
bool Rva00133AC0Owner::get() const
{
	return false;
}

struct Rva00133B40Owner
{
	bool get() const;
};

// ?get@Rva00133B40Owner@@QBE_NXZ
bool Rva00133B40Owner::get() const
{
	return false;
}

struct Rva00133B60Owner
{
	bool get() const;
};

// ?get@Rva00133B60Owner@@QBE_NXZ
bool Rva00133B60Owner::get() const
{
	return false;
}

struct Rva00133C30Owner
{
	unsigned char m_padding[0x478];
	unsigned short m_value;
	void set(unsigned short value);
};

// ?set@Rva00133C30Owner@@QAEXG@Z
void Rva00133C30Owner::set(unsigned short value)
{
	m_value = value;
}

struct Rva00139FB0Owner
{
	unsigned char m_padding[8];
	unsigned int m_value;
	unsigned int get();
};

// ?get@Rva00139FB0Owner@@QAEIXZ
unsigned int Rva00139FB0Owner::get()
{
	return m_value;
}

struct Rva00139FE0Owner
{
	unsigned char m_prefix[8];
	unsigned char m_value;
	unsigned char *address();
};

// ?address@Rva00139FE0Owner@@QAEPAEXZ
unsigned char *Rva00139FE0Owner::address()
{
	return &m_value;
}

struct Rva0013A060Owner
{
	unsigned int m_value;
	unsigned int get();
};

// ?get@Rva0013A060Owner@@QAEIXZ
unsigned int Rva0013A060Owner::get()
{
	return m_value;
}

struct Rva0013A310Owner
{
	unsigned char m_padding[4];
	void *m_base;
	void *at(unsigned int index);
};

// ?at@Rva0013A310Owner@@QAEPAXI@Z
void *Rva0013A310Owner::at(unsigned int index)
{
	return static_cast<unsigned char *>(m_base) + index * 4;
}

struct Rva0013DC90Owner
{
	unsigned char m_padding[4];
	unsigned int m_value;
	unsigned int get();
};

// ?get@Rva0013DC90Owner@@QAEIXZ
unsigned int Rva0013DC90Owner::get()
{
	return m_value;
}

struct Rva0013DCC0Owner
{
	unsigned char m_padding[4];
	unsigned int m_value;
	unsigned int get();
};

// ?get@Rva0013DCC0Owner@@QAEIXZ
unsigned int Rva0013DCC0Owner::get()
{
	return m_value;
}

struct Rva0013DCF0Owner
{
	unsigned char m_padding[4];
	unsigned int m_value;
	unsigned int get();
};

// ?get@Rva0013DCF0Owner@@QAEIXZ
unsigned int Rva0013DCF0Owner::get()
{
	return m_value;
}

struct Rva0013DD20Owner
{
	unsigned char m_padding[4];
	unsigned int m_value;
	unsigned int get();
};

// ?get@Rva0013DD20Owner@@QAEIXZ
unsigned int Rva0013DD20Owner::get()
{
	return m_value;
}
