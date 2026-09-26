// Five __thiscall readers of the form "follow a stored pointer, or hand back a
// fixed default when it is null":
//
//     mov eax,[ecx+<PTR>] / test eax,eax / jz L / mov eax,[eax+<FIELD>] / ret
//   L:mov eax,<DEFAULT> / ret
//
// WHAT THE BYTES SHOW.  The jz clears BOTH the second load and the ret, so the
// default is a second return statement, not a value assigned before the branch.
// The load offsets on both sides of the arrow are concrete, as are three of the
// five defaults.
//
//   * 0020CDC0 and 0026E720 return an int through `mov eax,<imm>`; a bool-typed
//     accessor would end `mov al,1` instead, which is exactly what 004892C0
//     does -- and 004892C0's field load is `mov al,[eax+8]`, one byte wide.  So
//     the return width is proven per row, not assumed across the family.
//   * 0063B040 and 0063B060 load a POINTER-sized field and return a DIR32
//     operand that build.py copies from retail.  That operand is not evidence;
//     what it points at is: RVA 0x00C7301C in .rdata holds a zero byte, i.e.
//     the empty string.  The natural reading is `return "";` on the null arm,
//     and the field is a `const char *`.  The bytes cannot prove the field is a
//     string rather than any other pointer -- only that it is four bytes wide
//     and shares a type with the default.
//
// IDENTITY IS NOT RECOVERED.  Names are address-derived, including the pointee
// classes (named after the reader that proves their layout) and the .rdata
// datum (named after its RVA).

#define BFME_PTR_OR_DEFAULT_INT( NAME, PTROFF, FIELDOFF, DEFAULT )        \
	class Gen##NAME                                                       \
	{                                                                     \
	public:                                                               \
		char m_lead[ FIELDOFF ];                                          \
		int m_field;                                                      \
	};                                                                    \
	class NAME                                                            \
	{                                                                     \
	public:                                                               \
		int get() const;                                                  \
		char m_lead[ PTROFF ];                                            \
		Gen##NAME *m_target;                                              \
	};                                                                    \
	int NAME::get() const                                                 \
	{                                                                     \
		if ( m_target )                                                   \
		{                                                                 \
			return m_target->m_field;                                     \
		}                                                                 \
		return DEFAULT;                                                   \
	}

BFME_PTR_OR_DEFAULT_INT( Rva0020CDC0, 4, 0x18, 30 )
BFME_PTR_OR_DEFAULT_INT( Rva0026E720, 0x58, 4, 999999 )

// Byte-wide field, bool return: the tail is `mov al,1` (two bytes), not
// `mov eax,1` (five).
class GenRva004892C0
{
public:
	char m_lead[ 8 ];
	bool m_field;
};

class Rva004892C0
{
public:
	bool get() const;
	char m_lead[ 0x10 ];
	GenRva004892C0 *m_target;
};

bool Rva004892C0::get() const
{
	if ( m_target )
	{
		return m_target->m_field;
	}
	return true;
}

// Two readers of one pointee, at two different field offsets, sharing one
// default.  RVA 0x00C7301C is the empty string in .rdata.
extern const char Rdata00C7301C[];

class GenRva0063B040
{
public:
	char m_lead[ 0x84 ];
	const char *m_name;
	char m_gap[ 8 ];
	const char *m_other;
};

class Rva0063B040
{
public:
	const char *get() const;
	char m_lead[ 0x64 ];
	GenRva0063B040 *m_target;
};

const char *Rva0063B040::get() const
{
	if ( m_target )
	{
		return m_target->m_name;
	}
	return Rdata00C7301C;
}

class Rva0063B060
{
public:
	const char *get() const;
	char m_lead[ 0x64 ];
	GenRva0063B040 *m_target;
};

const char *Rva0063B060::get() const
{
	if ( m_target )
	{
		return m_target->m_other;
	}
	return Rdata00C7301C;
}
