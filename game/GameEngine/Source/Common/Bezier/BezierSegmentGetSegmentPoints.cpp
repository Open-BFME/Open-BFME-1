// cl: /DNDEBUG /MD /EHsc
// stlport
// readable body of ?getSegmentPoints@BezierSegment@@QBEXHPAV?$vector@UCoord3D@@V?$allocator@UCoord3D@@@_STL@@@_STL@@@Z: game/GameEngine/Source/Common/Bezier/BezierSegmentGetSegmentPoints.cpp

typedef int Int;
typedef bool Bool;

struct Coord3D
{
	Coord3D() {}
	Coord3D(const Coord3D &that) { x = that.x; y = that.y; z = that.z; }
	~Coord3D() {}
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
	T *begin() { return _M_start; }
	T *end() { return _M_finish; }
	void clear()
	{
		random_access_iterator_tag tag;
		_M_finish = __copy(end(), end(), begin(), tag, (int *)0);
	}
	void resize(unsigned int size, T value = T());
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
	{
		BezFwdIterator iter(numSegments, this);
		iter.start();
		Int i = 0;
		while (!iter.done()) {
			outResult->begin()[i] = iter.getCurrent();
			++i;
			iter.next();
		}
	}
}
