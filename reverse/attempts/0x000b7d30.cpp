// ?getSegmentPoints@BezierSegment@@QBEXHPAV?$vector@UCoord3D@@V?$allocator@UCoord3D@@@_STL@@@_STL@@@Z
// partial score=0.5 date=2026-09-15
// cl: /DNDEBUG /MD /EHsc

typedef int Int;
typedef bool Bool;

struct Coord3D
{
	Coord3D();
	~Coord3D();
	float x, y, z;
};

namespace _STL
{
struct random_access_iterator_tag {};
template <class T> class allocator {};

template <class InputIterator, class OutputIterator, class Distance>
OutputIterator __copy(InputIterator first, InputIterator last, OutputIterator result,
	const random_access_iterator_tag &tag, Distance *distance);

template <class T, class A>
class vector
{
public:
	void clear()
	{
		random_access_iterator_tag tag;
		_M_finish = __copy(_M_finish, _M_finish, _M_start, tag, (int *)0);
	}
	void resize(unsigned int size, T value);
	void resize(unsigned int size) { resize(size, T()); }
	T &operator[](unsigned int index) { return _M_start[index]; }
private:
	T *_M_start;
	T *_M_finish;
	T *_M_end_of_storage;
};
}

typedef _STL::vector<Coord3D, _STL::allocator<Coord3D> > VecCoord3D;

class BezierSegment
{
	Coord3D m_controlPoints[4];
public:
	void getSegmentPoints(Int numSegments, VecCoord3D *outResult) const;
};

class BezFwdIterator
{
	Int mStep;
	Int mStepsDesired;
	BezierSegment mBezSeg;
	Coord3D mCurrPoint;
	Coord3D mDq;
	Coord3D mDDq;
	Coord3D mDDDq;
public:
	BezFwdIterator(Int stepsDesired, const BezierSegment *bezSeg);
	~BezFwdIterator() {}
	void start();
	Bool done();
	const Coord3D& getCurrent() const;
	void next();
};

void BezierSegment::getSegmentPoints(Int numSegments, VecCoord3D *outResult) const
{
	if (!outResult)
		return;
	outResult->clear();
	outResult->resize(numSegments);
	BezFwdIterator iter(numSegments, this);
	iter.start();
	Int i = 0;
	while (!iter.done()) {
		(*outResult)[i] = iter.getCurrent();
		++i;
		iter.next();
	}
}
