// Address-derived leaf bodies recovered from complete retail extents.

class Rva000FDB30Dword
{
public:
	unsigned int get() const;

private:
	char m_padding[8];
	unsigned int m_value;
};

// ?get@Rva000FDB30Dword@@QBEIXZ
unsigned int Rva000FDB30Dword::get() const
{
	return m_value;
}

// The carved boundary at 0x000957F0 contains only a return.
void Rva000957F0Noop()
{
}

class Rva00101B30Dword
{
public:
	unsigned int get() const;

private:
	char m_padding[0xC];
	unsigned int m_value;
};

// ?get@Rva00101B30Dword@@QBEIXZ
unsigned int Rva00101B30Dword::get() const
{
	return m_value;
}

// ?Rva00104740Store@@YAXPAI@Z
void Rva00104740Store(unsigned int *target)
{
	*target = 0x7FFu;
}

class Rva00106600Dword
{
public:
	unsigned int get() const;

private:
	char m_padding[0x20C];
	unsigned int m_value;
};

// ?get@Rva00106600Dword@@QBEIXZ
unsigned int Rva00106600Dword::get() const
{
	return m_value;
}

class Rva00106650Dword
{
public:
	unsigned int get() const;

private:
	char m_padding[4];
	unsigned int m_value;
};

// ?get@Rva00106650Dword@@QBEIXZ
unsigned int Rva00106650Dword::get() const
{
	return m_value;
}

class Rva0010A080Dword
{
public:
	unsigned int get() const;

	unsigned int m_value;
};

// ?get@Rva0010A080Dword@@QBEIXZ
unsigned int Rva0010A080Dword::get() const
{
	return m_value;
}

class Rva0010A710Dword
{
public:
	unsigned int get() const;

private:
	char m_padding[0xC];
	unsigned int m_value;
};

// ?get@Rva0010A710Dword@@QBEIXZ
unsigned int Rva0010A710Dword::get() const
{
	return m_value;
}

class Rva0010A750Dword
{
public:
	unsigned int get() const;

private:
	char m_padding[0x108];
	unsigned int m_value;
};

// ?get@Rva0010A750Dword@@QBEIXZ
unsigned int Rva0010A750Dword::get() const
{
	return m_value;
}

class Rva0010B650Byte
{
public:
	unsigned char get() const;

private:
	char m_padding[4];
	unsigned char m_value;
};

// ?get@Rva0010B650Byte@@QBEEXZ
unsigned char Rva0010B650Byte::get() const
{
	return m_value;
}

class Rva0010D2A0Self
{
public:
	void *get() const;
};

// ?get@Rva0010D2A0Self@@QBEPAXXZ
void *Rva0010D2A0Self::get() const
{
	return (void *)this;
}

class Rva0010D2C0Self
{
public:
	void *get() const;
};

// ?get@Rva0010D2C0Self@@QBEPAXXZ
void *Rva0010D2C0Self::get() const
{
	return (void *)this;
}

class Rva0010D300Self
{
public:
	void *get() const;
};

// ?get@Rva0010D300Self@@QBEPAXXZ
void *Rva0010D300Self::get() const
{
	return (void *)this;
}

class Rva0010D390Value
{
public:
	unsigned int get() const;

private:
	unsigned int m_value;
};

// ?get@Rva0010D390Value@@QBEIXZ
unsigned int Rva0010D390Value::get() const
{
	return m_value + 8;
}

class Rva00112940Dword
{
public:
	unsigned int get() const;

private:
	char m_padding[0x108];
	unsigned int m_value;
};

// ?get@Rva00112940Dword@@QBEIXZ
unsigned int Rva00112940Dword::get() const
{
	return m_value;
}

class Rva00115F20Self
{
public:
	void *get() const;
};

// ?get@Rva00115F20Self@@QBEPAXXZ
void *Rva00115F20Self::get() const
{
	return (void *)this;
}

// ?Rva0011A1A0False@@YA_NXZ
bool Rva0011A1A0False()
{
	return false;
}

// ?Rva0011A1B0False@@YA_NXZ
bool Rva0011A1B0False()
{
	return false;
}

// ?Rva0011A290Ret12@@YGXPAX00@Z
void __stdcall Rva0011A290Ret12(void *, void *, void *)
{
}

// ?Rva00121CD0Ret12@@YGXPAX00@Z
void __stdcall Rva00121CD0Ret12(void *, void *, void *)
{
}

// ?Rva00121CE0Zero@@YAHXZ
int Rva00121CE0Zero()
{
	return 0;
}

// ?Rva00121D00Zero@@YAHXZ
int Rva00121D00Zero()
{
	return 0;
}

class Rva00122270Self
{
public:
	void *get() const;
};

// ?get@Rva00122270Self@@QBEPAXXZ
void *Rva00122270Self::get() const
{
	return (void *)this;
}

// ?Rva00122280Noop@@YAXXZ
void Rva00122280Noop()
{
}

// The carved boundary at 0x001222B0 contains only a return.
void Rva001222B0Noop()
{
}

// The carved boundary at 0x00234CA0 contains only a return.
void Rva00234CA0Noop()
{
}

class Rva001222A0Self
{
public:
	void *get() const;
};

// ?get@Rva001222A0Self@@QBEPAXXZ
void *Rva001222A0Self::get() const
{
	return (void *)this;
}

class Rva001222C0Self
{
public:
	void *get() const;
};

// ?get@Rva001222C0Self@@QBEPAXXZ
void *Rva001222C0Self::get() const
{
	return (void *)this;
}

class Rva001222E0Self
{
public:
	void *get() const;
};

// ?get@Rva001222E0Self@@QBEPAXXZ
void *Rva001222E0Self::get() const
{
	return (void *)this;
}

// The carved boundary proves a one-byte ret-only body at 0x001222F0.
void Rva001222F0Noop()
{
}

// The carved boundary at 0x0040B1B0 contains only a return.
void Rva0040B1B0Noop()
{
}

// ?Rva0040B1C0Noop@@YAXXZ
void Rva0040B1C0Noop()
{
}

// Three immediate stores into the first three dwords and `this` left in eax:
// a constructor of a flat POD whose middle field starts at -1.  The carved
// extent at 0x00350020 is 23 bytes and holds nothing else.
class Rva00350020Record
{
public:
	Rva00350020Record();

private:
	int m_00;
	int m_04;
	int m_08;
};

// ??0Rva00350020Record@@QAE@XZ
Rva00350020Record::Rva00350020Record()
{
	m_00 = 0;
	m_04 = -1;
	m_08 = 0;
}

extern "C" void *__cdecl memset(void *, int, unsigned int);
#pragma intrinsic(memset)

// Retail clears the six dwords at +0x04 through a `lea edx,[eax+4]` base and
// then writes +0x20..+0x28 straight off eax.  Six plain field assignments, an
// inline clear member, a nested constructor and a pointer helper all fold the
// base back into each store; only a memset over the run makes MSVC 7.1
// materialise the address once (docs/shape_levers.md, the nested-array row).
class Rva007E8540Owner
{
public:
	Rva007E8540Owner();

private:
	int m_00;
	int m_slots[6];
	int m_1C;
	int m_20;
	int m_24;
	int m_28;
};

// ??0Rva007E8540Owner@@QAE@XZ
Rva007E8540Owner::Rva007E8540Owner()
{
	memset(m_slots, 0, sizeof(m_slots));
	m_20 = 0;
	m_24 = 0;
	m_28 = 0;
}

// One dword argument, `ret 4` and `this` returned in eax: a constructor that
// parks its pointer argument and, when it is not null, raises a plain
// non-interlocked count at +0x28 of the pointee.  The store happens before the
// branch, which is assignment-then-guard source order.  Complete carved extent
// at 0x00427A50.
class Rva00427A50Target
{
public:
	char m_lead[0x28];
	int m_refCount;
};

class Rva00427A50Holder
{
public:
	Rva00427A50Holder(Rva00427A50Target *target);

private:
	Rva00427A50Target *m_target;
};

// ??0Rva00427A50Holder@@QAE@PAVRva00427A50Target@@@Z
Rva00427A50Holder::Rva00427A50Holder(Rva00427A50Target *target)
{
	m_target = target;
	if (target != 0)
		target->m_refCount++;
}
