// cl: /DNDEBUG /DWIN32 /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// Open-BFME: BFME holder apply body, retail 0x0018B8B0.

#include <vector>

enum ObjectID
{
	INVALID_OBJECT_ID = 0
};

struct BfmePartCDF
{
	void bfmeCopyOneCDF(BfmePartCDF *other);
	int m_0, m_1, m_2;
};

class Rva0018B8B0Arg
{
public:
	BfmePartCDF *getPart();
};

class Rva0018B8B0Holder
{
public:
	void apply(Rva0018B8B0Arg *arg, bool flag);

private:
	int m_vptr;
	_STL::vector<ObjectID> m_ids;
};

// ?apply@Rva0018B8B0Holder@@QAEXPAVRva0018B8B0Arg@@_N@Z
void Rva0018B8B0Holder::apply(Rva0018B8B0Arg *arg, bool flag)
{
	if (arg)
	{
		if (flag)
			m_ids.clear();

		((BfmePartCDF *)&m_ids)->bfmeCopyOneCDF(arg->getPart());
	}
}
