// cl: /O2

struct Rva002DB3F0Vec6
{
	int v[6];

	bool notEquals(const Rva002DB3F0Vec6 *other) const;
	__forceinline bool equals(const Rva002DB3F0Vec6 *other) const
	{
		for (unsigned i = 0; i < 6; ++i)
		{
			if (v[i] != other->v[i])
				return false;
		}
		return true;
	}
};

bool Rva002DB3F0Vec6::notEquals(
	const Rva002DB3F0Vec6 *other) const
{
	return !equals(other);
}
