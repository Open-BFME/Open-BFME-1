// cl: /O2 /MD
// ILT 0x00049341 forwards to the matched DynamicVectorClass<Vector2> constructor at 0x0013B6A0.
#include <new>

class Vector2;

template<class T>
class VectorClass
{
public:
	virtual ~VectorClass();

protected:
	T *Vector;
	int VectorMax;
	bool IsValid;
	bool IsAllocated;
};

template<class T>
class DynamicVectorClass : public VectorClass<T>
{
public:
	DynamicVectorClass(unsigned size, T const *array) throw();

protected:
	int ActiveCount;
	int GrowthStep;
};

class Gen_00C71020Target;
extern Gen_00C71020Target TheBfmeObject_00C71020;
void bfmeForward_00C71020(void);
extern "C" int __cdecl atexit(void (__cdecl *callback)());

void bfmeRva00C6DD80Initialize()
{
	new (&TheBfmeObject_00C71020) DynamicVectorClass<Vector2>(0, 0);
	atexit(bfmeForward_00C71020);
}
