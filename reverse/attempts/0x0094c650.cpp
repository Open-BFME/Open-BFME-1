// ??$_Construct@U?$pair@$$CBIURva0094CCF0Value@@@_STL@@U12@@_STL@@YAXPAU?$pair@$$CBIURva0094CCF0Value@@@0@ABU10@@Z
// partial score=0.92 date=2026-09-02
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport

#include <map>

struct Rva0094CCF0Value
{
	unsigned int body[4];
};

typedef _STL::pair<const unsigned int, Rva0094CCF0Value> Rva0094CCF0Pair;

	namespace _STL
{
	template <>
	void _Construct(
		Rva0094CCF0Pair *destination,
		const Rva0094CCF0Pair &source)
	{
		if (destination != 0) {
			const unsigned int *in = (const unsigned int *)&source;
			unsigned int *out = (unsigned int *)destination;
			unsigned int pointer = *in;
			*out = pointer;
			if (pointer != 0) {
				++*(unsigned short *)(pointer + 4);
			}

			++in;
			++out;
			out[0] = in[0];
			out[1] = in[1];
			out[2] = in[2];
			out[3] = in[3];
		}
	}
}
