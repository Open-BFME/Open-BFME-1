// Address-derived leaf bodies recovered from carved boundaries.
// The declarations preserve only the observed ABI and field offsets.

int Rva0020DB80Get(void)
{
	return -1;
}

int Rva0020DB90Get(void)
{
	return 0;
}

bool Rva0020DBA0Get(void)
{
	return false;
}

class Rva0020DBC0Owner
{
public:
	void ret8(int first, int second);
};

void Rva0020DBC0Owner::ret8(int first, int second)
{
	(void)first;
	(void)second;
}

class Rva0020DBD0Owner
{
public:
	void ret8(int first, int second);
};

void Rva0020DBD0Owner::ret8(int first, int second)
{
	(void)first;
	(void)second;
}

class Rva0020DBF0Owner
{
public:
	void ret4(int value);
};

void Rva0020DBF0Owner::ret4(int value)
{
	(void)value;
}

class Rva0020DC10Owner
{
public:
	void ret4(int value);
};

void Rva0020DC10Owner::ret4(int value)
{
	(void)value;
}

class Rva0020DC20Owner
{
public:
	void ret4(int value);
};

void Rva0020DC20Owner::ret4(int value)
{
	(void)value;
}

bool Rva0020DC30Get(void)
{
	return true;
}

class Rva0020DC60Owner
{
public:
	float get(void) const;

private:
	char m_lead[4];
	float m_value;
};

float Rva0020DC60Owner::get(void) const
{
	return m_value;
}

// ?Rva0020DC70Noop@@YAXXZ
void Rva0020DC70Noop(void)
{
}

class Rva0020DC90Owner
{
public:
	void ret4(int value);
};

void Rva0020DC90Owner::ret4(int value)
{
	(void)value;
}

class Rva0020DCB0Owner
{
public:
	void ret4(int value);
};

void Rva0020DCB0Owner::ret4(int value)
{
	(void)value;
}

int Rva0020DCC0Get(void)
{
	return 0;
}

class Rva0020DDA0Owner
{
public:
	char *get(void) const;

private:
	char m_lead[0x1c];
	char m_value;
};

char *Rva0020DDA0Owner::get(void) const
{
	return (char *)&m_value;
}

class Rva0020DDE0Owner
{
public:
	int get(void) const;

private:
	char m_lead[8];
	int m_value;
};

int Rva0020DDE0Owner::get(void) const
{
	return m_value;
}

class Rva0020E180Owner
{
public:
	int get(void) const;

private:
	char m_lead[0x20];
	int m_value;
};

int Rva0020E180Owner::get(void) const
{
	return m_value;
}

class Rva0020E190Owner
{
public:
	float get(void) const;

private:
	char m_lead[0x10];
	float m_value;
};

float Rva0020E190Owner::get(void) const
{
	return m_value;
}

class Rva0020E1A0Owner
{
public:
	float get(void) const;

private:
	char m_lead[0x1c];
	float m_value;
};

float Rva0020E1A0Owner::get(void) const
{
	return m_value;
}

class Rva0020E1DOwner
{
public:
	void *get(void);
};

void *Rva0020E1DOwner::get(void)
{
	return this;
}

class Rva0020E570Owner
{
public:
	int get(void) const;

private:
	char m_lead[4];
	int m_value;
};

int Rva0020E570Owner::get(void) const
{
	return m_value;
}
