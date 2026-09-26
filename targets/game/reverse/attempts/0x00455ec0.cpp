// ??$__partial_sort@PAHHUQ4Sort004567A0@@@_STL@@YAXPAH000UQ4Sort004567A0@@@Z
// partial score=0.7 date=2026-09-02
// cl: -GX-
// stlport
//
// STLport __partial_sort over a four-byte scalar with Q4Sort004567A0.  The
// 140-byte __introsort_loop at 0x004567A0 already names this instantiation;
// make_heap 0x00453C20, adjust_heap 0x00453290, sort_heap 0x004546F0 and the
// comparator ILT 0x00039CB1 are claimed.  Own TU so Q4IntrosortLoop.cpp's
// matched rows stay put.

#include <algorithm>

struct Q4Sort004567A0
{
	void *m_state;
	bool operator()(int, int) const;
};

void q4PartialSort004567A0(int *first, int *middle, int *last, int *tag,
	Q4Sort004567A0 comp)
{
	_STL::__partial_sort(first, middle, last, tag, comp);
}
