// Five bounds-checked float accessors.
//
// Each turns a one-based index into a zero-based one, refuses it when it falls
// outside 0..31, and otherwise loads a float from an array at a fixed offset in
// the object. The refusal returns a shared default read straight from memory.
//
// The check reads as two tests, js after the dec and jge against 0x20, so the
// index is signed and the compiler is testing the decremented value rather
// than the argument; the guarded load is the fall-through, which puts the
// default return last in the source.

extern float TheBfmeDefaultValue;				// 0x01075334

class Gen_00083240
{
public:
	float bfmeGet0(int index) const;
	float bfmeGet80(int index) const;
	float bfmeGet100(int index) const;
	float bfmeGet180(int index) const;
	float bfmeGet200(int index) const;

private:
	float m_bfmeValues[0x220 / 4];
};


// ?bfmeGet0@Gen_00083240@@QBEMH@Z
float Gen_00083240::bfmeGet0(int index) const
{
	int slot = index - 1;

	if (slot >= 0 && slot < 32)
		return m_bfmeValues[0 + slot];

	return TheBfmeDefaultValue;
}

// ?bfmeGet80@Gen_00083240@@QBEMH@Z
float Gen_00083240::bfmeGet80(int index) const
{
	int slot = index - 1;

	if (slot >= 0 && slot < 32)
		return m_bfmeValues[32 + slot];

	return TheBfmeDefaultValue;
}

// ?bfmeGet100@Gen_00083240@@QBEMH@Z
float Gen_00083240::bfmeGet100(int index) const
{
	int slot = index - 1;

	if (slot >= 0 && slot < 32)
		return m_bfmeValues[64 + slot];

	return TheBfmeDefaultValue;
}

// ?bfmeGet180@Gen_00083240@@QBEMH@Z
float Gen_00083240::bfmeGet180(int index) const
{
	int slot = index - 1;

	if (slot >= 0 && slot < 32)
		return m_bfmeValues[96 + slot];

	return TheBfmeDefaultValue;
}

// ?bfmeGet200@Gen_00083240@@QBEMH@Z
float Gen_00083240::bfmeGet200(int index) const
{
	int slot = index - 1;

	if (slot >= 0 && slot < 32)
		return m_bfmeValues[128 + slot];

	return TheBfmeDefaultValue;
}
