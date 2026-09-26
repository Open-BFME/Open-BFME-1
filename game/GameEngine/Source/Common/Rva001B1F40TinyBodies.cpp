// Address-derived leaf bodies recovered from the carved retail range.
// No semantic owner is proven for these bodies.

// cl: /DNDEBUG /MD /EHsc

struct Rva001B1F40FloatField
{
	float get() const;
};

// ?get@Rva001B1F40FloatField@@QBEMXZ
float Rva001B1F40FloatField::get() const
{
	return *(const float *)((const char *)this + 0x1c);
}

struct Rva001B1F60FloatField
{
	float get() const;
};

// ?get@Rva001B1F60FloatField@@QBEMXZ
float Rva001B1F60FloatField::get() const
{
	return *(const float *)((const char *)this + 8);
}

struct Rva001B20C0Address
{
	void *get() const;
};

// ?get@Rva001B20C0Address@@QBEPAXXZ
void *Rva001B20C0Address::get() const
{
	return (void *)((const char *)this + 0x58);
}

// ?Rva001B20A0Noop@@YAXXZ
void Rva001B20A0Noop()
{
}

// ?Rva001B2AE0Noop@@YGXPAX@Z
void __stdcall Rva001B2AE0Noop(void *)
{
}

struct Rva001B2F30DwordField
{
	int get() const;
};

// ?get@Rva001B2F30DwordField@@QBEHXZ
int Rva001B2F30DwordField::get() const
{
	return *(const int *)((const char *)this + 8);
}

struct Rva001B3A60Address
{
	void *get() const;
};

// ?get@Rva001B3A60Address@@QBEPAXXZ
void *Rva001B3A60Address::get() const
{
	return (void *)((const char *)this - 0x64);
}

struct Rva001B3A70Address
{
	void *get() const;
};

// ?get@Rva001B3A70Address@@QBEPAXXZ
void *Rva001B3A70Address::get() const
{
	return (void *)((const char *)this - 0x74);
}

struct Rva001B3A80FloatField
{
	float get() const;
};

// ?get@Rva001B3A80FloatField@@QBEMXZ
float Rva001B3A80FloatField::get() const
{
	return *(const float *)((const char *)this - 0x68);
}

struct Rva001B3F50FloatField
{
	float get() const;
};

// ?get@Rva001B3F50FloatField@@QBEMXZ
float Rva001B3F50FloatField::get() const
{
	return *(const float *)((const char *)this + 0x4c);
}

struct Rva001B3F90ByteField
{
	unsigned char get() const;
};

// ?get@Rva001B3F90ByteField@@QBEEXZ
unsigned char Rva001B3F90ByteField::get() const
{
	return *(const unsigned char *)((const char *)this + 0x5c);
}

struct Rva001B3FA0Counter
{
	void increment();
};

// ?increment@Rva001B3FA0Counter@@QAEXXZ
void Rva001B3FA0Counter::increment()
{
	++*(unsigned int *)this;
}

struct Rva001B3FC0DwordField
{
	int get() const;
};

// ?get@Rva001B3FC0DwordField@@QBEHXZ
int Rva001B3FC0DwordField::get() const
{
	return *(const int *)((const char *)this + 8);
}

struct Rva001B3FD0DwordField
{
	int get() const;
};

// ?get@Rva001B3FD0DwordField@@QBEHXZ
int Rva001B3FD0DwordField::get() const
{
	return *(const int *)((const char *)this + 0x20);
}

// ?Rva001B4050Get@@YAMXZ
float Rva001B4050Get()
{
	return *(const float *)0x01084C3C;
}

struct Rva001B40B0DwordSlot
{
	void set(int value);
};

// ?set@Rva001B40B0DwordSlot@@QAEXH@Z
void Rva001B40B0DwordSlot::set(int value)
{
	*(int *)((char *)this + 0x474) = value;
}

struct Rva001B40C0FlagBits
{
	bool test(int bit) const;
};

// ?test@Rva001B40C0FlagBits@@QBE_NH@Z
bool Rva001B40C0FlagBits::test(int bit) const
{
	return (*(const unsigned int *)((const char *)this + 0x3f0) & (1u << bit)) != 0;
}

// ?Rva001B4960Noop@@YGXPAX@Z
void __stdcall Rva001B4960Noop(void *)
{
}

// ?Rva001B4970Noop@@YGXPAX@Z
void __stdcall Rva001B4970Noop(void *)
{
}

struct Rva001B4BD0Self
{
	void *get();
};

// ?get@Rva001B4BD0Self@@QAEPAXXZ
void *Rva001B4BD0Self::get()
{
	return this;
}

// Retail RVA 0x001B4BE0 is a one-byte carved no-op.  No semantic owner is
// proven, so this source keeps the function name address-derived.

// ?Rva001B4BE0Noop@@YAXXZ
void Rva001B4BE0Noop(void)
{
}

struct Rva001B4C10Address
{
	void *get() const;
};

// ?get@Rva001B4C10Address@@QBEPAXXZ
void *Rva001B4C10Address::get() const
{
	return (void *)(*(const unsigned int *)this + 0x10);
}

struct Rva001B4CB0Self
{
	void *get();
};

// ?get@Rva001B4CB0Self@@QAEPAXXZ
void *Rva001B4CB0Self::get()
{
	return this;
}

struct Rva001B4CE0Self
{
	void *get();
};

// ?get@Rva001B4CE0Self@@QAEPAXXZ
void *Rva001B4CE0Self::get()
{
	return this;
}

struct Rva001B4E00Address
{
	void *get() const;
};

// ?get@Rva001B4E00Address@@QBEPAXXZ
void *Rva001B4E00Address::get() const
{
	return (void *)((const char *)this + 8);
}

struct Rva001B4F70DwordField
{
	int get() const;
};

// ?get@Rva001B4F70DwordField@@QBEHXZ
int Rva001B4F70DwordField::get() const
{
	return *(const int *)((const char *)this + 4);
}

struct Rva001C0180Self
{
	void *get();
};

// ?get@Rva001C0180Self@@QAEPAXXZ
void *Rva001C0180Self::get()
{
	return this;
}
