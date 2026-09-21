// cl: /O2 /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHs-c-

class Rva001FB540Dword
{
private:
	unsigned char m_pad[4];

public:
	unsigned int m_value;
	unsigned int get() const;
};

class Rva001FBC60Dword
{
private:
	unsigned char m_pad[4];

public:
	unsigned int m_value;
	unsigned int get() const;
};

class Rva001FBEC0False
{
public:
	bool get() const;
};

class Rva001FC3B0Float
{
private:
	unsigned char m_pad[0x38];

public:
	float m_value;
	float get() const;
};

class Rva001FC3C0Byte
{
private:
	unsigned char m_pad[0x30];

public:
	unsigned char m_value;
	unsigned char get() const;
};

class Rva001FC3E0Dword
{
private:
	unsigned char m_pad[0x2c];

public:
	unsigned int m_value;
	unsigned int get() const;
};

class Rva001FC470MinusOne
{
public:
	int get() const;
};

class Rva001FC540Dword
{
private:
	unsigned char m_pad[8];

public:
	unsigned int m_value;
	unsigned int get() const;
};

class Rva001FE4A0Byte
{
private:
	unsigned char m_pad[0x12];

public:
	bool m_value;
	bool get() const;
};

class Rva001FE4B0FloatFromInt
{
private:
	unsigned char m_pad[0x18];

public:
	int m_value;
	float get() const;
};

class Rva001FE4C0Byte
{
private:
	unsigned char m_pad[0x15];

public:
	bool m_value;
	bool get() const;
};

class Rva001FFB00Byte
{
private:
	unsigned char m_pad[0x5e];

public:
	bool m_value;
	bool get() const;
};

class Rva00200190Dword
{
private:
	unsigned char m_pad[4];

public:
	unsigned int m_value;
	unsigned int get() const;
};

class Rva00200900Self
{
public:
	void *get() const;
};

class Rva00200920Self
{
public:
	void *get() const;
};

class Rva00200940Dword
{
public:
	unsigned int m_value;
	unsigned int get() const;
};

class Rva00200950Dword
{
public:
	unsigned int m_value;
	unsigned int get() const;
};

class Rva00200960Dword
{
public:
	unsigned int m_value;
	unsigned int get() const;
};

class Rva00200970Dword
{
public:
	unsigned int m_value;
	unsigned int get() const;
};

class Rva00200AB0Dword
{
private:
	unsigned char m_pad[4];

public:
	unsigned int m_value;
	unsigned int get() const;
};

class Rva00201B80Dword
{
private:
	unsigned char m_pad[4];

public:
	unsigned int m_value;
	unsigned int get() const;
};

class Rva002029A0Dword
{
private:
	unsigned char m_pad[4];

public:
	unsigned int m_value;
	unsigned int get() const;
};

class Rva00202EE0Dword
{
private:
	unsigned char m_pad[4];

public:
	unsigned int m_value;
	unsigned int get() const;
};

class Rva00203BF0Dword
{
private:
	unsigned char m_pad[4];

public:
	unsigned int m_value;
	unsigned int get() const;
};

// ?get@Rva001FB540Dword@@QBEIXZ
unsigned int Rva001FB540Dword::get() const
{
	return m_value;
}

// ?get@Rva001FBC60Dword@@QBEIXZ
unsigned int Rva001FBC60Dword::get() const
{
	return m_value;
}

// ?get@Rva001FBEC0False@@QBE_NXZ
bool Rva001FBEC0False::get() const
{
	return false;
}

// ?get@Rva001FC3B0Float@@QBEMXZ
float Rva001FC3B0Float::get() const
{
	return m_value;
}

// ?get@Rva001FC3C0Byte@@QBEEXZ
unsigned char Rva001FC3C0Byte::get() const
{
	return m_value;
}

// ?get@Rva001FC3E0Dword@@QBEIXZ
unsigned int Rva001FC3E0Dword::get() const
{
	return m_value;
}

// ?get@Rva001FC470MinusOne@@QBEHXZ
int Rva001FC470MinusOne::get() const
{
	return -1;
}

// ?get@Rva001FC540Dword@@QBEIXZ
unsigned int Rva001FC540Dword::get() const
{
	return m_value;
}

// ?get@Rva001FE4A0Byte@@QBE_NXZ
bool Rva001FE4A0Byte::get() const
{
	return m_value;
}

// ?get@Rva001FE4B0FloatFromInt@@QBEMXZ
float Rva001FE4B0FloatFromInt::get() const
{
	return (float)m_value;
}

// ?get@Rva001FE4C0Byte@@QBE_NXZ
bool Rva001FE4C0Byte::get() const
{
	return m_value;
}

// ?get@Rva001FFB00Byte@@QBE_NXZ
bool Rva001FFB00Byte::get() const
{
	return m_value;
}

// ?get@Rva00200190Dword@@QBEIXZ
unsigned int Rva00200190Dword::get() const
{
	return m_value;
}

// ?get@Rva00200900Self@@QBEPAXXZ
void *Rva00200900Self::get() const
{
	return (void *)this;
}

// ?get@Rva00200920Self@@QBEPAXXZ
void *Rva00200920Self::get() const
{
	return (void *)this;
}

// Retail 0x00200930 is a one-byte standalone ret with no proven semantic identity.
void Rva00200930()
{
}

// ?get@Rva00200940Dword@@QBEIXZ
unsigned int Rva00200940Dword::get() const
{
	return m_value;
}

// ?get@Rva00200950Dword@@QBEIXZ
unsigned int Rva00200950Dword::get() const
{
	return m_value;
}

// ?get@Rva00200960Dword@@QBEIXZ
unsigned int Rva00200960Dword::get() const
{
	return m_value;
}

// ?get@Rva00200970Dword@@QBEIXZ
unsigned int Rva00200970Dword::get() const
{
	return m_value;
}

// ?get@Rva00200AB0Dword@@QBEIXZ
unsigned int Rva00200AB0Dword::get() const
{
	return m_value;
}

// ?get@Rva00201B80Dword@@QBEIXZ
unsigned int Rva00201B80Dword::get() const
{
	return m_value;
}

// ?Rva00202920@@YGXPAX@Z
void __stdcall Rva00202920(void *)
{
}

// ?get@Rva002029A0Dword@@QBEIXZ
unsigned int Rva002029A0Dword::get() const
{
	return m_value;
}

// ?get@Rva00202EE0Dword@@QBEIXZ
unsigned int Rva00202EE0Dword::get() const
{
	return m_value;
}

// ?get@Rva00203BF0Dword@@QBEIXZ
unsigned int Rva00203BF0Dword::get() const
{
	return m_value;
}
