// cl: /O2 /DNDEBUG /MD
// Address-derived owners for complete carved leaf bodies.

#include <math.h>

#pragma intrinsic(tan)

#define BfmeKTHE (*(const float *)0x0109ECC0)

class Rva007AE410ByteField
{
public:
	unsigned char get() const;

private:
	char m_padding[0x64];
	unsigned char m_value;
};

// ?get@Rva007AE410ByteField@@QBEEXZ
unsigned char Rva007AE410ByteField::get() const
{
	return m_value;
}

class Rva007AE740AddressField
{
public:
	void *get();

private:
	char m_padding[0x34];
};

// ?get@Rva007AE740AddressField@@QAEPAXXZ
void *Rva007AE740AddressField::get()
{
	return m_padding + 0x34;
}

class Rva007AE750AddressField
{
public:
	void *get();

private:
	char m_padding[0x7c];
};

// ?get@Rva007AE750AddressField@@QAEPAXXZ
void *Rva007AE750AddressField::get()
{
	return m_padding + 0x7c;
}

class Rva007AF070Self
{
public:
	Rva007AF070Self *getThis();
};

// ?getThis@Rva007AF070Self@@QAEPAV1@XZ
Rva007AF070Self *Rva007AF070Self::getThis()
{
	return this;
}

class Rva007AF2D0FloatField
{
public:
	float get() const;

private:
	char m_padding[0x20];
	float m_value;
};

// ?get@Rva007AF2D0FloatField@@QBEMXZ
float Rva007AF2D0FloatField::get() const
{
	return m_value;
}

class Rva007AF4A0AddressField
{
public:
	void *get();

private:
	char m_padding[8];
};

// ?get@Rva007AF4A0AddressField@@QAEPAXXZ
void *Rva007AF4A0AddressField::get()
{
	return m_padding + 8;
}

class Rva007B10F0DwordField
{
public:
	unsigned int get() const;

private:
	char m_padding[8];
	unsigned int m_value;
};

// ?get@Rva007B10F0DwordField@@QBEIXZ
unsigned int Rva007B10F0DwordField::get() const
{
	return m_value;
}

class Rva007B7C70DwordField
{
public:
	unsigned int get() const;

private:
	char m_padding[4];
	unsigned int m_value;
};

// ?get@Rva007B7C70DwordField@@QBEIXZ
unsigned int Rva007B7C70DwordField::get() const
{
	return m_value;
}

class Rva007B7F40DwordField
{
public:
	unsigned int get() const;

private:
	char m_padding[0x18];
	unsigned int m_value;
};

// ?get@Rva007B7F40DwordField@@QBEIXZ
unsigned int Rva007B7F40DwordField::get() const
{
	return m_value;
}

class Rva007B7F60DwordField
{
public:
	unsigned int get() const;

private:
	char m_padding[0x10];
	unsigned int m_value;
};

// ?get@Rva007B7F60DwordField@@QBEIXZ
unsigned int Rva007B7F60DwordField::get() const
{
	return m_value;
}

class Rva007B7F70DwordField
{
public:
	unsigned int get() const;

private:
	char m_padding[0x14];
	unsigned int m_value;
};

// ?get@Rva007B7F70DwordField@@QBEIXZ
unsigned int Rva007B7F70DwordField::get() const
{
	return m_value;
}

class Rva007B80F0DwordField
{
public:
	unsigned int get() const;

private:
	char m_padding[0x1c];
	unsigned int m_value;
};

// ?get@Rva007B80F0DwordField@@QBEIXZ
unsigned int Rva007B80F0DwordField::get() const
{
	return m_value;
}

class Rva007B8120DwordField
{
public:
	unsigned int get() const;

private:
	char m_padding[0x14];
	unsigned int m_value;
};

// ?get@Rva007B8120DwordField@@QBEIXZ
unsigned int Rva007B8120DwordField::get() const
{
	return m_value;
}

class Rva007B96A0Self
{
public:
	Rva007B96A0Self *getThis();
};

// ?getThis@Rva007B96A0Self@@QAEPAV1@XZ
Rva007B96A0Self *Rva007B96A0Self::getThis()
{
	return this;
}

class Rva007C0520ByteField
{
public:
	unsigned char get() const;

private:
	char m_padding[4];
	unsigned char m_value;
};

// ?get@Rva007C0520ByteField@@QBEEXZ
unsigned char Rva007C0520ByteField::get() const
{
	return m_value;
}

class Rva007C0E70Tangent
{
public:
	void set(float angle);

private:
	char m_padding[0x88];
	float m_value;
};

// ?set@Rva007C0E70Tangent@@QAEXM@Z
void Rva007C0E70Tangent::set(float angle)
{
	m_value = (float)tan(angle * BfmeKTHE);
}

class Rva007C5570DwordField
{
public:
	unsigned int get() const;

private:
	char m_padding[0x20];
	unsigned int m_value;
};

// ?get@Rva007C5570DwordField@@QBEIXZ
unsigned int Rva007C5570DwordField::get() const
{
	return m_value;
}

class Rva007C5580DwordField
{
public:
	unsigned int get() const;

private:
	char m_padding[0x24];
	unsigned int m_value;
};

// ?get@Rva007C5580DwordField@@QBEIXZ
unsigned int Rva007C5580DwordField::get() const
{
	return m_value;
}

class Rva007C5590FloatField
{
public:
	float get() const;

private:
	char m_padding[0x2c];
	float m_value;
};

// ?get@Rva007C5590FloatField@@QBEMXZ
float Rva007C5590FloatField::get() const
{
	return m_value;
}

class Rva007C55A0FloatField
{
public:
	float get() const;

private:
	char m_padding[0x30];
	float m_value;
};

// ?get@Rva007C55A0FloatField@@QBEMXZ
float Rva007C55A0FloatField::get() const
{
	return m_value;
}

class Rva007D0C70Self
{
public:
	Rva007D0C70Self *getThis();
};

// ?getThis@Rva007D0C70Self@@QAEPAV1@XZ
Rva007D0C70Self *Rva007D0C70Self::getThis()
{
	return this;
}

class Rva007D1EF0Self
{
public:
	Rva007D1EF0Self *getThis();
};

// ?getThis@Rva007D1EF0Self@@QAEPAV1@XZ
Rva007D1EF0Self *Rva007D1EF0Self::getThis()
{
	return this;
}

class Rva007D2300Self
{
public:
	Rva007D2300Self *getThis();
};

// ?getThis@Rva007D2300Self@@QAEPAV1@XZ
Rva007D2300Self *Rva007D2300Self::getThis()
{
	return this;
}

class Rva007D4E70Self
{
public:
	Rva007D4E70Self *getThis();
};

// ?getThis@Rva007D4E70Self@@QAEPAV1@XZ
Rva007D4E70Self *Rva007D4E70Self::getThis()
{
	return this;
}

#undef BfmeKTHE
