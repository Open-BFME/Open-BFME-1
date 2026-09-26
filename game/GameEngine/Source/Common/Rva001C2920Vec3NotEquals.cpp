// cl: /O2

struct Rva001C2920Vec3
{
	int v[3];

	bool notEquals(const Rva001C2920Vec3 *other) const;
	__forceinline bool equals(const Rva001C2920Vec3 *other) const
	{
		for (unsigned i = 0; i < 3; ++i)
		{
			if (v[i] != other->v[i])
				return false;
		}
		return true;
	}
};

bool Rva001C2920Vec3::notEquals(
	const Rva001C2920Vec3 *other) const
{
	return !equals(other);
}
