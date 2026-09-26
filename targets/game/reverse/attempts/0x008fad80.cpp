// ?rva008fad80@@YAXPAUGen_t_008fb410_p16pod@@00PAPAU1@0001@Z
// partial score=0.8 date=2026-09-06
// ?rva008fad80@@YAXUGen_t_008fb410_p16pod_iter@@0@Z
// cl: /DNDEBUG /MD /D_STLP_USE_STATIC_LIB
// stlport

#include <deque>

struct Gen_t_008fb410_p16pod { int a[4]; };
bool operator==(const Gen_t_008fb410_p16pod &, const Gen_t_008fb410_p16pod &);
bool operator<(const Gen_t_008fb410_p16pod &, const Gen_t_008fb410_p16pod &);

template class _STL::deque<Gen_t_008fb410_p16pod>;

typedef _STL::deque<Gen_t_008fb410_p16pod>::iterator Iter;

void __cdecl rva008fad80(
	Gen_t_008fb410_p16pod *firstCur, Gen_t_008fb410_p16pod *firstFirst,
	Gen_t_008fb410_p16pod *firstLast, Gen_t_008fb410_p16pod **firstNode,
	Gen_t_008fb410_p16pod *lastCur, Gen_t_008fb410_p16pod *lastFirst,
	Gen_t_008fb410_p16pod *lastLast, Gen_t_008fb410_p16pod **lastNode)
{
	Iter last;
	last._M_cur = lastCur;
	last._M_first = lastFirst;
	last._M_last = lastLast;
	last._M_node = lastNode;

	Iter first;
	first._M_cur = firstCur;
	first._M_first = firstFirst;
	first._M_last = firstLast;
	first._M_node = firstNode;

	_STL::__destroy_aux(first, last, _STL::__false_type());
}
