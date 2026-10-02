// ?toNumber@AptValue@@QAEMXZ
// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// Retail 0x008983D0 is the Apt value numeric coercion used by the named
// Apt callbacks and by the Apt comparison/action bodies.  The member layout
// is the one independently matched by AptValue::toInteger and the value
// checks; the address-derived dispatch aliases in the retail call inventory
// are not used as the source identity.

extern "C" float Rva008921B0Atof(const char *text);
extern const float BfmeZeroRange;

// The true/false value is retail's 1.0f literal at VA 0x01075334 (bytes
// 00 00 80 3f, in a .rdata pool of float literals: 1.0f, 3.0f, 0.5f, 4.0f),
// so it is spelled as the compiler constant here.  Declaring it as an extern
// float global made this object reference ?g_bfmeDefaultBU@@3MA, a name
// nothing in the tree defines; the compiler emits the same __real@3f800000
// COMDAT literal at the same retail operand.

struct AptStringData
{
	unsigned short m_refs;
	unsigned short m_length;
	unsigned int m_capacity;
	char m_text[1];
};

class AptValue
{
public:
	float toNumber();
	bool isUndefined() const
	{
		return ((m_valueBits >> 15) & 1) == 0;
	}

private:
	void *m_vtable;
	unsigned int m_valueBits;
	union
	{
		unsigned char m_boolean;
		int m_integer;
		float m_float;
		AptStringData *m_string;
	};
	unsigned char m_unmodelled_0C[0x14];
	AptValue *m_indirectValue;
};

extern AptValue *g_bfmeFallbackDB;

float AptValue::toNumber()
{
	if (isUndefined())
		return BfmeZeroRange;

	unsigned int type = m_valueBits & 0x3f;
	switch (type)
	{
		case 1:
		case 42:
		{
			const AptValue *value = this;
			if (type != 1)
				value = m_indirectValue;
			return Rva008921B0Atof(value->m_string->m_text);
		}

		case 5:
			return m_boolean ? 1.0f : BfmeZeroRange;

		case 7:
			return static_cast<float>(m_integer);

		case 6:
			return m_float;

		default:
			return (this != g_bfmeFallbackDB) ? 1.0f : BfmeZeroRange;
	}
}
