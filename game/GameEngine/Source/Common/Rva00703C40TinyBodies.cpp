// cl: /DNDEBUG /MD /EHsc
// Address-derived owners for complete carved leaf bodies.

class Rva00703C40
{
public:
	unsigned char body() const;

private:
	char m_padding[0x18];
	unsigned char m_value;
};

// ?body@Rva00703C40@@QBEEXZ
unsigned char Rva00703C40::body() const
{
	return m_value;
}

class Rva00703C50
{
public:
	int body() const;

private:
	char m_padding[0x0C];
	int m_value;
};

// ?body@Rva00703C50@@QBEHXZ
int Rva00703C50::body() const
{
	return m_value;
}

class Rva00703C60
{
public:
	int body() const;

private:
	char m_padding[8];
	int m_value;
};

// ?body@Rva00703C60@@QBEHXZ
int Rva00703C60::body() const
{
	return m_value;
}

class Rva00703C70
{
public:
	int body() const;
};

// ?body@Rva00703C70@@QBEHXZ
int Rva00703C70::body() const
{
	return 0;
}

class Rva00704320
{
public:
	Rva00704320 *body();
};

// ?body@Rva00704320@@QAEPAV1@XZ
Rva00704320 *Rva00704320::body()
{
	return this;
}

class Rva00710D10
{
public:
	char *body();

private:
	char m_padding[0x9C];
	char m_value;
};

// ?body@Rva00710D10@@QAEPADXZ
char *Rva00710D10::body()
{
	return &m_value;
}

class Rva00710FA0
{
public:
	int body() const;

private:
	char m_padding[8];
	int m_value;
};

// ?body@Rva00710FA0@@QBEHXZ
int Rva00710FA0::body() const
{
	return m_value;
}

class Rva00716490
{
public:
	Rva00716490 *body();
};

// ?body@Rva00716490@@QAEPAV1@XZ
Rva00716490 *Rva00716490::body()
{
	return this;
}

class Rva00716580
{
public:
	int body() const;

private:
	char m_padding[0x20];
	int m_value;
};

// ?body@Rva00716580@@QBEHXZ
int Rva00716580::body() const
{
	return m_value;
}

class Rva007165A0
{
public:
	float body() const;

private:
	char m_padding[0x2C];
	float m_value;
};

// ?body@Rva007165A0@@QBEMXZ
float Rva007165A0::body() const
{
	return m_value;
}

class Rva007165B0
{
public:
	float body() const;

private:
	char m_padding[0x30];
	float m_value;
};

// ?body@Rva007165B0@@QBEMXZ
float Rva007165B0::body() const
{
	return m_value;
}

class Rva00717AE0
{
public:
	void body(int value);
};

// ?body@Rva00717AE0@@QAEXH@Z
void Rva00717AE0::body(int value)
{
}

class Rva0071D9E0
{
public:
	Rva0071D9E0 *body();
};

// ?body@Rva0071D9E0@@QAEPAV1@XZ
Rva0071D9E0 *Rva0071D9E0::body()
{
	return this;
}

class Rva00722520
{
public:
	Rva00722520 *body();
};

// ?body@Rva00722520@@QAEPAV1@XZ
Rva00722520 *Rva00722520::body()
{
	return this;
}

class Rva00728B20
{
public:
	Rva00728B20 *body();
};

// ?body@Rva00728B20@@QAEPAV1@XZ
Rva00728B20 *Rva00728B20::body()
{
	return this;
}

class Rva0072EB00
{
public:
	Rva0072EB00 *body();
};

// ?body@Rva0072EB00@@QAEPAV1@XZ
Rva0072EB00 *Rva0072EB00::body()
{
	return this;
}

class Rva00739F80
{
public:
	bool body() const;

private:
	char m_padding[0x34];
	int m_first;
	int m_second;
};

// ?body@Rva00739F80@@QBE_NXZ
bool Rva00739F80::body() const
{
	int count = 0;
	const int *entry = &m_second;
	do
	{
		if (entry[-1] == 0 && entry[0] == 0)
			return false;
		++count;
		entry += 5;
	}
	while (count < 1);
	return true;
}

class Rva0073A310
{
public:
	unsigned char body() const;
};

// ?body@Rva0073A310@@QBEEXZ
unsigned char Rva0073A310::body() const
{
	return 0;
}

class Rva0073A5C0
{
public:
	float body() const;

private:
	char m_padding[0x20];
	float m_value;
};

// ?body@Rva0073A5C0@@QBEMXZ
float Rva0073A5C0::body() const
{
	return m_value;
}

class Rva0073A5D0
{
public:
	float body() const;

private:
	char m_padding[0x18];
	float m_value;
};

// ?body@Rva0073A5D0@@QBEMXZ
float Rva0073A5D0::body() const
{
	return m_value;
}

class Rva0073A5E0
{
public:
	float body() const;

private:
	char m_padding[0x24];
	float m_value;
};

// ?body@Rva0073A5E0@@QBEMXZ
float Rva0073A5E0::body() const
{
	return m_value;
}

class Rva0073A5F0
{
public:
	float body() const;

private:
	char m_padding[0x28];
	float m_value;
};

// ?body@Rva0073A5F0@@QBEMXZ
float Rva0073A5F0::body() const
{
	return m_value;
}

class Rva0073A670
{
public:
	int body() const;

private:
	char m_padding[4];
	int m_value;
};

// ?body@Rva0073A670@@QBEHXZ
int Rva0073A670::body() const
{
	return m_value;
}

class Rva0073A730
{
public:
	int body() const;

private:
	char m_padding[0x20];
	int m_value;
};

// ?body@Rva0073A730@@QBEHXZ
int Rva0073A730::body() const
{
	return m_value;
}

class Rva0073A770
{
public:
	unsigned char body() const;

private:
	char m_padding[0x1C];
	unsigned char m_value;
};

// ?body@Rva0073A770@@QBEEXZ
unsigned char Rva0073A770::body() const
{
	return m_value;
}
