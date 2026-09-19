// cl: /DNDEBUG /DWIN32 /MD /EHs-c-

// Open-BFME: ModelConditionFlags::operator!=, retail RVA 0x001C2870.
// The upstream 320-bit flag comparison is an equality helper negated by the
// public inequality operator; keeping that helper boundary visible preserves
// STLport's redundant bool-normalisation tails.

typedef bool Bool;
typedef unsigned int UnsignedInt;

class ModelConditionFlags
{
public:
	Bool operator!=(const ModelConditionFlags &other) const;

private:
	__forceinline Bool equals(const ModelConditionFlags *other) const
	{
		for (UnsignedInt i = 0; i < 10; ++i)
		{
			if (m_bits[i] != other->m_bits[i])
				return false;
		}
		return true;
	}
	UnsignedInt m_bits[10];
};

Bool ModelConditionFlags::operator!=(const ModelConditionFlags &other) const
{
	return !equals(&other);
}
