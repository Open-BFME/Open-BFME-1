// cl: /DNDEBUG /MD

typedef int Int;
typedef unsigned int UnsignedInt;
typedef bool Bool;

class Rva002DB290
{
public:
	Bool same(const Rva002DB290 *other) const;

private:
	Int m_values[6];
};

Bool Rva002DB290::same(const Rva002DB290 *other) const
{
	for (UnsignedInt index = 0; index < 6; ++index)
	{
		if (m_values[index] != other->m_values[index])
			return false;
	}
	return true;
}
