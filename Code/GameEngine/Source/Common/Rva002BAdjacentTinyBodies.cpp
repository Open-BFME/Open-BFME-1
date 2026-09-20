// cl: /O2 /Ob0 /DNDEBUG /MD

class Rva002BBBE0Owner
{
public:
	int get() const;

private:
	char m_padding[0x1c];
};

class Rva002BBC00Owner
{
public:
	int get() const;

private:
	char m_padding[0x1c];
};

class Rva002BBC20Owner
{
public:
	int get() const;

private:
	char m_padding[0x1c];
};

class Rva002C7650Owner
{
public:
	int get() const;

private:
	char m_padding[4];
};

class Rva002C7DC0Owner
{
public:
	unsigned char get() const;

private:
	char m_padding[0xd4];
};

class Rva002C7E20Owner
{
public:
	int get() const;

private:
	char m_padding[0xd0];
};

class Rva002C26E0Owner
{
public:
	void *get() const;
};

class Rva002C7A60Owner
{
public:
	void *get() const;
};

// ?get@Rva002BBBE0Owner@@QBEHXZ
int Rva002BBBE0Owner::get() const
{
	return *reinterpret_cast<const int *>(reinterpret_cast<const char *>(this) + 0x1c);
}

// ?get@Rva002BBC00Owner@@QBEHXZ
int Rva002BBC00Owner::get() const
{
	return *reinterpret_cast<const int *>(reinterpret_cast<const char *>(this) + 0x1c);
}

// ?get@Rva002BBC20Owner@@QBEHXZ
int Rva002BBC20Owner::get() const
{
	return *reinterpret_cast<const int *>(reinterpret_cast<const char *>(this) + 0x1c);
}

// ?Rva002BC040@@YGXH@Z
void __stdcall Rva002BC040(int)
{
}

// ?Rva002BC3C0@@YA_NXZ
bool __cdecl Rva002BC3C0(void)
{
	return false;
}

// ?Rva002BC660@@YGXHHH@Z
void __stdcall Rva002BC660(int, int, int)
{
}

// ?Rva002BECC0@@YA_NXZ
bool __cdecl Rva002BECC0(void)
{
	return true;
}

// ?Rva002C1250@@YAPBDXZ
const char *__cdecl Rva002C1250(void)
{
	return "GiantBirdGuardAttackAggressorState";
}

// ?get@Rva002C26E0Owner@@QBEPAXXZ
void *Rva002C26E0Owner::get() const
{
	return (void *)this;
}

// ?Rva002C2700@@YA_NXZ
bool __cdecl Rva002C2700(void)
{
	return true;
}

// ?Rva002C4240@@YGXH@Z
void __stdcall Rva002C4240(int)
{
}

// ?Rva002C4250@@YGXH@Z
void __stdcall Rva002C4250(int)
{
}

// ?Rva002C4260@@YGXH@Z
void __stdcall Rva002C4260(int)
{
}

// ?Rva002C4280@@YA_NXZ
bool __cdecl Rva002C4280(void)
{
	return true;
}

// ?Rva002C4290@@YGXH@Z
void __stdcall Rva002C4290(int)
{
}

// ?Rva002C42B0@@YA_NXZ
bool __cdecl Rva002C42B0(void)
{
	return true;
}

// ?Rva002C42C0@@YA_NXZ
bool __cdecl Rva002C42C0(void)
{
	return false;
}

// ?get@Rva002C7650Owner@@QBEHXZ
int Rva002C7650Owner::get() const
{
	return *reinterpret_cast<const int *>(reinterpret_cast<const char *>(this) + 4);
}

// ?get@Rva002C7A60Owner@@QBEPAXXZ
void *Rva002C7A60Owner::get() const
{
	return (void *)this;
}

// ?get@Rva002C7DC0Owner@@QBEEXZ
unsigned char Rva002C7DC0Owner::get() const
{
	return *reinterpret_cast<const unsigned char *>(reinterpret_cast<const char *>(this) + 0xd4);
}

// ?get@Rva002C7E20Owner@@QBEHXZ
int Rva002C7E20Owner::get() const
{
	return *reinterpret_cast<const int *>(reinterpret_cast<const char *>(this) + 0xd0);
}

// ?Rva002C7E80@@YA_NXZ
bool __cdecl Rva002C7E80(void)
{
	return true;
}

// ?Rva002C8280@@YGXH@Z
void __stdcall Rva002C8280(int)
{
}

// ?Rva002C8290@@YAHXZ
int __cdecl Rva002C8290(void)
{
	return 0;
}

// ?Rva002C82B0@@YGXH@Z
void __stdcall Rva002C82B0(int)
{
}

// ?dup_002BBBF0@@YAXXZ
void dup_002BBBF0(void)
{
}
