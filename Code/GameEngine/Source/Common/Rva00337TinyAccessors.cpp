// Address-derived reconstructions of retail's tiny thiscall accessors.
// The owner and method identities remain unresolved; each class retains its RVA.
// Retail proves only a 32-bit receiver-relative read or a this-pointer return.

// cl: /DNDEBUG /MD

class Rva00337360
{
public:
	unsigned int get() const;

private:
	unsigned char m_padding[0x1C];
	unsigned int m_value;
};

// ?get@Rva00337360@@QBEIXZ
unsigned int Rva00337360::get() const
{
	return m_value;
}

class Rva00337370
{
public:
	unsigned int get() const;

private:
	unsigned int m_value;
};

// ?get@Rva00337370@@QBEIXZ
unsigned int Rva00337370::get() const
{
	return m_value;
}

class Rva003373A0
{
public:
	Rva003373A0 *get();
};

// ?get@Rva003373A0@@QAEPAV1@XZ
Rva003373A0 *Rva003373A0::get()
{
	return this;
}

class Rva003373E0
{
public:
	Rva003373E0 *get();
};

// ?get@Rva003373E0@@QAEPAV1@XZ
Rva003373E0 *Rva003373E0::get()
{
	return this;
}

class Rva003374A0
{
public:
	Rva003374A0 *get();
};

// ?get@Rva003374A0@@QAEPAV1@XZ
Rva003374A0 *Rva003374A0::get()
{
	return this;
}

class Rva003374C0
{
public:
	unsigned int get() const;

private:
	unsigned int m_value;
};

// ?get@Rva003374C0@@QBEIXZ
unsigned int Rva003374C0::get() const
{
	return m_value;
}

class Rva003374F0
{
public:
	unsigned int get() const;

private:
	unsigned char m_padding[4];
	unsigned int m_value;
};

// ?get@Rva003374F0@@QBEIXZ
unsigned int Rva003374F0::get() const
{
	return m_value;
}

class Rva00337520
{
public:
	Rva00337520 *get();
};

// ?get@Rva00337520@@QAEPAV1@XZ
Rva00337520 *Rva00337520::get()
{
	return this;
}

class Rva00337710
{
public:
	Rva00337710 *get();
};

// ?get@Rva00337710@@QAEPAV1@XZ
Rva00337710 *Rva00337710::get()
{
	return this;
}

class Rva00337820
{
public:
	unsigned int get() const;

private:
	unsigned char m_padding[4];
	unsigned int m_value;
};

// ?get@Rva00337820@@QBEIXZ
unsigned int Rva00337820::get() const
{
	return m_value;
}

class Rva00337830
{
public:
	Rva00337830 *get();
};

// ?get@Rva00337830@@QAEPAV1@XZ
Rva00337830 *Rva00337830::get()
{
	return this;
}

class Rva00337890
{
public:
	Rva00337890 *get();
};

// ?get@Rva00337890@@QAEPAV1@XZ
Rva00337890 *Rva00337890::get()
{
	return this;
}

class Rva003378B0
{
public:
	unsigned int get() const;

private:
	unsigned char m_padding[4];
	unsigned int m_value;
};

// ?get@Rva003378B0@@QBEIXZ
unsigned int Rva003378B0::get() const
{
	return m_value;
}

class Rva003378C0
{
public:
	Rva003378C0 *get();
};

// ?get@Rva003378C0@@QAEPAV1@XZ
Rva003378C0 *Rva003378C0::get()
{
	return this;
}

class Rva00337960
{
public:
	int get() const;

private:
	int m_value;
};

// ?get@Rva00337960@@QBEHXZ
int Rva00337960::get() const
{
	return m_value + 0x10;
}

class Rva00337AC0
{
public:
	unsigned int get() const;

private:
	unsigned int m_value;
};

// ?get@Rva00337AC0@@QBEIXZ
unsigned int Rva00337AC0::get() const
{
	return m_value;
}

class Rva00337AD0
{
public:
	unsigned int get() const;

private:
	unsigned int m_value;
};

// ?get@Rva00337AD0@@QBEIXZ
unsigned int Rva00337AD0::get() const
{
	return m_value;
}
