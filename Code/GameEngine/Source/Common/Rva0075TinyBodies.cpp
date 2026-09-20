// Address-derived tiny bodies from the 0x0075xxxx carved family.
// The instruction shapes prove ABI widths and field offsets, not semantic names.

class Rva007516F0
{
public:
	void *value();
};

void *Rva007516F0::value()
{
	return this;
}

class Rva00751760
{
	char m_pad[4];

public:
	int value() const;
};

int Rva00751760::value() const
{
	return *(const int *)((const char *)this + 4);
}

class Rva007517F0
{
public:
	void invoke(int value);
};

void Rva007517F0::invoke(int value)
{
	(void)value;
}

class Rva00751820
{
public:
	void invoke(int value);
};

void Rva00751820::invoke(int value)
{
	(void)value;
}

class Rva00751810
{
public:
	void invoke();
};

void Rva00751810::invoke()
{
}

class Rva00751B50
{
	char m_pad[4];

public:
	int value() const;
};

int Rva00751B50::value() const
{
	return *(const int *)((const char *)this + 4);
}

class Rva00751B60
{
	char m_pad[0x14];

public:
	int value() const;
};

int Rva00751B60::value() const
{
	return *(const int *)((const char *)this + 0x14);
}

class Rva00751B70
{
	char m_pad[4];

public:
	int value() const;
};

int Rva00751B70::value() const
{
	return *(const int *)((const char *)this + 4);
}

class Rva00751B80
{
	char m_pad[4];

public:
	int value() const;
};

int Rva00751B80::value() const
{
	return *(const int *)((const char *)this + 4);
}

class Rva00751D70
{
public:
	void invoke(int first, int second);
};

void Rva00751D70::invoke(int first, int second)
{
	(void)first;
	(void)second;
}

class Rva00751D90
{
public:
	void *value() const;
};

void *Rva00751D90::value() const
{
	if (this != 0)
		return (char *)this + 0x0C;
	return 0;
}

class Rva00751DC0
{
public:
	void invoke();
};

void Rva00751DC0::invoke()
{
}

class Rva00752000
{
public:
	void *value();
};

void *Rva00752000::value()
{
	return this;
}

class Rva007520A0
{
public:
	void *value();
};

void *Rva007520A0::value()
{
	return this;
}

class Rva007520C0
{
public:
	void *value();
};

void *Rva007520C0::value()
{
	return this;
}

class Rva00752100
{
public:
	void *value();
};

void *Rva00752100::value()
{
	return this;
}

class Rva00752480
{
public:
	void *value(int argument);
};

void *Rva00752480::value(int argument)
{
	(void)argument;
	return this;
}

class Rva00752670
{
public:
	bool value() const;
};

bool Rva00752670::value() const
{
	return false;
}

class Rva00752680
{
public:
	bool value() const;
};

bool Rva00752680::value() const
{
	return false;
}

class Rva007526F0
{
public:
	bool value() const;
};

bool Rva007526F0::value() const
{
	return false;
}

class Rva00752760
{
public:
	bool value() const;
};

bool Rva00752760::value() const
{
	return false;
}

class Rva00752780
{
public:
	bool value() const;
};

bool Rva00752780::value() const
{
	return false;
}
