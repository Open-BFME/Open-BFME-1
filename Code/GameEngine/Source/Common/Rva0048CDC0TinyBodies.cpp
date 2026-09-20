// cl: /DNDEBUG /MD /EHsc
// Address-derived owners for the adjacent carved accessors and no-op methods.

class Rva0048CDC0DwordField
{
public:
	int get() const;

	char m_lead[0x8];
	int m_value;
};

// ?get@Rva0048CDC0DwordField@@QBEHXZ
int Rva0048CDC0DwordField::get() const
{
	return m_value;
}

class Rva0048CEF0ByteField
{
public:
	unsigned char get() const;

	char m_lead[0x1C];
	unsigned char m_value;
};

// ?get@Rva0048CEF0ByteField@@QBEEXZ
unsigned char Rva0048CEF0ByteField::get() const
{
	return m_value;
}

class Rva0048E310FieldAddress
{
public:
	char *get();

	char m_lead[0x8];
	char m_value;
};

// ?get@Rva0048E310FieldAddress@@QAEPADXZ
char *Rva0048E310FieldAddress::get()
{
	return &m_value;
}

class Rva0048E370DwordField
{
public:
	int get() const;

	char m_lead[0xC];
	int m_value;
};

// ?get@Rva0048E370DwordField@@QBEHXZ
int Rva0048E370DwordField::get() const
{
	return m_value;
}

class Rva0048E620Self
{
public:
	Rva0048E620Self *body();
};

// ?body@Rva0048E620Self@@QAEPAV1@XZ
Rva0048E620Self *Rva0048E620Self::body()
{
	return this;
}

class Rva0048E680Self
{
public:
	Rva0048E680Self *body();
};

// ?body@Rva0048E680Self@@QAEPAV1@XZ
Rva0048E680Self *Rva0048E680Self::body()
{
	return this;
}

class Rva00490240DwordField
{
public:
	int get() const;

	char m_lead[0x44];
	int m_value;
};

// ?get@Rva00490240DwordField@@QBEHXZ
int Rva00490240DwordField::get() const
{
	return m_value;
}

class Rva00490540NoOp
{
public:
	void body(int first, int second);
};

// ?body@Rva00490540NoOp@@QAEXHH@Z
void Rva00490540NoOp::body(int first, int second)
{
}

class Rva00490780NoOp
{
public:
	void body(int first, int second);
};

// ?body@Rva00490780NoOp@@QAEXHH@Z
void Rva00490780NoOp::body(int first, int second)
{
}

class Rva00490E00NoOp
{
public:
	void body(int first, int second);
};

// ?body@Rva00490E00NoOp@@QAEXHH@Z
void Rva00490E00NoOp::body(int first, int second)
{
}

class Rva00494280DwordField
{
public:
	int get() const;

	char m_lead[0x8];
	int m_value;
};

// ?get@Rva00494280DwordField@@QBEHXZ
int Rva00494280DwordField::get() const
{
	return m_value;
}

class Rva00494490Self
{
public:
	Rva00494490Self *body();
};

// ?body@Rva00494490Self@@QAEPAV1@XZ
Rva00494490Self *Rva00494490Self::body()
{
	return this;
}

class Rva00497C30Self
{
public:
	Rva00497C30Self *body();
};

// ?body@Rva00497C30Self@@QAEPAV1@XZ
Rva00497C30Self *Rva00497C30Self::body()
{
	return this;
}

class Rva00497D40DwordField
{
public:
	int get() const;

	char m_lead[0x8];
	int m_value;
};

// ?get@Rva00497D40DwordField@@QBEHXZ
int Rva00497D40DwordField::get() const
{
	return m_value;
}

class Rva00497D50DwordField
{
public:
	int get() const;

	char m_lead[0x4];
	int m_value;
};

// ?get@Rva00497D50DwordField@@QBEHXZ
int Rva00497D50DwordField::get() const
{
	return m_value;
}

class Rva00497D60DwordField
{
public:
	int get() const;

	int m_value;
};

// ?get@Rva00497D60DwordField@@QBEHXZ
int Rva00497D60DwordField::get() const
{
	return m_value;
}

class Rva00497D70DwordField
{
public:
	int get() const;

	char m_lead[0x10];
	int m_value;
};

// ?get@Rva00497D70DwordField@@QBEHXZ
int Rva00497D70DwordField::get() const
{
	return m_value;
}

class Rva00497E30Self
{
public:
	Rva00497E30Self *body();
};

// ?body@Rva00497E30Self@@QAEPAV1@XZ
Rva00497E30Self *Rva00497E30Self::body()
{
	return this;
}

class Rva00499E70Zero
{
public:
	int body() const;
};

// ?body@Rva00499E70Zero@@QBEHXZ
int Rva00499E70Zero::body() const
{
	return 0;
}

class Rva00499EB0DwordField
{
public:
	int get() const;

	int m_value;
};

// ?get@Rva00499EB0DwordField@@QBEHXZ
int Rva00499EB0DwordField::get() const
{
	return m_value;
}

class Rva00499EC0DwordField
{
public:
	int get() const;

	int m_value;
};

// ?get@Rva00499EC0DwordField@@QBEHXZ
int Rva00499EC0DwordField::get() const
{
	return m_value;
}

class Rva0049AF30Self
{
public:
	Rva0049AF30Self *body();
};

// ?body@Rva0049AF30Self@@QAEPAV1@XZ
Rva0049AF30Self *Rva0049AF30Self::body()
{
	return this;
}

class Rva0049AF50DwordField
{
public:
	int get() const;

	char m_lead[0x4];
	int m_value;
};

// ?get@Rva0049AF50DwordField@@QBEHXZ
int Rva0049AF50DwordField::get() const
{
	return m_value;
}

class Rva0049AF70DwordField
{
public:
	int get() const;

	int m_value;
};

// ?get@Rva0049AF70DwordField@@QBEHXZ
int Rva0049AF70DwordField::get() const
{
	return m_value;
}

class Rva0049C980DwordField
{
public:
	int get() const;

	char m_lead[0x60];
	int m_value;
};

// ?get@Rva0049C980DwordField@@QBEHXZ
int Rva0049C980DwordField::get() const
{
	return m_value;
}
