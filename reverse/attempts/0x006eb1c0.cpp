// ?getDisplayModeCount@W3DDisplay@@UAEHXZ
// partial score=0.96 date=2026-09-18
// cl: /O2 /Ob1 /EHsc

#include <math.h>

struct Rva006EB1C0ResolutionDesc
{
	int Width;
	int Height;
	int BitDepth;
	int RefreshRate;
};

template <class T>
class Rva006EB1C0DynamicVector
{
public:
	__forceinline int size(void) const { return m_activeCount; }
	__forceinline T *begin(void) const { return m_vector; }

private:
	void *m_vtable;
	T *m_vector;
	int m_vectorMax;
	bool m_isValid;
	bool m_isAllocated;
	unsigned char m_padding0e[2];
	int m_activeCount;
	int m_growthStep;
};

struct Rva006EB1C0RenderDeviceDesc
{
	unsigned char m_unmodelled_000[0x5a0];
	Rva006EB1C0DynamicVector<Rva006EB1C0ResolutionDesc> m_resolutions;
};

class Rva006EB1C0DX8WrapperAccess
{
public:
	static const Rva006EB1C0RenderDeviceDesc &getRenderDeviceDesc(void);
};

int Rva006EB1C0GetDisplayModeCount(void)
{
	const Rva006EB1C0RenderDeviceDesc &devDesc =
		Rva006EB1C0DX8WrapperAccess::getRenderDeviceDesc();
	const Rva006EB1C0DynamicVector<Rva006EB1C0ResolutionDesc> &resolutions =
		devDesc.m_resolutions;

	int numResolutions = 0;
	for (int res = 0; res < resolutions.size(); ++res)
	{
		if (resolutions.begin()[res].BitDepth >= 24 && resolutions.begin()[res].Width >= 800
			&& fabs((float)resolutions.begin()[res].Width / (float)resolutions.begin()[res].Height
				- *(const float *)0x0111e368) < *(const float *)0x01076c24)
		{
			++numResolutions;
		}
	}

	return numResolutions;
}
