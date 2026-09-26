// A remove that looks its item up, takes the first slot holding it out of the
// vector and then deletes it.
//
// The delete is tail-duplicated into both exits because the loop leaves by a
// break. The search reads its element through the index accessor -- MSVC
// derives a walking cursor from it -- while the erase takes the position as
// begin() plus the same index, which is what keeps the start pointer read for
// the span alive across the loop in a callee-saved register.

extern "C" __declspec(dllimport) void * __cdecl memmove(void *destination, const void *source, unsigned int bytes);

class BfmeItemAN
{
public:
	virtual ~BfmeItemAN(void);				// slot +0x00
};

class BfmeVecAN
{
public:
	unsigned int bfmeSize(void) const
	{
		return (unsigned int)(m_bfmeFinish - m_bfmeStart);
	}

	BfmeItemAN **bfmeBegin(void) const
	{
		return m_bfmeStart;
	}

	BfmeItemAN *bfmeAt(unsigned int index) const
	{
		return m_bfmeStart[index];
	}

	void bfmeErase(BfmeItemAN **position)
	{
		BfmeItemAN **next = position + 1;

		if (m_bfmeFinish != next)
			memmove(position, next, (char *)m_bfmeFinish - (char *)next);

		m_bfmeFinish = m_bfmeFinish - 1;
	}

	BfmeItemAN **m_bfmeStart;				// +0x00
	BfmeItemAN **m_bfmeFinish;				// +0x04
	BfmeItemAN **m_bfmeEnd;					// +0x08
};

class Gen_003C02B0
{
public:
	void bfmeRemove(int key);

private:
	BfmeItemAN *bfmeFind(int key);				// retail thunk 0x00032A56 -> 0x00432A56

	int m_bfmeHead[3];					// +0x00
	BfmeVecAN m_bfmeVector;					// +0x0C
};

// ?bfmeRemove@Gen_003C02B0@@QAEXH@Z
void Gen_003C02B0::bfmeRemove(int key)
{
	BfmeItemAN *item = bfmeFind(key);

	if (!item)
		return;

	for (unsigned int index = 0; index < m_bfmeVector.bfmeSize(); ++index)
	{
		if (m_bfmeVector.bfmeAt(index) == item)
		{
			m_bfmeVector.bfmeErase(m_bfmeVector.bfmeBegin() + index);

			break;
		}
	}

	delete item;
}
