// cl: /O2 /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD
// Retail bodies at 0x00382660-0x00382A60 are opaque four-byte accessors.

class Rva00382660Field
{
public:
	unsigned char m_padding[0x14];
	unsigned m_value;
	unsigned get(void) const;
};

unsigned Rva00382660Field::get(void) const
{
	return m_value;
}

class Rva003826F0Field
{
public:
	unsigned char m_padding[0x50];
	void *get(void) const;
};

void *Rva003826F0Field::get(void) const
{
	return (void *)(m_padding + 0x50);
}

class Rva00382700Field
{
public:
	unsigned char m_padding[0x60];
	void *get(void) const;
};

void *Rva00382700Field::get(void) const
{
	return (void *)(m_padding + 0x60);
}

class Rva00382710Field
{
public:
	unsigned char m_padding[0x64];
	void *get(void) const;
};

void *Rva00382710Field::get(void) const
{
	return (void *)(m_padding + 0x64);
}

class Rva00382770Field
{
public:
	unsigned char m_padding[0x34];
	void *get(void) const;
};

void *Rva00382770Field::get(void) const
{
	return (void *)(m_padding + 0x34);
}

class Rva003827D0Field
{
public:
	unsigned char m_padding[0x10];
	unsigned m_value;
	unsigned get(void) const;
};

unsigned Rva003827D0Field::get(void) const
{
	return m_value;
}

class Rva00382800Field
{
public:
	unsigned char m_padding[0x50];
	unsigned m_value;
	unsigned get(void) const;
};

unsigned Rva00382800Field::get(void) const
{
	return m_value;
}

class Rva00382830Field
{
public:
	unsigned char m_padding[0x20];
	void *get(void) const;
};

void *Rva00382830Field::get(void) const
{
	return (void *)(m_padding + 0x20);
}

class Rva00382930Field
{
public:
	unsigned char m_padding[2];
	unsigned char m_value;
	unsigned char get(void) const;
};

unsigned char Rva00382930Field::get(void) const
{
	return m_value;
}

class Rva00382940Field
{
public:
	unsigned char m_padding[8];
	void *get(void) const;
};

void *Rva00382940Field::get(void) const
{
	return (void *)(m_padding + 8);
}

class Rva003829A0Field
{
public:
	unsigned char m_padding[8];
	unsigned char m_value;
	unsigned char get(void) const;
};

unsigned char Rva003829A0Field::get(void) const
{
	return m_value;
}

class Rva003829D0Field
{
public:
	unsigned char m_padding[0x2c];
	unsigned char m_value;
	unsigned char get(void) const;
};

unsigned char Rva003829D0Field::get(void) const
{
	return m_value;
}

class Rva00382A10Field
{
public:
	unsigned char m_padding[0x48];
	unsigned m_value;
	unsigned get(void) const;
};

unsigned Rva00382A10Field::get(void) const
{
	return m_value;
}

class Rva00382A20Field
{
public:
	unsigned char m_padding[4];
	void *get(void) const;
};

void *Rva00382A20Field::get(void) const
{
	return (void *)(m_padding + 4);
}

class Rva00382A30Field
{
public:
	unsigned char m_padding[8];
	void *get(void) const;
};

void *Rva00382A30Field::get(void) const
{
	return (void *)(m_padding + 8);
}

class Rva00382A40Field
{
public:
	unsigned char m_padding[0x0c];
	unsigned char m_value;
	unsigned char get(void) const;
};

unsigned char Rva00382A40Field::get(void) const
{
	return m_value;
}

class Rva00382A50Field
{
public:
	unsigned char m_padding[0x14];
	unsigned char m_value;
	unsigned char get(void) const;
};

unsigned char Rva00382A50Field::get(void) const
{
	return m_value;
}

class Rva00382A60Field
{
public:
	unsigned char m_padding[0x10];
	unsigned m_value;
	unsigned get(void) const;
};

unsigned Rva00382A60Field::get(void) const
{
	return m_value;
}
