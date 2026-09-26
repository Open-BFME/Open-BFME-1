// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// Complete carved leaf bodies with address-derived owners and names.

class Rva007D4FE0Body
{
public:
	Rva007D4FE0Body *body();
};

// ?body@Rva007D4FE0Body@@QAEPAV1@XZ
Rva007D4FE0Body *Rva007D4FE0Body::body()
{
	return this;
}

class Rva007D87B0Body
{
public:
	Rva007D87B0Body *body();
};

// ?body@Rva007D87B0Body@@QAEPAV1@XZ
Rva007D87B0Body *Rva007D87B0Body::body()
{
	return this;
}

class Rva007D9930Body
{
public:
	Rva007D9930Body *body();
};

// ?body@Rva007D9930Body@@QAEPAV1@XZ
Rva007D9930Body *Rva007D9930Body::body()
{
	return this;
}

class Rva007DB9B0Body
{
public:
	Rva007DB9B0Body *body();
};

// ?body@Rva007DB9B0Body@@QAEPAV1@XZ
Rva007DB9B0Body *Rva007DB9B0Body::body()
{
	return this;
}

class Rva007E2DE0Body
{
	char m_padding[4];
	int m_value;

public:
	int body() const;
};

// ?body@Rva007E2DE0Body@@QBEHXZ
int Rva007E2DE0Body::body() const
{
	return m_value;
}

class Rva007E2DF0Body
{
	char m_padding[8];
	char m_value;

public:
	char *body();
};

// ?body@Rva007E2DF0Body@@QAEPADXZ
char *Rva007E2DF0Body::body()
{
	return &m_value;
}

class Rva007E3140Body
{
	char m_padding[8];
	int m_value;

public:
	int body() const;
};

// ?body@Rva007E3140Body@@QBEHXZ
int Rva007E3140Body::body() const
{
	return m_value;
}

class Rva007E3150Body
{
public:
	Rva007E3150Body *body();
};

// ?body@Rva007E3150Body@@QAEPAV1@XZ
Rva007E3150Body *Rva007E3150Body::body()
{
	return this;
}

// ?Rva007E3B30Noop@@YGXPAX@Z
void __stdcall Rva007E3B30Noop(void *)
{
}

class Rva007E3C00Body
{
	char m_padding[0x2C];
	int m_value;

public:
	int body() const;
};

// ?body@Rva007E3C00Body@@QBEHXZ
int Rva007E3C00Body::body() const
{
	return m_value;
}

class Rva007E4740Body
{
	char m_padding[0x48];
	int m_value;

public:
	int body() const;
};

// ?body@Rva007E4740Body@@QBEHXZ
int Rva007E4740Body::body() const
{
	return m_value;
}

// ?Rva007E4760Noop@@YGXPAX@Z
void __stdcall Rva007E4760Noop(void *)
{
}

class Rva007E4770Body
{
	char m_padding[0x34];
	int m_value;

public:
	int body() const;
};

// ?body@Rva007E4770Body@@QBEHXZ
int Rva007E4770Body::body() const
{
	return m_value;
}

class Rva007E7840Body
{
	char m_padding[4];
	int m_value;

public:
	int body() const;
};

// ?body@Rva007E7840Body@@QBEHXZ
int Rva007E7840Body::body() const
{
	return m_value;
}

extern "C" char *__cdecl strcpy(char *, const char *);
#pragma intrinsic(strcpy)

// ?Rva009C8660Body@@YAXPBD@Z
void __cdecl Rva009C8660Body(const char *source)
{
	strcpy((char *)0x0134CA48, source);
}
