// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD

class Rva000B55D0
{
public:
	int bit(void);

	char m_pad[0x98];
	unsigned int m_bits;
};

// ?bit@Rva000B55D0@@QAEHXZ
int Rva000B55D0::bit(void)
{
	return (m_bits >> 4) & 1;
}

class Rva000B55E0
{
public:
	int bit(void);

	char m_pad[0x98];
	unsigned int m_bits;
};

// ?bit@Rva000B55E0@@QAEHXZ
int Rva000B55E0::bit(void)
{
	return (m_bits >> 5) & 1;
}

class Rva000B55F0
{
public:
	int bit(void);

	char m_pad[0x98];
	unsigned int m_bits;
};

// ?bit@Rva000B55F0@@QAEHXZ
int Rva000B55F0::bit(void)
{
	return (m_bits >> 6) & 1;
}

class Rva000B5600
{
public:
	int bit(void);

	char m_pad[0x98];
	unsigned int m_bits;
};

// ?bit@Rva000B5600@@QAEHXZ
int Rva000B5600::bit(void)
{
	return (m_bits >> 7) & 1;
}

class Rva000B6500
{
public:
	Rva000B6500 *get(void);
};

// ?get@Rva000B6500@@QAEPAV1@XZ
Rva000B6500 *Rva000B6500::get(void)
{
	return this;
}

class Rva000B9240
{
public:
	Rva000B9240 *get(void);
};

// ?get@Rva000B9240@@QAEPAV1@XZ
Rva000B9240 *Rva000B9240::get(void)
{
	return this;
}

class Rva000BE6D0
{
public:
	char *get(void);

	char m_pad[8];
};

// ?get@Rva000BE6D0@@QAEPADXZ
char *Rva000BE6D0::get(void)
{
	return m_pad + 8;
}

class Rva000BE730
{
public:
	void *get(void);
};

// ?get@Rva000BE730@@QAEPAXXZ
void *Rva000BE730::get(void)
{
	return (void *)0x01082F58;
}

class Rva000BE850
{
public:
	char *get(void);

	char *m_value;
};

// ?get@Rva000BE850@@QAEPADXZ
char *Rva000BE850::get(void)
{
	return m_value + 16;
}

class Rva000BE870
{
public:
	char *get(void);

	char *m_value;
};

// ?get@Rva000BE870@@QAEPADXZ
char *Rva000BE870::get(void)
{
	return m_value + 16;
}

class Rva000BE9C0
{
public:
	int get(void);

	char m_pad[4];
	int m_value;
};

// ?get@Rva000BE9C0@@QAEHXZ
int Rva000BE9C0::get(void)
{
	return m_value;
}

class Rva000BE9F0
{
public:
	int get(void);

	char m_pad[4];
	int m_value;
};

// ?get@Rva000BE9F0@@QAEHXZ
int Rva000BE9F0::get(void)
{
	return m_value;
}

class Rva000BEB10
{
public:
	int get(void);

	char m_pad[4];
	int m_value;
};

// ?get@Rva000BEB10@@QAEHXZ
int Rva000BEB10::get(void)
{
	return m_value;
}

class Rva000BEC00
{
public:
	Rva000BEC00 *get(void);
};

// ?get@Rva000BEC00@@QAEPAV1@XZ
Rva000BEC00 *Rva000BEC00::get(void)
{
	return this;
}

class Rva000BEC10
{
public:
	Rva000BEC10 *get(void);
};

// ?get@Rva000BEC10@@QAEPAV1@XZ
Rva000BEC10 *Rva000BEC10::get(void)
{
	return this;
}

class Rva000C2D20
{
public:
	unsigned char get(void);

	char m_pad[8];
	unsigned char m_value;
};

// ?get@Rva000C2D20@@QAEEXZ
unsigned char Rva000C2D20::get(void)
{
	return m_value;
}

class Rva000C3620
{
public:
	int get(void);

	int m_value;
};

// ?get@Rva000C3620@@QAEHXZ
int Rva000C3620::get(void)
{
	return m_value;
}

class Rva000C3BA0
{
public:
	int get(void);
};

// ?get@Rva000C3BA0@@QAEHXZ
int Rva000C3BA0::get(void)
{
	return -1;
}

class Rva000C3C60
{
public:
	int get(void);

	char m_pad[0x2c];
	int m_value;
};

// ?get@Rva000C3C60@@QAEHXZ
int Rva000C3C60::get(void)
{
	return m_value;
}

class Rva000C3C80
{
public:
	int get(void);

	char m_pad[0xc];
	int m_value;
};

// ?get@Rva000C3C80@@QAEHXZ
int Rva000C3C80::get(void)
{
	return m_value;
}

class Rva000C3CC0
{
public:
	int get(void);

	char m_pad[0x18];
	int m_value;
};

// ?get@Rva000C3CC0@@QAEHXZ
int Rva000C3CC0::get(void)
{
	return m_value;
}

class Rva000C3CD0
{
public:
	int get(void);

	char m_pad[0x34];
	int m_value;
};

// ?get@Rva000C3CD0@@QAEHXZ
int Rva000C3CD0::get(void)
{
	return m_value;
}

class Rva000C3E90
{
public:
	int get(void);

	char m_pad[4];
	int m_value;
};

// ?get@Rva000C3E90@@QAEHXZ
int Rva000C3E90::get(void)
{
	return m_value;
}

class Rva000C4410
{
public:
	int get(void);

	char m_pad[4];
	int m_value;
};

// ?get@Rva000C4410@@QAEHXZ
int Rva000C4410::get(void)
{
	return m_value;
}

class Rva000CA680
{
public:
	char *get(void);

	char *m_value;
};

// ?get@Rva000CA680@@QAEPADXZ
char *Rva000CA680::get(void)
{
	return m_value + 8;
}
