// Three marks kept side by side, asked for by number. Anything else is not a
// mark at all and answers no.

class BfmeThingXS
{
public:
	unsigned char bfmeMarkXS(int which) const;

private:
	unsigned char m_bfmeHead[0x1ec];	// 0x000
	unsigned char m_bfmeFirst;		// 0x1ec
	unsigned char m_bfmeSecond;		// 0x1ed
	unsigned char m_bfmeThird;		// 0x1ee
};

unsigned char BfmeThingXS::bfmeMarkXS(int which) const
{
	switch (which)
	{
		case 0:
			return m_bfmeFirst;

		case 1:
			return m_bfmeSecond;

		case 2:
			return m_bfmeThird;
	}

	return 0;
}
