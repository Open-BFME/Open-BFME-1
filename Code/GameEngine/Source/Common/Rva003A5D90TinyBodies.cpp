// cl: -GX-
// stlport
// Address-derived leaf and vector-clear bodies from one carved batch.

struct Gen003A9B60;
struct Gen003A9C30;
struct Gen003A9CF0;

namespace _STL
{
template <class T>
class allocator
{
};

template <class T, class A = allocator<T> >
class vector
{
public:
	void clear()
	{
		erase(m_start, m_finish);
	}

	T *erase(T *first, T *last);

private:
	T *m_start;
	T *m_finish;
	T *m_end;
};
}

// ?d_003A5DB0@@YAXXZ
void d_003A5DB0()
{
}

// Retail 0x003A5DA0 contains only ret.
void Rva003A5DA0Noop()
{
}

class Rva003A5D90Dword
{
public:
	unsigned int get() const;

private:
	unsigned int m_value;
};

// ?get@Rva003A5D90Dword@@QBEIXZ
unsigned int Rva003A5D90Dword::get() const
{
	return m_value;
}

class Rva003B0000Vector
{
public:
	void clear();

private:
	_STL::vector<Gen003A9B60> m_vector;
};

// ?clear@Rva003B0000Vector@@QAEXXZ
void Rva003B0000Vector::clear()
{
	m_vector.clear();
}

class Rva003B0010Vector
{
public:
	void clear();

private:
	_STL::vector<Gen003A9C30> m_vector;
};

// ?clear@Rva003B0010Vector@@QAEXXZ
void Rva003B0010Vector::clear()
{
	m_vector.clear();
}

class Rva003B0020Vector
{
public:
	void clear();

private:
	_STL::vector<Gen003A9CF0> m_vector;
};

// ?clear@Rva003B0020Vector@@QAEXXZ
void Rva003B0020Vector::clear()
{
	m_vector.clear();
}

class Rva003B2D20Byte
{
public:
	unsigned char get() const;

private:
	char m_padding[0x1C];
	unsigned char m_value;
};

// ?get@Rva003B2D20Byte@@QBEEXZ
unsigned char Rva003B2D20Byte::get() const
{
	return m_value;
}

class Rva003CB960Address
{
public:
	void *get();

private:
	char m_padding[0x24];
	char m_value;
};

// ?get@Rva003CB960Address@@QAEPAXXZ
void *Rva003CB960Address::get()
{
	return &m_value;
}

class Rva003CB970Address
{
public:
	void *get();

private:
	char m_padding[0x30];
	char m_value;
};

// ?get@Rva003CB970Address@@QAEPAXXZ
void *Rva003CB970Address::get()
{
	return &m_value;
}

class Rva003CB980Address
{
public:
	void *get();

private:
	char m_padding[0x58];
	char m_value;
};

// ?get@Rva003CB980Address@@QAEPAXXZ
void *Rva003CB980Address::get()
{
	return &m_value;
}

class Rva003CB990Byte
{
public:
	unsigned char get() const;

private:
	char m_padding[0x64];
	unsigned char m_value;
};

// ?get@Rva003CB990Byte@@QBEEXZ
unsigned char Rva003CB990Byte::get() const
{
	return m_value;
}

class Rva003CBA10Self
{
public:
	void *get();
};

// ?get@Rva003CBA10Self@@QAEPAXXZ
void *Rva003CBA10Self::get()
{
	return (void *)this;
}

class Rva003CBA20Address
{
public:
	void *get();

private:
	char m_padding[0x14];
	char m_value;
};

// ?get@Rva003CBA20Address@@QAEPAXXZ
void *Rva003CBA20Address::get()
{
	return &m_value;
}

class Rva003CBA30Float
{
public:
	float get() const;

private:
	char m_padding[0x0C];
	float m_value;
};

// ?get@Rva003CBA30Float@@QBEMXZ
float Rva003CBA30Float::get() const
{
	return m_value;
}

class Rva003CBA40Float
{
public:
	float get() const;

private:
	char m_padding[0x10];
	float m_value;
};

// ?get@Rva003CBA40Float@@QBEMXZ
float Rva003CBA40Float::get() const
{
	return m_value;
}

class Rva003CBC70Dword
{
public:
	unsigned int get() const;

private:
	unsigned int m_value;
};

// ?get@Rva003CBC70Dword@@QBEIXZ
unsigned int Rva003CBC70Dword::get() const
{
	return m_value;
}

class Rva003CBCA0Dword
{
public:
	unsigned int get() const;

private:
	char m_padding[4];
	unsigned int m_value;
};

// ?get@Rva003CBCA0Dword@@QBEIXZ
unsigned int Rva003CBCA0Dword::get() const
{
	return m_value;
}

class Rva003CBD60Self
{
public:
	void *get();
};

// ?get@Rva003CBD60Self@@QAEPAXXZ
void *Rva003CBD60Self::get()
{
	return (void *)this;
}

class Rva003CBDD0Self
{
public:
	void *get();
};

// ?get@Rva003CBDD0Self@@QAEPAXXZ
void *Rva003CBDD0Self::get()
{
	return (void *)this;
}

class Rva003CBDF0Dword
{
public:
	unsigned int get() const;

private:
	unsigned int m_value;
};

// ?get@Rva003CBDF0Dword@@QBEIXZ
unsigned int Rva003CBDF0Dword::get() const
{
	return m_value;
}

class Rva003CBE20Dword
{
public:
	unsigned int get() const;

private:
	char m_padding[4];
	unsigned int m_value;
};

// ?get@Rva003CBE20Dword@@QBEIXZ
unsigned int Rva003CBE20Dword::get() const
{
	return m_value;
}

class Rva003CBE40Self
{
public:
	void *get();
};

// ?get@Rva003CBE40Self@@QAEPAXXZ
void *Rva003CBE40Self::get()
{
	return (void *)this;
}

class Rva003CBE80Self
{
public:
	void *get();
};

// ?get@Rva003CBE80Self@@QAEPAXXZ
void *Rva003CBE80Self::get()
{
	return (void *)this;
}

class Rva003CBEA0Dword
{
public:
	unsigned int get() const;

private:
	unsigned int m_value;
};

// ?get@Rva003CBEA0Dword@@QBEIXZ
unsigned int Rva003CBEA0Dword::get() const
{
	return m_value;
}

class Rva0043A550Byte
{
public:
	unsigned char get() const;

private:
	char m_padding[0x0C];
	unsigned char m_value;
};

// ?get@Rva0043A550Byte@@QBEEXZ
unsigned char Rva0043A550Byte::get() const
{
	return m_value;
}

class Rva0043A660Dword
{
public:
	unsigned int get() const;

private:
	char m_padding[0x10];
	unsigned int m_value;
};

// ?get@Rva0043A660Dword@@QBEIXZ
unsigned int Rva0043A660Dword::get() const
{
	return m_value;
}

class Rva0043A6D0ByteSlot
{
public:
	void set(unsigned char value);

private:
	char m_padding[0x12B1];
};

// ?set@Rva0043A6D0ByteSlot@@QAEXE@Z
void Rva0043A6D0ByteSlot::set(unsigned char value)
{
	*reinterpret_cast<unsigned char *>(reinterpret_cast<char *>(this) + 0x12B1) = value;
}
