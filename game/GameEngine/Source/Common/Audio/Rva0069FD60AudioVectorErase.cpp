// cl: /EHsc
// stlport
//
// 0x0069FD60 is the single-element erase member of an STL vector whose
// retail stride is 0x78 bytes.  The body computes first + 0x78, shifts the
// remaining records through the pinned __copy helper at 0x00044396, moves the
// vector end back by one record, and performs a direct element-destruction
// call through 0x0003FCEC.  The surrounding stripped GameAudio object
// contributes the address context; this record name describes only the
// proven vector ABI and member operations.

#include <vector>

struct Gen_uw_0003fcec
{
	~Gen_uw_0003fcec();

	char m_body[ 0x78 ];
};

template class _STL::vector<Gen_uw_0003fcec>;
