// The sole callers are ILT thunks, which prove member-call ABI but do not
// identify the owning types. Keep both addresses in their names.
class DwordAccessor0075D6B0
{
public:
	int getDword0075D6B0() const;

private:
	int m_value;
};

int DwordAccessor0075D6B0::getDword0075D6B0() const
{
	return m_value;
}

class PointerOffsetAccessor0075D6F0
{
public:
	char *getPointerOffset0075D6F0() const;

private:
	char *m_value;
};

char *PointerOffsetAccessor0075D6F0::getPointerOffset0075D6F0() const
{
	return m_value + 0x10;
}
