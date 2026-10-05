// Open-BFME5 conversions.
// stlport
#include <ostream>

namespace _STL
{
extern ostream cerr;
extern ostream clog;
}

extern char g_bfme918VftA[];

class BfmeSub918P
{
public:
	void bfmeDtor918P();
};


void bfmeGo918C(void)
{
	int d = *(int *)(*(char **)&_STL::cerr + 4);
	*(char **)((char *)&_STL::cerr + d) = g_bfme918VftA;
	((BfmeSub918P *)((char *)&_STL::cerr + 4))->bfmeDtor918P();
}

void bfmeGo918D(void)
{
	int d = *(int *)(*(char **)&_STL::clog + 4);
	*(char **)((char *)&_STL::clog + d) = g_bfme918VftA;
	((BfmeSub918P *)((char *)&_STL::clog + 4))->bfmeDtor918P();
}
