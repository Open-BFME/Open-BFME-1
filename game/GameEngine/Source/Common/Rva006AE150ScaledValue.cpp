// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD
// Clean reconstruction of the 0x006AE150 scaled value query.

#define Rva006AE150Zero (*(const float *)0x01075350)

class Rva006AE150Argument
{
public:
	float base();
	float scale();
	float limit();
	bool enabled();

	char m_pad08[8];
	void *m_value;
	char m_pad0c[0x1c];
	unsigned int m_kind;
};

class Rva006AE150Owner;

class Rva006AE150Entry
{
public:
	float adjust(Rva006AE150Argument *argument);

private:
	char m_data[0x1c4];
};

struct Rva006AE150Value
{
	char m_pad84[0x84];
	int m_type;
};

class Rva006AE150Owner
{
public:
	float compute(Rva006AE150Argument *argument, int apply);
	float adjust(Rva006AE150Argument *argument);

private:
	char m_padb8[0xb8];
	Rva006AE150Entry m_entries[3];
	int m_value;
};

float Rva006AE150Owner::compute(Rva006AE150Argument *argument, int apply)
{
	switch (argument->m_kind)
	{
	case 0:
		if (m_value != 0)
			return Rva006AE150Zero;
		break;
	case 1:
		if (m_value != 1)
			return Rva006AE150Zero;
		break;
	}

	float result = argument->base();
	result *= argument->scale();
	Rva006AE150Value *value = (Rva006AE150Value *)argument->m_value;
	if (value->m_type == 2 && argument->enabled())
	{
		result *= adjust(argument);
		float limit = argument->limit();
		if (result < limit)
			result = limit;
	}
	if (apply)
	{
		int kind = argument->m_kind;
		result *= m_entries[kind].adjust(argument);
	}
	return result;
}
