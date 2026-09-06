// ?d_003c57d0@@YAXXZ
// partial score=0.95 date=2026-09-05
// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB
// stlport
//
// Twin of 0x0018B9A0 (Rva0018B9A0AddObjectID.cpp): vector push_back at +0x04,
// inlined addObjectID. The overflow path calls the already-matched
// vector<Gen_t_003c54a0_m4pod> growth helper at 0x003C54A0
// (Code/gen_small/fam_001.cpp family f265_b7a8aa), so the element type here
// must reuse that exact decorated name and cl: line. Address-derived —
// owning type is not recovered.

#include <vector>

struct Gen_t_003c54a0_m4pod { int a[1]; };
bool operator==(const Gen_t_003c54a0_m4pod&, const Gen_t_003c54a0_m4pod&);
bool operator<(const Gen_t_003c54a0_m4pod&, const Gen_t_003c54a0_m4pod&);

class Rva003C5700Holder
{
public:
	void addObjectID( Gen_t_003c54a0_m4pod id );

private:
	int m_vptr;
	_STL::vector<Gen_t_003c54a0_m4pod> m_ids;
};

void Rva003C5700Holder::addObjectID( Gen_t_003c54a0_m4pod id )
{
	m_ids.push_back( id );
}
