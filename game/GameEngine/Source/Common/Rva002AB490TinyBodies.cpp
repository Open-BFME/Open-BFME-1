// cl: /DNDEBUG /MD /EHs-c-

class Rva002AB490
{
public:
	int get() const;

private:
	unsigned char m_pad[ 4 ];
	int m_value;
};

// ?get@Rva002AB490@@QBEHXZ
int Rva002AB490::get() const
{
	return m_value;
}

class Rva002AC060
{
public:
	int get() const;

private:
	unsigned char m_pad[ 0x38 ];
	int m_value;
};

// ?get@Rva002AC060@@QBEHXZ
int Rva002AC060::get() const
{
	return m_value;
}

class Rva002AE1F0
{
public:
	int get() const;

private:
	unsigned char m_pad[ 4 ];
	int m_value;
};

// ?get@Rva002AE1F0@@QBEHXZ
int Rva002AE1F0::get() const
{
	return m_value;
}

class Rva002AF1D0
{
public:
	int get() const;

private:
	unsigned char m_pad[ 4 ];
	int m_value;
};

// ?get@Rva002AF1D0@@QBEHXZ
int Rva002AF1D0::get() const
{
	return m_value;
}

class Rva002B0AA0
{
public:
	int get() const;

private:
	unsigned char m_pad[ 4 ];
	int m_value;
};

// ?get@Rva002B0AA0@@QBEHXZ
int Rva002B0AA0::get() const
{
	return m_value;
}

class Rva002B0FA0
{
public:
	unsigned char get() const;
};

// ?get@Rva002B0FA0@@QBEEXZ
unsigned char Rva002B0FA0::get() const
{
	return 0;
}

class Rva002B0FC0
{
public:
	unsigned char get() const;
};

// ?get@Rva002B0FC0@@QBEEXZ
unsigned char Rva002B0FC0::get() const
{
	return 0;
}

class Rva002B0FD0
{
public:
	unsigned char get() const;
};

// ?get@Rva002B0FD0@@QBEEXZ
unsigned char Rva002B0FD0::get() const
{
	return 0;
}

class Rva002B1030
{
public:
	int get() const;

private:
	unsigned char m_pad[ 4 ];
	int m_value;
};

// ?get@Rva002B1030@@QBEHXZ
int Rva002B1030::get() const
{
	return m_value;
}

class Rva002B2130
{
public:
	void noop( int unused );
};

// ?noop@Rva002B2130@@QAEXH@Z
void Rva002B2130::noop( int unused )
{
}

class Rva002B2B10
{
public:
	unsigned char get() const;

private:
	unsigned char m_pad[ 0x18 ];
	unsigned char m_value;
};

// ?get@Rva002B2B10@@QBEEXZ
unsigned char Rva002B2B10::get() const
{
	return m_value;
}

class Rva002B2BC0
{
public:
	int get() const;

private:
	unsigned char m_pad[ 4 ];
	int m_value;
};

// ?get@Rva002B2BC0@@QBEHXZ
int Rva002B2BC0::get() const
{
	return m_value;
}

class Rva002B3070
{
public:
	int get() const;

private:
	unsigned char m_pad[ 4 ];
	int m_value;
};

// ?get@Rva002B3070@@QBEHXZ
int Rva002B3070::get() const
{
	return m_value;
}

class Rva002B4310
{
public:
	Rva002B4310();
	virtual void slot();
};

// ??0Rva002B4310@@QAE@XZ
Rva002B4310::Rva002B4310()
{
}

class Rva002B46E0
{
public:
	int get() const;

private:
	unsigned char m_pad[ 4 ];
	int m_value;
};

// ?get@Rva002B46E0@@QBEHXZ
int Rva002B46E0::get() const
{
	return m_value;
}

class Rva002B6830
{
public:
	int get() const;

private:
	unsigned char m_pad[ 0x20 ];
	int m_value;
};

// ?get@Rva002B6830@@QBEHXZ
int Rva002B6830::get() const
{
	return m_value;
}

class Rva002B6870
{
public:
	int get() const;

private:
	unsigned char m_pad[ 0x128 ];
	int m_value;
};

// ?get@Rva002B6870@@QBEHXZ
int Rva002B6870::get() const
{
	return m_value;
}

class Rva002B6AD0
{
public:
	int get() const;

private:
	unsigned char m_pad[ 4 ];
	int m_value;
};

// ?get@Rva002B6AD0@@QBEHXZ
int Rva002B6AD0::get() const
{
	return m_value;
}

class Rva002B6E70Holder
{
public:
	unsigned char m_pad[ 0x64 ];
	float m_value;
};

class Rva002B6E70
{
public:
	float get() const;
};

// ?get@Rva002B6E70@@QBEMXZ
float Rva002B6E70::get() const
{
	const Rva002B6E70Holder *holder =
		*(const Rva002B6E70Holder *const *)( (const char *)this - 0x33c );
	return holder->m_value;
}

class Rva002B7830
{
public:
	int get() const;
};

// ?get@Rva002B7830@@QBEHXZ
int Rva002B7830::get() const
{
	return 0;
}

class Rva002B9F50
{
public:
	void noop( int unused );
};

// ?noop@Rva002B9F50@@QAEXH@Z
void Rva002B9F50::noop( int unused )
{
}

class Rva002BA010
{
public:
	int get() const;

private:
	unsigned char m_pad[ 4 ];
	int m_value;
};

// ?get@Rva002BA010@@QBEHXZ
int Rva002BA010::get() const
{
	return m_value;
}

class Rva002BB850
{
public:
	int get() const;

private:
	int m_value;
};

// ?get@Rva002BB850@@QBEHXZ
int Rva002BB850::get() const
{
	return m_value;
}

struct Rva002BB920Block
{
	int m_first;
	int m_second;
	int m_third;
};

class Rva002BB920
{
public:
	void assign( const Rva002BB920Block &value );

private:
	unsigned char m_pad[ 0x47c ];
	Rva002BB920Block m_value;
};

// ?assign@Rva002BB920@@QAEXABURva002BB920Block@@@Z
void Rva002BB920::assign( const Rva002BB920Block &value )
{
	m_value = value;
}

class Rva002BB9F0
{
public:
	int get() const;

private:
	unsigned char m_pad[ 0x3fc ];
	int m_value;
};

// ?get@Rva002BB9F0@@QBEHXZ
int Rva002BB9F0::get() const
{
	return m_value;
}
