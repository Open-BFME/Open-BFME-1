// A node joined to its owner as it is made.

class BfmeNodeZK;

class BfmeOwnerZK
{
public:
	unsigned char m_bfmeHead[0x98];		// 0x00
	BfmeNodeZK *m_bfmeLast;			// 0x98
	BfmeNodeZK *m_bfmeFirst;		// 0x9c
};

class BfmeNodeZK
{
public:
	BfmeNodeZK(BfmeOwnerZK *owner);

	BfmeOwnerZK *m_bfmeOwner;		// 0x0
	BfmeNodeZK *m_bfmeAfter;		// 0x4
	BfmeNodeZK *m_bfmeBefore;		// 0x8
};

BfmeNodeZK::BfmeNodeZK(BfmeOwnerZK *owner)
{
	m_bfmeOwner = owner;

	if (owner != 0)
	{
		m_bfmeAfter = owner->m_bfmeFirst;
		m_bfmeBefore = 0;
		owner->m_bfmeFirst = this;

		if (m_bfmeAfter != 0)
			m_bfmeAfter->m_bfmeBefore = this;
		else
			m_bfmeOwner->m_bfmeLast = this;

		return;
	}

	m_bfmeBefore = 0;
	m_bfmeAfter = 0;
}
