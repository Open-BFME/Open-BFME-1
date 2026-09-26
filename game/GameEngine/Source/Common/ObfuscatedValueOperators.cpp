// cl: /DNDEBUG /MD /EHs-c-
// Open-BFME5: the operator set of the obfuscated-scalar wrappers, ten bodies
// recovered from the retail obfuscated-value family.
//
// Every one of them holds its payload at this+4 and reaches it only through one
// of the four 100-byte __cdecl hook wrappers already in the ledger from
// game/GameEngine/Source/Common/BigObfHookWrappers.cpp:
//
//   ?Rva00062EF0@@YAHHH@Z   ?Rva000771C0@@YAHHH@Z    encode(value value)
//   ?Rva00077240@@YAHHH@Z                            combine(lhs rhs)
//   ?Rva00077140@@YAHHH@Z                            compare(lhs rhs)
//
// which is what these bodies are: the value never appears in the clear, every
// read and write of it goes through a wrapper, and even equality is a wrapper
// call whose result is tested against the sentinel 0xA590217B rather than
// against zero. That sentinel is the strongest single tell in the family --
// nothing but a deliberately obfuscated comparison returns a magic word.
//
// The classes are split by CALLEE and by fold. 0x00063850 / 0x00063B00 /
// 0x00063910 use the 0x00062EF0 encoder and are one type. 0x00077710 and
// 0x00078170 are byte-identical inequality operators that the compiler did NOT
// fold, so they are two distinct types over the same helpers, and each is
// grouped with the bodies at its own address range.
//
// The encode-from-reference constructors dereference their argument at offset
// ZERO, not at +4, so the source they take is a bare Int by reference and not
// another wrapper.
//
// The binary operators load the right-hand operand into a NAMED LOCAL before
// the call, and that is not cosmetic: written as one expression MSVC keeps the
// operand POINTER live in eax and picks a fresh register for the value, which
// costs a different encoding at every one of these six sites. Retail reuses eax
// in place, which only happens once the reference is dead at the load.
//
// Identity is address-derived; the helpers keep the names BigObfHookWrappers.cpp
// gave them so the two translation units agree on the callees.

typedef int Int;

extern "C++"
{
	Int Rva00062EF0(Int a, Int b);
	Int Rva000771C0(Int a, Int b);
	Int Rva00077240(Int a, Int b);
	Int Rva00077140(Int a, Int b);
}

// ---------------------------------------------------------------------------
// the 0x00062EF0 encoder's type

class Rva00062EF0Value
{
public:
	Rva00062EF0Value(const Int &value);
	Rva00062EF0Value(Int kind, Int value, Int raw);

	void setValue(Int value);

private:
	Int m_unreconstructed_00;							///< retail this+0x00
	Int m_value;										///< retail this+0x04
};

// ?setValue@Rva00062EF0Value@@QAEXH@Z
void Rva00062EF0Value::setValue(Int value)
{
	m_value = Rva00062EF0(value, value);
}

// ??0Rva00062EF0Value@@QAE@ABH@Z
Rva00062EF0Value::Rva00062EF0Value(const Int &value)
{
	m_value = Rva00062EF0(value, value);
}

// ??0Rva00062EF0Value@@QAE@HHH@Z
Rva00062EF0Value::Rva00062EF0Value(Int kind, Int value, Int raw)
{
	if (kind == 2)
	{
		m_value = raw;
	}
	else if (kind == 1)
	{
		m_value = Rva00062EF0(value, value);
	}
}

// ---------------------------------------------------------------------------
// the type at 0x000777xx

class Rva00077710Value
{
public:
	bool operator!=(const Rva00077710Value &other) const;
	Rva00077710Value operator+(const Rva00077710Value &other) const;

private:
	Rva00077710Value(Int value) { m_value = value; }

	Int m_unreconstructed_00;							///< retail this+0x00
	Int m_value;										///< retail this+0x04
};

// ??9Rva00077710Value@@QBE_NABV0@@Z
bool Rva00077710Value::operator!=(const Rva00077710Value &other) const
{
	Int rhs = other.m_value;
	Int lhs = m_value;

	return Rva00077140(lhs, rhs) != (Int)0xA590217B;
}

// ??HRva00077710Value@@QBE?AV0@ABV0@@Z
Rva00077710Value Rva00077710Value::operator+(const Rva00077710Value &other) const
{
	Int rhs = other.m_value;

	return Rva00077710Value(Rva00077240(m_value, rhs));
}

// ---------------------------------------------------------------------------
// the type at 0x000781xx

class Rva000781A0Value
{
public:
	Rva000781A0Value(const Int &value);
	Rva000781A0Value(Int kind, Int value, Int raw);

	void setValue(Int value);
	Rva000781A0Value &operator+=(const Rva000781A0Value &other);
	bool operator!=(const Rva000781A0Value &other) const;

private:
	Int m_unreconstructed_00;							///< retail this+0x00
	Int m_value;										///< retail this+0x04
};

// ?setValue@Rva000781A0Value@@QAEXH@Z
void Rva000781A0Value::setValue(Int value)
{
	m_value = Rva000771C0(value, value);
}

// ??0Rva000781A0Value@@QAE@ABH@Z
Rva000781A0Value::Rva000781A0Value(const Int &value)
{
	m_value = Rva000771C0(value, value);
}

// ??0Rva000781A0Value@@QAE@HHH@Z
Rva000781A0Value::Rva000781A0Value(Int kind, Int value, Int raw)
{
	if (kind == 2)
	{
		m_value = raw;
	}
	else if (kind == 1)
	{
		m_value = Rva000771C0(value, value);
	}
}

// ??YRva000781A0Value@@QAEAAV0@ABV0@@Z
Rva000781A0Value &Rva000781A0Value::operator+=(const Rva000781A0Value &other)
{
	Int rhs = other.m_value;

	m_value = Rva00077240(m_value, rhs);
	return *this;
}

// ??9Rva000781A0Value@@QBE_NABV0@@Z
bool Rva000781A0Value::operator!=(const Rva000781A0Value &other) const
{
	Int rhs = other.m_value;
	Int lhs = m_value;

	return Rva00077140(lhs, rhs) != (Int)0xA590217B;
}
