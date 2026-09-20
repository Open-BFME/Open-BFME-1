// cl: /O2 /Ob0
// Address-derived accessors recovered from carved retail boundaries.

class Rva000A33E0
{
public:
	unsigned int fieldAt04() const;

private:
	char m_before[0x4];
	unsigned int m_value;
};

// ?fieldAt04@Rva000A33E0@@QBEIXZ
unsigned int Rva000A33E0::fieldAt04() const
{
	return m_value;
}

class Rva000A3500
{
public:
	unsigned char zero() const;
};

// ?zero@Rva000A3500@@QBEEXZ
unsigned char Rva000A3500::zero() const
{
	return 0;
}

class Rva000A3510
{
public:
	unsigned char zero() const;
};

// ?zero@Rva000A3510@@QBEEXZ
unsigned char Rva000A3510::zero() const
{
	return 0;
}

class Rva000A3530
{
public:
	unsigned char zero() const;
};

// ?zero@Rva000A3530@@QBEEXZ
unsigned char Rva000A3530::zero() const
{
	return 0;
}

class Rva000A71A0
{
public:
	unsigned int fieldAt20() const;

private:
	char m_before[0x20];
	unsigned int m_value;
};

// ?fieldAt20@Rva000A71A0@@QBEIXZ
unsigned int Rva000A71A0::fieldAt20() const
{
	return m_value;
}

class Rva000A72A0
{
public:
	Rva000A72A0 *getThis();
};

// ?getThis@Rva000A72A0@@QAEPAV1@XZ
Rva000A72A0 *Rva000A72A0::getThis()
{
	return this;
}

class Rva000A72C0
{
public:
	Rva000A72C0 *getThis();
};

// ?getThis@Rva000A72C0@@QAEPAV1@XZ
Rva000A72C0 *Rva000A72C0::getThis()
{
	return this;
}

class Rva000A89C0
{
public:
	Rva000A89C0 *getThis();
};

// ?getThis@Rva000A89C0@@QAEPAV1@XZ
Rva000A89C0 *Rva000A89C0::getThis()
{
	return this;
}

class Rva000A8A00
{
public:
	Rva000A8A00 *getThis();
};

// ?getThis@Rva000A8A00@@QAEPAV1@XZ
Rva000A8A00 *Rva000A8A00::getThis()
{
	return this;
}

class Rva000A8A40
{
public:
	void *fieldAt10() const;

private:
	void *m_base;
};

// ?fieldAt10@Rva000A8A40@@QBEPAXXZ
void *Rva000A8A40::fieldAt10() const
{
	return reinterpret_cast<char *>(m_base) + 0x10;
}

class Rva000A8C40
{
public:
	unsigned int fieldAt04() const;

private:
	char m_before[0x4];
	unsigned int m_value;
};

// ?fieldAt04@Rva000A8C40@@QBEIXZ
unsigned int Rva000A8C40::fieldAt04() const
{
	return m_value;
}

class Rva000AF800
{
public:
	unsigned int fieldAt2C() const;

private:
	char m_before[0x2C];
	unsigned int m_value;
};

// ?fieldAt2C@Rva000AF800@@QBEIXZ
unsigned int Rva000AF800::fieldAt2C() const
{
	return m_value;
}

class Rva000AF870
{
public:
	void *fieldAt08() const;
};

// ?fieldAt08@Rva000AF870@@QBEPAXXZ
void *Rva000AF870::fieldAt08() const
{
	return reinterpret_cast<char *>(const_cast<Rva000AF870 *>(this)) + 0x8;
}

class Rva000AF890
{
public:
	void *fieldAt40() const;
};

// ?fieldAt40@Rva000AF890@@QBEPAXXZ
void *Rva000AF890::fieldAt40() const
{
	return reinterpret_cast<char *>(const_cast<Rva000AF890 *>(this)) + 0x40;
}

class Rva000AF8B0
{
public:
	void *fieldAt60() const;
};

// ?fieldAt60@Rva000AF8B0@@QBEPAXXZ
void *Rva000AF8B0::fieldAt60() const
{
	return reinterpret_cast<char *>(const_cast<Rva000AF8B0 *>(this)) + 0x60;
}

class Rva000AF9F0
{
public:
	unsigned int fieldAt00() const;

private:
	unsigned int m_value;
};

// ?fieldAt00@Rva000AF9F0@@QBEIXZ
unsigned int Rva000AF9F0::fieldAt00() const
{
	return m_value;
}

class Rva000AFA10
{
public:
	Rva000AFA10 *getThis();
};

// ?getThis@Rva000AFA10@@QAEPAV1@XZ
Rva000AFA10 *Rva000AFA10::getThis()
{
	return this;
}

class Rva000AFB00
{
public:
	unsigned int fieldAt00() const;

private:
	unsigned int m_value;
};

// ?fieldAt00@Rva000AFB00@@QBEIXZ
unsigned int Rva000AFB00::fieldAt00() const
{
	return m_value;
}

class Rva000AFB20
{
public:
	unsigned int fieldAt00() const;

private:
	unsigned int m_value;
};

// ?fieldAt00@Rva000AFB20@@QBEIXZ
unsigned int Rva000AFB20::fieldAt00() const
{
	return m_value;
}

class Rva000B20B0
{
public:
	float fieldAt10() const;

private:
	char m_before[0x10];
	float m_value;
};

// ?fieldAt10@Rva000B20B0@@QBEMXZ
float Rva000B20B0::fieldAt10() const
{
	return m_value;
}

class Rva000B20D0
{
public:
	float fieldAt18() const;

private:
	char m_before[0x18];
	float m_value;
};

// ?fieldAt18@Rva000B20D0@@QBEMXZ
float Rva000B20D0::fieldAt18() const
{
	return m_value;
}

class Rva000B20F0
{
public:
	float fieldAt20() const;

private:
	char m_before[0x20];
	float m_value;
};

// ?fieldAt20@Rva000B20F0@@QBEMXZ
float Rva000B20F0::fieldAt20() const
{
	return m_value;
}

class Rva000B22D0
{
public:
	void setValue(unsigned int value);

private:
	char m_before[0x2C];
	unsigned int m_value;
	unsigned int m_state;
};

// ?setValue@Rva000B22D0@@QAEXI@Z
void Rva000B22D0::setValue(unsigned int value)
{
	if (m_state == 5 || m_state == 4)
	{
		m_value = value;
		m_state = 5;
	}
}

class Rva000B51B0
{
public:
	unsigned int fieldAt34() const;

private:
	char m_before[0x34];
	unsigned int m_value;
};

// ?fieldAt34@Rva000B51B0@@QBEIXZ
unsigned int Rva000B51B0::fieldAt34() const
{
	return m_value;
}

class Rva000B51D0
{
public:
	float fieldAt78() const;

private:
	char m_before[0x78];
	float m_value;
};

// ?fieldAt78@Rva000B51D0@@QBEMXZ
float Rva000B51D0::fieldAt78() const
{
	return m_value;
}

// ?Rva000A35A0Noop@@YAXXZ
void Rva000A35A0Noop()
{
}
