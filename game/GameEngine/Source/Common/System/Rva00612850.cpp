
class BfmeNodePV
{
public:
	unsigned char m_bfmeHeadPV[ 0x14 ];
	void *m_bfmeValuePV;
};

class BfmeTablePV
{
public:
	void bfmeLookupPV( BfmeNodePV **found, void **key );

	BfmeNodePV *m_bfmeEndPV;
};

class Rva00612850
{
public:
	void *method( void *key );

	unsigned char m_bfmeHeadPV[ 0x27c ];
	BfmeTablePV m_bfmeTablePV;
};

void *Rva00612850::method( void *key )
{
	BfmeNodePV *found;
	if( !key )
	{
		return 0;
	}
	else
	{
		m_bfmeTablePV.bfmeLookupPV( &found, &key );
		if( found == m_bfmeTablePV.m_bfmeEndPV )
			return 0;

		return found->m_bfmeValuePV;
	}
}
