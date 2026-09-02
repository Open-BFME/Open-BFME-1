struct BfmeStateValue
{
	char m_bfmeFields[4];
	unsigned int m_bfmeState;
};

struct BfmeStateOwner
{
	char m_bfmeFields[4];
	BfmeStateValue *m_bfmeValue;
};

class Gen_0028F480
{
public:
	bool bfmeTest(void) const;

private:
	char m_bfmeFields[0x8C];
	BfmeStateOwner *m_bfmeOwner;
};

// ?bfmeTest@Gen_0028F480@@QBE_NXZ
bool Gen_0028F480::bfmeTest(void) const
{
	if (m_bfmeOwner != 0)
	{
		switch (m_bfmeOwner->m_bfmeValue->m_bfmeState)
		{
			case 0:
			case 3:
			case 4:
			case 5:
			case 6:
			case 7:
			case 9:
				return true;
		}
	}

	return false;
}
