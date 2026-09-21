// cl: /O2 /Ob0 /DNDEBUG /MD /EHs-c-
// Address-derived ABI slices for complete tiny carved bodies.

class Rva006628E0Address
{
public:
	void *get() const;
};

// ?get@Rva006628E0Address@@QBEPAXXZ
void *Rva006628E0Address::get() const
{
	return (char *)this + 0x1c;
}

class Rva00662930Byte
{
public:
	unsigned char get() const;

private:
	char m_padding[0x0c];
	unsigned char m_value;
};

// ?get@Rva00662930Byte@@QBEEXZ
unsigned char Rva00662930Byte::get() const
{
	return m_value;
}

class Rva00662980Address
{
public:
	void *get() const;
};

// ?get@Rva00662980Address@@QBEPAXXZ
void *Rva00662980Address::get() const
{
	return (char *)this + 0x14;
}

class Rva006629C0Dword
{
public:
	unsigned int get() const;

private:
	unsigned int m_value;
};

// ?get@Rva006629C0Dword@@QBEIXZ
unsigned int Rva006629C0Dword::get() const
{
	return m_value;
}

class Rva006629D0Float
{
public:
	float get() const;

private:
	char m_padding[0x20];
	float m_value;
};

// ?get@Rva006629D0Float@@QBEMXZ
float Rva006629D0Float::get() const
{
	return m_value;
}

class Rva00663C60Self
{
public:
	void *identity() const;
};

// ?identity@Rva00663C60Self@@QBEPAXXZ
void *Rva00663C60Self::identity() const
{
	return (void *)this;
}

class Rva00663C80Self
{
public:
	void *identity() const;
};

// ?identity@Rva00663C80Self@@QBEPAXXZ
void *Rva00663C80Self::identity() const
{
	return (void *)this;
}

class Rva00663CA0Self
{
public:
	void *identity() const;
};

// ?identity@Rva00663CA0Self@@QBEPAXXZ
void *Rva00663CA0Self::identity() const
{
	return (void *)this;
}

class Rva00663CD0DwordPlusTen
{
public:
	unsigned int get() const;

private:
	unsigned int m_value;
};

// ?get@Rva00663CD0DwordPlusTen@@QBEIXZ
unsigned int Rva00663CD0DwordPlusTen::get() const
{
	return m_value + 0x10;
}

class Rva00663D30DwordPlusTen
{
public:
	unsigned int get() const;

private:
	unsigned int m_value;
};

// ?get@Rva00663D30DwordPlusTen@@QBEIXZ
unsigned int Rva00663D30DwordPlusTen::get() const
{
	return m_value + 0x10;
}

class Rva00664050Dword
{
public:
	unsigned int get() const;

private:
	char m_padding[4];
	unsigned int m_value;
};

// ?get@Rva00664050Dword@@QBEIXZ
unsigned int Rva00664050Dword::get() const
{
	return m_value;
}

class Rva00664080Dword
{
public:
	unsigned int get() const;

private:
	char m_padding[4];
	unsigned int m_value;
};

// ?get@Rva00664080Dword@@QBEIXZ
unsigned int Rva00664080Dword::get() const
{
	return m_value;
}

class Rva00670D50Noop
{
public:
	void invoke(int value);
};

// ?invoke@Rva00670D50Noop@@QAEXH@Z
void Rva00670D50Noop::invoke(int value)
{
}

class Rva00670D60Noop
{
public:
	void invoke(int value);
};

// ?invoke@Rva00670D60Noop@@QAEXH@Z
void Rva00670D60Noop::invoke(int value)
{
}

class Rva006795D0Self
{
public:
	void *identity() const;
};

// ?identity@Rva006795D0Self@@QBEPAXXZ
void *Rva006795D0Self::identity() const
{
	return (void *)this;
}

// ?Rva006795E0NoOp@@YAXXZ
void Rva006795E0NoOp()
{
}

class Rva00681D60Dword
{
public:
	unsigned int get() const;

private:
	char m_padding[0x2c];
	unsigned int m_value;
};

// ?get@Rva00681D60Dword@@QBEIXZ
unsigned int Rva00681D60Dword::get() const
{
	return m_value;
}

class Rva00684BD0Dword
{
public:
	unsigned int get() const;

private:
	char m_padding[0x64];
	unsigned int m_value;
};

// ?get@Rva00684BD0Dword@@QBEIXZ
unsigned int Rva00684BD0Dword::get() const
{
	return m_value;
}

class Rva00684C20Indexed
{
public:
	void *get(int index);
};

// ?get@Rva00684C20Indexed@@QAEPAXH@Z
void *Rva00684C20Indexed::get(int index)
{
	return (char *)this + 0x88 + index * 0x68;
}

class Rva00684C50Byte
{
public:
	unsigned char get() const;

private:
	char m_padding[0x3a4];
	unsigned char m_value;
};

// ?get@Rva00684C50Byte@@QBEEXZ
unsigned char Rva00684C50Byte::get() const
{
	return m_value;
}

class Rva00685620Dword
{
public:
	unsigned int get() const;

private:
	char m_padding[0x40];
	unsigned int m_value;
};

// ?get@Rva00685620Dword@@QBEIXZ
unsigned int Rva00685620Dword::get() const
{
	return m_value;
}

class Rva00685630Address
{
public:
	void *get() const;
};

// ?get@Rva00685630Address@@QBEPAXXZ
void *Rva00685630Address::get() const
{
	return (char *)this + 0x44;
}

class Rva00686DE0Self
{
public:
	void *identity() const;
};

// ?identity@Rva00686DE0Self@@QBEPAXXZ
void *Rva00686DE0Self::identity() const
{
	return (void *)this;
}

class Rva0068DA30Self
{
public:
	void *identity() const;
};

// ?identity@Rva0068DA30Self@@QBEPAXXZ
void *Rva0068DA30Self::identity() const
{
	return (void *)this;
}
