// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /Ob0 /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib
#include "Common/GameMemory.h"
#include "Common/Overridable.h"

void __cdecl operator delete[](void *p);

class BfmeOverride1137
{
public:
	virtual void bfmeDeleteZB(int flag) = 0;

	const Overridable *m_bfme04ZB;
};

class WeatherSetting;

template <class T> class OVERRIDE
{
public:
	T *ptr;
};

extern OVERRIDE<WeatherSetting> TheWeatherSetting;

class SubsystemInterface
{
public:
	virtual ~SubsystemInterface();
	virtual void bfmeS1ZB() = 0;
};

static __forceinline BfmeOverride1137 *bfmeWalkZB(BfmeOverride1137 *p)
{
	if (p->m_bfme04ZB == 0)
		return p;

	return (BfmeOverride1137 *)p->m_bfme04ZB->getFinalOverride();
}

class BfmeHostZB : public SubsystemInterface
{
public:
	virtual ~BfmeHostZB();

	unsigned char m_bfme04ZB[4];
	char *m_bfme08ZB;
};

BfmeHostZB::~BfmeHostZB()
{
	operator delete[](m_bfme08ZB);

	m_bfme08ZB = 0;

	BfmeOverride1137 *g = (BfmeOverride1137 *)TheWeatherSetting.ptr;

	if (g != 0)
	{
		const Overridable *n = g->m_bfme04ZB;

		if ((n != 0 ? (BfmeOverride1137 *)n->getFinalOverride() : g) != 0)
		{
			BfmeOverride1137 *ov = (n != 0 ? (BfmeOverride1137 *)n->getFinalOverride() : g);

			if (ov != 0)
				ov->bfmeDeleteZB(1);

			TheWeatherSetting.ptr = 0;
		}
	}
}
