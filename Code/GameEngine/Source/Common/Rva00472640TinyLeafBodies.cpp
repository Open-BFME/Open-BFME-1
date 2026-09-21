// The carved bodies below have complete ret boundaries but no semantic owner.
// Their RVA-derived types preserve the observed ABI without inventing names.

class Rva00472640Owner
{
public:
	int get() const;

private:
	int m_value;
};

// ?get@Rva00472640Owner@@QBEHXZ
int Rva00472640Owner::get() const
{
	return m_value;
}

class Rva00472650Owner
{
public:
	int get() const;

private:
	int m_value;
};

// ?get@Rva00472650Owner@@QBEHXZ
int Rva00472650Owner::get() const
{
	return m_value;
}

class Rva00472680Owner
{
public:
	int get() const;

private:
	int m_value;
};

// ?get@Rva00472680Owner@@QBEHXZ
int Rva00472680Owner::get() const
{
	return m_value;
}

class Rva004726B0Owner
{
public:
	int get() const;

private:
	char m_prefix[4];
	int m_value;
};

// ?get@Rva004726B0Owner@@QBEHXZ
int Rva004726B0Owner::get() const
{
	return m_value;
}

class Rva004726D0Owner
{
public:
	int get() const;

private:
	int m_value;
};

// ?get@Rva004726D0Owner@@QBEHXZ
int Rva004726D0Owner::get() const
{
	return m_value;
}

class Rva004726F0Owner
{
public:
	Rva004726F0Owner *identity();
};

// ?identity@Rva004726F0Owner@@QAEPAV1@XZ
Rva004726F0Owner *Rva004726F0Owner::identity()
{
	return this;
}

class Rva00472730Owner
{
public:
	int get() const;

private:
	int m_value;
};

// ?get@Rva00472730Owner@@QBEHXZ
int Rva00472730Owner::get() const
{
	return m_value;
}

class Rva00472740Owner
{
public:
	Rva00472740Owner *identity();
};

// ?identity@Rva00472740Owner@@QAEPAV1@XZ
Rva00472740Owner *Rva00472740Owner::identity()
{
	return this;
}

class Rva00472760Owner
{
public:
	Rva00472760Owner *identity();
};

// ?identity@Rva00472760Owner@@QAEPAV1@XZ
Rva00472760Owner *Rva00472760Owner::identity()
{
	return this;
}

class Rva00472780Owner
{
public:
	Rva00472780Owner *identity();
};

// ?identity@Rva00472780Owner@@QAEPAV1@XZ
Rva00472780Owner *Rva00472780Owner::identity()
{
	return this;
}

// ?Rva00472790NoOp@@YAXXZ
void Rva00472790NoOp()
{
}

// ?Rva00472840Noop@@YAXXZ
void Rva00472840Noop()
{
}

class Rva004727B0Owner
{
public:
	char *get() const;

private:
	char *m_base;
};

// ?get@Rva004727B0Owner@@QBEPADXZ
char *Rva004727B0Owner::get() const
{
	return m_base + 0x10;
}

class Rva004727F0Owner
{
public:
	char *get() const;

private:
	char *m_base;
};

// ?get@Rva004727F0Owner@@QBEPADXZ
char *Rva004727F0Owner::get() const
{
	return m_base + 0x10;
}

class Rva00472830Owner
{
public:
	char *get() const;

private:
	char *m_base;
};

// ?get@Rva00472830Owner@@QBEPADXZ
char *Rva00472830Owner::get() const
{
	return m_base + 0x10;
}

class Rva00472B30Owner
{
public:
	int get() const;

private:
	char m_prefix[4];
	int m_value;
};

// ?get@Rva00472B30Owner@@QBEHXZ
int Rva00472B30Owner::get() const
{
	return m_value;
}

class Rva00472B90Owner
{
public:
	int get() const;

private:
	char m_prefix[4];
	int m_value;
};

// ?get@Rva00472B90Owner@@QBEHXZ
int Rva00472B90Owner::get() const
{
	return m_value;
}

// ?Rva00472DA0False@@YA_NXZ
bool Rva00472DA0False()
{
	return false;
}

// ?Rva00472DC0False@@YA_NXZ
bool Rva00472DC0False()
{
	return false;
}
