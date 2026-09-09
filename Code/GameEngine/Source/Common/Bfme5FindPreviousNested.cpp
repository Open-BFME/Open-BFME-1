// cl: /DNDEBUG /MD /EHsc
// Gen_007602B0::bfmeFindPrevious, retail body 0x007602B0.

class BfmeItemED
{
public:
	unsigned char m_unreconstructed[0xbc];
};

class Gen_0075F1A0View
{
private:
	unsigned char m_unreconstructed[0x24];

public:
	BfmeItemED *m_start;
	BfmeItemED *m_finish;
};

class Gen_007602B0
{
public:
	BfmeItemED *bfmeFindPrevious( BfmeItemED *item ) const;

private:
	unsigned char m_unreconstructed[4];
	Gen_0075F1A0View *m_owner;
};

// ?bfmeFindPrevious@Gen_007602B0@@QBEPAVBfmeItemED@@PAV2@@Z
BfmeItemED *Gen_007602B0::bfmeFindPrevious( BfmeItemED *item ) const
{
	BfmeItemED *previous = 0;
	BfmeItemED *entry = m_owner->m_start;
	BfmeItemED *finish = m_owner->m_finish;

	while ( entry != finish )
	{
		if ( entry == item )
			return previous;

		previous = entry;
		++entry;
	}

	return 0;
}
