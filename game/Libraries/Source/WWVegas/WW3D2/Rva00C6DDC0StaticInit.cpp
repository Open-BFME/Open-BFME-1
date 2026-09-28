// cl: /O2 /MD
#include <new>

struct Rva009080A0Element;

template<class T>
class DynamicVectorClass
{
public:
	DynamicVectorClass(unsigned int size, T const *array) throw();
};

void bfmeForward_00C71030(void);
extern "C" int __cdecl atexit(void (__cdecl *callback)());

class Gen_00C71030Target
{
public:
	__forceinline Gen_00C71030Target()
	{
		new (this) DynamicVectorClass<Rva009080A0Element>(0, 0);
		atexit(bfmeForward_00C71030);
	}

	void bfmeForward(void);
};

Gen_00C71030Target TheBfmeObject_00C71030;
