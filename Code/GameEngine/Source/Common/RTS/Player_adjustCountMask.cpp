// ?adjustCountMask@Player@@QAEX_NH@Z
// Retail 0x000CE710, 211 bytes.  BFME keeps four count-mask entries in each
// rotated loop iteration; the induction variable starts at one so MSVC 7.1
// emits the retail EDI/ESI/EBX/EDX allocation and back edge.
// cl: /DNDEBUG /MD /EHsc

class Object;

void rva000C9CC0Visit(Object *obj, void *user);

class Player
{
public:
	void adjustCountMask(bool increment, int index);
	void iterateObjects(void (*func)(Object *, void *), void *user) const;

private:
	unsigned char m_unmodelled_000[0x2C4];
	int m_counts[32];
	unsigned short m_mask;
};

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
	int i = 1;
	do
	{
		if (m_counts[i - 1] > 0)
			mask |= 1u << (i - 1);
		else
			mask &= ~(1u << (i - 1));
		if (m_counts[i] > 0)
			mask |= 1u << i;
		else
			mask &= ~(1u << i);
		if (m_counts[i + 1] > 0)
			mask |= 1u << (i + 1);
		else
			mask &= ~(1u << (i + 1));
		if (m_counts[i + 2] > 0)
			mask |= 1u << (i + 2);
		else
			mask &= ~(1u << (i + 2));
		i += 4;
	} while (i - 1 < 32);
	m_mask = (unsigned short)mask;
	iterateObjects(rva000C9CC0Visit, 0);
}
