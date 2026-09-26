// BFME Pathfinder-side bounded table accessor.  The table has 0x44-byte
// records and stores the integer value returned as a float at +0x89c.

extern const float BfmeZeroRange; // retail 0x01075350

class Gen_003D5BF0
{
public:
	float bfmeValue(int entryIndex) const;

private:
	char m_bfmeHead[0x89c];
	struct Entry
	{
		int m_bfmeValue;
		char m_bfmeTail[0x40];
	} m_bfmeEntries[16];
};

// ?bfmeValue@Gen_003D5BF0@@QBEMH@Z
float Gen_003D5BF0::bfmeValue(int entryIndex) const
{
	if (entryIndex < 2)
		goto zero;
	if (entryIndex > 15)
		goto zero;
	goto table;

zero:
	return BfmeZeroRange;

table:
	return (float)m_bfmeEntries[entryIndex].m_bfmeValue;
}
