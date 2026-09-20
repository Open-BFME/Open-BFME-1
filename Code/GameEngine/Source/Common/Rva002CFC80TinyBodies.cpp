// Address-derived tiny bodies recovered from carved retail boundaries.
// The owners remain opaque because the available evidence does not prove their identities.

class Rva002CFC80
{
public:
	void slot( void *value );
};

// ?slot@Rva002CFC80@@QAEXPAX@Z
void Rva002CFC80::slot( void * )
{
}

class Rva002CFC90
{
public:
	void slot( void *first, void *second );
};

// ?slot@Rva002CFC90@@QAEXPAX0@Z
void Rva002CFC90::slot( void *, void * )
{
}

class Rva002CFD30
{
public:
	int getField04() const;
};

// ?getField04@Rva002CFD30@@QBEHXZ
int Rva002CFD30::getField04() const
{
	return *(const int *)((const char *)this + 4);
}

class Rva002D0600
{
public:
	int getField04() const;
};

// ?getField04@Rva002D0600@@QBEHXZ
int Rva002D0600::getField04() const
{
	return *(const int *)((const char *)this + 4);
}

class Rva002D1450
{
public:
	void slot( void *value );
};

// ?slot@Rva002D1450@@QAEXPAX@Z
void Rva002D1450::slot( void * )
{
}

class Rva002D1470
{
public:
	int getField04() const;
};

// ?getField04@Rva002D1470@@QBEHXZ
int Rva002D1470::getField04() const
{
	return *(const int *)((const char *)this + 4);
}

class Rva002D16C0
{
public:
	bool getValue() const;
};

// ?getValue@Rva002D16C0@@QBE_NXZ
bool Rva002D16C0::getValue() const
{
	return false;
}

class Rva002D16E0
{
public:
	int getValue() const;
};

// ?getValue@Rva002D16E0@@QBEHXZ
int Rva002D16E0::getValue() const
{
	return 0;
}

class Rva002D16F0
{
public:
	void slot( void *first, void *second );
};

// ?slot@Rva002D16F0@@QAEXPAX0@Z
void Rva002D16F0::slot( void *, void * )
{
}

class Rva002D2260
{
public:
	void slot( void *value );
};

// ?slot@Rva002D2260@@QAEXPAX@Z
void Rva002D2260::slot( void * )
{
}

class Rva002D2270
{
public:
	void slot( void *first, void *second );
};

// ?slot@Rva002D2270@@QAEXPAX0@Z
void Rva002D2270::slot( void *, void * )
{
}

class Rva002ED1C0
{
public:
	void setValue( unsigned char value );
};

// ?setValue@Rva002ED1C0@@QAEXE@Z
void Rva002ED1C0::setValue( unsigned char value )
{
	*(unsigned char *)((char *)this + 0x92) = value;
}

class Rva002ED1D0
{
public:
	void setValue( unsigned char value );
};

// ?setValue@Rva002ED1D0@@QAEXE@Z
void Rva002ED1D0::setValue( unsigned char value )
{
	*(unsigned char *)((char *)this + 0x93) = value;
}

class Rva002ED200
{
public:
	void setValue( unsigned char value );
};

// ?setValue@Rva002ED200@@QAEXE@Z
void Rva002ED200::setValue( unsigned char value )
{
	*(unsigned char *)((char *)this + 0x114) = value;
}

class Rva002ED280
{
public:
	void setValue( unsigned char value );
};

// ?setValue@Rva002ED280@@QAEXE@Z
void Rva002ED280::setValue( unsigned char value )
{
	*(unsigned char *)((char *)this + 0x681) = value;
}

class Rva002ED420
{
public:
	void setValue( unsigned char value );
};

// ?setValue@Rva002ED420@@QAEXE@Z
void Rva002ED420::setValue( unsigned char value )
{
	*(unsigned char *)((char *)this + 0x18F4) = value;
}

class Rva002ED4E0
{
public:
	int getField08() const;
};

// ?getField08@Rva002ED4E0@@QBEHXZ
int Rva002ED4E0::getField08() const
{
	return *(const int *)((const char *)this + 8);
}

class Rva002ED4F0
{
public:
	float getField0C() const;
};

// ?getField0C@Rva002ED4F0@@QBEMXZ
float Rva002ED4F0::getField0C() const
{
	return *(const float *)((const char *)this + 0xC);
}

class Rva002ED500
{
public:
	void *getField10() const;
};

// ?getField10@Rva002ED500@@QBEPAXXZ
void *Rva002ED500::getField10() const
{
	return (void *)((const char *)this + 0x10);
}

class Rva002ED550
{
public:
	Rva002ED550( void *value, unsigned char flag );

	unsigned int m_vptr;
	unsigned int m_zero;
	void *m_value;
	unsigned char m_flag;
};

// ??0Rva002ED550@@QAE@PAXE@Z
Rva002ED550::Rva002ED550( void *value, unsigned char flag )
{
	m_zero = 0;
	m_vptr = 0x010CFFD0;
	m_value = value;
	m_flag = flag;
}

class Rva0034FFF0
{
public:
	int getField1C() const;
};

// ?getField1C@Rva0034FFF0@@QBEHXZ
int Rva0034FFF0::getField1C() const
{
	return *(const int *)((const char *)this + 0x1C);
}

// ?Rva00350000Empty@@YAXXZ
void Rva00350000Empty()
{
}

class Rva00350010
{
public:
	void slot( void *value );
};

// ?slot@Rva00350010@@QAEXPAX@Z
void Rva00350010::slot( void * )
{
}

class Rva00350040
{
public:
	void release();

	Rva00350040 *m_next;
};

// ?release@Rva00350040@@QAEXXZ
void Rva00350040::release()
{
	Rva00350040 *next = m_next;
	if ( next != 0 )
	{
		next->release();
		delete next;
	}
}

class Rva00350060
{
public:
	int getField04() const;
};

// ?getField04@Rva00350060@@QBEHXZ
int Rva00350060::getField04() const
{
	return *(const int *)((const char *)this + 4);
}

class Rva00350070
{
public:
	int getField08() const;
};

// ?getField08@Rva00350070@@QBEHXZ
int Rva00350070::getField08() const
{
	return *(const int *)((const char *)this + 8);
}
