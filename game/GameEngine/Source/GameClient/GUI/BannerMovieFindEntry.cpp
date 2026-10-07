// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD

// Retail calls ILT 0x000434E6 -> 0x00581CE0, matched in BannerUI.cpp as
// _STL::__find_if<BannerMovieEntry *, BannerMovieEntryMatches> (the body
// std::find_if forwards to). Only its declaration is needed here.
struct BannerMovieEntry;

class BannerMovieEntryMatches
{
public:
	BannerMovieEntryMatches(int id) : m_id(id) {}

private:
	int m_id;
};

namespace _STL
{
struct random_access_iterator_tag;

template <class _RandomAccessIter, class _Predicate>
_RandomAccessIter __find_if(_RandomAccessIter __first, _RandomAccessIter __last,
	_Predicate __pred, const random_access_iterator_tag &);
}

class BfmeRangeOwner
{
public:
	void *find(int value);

private:
	unsigned char m_pad00[0x30];
	void *m_begin;
	void *m_end;
};

// ?find@BfmeRangeOwner@@QAEPAXH@Z
void *BfmeRangeOwner::find(int value)
{
	void *rangeEnd = m_end;
	void *foundEntry = _STL::__find_if((BannerMovieEntry *)m_begin, (BannerMovieEntry *)rangeEnd,
		BannerMovieEntryMatches(value), *(const _STL::random_access_iterator_tag *)&value);
	return foundEntry == rangeEnd ? 0 : foundEntry;
}
