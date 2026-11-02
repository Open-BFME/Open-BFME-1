
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

// The table lookup is reached through ILT 0x0002DF6F (body 0x00610950), which the
// ledger defines as ?j_0002df6f@@YAXXZ; the call names it through a member pointer.
extern void j_0002df6f(void);

void *Rva00612850::method( void *key )
{
	BfmeNodePV *found;
	if( !key )
	{
		return 0;
	}
	else
	{
		union { void (*raw)(void); void (BfmeTablePV::*member)(BfmeNodePV **, void **); } call;
		call.raw = j_0002df6f;
		(m_bfmeTablePV.*call.member)( &found, &key );
		if( found == m_bfmeTablePV.m_bfmeEndPV )
			return 0;

		return found->m_bfmeValuePV;
	}
}
