// cl: /O2 /DNDEBUG /MD
// Address-derived leaf accessors recovered from carved retail bodies.

class Rva00336550
{
public:
	const char *getAddress() const;

	char m_storage[0x0d];
};

// ?getAddress@Rva00336550@@QBEPBDXZ
const char *Rva00336550::getAddress() const
{
	return m_storage + 0x0c;
}

class Rva003365B0
{
public:
	unsigned char getByte() const;

	char m_padding[0x0c];
	unsigned char m_value;
};

// ?getByte@Rva003365B0@@QBEEXZ
unsigned char Rva003365B0::getByte() const
{
	return m_value;
}

class Rva003365C0
{
public:
	unsigned char getByte() const;

	char m_padding[0x0d];
	unsigned char m_value;
};

// ?getByte@Rva003365C0@@QBEEXZ
unsigned char Rva003365C0::getByte() const
{
	return m_value;
}

class Rva003365D0
{
public:
	unsigned int getDword() const;

	char m_padding[0x04];
	unsigned int m_value;
};

// ?getDword@Rva003365D0@@QBEIXZ
unsigned int Rva003365D0::getDword() const
{
	return m_value;
}

class Rva003365E0
{
public:
	unsigned int getDword() const;

	char m_padding[0x08];
	unsigned int m_value;
};

// ?getDword@Rva003365E0@@QBEIXZ
unsigned int Rva003365E0::getDword() const
{
	return m_value;
}

class Rva00336600
{
public:
	unsigned int getDword() const;

	char m_padding[0x3c];
	unsigned int m_value;
};

// ?getDword@Rva00336600@@QBEIXZ
unsigned int Rva00336600::getDword() const
{
	return m_value;
}

class Rva00336620
{
public:
	void incrementDword();

	char m_padding[0x3c];
	unsigned int m_value;
};

// ?incrementDword@Rva00336620@@QAEXXZ
void Rva00336620::incrementDword()
{
	++m_value;
}

class Rva00336650
{
public:
	float getFloat() const;

	char m_padding[0x34];
	float m_value;
};

// ?getFloat@Rva00336650@@QBEMXZ
float Rva00336650::getFloat() const
{
	return m_value;
}

class Rva00336660
{
public:
	unsigned char getByte() const;

	char m_padding[0x17];
	unsigned char m_value;
};

// ?getByte@Rva00336660@@QBEEXZ
unsigned char Rva00336660::getByte() const
{
	return m_value;
}

class Rva00336680
{
public:
	unsigned int getDword() const;

	char m_padding[0x24];
	unsigned int m_value;
};

// ?getDword@Rva00336680@@QBEIXZ
unsigned int Rva00336680::getDword() const
{
	return m_value;
}

class Rva00336690
{
public:
	unsigned int getDword() const;

	unsigned int m_value;
};

// ?getDword@Rva00336690@@QBEIXZ
unsigned int Rva00336690::getDword() const
{
	return m_value;
}

class Rva003366C0
{
public:
	Rva003366C0 *clearFirstByte();

	unsigned char m_value;
};

// ?clearFirstByte@Rva003366C0@@QAEPAV1@XZ
Rva003366C0 *Rva003366C0::clearFirstByte()
{
	m_value = 0;
	return this;
}

class Rva003366F0
{
public:
	unsigned char getByte() const;

	char m_padding[0x1d];
	unsigned char m_value;
};

// ?getByte@Rva003366F0@@QBEEXZ
unsigned char Rva003366F0::getByte() const
{
	return m_value;
}

class Rva00336710
{
public:
	unsigned int getDword() const;

	char m_padding[0x04];
	unsigned int m_value;
};

// ?getDword@Rva00336710@@QBEIXZ
unsigned int Rva00336710::getDword() const
{
	return m_value;
}

class Rva00336850
{
public:
	void *getThis();
};

// ?getThis@Rva00336850@@QAEPAXXZ
void *Rva00336850::getThis()
{
	return this;
}

class Rva00336890
{
public:
	void *getThis();
};

// ?getThis@Rva00336890@@QAEPAXXZ
void *Rva00336890::getThis()
{
	return this;
}
