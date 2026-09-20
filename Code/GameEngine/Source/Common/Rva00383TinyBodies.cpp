// Retail tiny bodies at 0x00383C60-0x00384700.
// Owners remain address-derived because the thunks have no named callers.
// The declarations follow matched self-return and dword-getter donors.

class Rva00383C60Self
{
public:
	Rva00383C60Self *self();
};

// ?self@Rva00383C60Self@@QAEPAV1@XZ
Rva00383C60Self *Rva00383C60Self::self()
{
	return this;
}

class Rva00383C80Self
{
public:
	Rva00383C80Self *self();
};

// ?self@Rva00383C80Self@@QAEPAV1@XZ
Rva00383C80Self *Rva00383C80Self::self()
{
	return this;
}

class Rva00383CA0PtrOffset
{
public:
	char *get() const;

private:
	char *m_base;
};

// ?get@Rva00383CA0PtrOffset@@QBEPADXZ
char *Rva00383CA0PtrOffset::get() const
{
	return m_base + 8;
}

class Rva00383D20Self
{
public:
	Rva00383D20Self *self();
};

// ?self@Rva00383D20Self@@QAEPAV1@XZ
Rva00383D20Self *Rva00383D20Self::self()
{
	return this;
}

class Rva00383D80Self
{
public:
	Rva00383D80Self *self();
};

// ?self@Rva00383D80Self@@QAEPAV1@XZ
Rva00383D80Self *Rva00383D80Self::self()
{
	return this;
}

class Rva00383E00Self
{
public:
	Rva00383E00Self *self();
};

// ?self@Rva00383E00Self@@QAEPAV1@XZ
Rva00383E00Self *Rva00383E00Self::self()
{
	return this;
}

class Rva00383E30Self
{
public:
	Rva00383E30Self *self();
};

// ?self@Rva00383E30Self@@QAEPAV1@XZ
Rva00383E30Self *Rva00383E30Self::self()
{
	return this;
}

class Rva00383E60Self
{
public:
	Rva00383E60Self *self();
};

// ?self@Rva00383E60Self@@QAEPAV1@XZ
Rva00383E60Self *Rva00383E60Self::self()
{
	return this;
}

class Rva00383E90Self
{
public:
	Rva00383E90Self *self();
};

// ?self@Rva00383E90Self@@QAEPAV1@XZ
Rva00383E90Self *Rva00383E90Self::self()
{
	return this;
}

class Rva00383FA0Field10
{
public:
	int get() const;

private:
	char m_beforeField10[ 0x10 ];
	int m_field10;
};

// ?get@Rva00383FA0Field10@@QBEHXZ
int Rva00383FA0Field10::get() const
{
	return m_field10;
}

class Rva00384240Field4
{
public:
	int get() const;

private:
	char m_beforeField4[ 0x4 ];
	int m_field4;
};

// ?get@Rva00384240Field4@@QBEHXZ
int Rva00384240Field4::get() const
{
	return m_field4;
}

class Rva00384320Self
{
public:
	Rva00384320Self *self();
};

// ?self@Rva00384320Self@@QAEPAV1@XZ
Rva00384320Self *Rva00384320Self::self()
{
	return this;
}

class Rva00384700Self
{
public:
	Rva00384700Self *self();
};

// ?self@Rva00384700Self@@QAEPAV1@XZ
Rva00384700Self *Rva00384700Self::self()
{
	return this;
}
