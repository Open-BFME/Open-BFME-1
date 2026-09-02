// ?apply@Rva0018B8B0Holder@@QAEXPAVRva0018B8B0Arg@@_N@Z
// partial score=0.92 date=2026-09-02
// cl: /DNDEBUG /MD /EHsc
// stlport
//
// Retail 0x0018B8B0: if the argument is live and the flag is set, clear the
// ObjectID vector at +0x04; then copy a 12-byte part from a getter on the
// argument into the same +0x04 slot via BfmePartCDF::bfmeCopyOneCDF.

#include <vector>

enum ObjectID
{
	INVALID_OBJECT_ID = 0
};

struct BfmePartCDF
{
	void bfmeCopyOneCDF( BfmePartCDF *other );
	int m_0;
	int m_1;
	int m_2;
};

class Rva0018B8B0Arg
{
public:
	BfmePartCDF *getPart();
};

class Rva0018B8B0Holder
{
public:
	void apply( Rva0018B8B0Arg *arg, bool flag );

private:
	int m_vptr;
	_STL::vector<ObjectID> m_ids;
};

// ?apply@Rva0018B8B0Holder@@QAEXPAVRva0018B8B0Arg@@_N@Z present-unmatched
void Rva0018B8B0Holder::apply( Rva0018B8B0Arg *arg, bool flag )
{
	if ( arg )
	{
		if ( flag )
			m_ids.clear();
		( (BfmePartCDF *)&m_ids )->bfmeCopyOneCDF( arg->getPart() );
	}
}
