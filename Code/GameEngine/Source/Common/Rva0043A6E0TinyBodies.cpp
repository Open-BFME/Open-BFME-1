// cl: /O2 /DNDEBUG /MD /EHsc
// Address-derived owners for complete tiny carved bodies.

template <typename Char>
class StringBase
{
	friend class UnicodeString;

	private:
	void releaseBuffer();
};

class UnicodeString : private StringBase<unsigned short>
{
public:
	~UnicodeString() { releaseBuffer(); }
};

class Rva0043A6E0Body
{
public:
	void body(unsigned char value);

private:
	unsigned char m_padding[0x12B3];
	unsigned char m_value;
};

// ?body@Rva0043A6E0Body@@QAEXE@Z
void Rva0043A6E0Body::body(unsigned char value)
{
	m_value = value;
}

class Rva0043A6F0Body
{
public:
	void body(unsigned char value);

private:
	unsigned char m_padding[0x12B4];
	unsigned char m_value;
};

// ?body@Rva0043A6F0Body@@QAEXE@Z
void Rva0043A6F0Body::body(unsigned char value)
{
	m_value = value;
}

class Rva0043A700Body
{
public:
	void body(unsigned char value);

private:
	unsigned char m_padding[0x12B5];
	unsigned char m_value;
};

// ?body@Rva0043A700Body@@QAEXE@Z
void Rva0043A700Body::body(unsigned char value)
{
	m_value = value;
}

class Rva0043A710Body
{
public:
	void body(unsigned char value);

private:
	unsigned char m_padding[0x12B6];
	unsigned char m_value;
};

// ?body@Rva0043A710Body@@QAEXE@Z
void Rva0043A710Body::body(unsigned char value)
{
	m_value = value;
}

class Rva0043A730Body
{
public:
	void body(unsigned char value);

private:
	unsigned char m_padding[0x12B8];
	unsigned char m_value;
};

// ?body@Rva0043A730Body@@QAEXE@Z
void Rva0043A730Body::body(unsigned char value)
{
	m_value = value;
}

class Rva0043A760Body
{
public:
	void body(unsigned char value);

private:
	unsigned char m_padding[0x12BB];
	unsigned char m_value;
};

// ?body@Rva0043A760Body@@QAEXE@Z
void Rva0043A760Body::body(unsigned char value)
{
	m_value = value;
}

class Rva0043A770Body
{
public:
	void body();

private:
	unsigned char m_padding[0x554];
	int m_value;
};

// ?body@Rva0043A770Body@@QAEXXZ
void Rva0043A770Body::body()
{
	++m_value;
}

class Rva0043A7B0Body
{
public:
	unsigned char body() const;

private:
	unsigned char m_padding[0x58];
	unsigned char m_value;
};

// ?body@Rva0043A7B0Body@@QBEEXZ
unsigned char Rva0043A7B0Body::body() const
{
	return m_value;
}

class Rva0043A7D0Body
{
public:
	float body() const;

private:
	unsigned char m_padding[0x28];
	float m_value;
};

// ?body@Rva0043A7D0Body@@QBEMXZ
float Rva0043A7D0Body::body() const
{
	return m_value;
}

class Rva0043DEE0Body
{
public:
	void body(UnicodeString value, ...);
};

// ?body@Rva0043DEE0Body@@QAAXVUnicodeString@@ZZ
void Rva0043DEE0Body::body(UnicodeString value, ...)
{
}

class Rva0043DEF0Body
{
public:
	void body(const void *color, UnicodeString value, ...);
};

// ?body@Rva0043DEF0Body@@QAAXPBXVUnicodeString@@ZZ
void Rva0043DEF0Body::body(const void *color, UnicodeString value, ...)
{
}

class Rva0044CC10Body
{
public:
	Rva0044CC10Body *body();
};

// ?body@Rva0044CC10Body@@QAEPAV1@XZ
Rva0044CC10Body *Rva0044CC10Body::body()
{
	return this;
}

class Rva0044CC40Body
{
public:
	char *body() const;

private:
	char *m_value;
};

// ?body@Rva0044CC40Body@@QBEPADXZ
char *Rva0044CC40Body::body() const
{
	return m_value + 0x10;
}

class Rva0044CD40Body
{
public:
	int body() const;

private:
	unsigned char m_padding[4];
	int m_value;
};

// ?body@Rva0044CD40Body@@QBEHXZ
int Rva0044CD40Body::body() const
{
	return m_value;
}

class Rva0044F360Body
{
public:
	void body(int value);
};

// ?body@Rva0044F360Body@@QAEXH@Z
void Rva0044F360Body::body(int value)
{
}

class Rva0044F5F0Body
{
public:
	unsigned char body() const;

private:
	unsigned char m_value;
};

// ?body@Rva0044F5F0Body@@QBEEXZ
unsigned char Rva0044F5F0Body::body() const
{
	return m_value;
}

class Rva0044F6B0Body
{
public:
	int body() const;

private:
	unsigned char m_padding[0x48];
	int m_value;
};

// ?body@Rva0044F6B0Body@@QBEHXZ
int Rva0044F6B0Body::body() const
{
	return m_value;
}

class Rva0044F6C0Body
{
public:
	unsigned char body() const;

private:
	unsigned char m_padding[0xD];
	unsigned char m_value;
};

// ?body@Rva0044F6C0Body@@QBEEXZ
unsigned char Rva0044F6C0Body::body() const
{
	return m_value;
}

class Rva0044FC10Body
{
public:
	int body() const;

private:
	int m_value;
};

// ?body@Rva0044FC10Body@@QBEHXZ
int Rva0044FC10Body::body() const
{
	return m_value;
}

class Rva0044FC20Body
{
public:
	Rva0044FC20Body *body();
};

// ?body@Rva0044FC20Body@@QAEPAV1@XZ
Rva0044FC20Body *Rva0044FC20Body::body()
{
	return this;
}

class Rva0044FCA0Body
{
public:
	Rva0044FCA0Body *body();
};

// ?body@Rva0044FCA0Body@@QAEPAV1@XZ
Rva0044FCA0Body *Rva0044FCA0Body::body()
{
	return this;
}

class Rva0044FF30Body
{
public:
	unsigned char body() const;
};

// ?body@Rva0044FF30Body@@QBEEXZ
unsigned char Rva0044FF30Body::body() const
{
	return 0;
}

class Rva0044FF40Body
{
public:
	unsigned char body() const;
};

// ?body@Rva0044FF40Body@@QBEEXZ
unsigned char Rva0044FF40Body::body() const
{
	return 0;
}

class Rva0044FF50Body
{
public:
	unsigned char body() const;
};

// ?body@Rva0044FF50Body@@QBEEXZ
unsigned char Rva0044FF50Body::body() const
{
	return 0;
}

class Rva0044FFF0Body
{
public:
	int body() const;

private:
	unsigned char m_padding[4];
	int m_value;
};

// ?body@Rva0044FFF0Body@@QBEHXZ
int Rva0044FFF0Body::body() const
{
	return m_value;
}
