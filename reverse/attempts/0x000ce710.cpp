// ?adjustCountMask@Player@@QAEX_NH@Z
// partial score=0.9 date=2026-09-03
// cl: /DNDEBUG /MD /EHsc
//
// 0x000CE710: increment or decrement counts[index] at this+0x2C4. On the
// 0<->1 edge, rebuild a 32-count bit mask (store the low 16 bits at +0x344)
// and Player::iterateObjects a per-object visitor (0x000C9CC0). This is a
// Player this (iterateObjects ILT 0x0002F1CB). Method name is not recovered.
//
// Near miss: 214 vs 211. Increment path matches (edx load/inc, ecx copy,
// cmp 1) except this is ebx not retail edi; rebuild loop is 3 bytes long.
// Pin visitor ?rva000C9CC0Visit@@YAXPAVObject@@PAX@Z at 0x000C9CC0.

class Object;

void rva000C9CC0Visit(Object *obj, void *user);

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Player.h
class Player
{
public:
	void adjustCountMask(bool increment, int index);
	void iterateObjects(void (*func)(Object *, void *), void *user) const;	// ILT 0x0002F1CB

private:
	unsigned char m_unmodelled_000[0x2C4];
	int m_counts[32];						// +0x2C4
	unsigned short m_mask;					// +0x344
};

// ?adjustCountMask@Player@@QAEX_NH@Z
void Player::adjustCountMask(bool increment, int index)
{
	if (increment)
	{
		if (++m_counts[index] != 1)
			return;
	}
	else
	{
		if (--m_counts[index] != 0)
			return;
	}

	unsigned int mask = 0;
	for (int i = 0; i < 32; ++i)
	{
		unsigned int bit = 1u << i;
		if (m_counts[i] > 0)
			mask |= bit;
		else
			mask &= ~bit;
	}
	m_mask = (unsigned short)mask;
	iterateObjects(rva000C9CC0Visit, 0);
}
