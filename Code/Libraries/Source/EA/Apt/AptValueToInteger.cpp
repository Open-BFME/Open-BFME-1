// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

extern "C" long __cdecl strtol(const char *text, char **end, int base);
extern "C" int __cdecl atoi(const char *text);

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
	int toInteger() const;
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

extern AptValue *gpNullValue;

int AptValue::toInteger() const
{
	if (isUndefined())
	{
		return 0;
	}

	unsigned int type = m_valueBits & 0x3F;
	switch (type)
	{
		case 1:
		{
			const AptValue *value = this;
			if (type != 1)
			{
				value = m_indirectValue;
			}

			AptStringData *string = value->m_string;
			if (string->m_length > 2 && string->m_text[0] == '0' && string->m_text[1] == 'x')
			{
				return strtol(string->m_text, 0, 16);
			}
			return atoi(string->m_text);
		}

		case 5:
			return m_boolean;

		case 7:
			return m_integer;

		case 6:
			return static_cast<int>(m_float);

		case 42:
			if (this == gpNullValue)
			{
				return 0;
			}
			return 1;

		default:
			return this != gpNullValue;
	}
}
