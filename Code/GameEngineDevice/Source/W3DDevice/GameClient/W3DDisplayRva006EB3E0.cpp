// cl: /O2 /Ob1 /EHsc

// Retail 0x006EB3E0 is the complete 178-byte body reached by slot 19 of the
// W3DDisplay vtable at 0x0111EDD0.  Its original virtual spelling is retained
// as an address-derived method: the vtable proves the W3DDisplay owner, while
// the source-level display-mode description name is not used as an identity
// claim here.

#include <math.h>

struct Rva006EB3E0ResolutionDesc
{
	int Width;
	int Height;
	int BitDepth;
	int RefreshRate;
};

template <class T>
class Rva006EB3E0DynamicVector
{
public:
	int Count(void) const
	{
		return m_activeCount;
	}

	const T &operator[](int index) const
	{
		return m_vector[index];
	}

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

class RenderDeviceDescClass
{
public:
	const Rva006EB3E0DynamicVector<Rva006EB3E0ResolutionDesc> &
	Enumerate_Resolutions(void) const
	{
		return m_resolutions;
	}

private:
	unsigned char m_unmodelled_000[0x5a0];
	Rva006EB3E0DynamicVector<Rva006EB3E0ResolutionDesc> m_resolutions;
};

// The retail call uses the tracked incremental-link thunk at 0x008FD190,
// which is the thunk candidate for this already-matched provider body.
class W3DDisplay;
class DX8Wrapper
{
	// Keep the original protected-static access encoded in the retail symbol.
protected:
	static const RenderDeviceDescClass &Get_Render_Device_Desc(int device);
	friend class W3DDisplay;
};

#define RVA006EB3E0_DATA(type, address) (*reinterpret_cast<const type *>(address))

class W3DDisplay
{
public:
	virtual void rva006EB3E0(int modeIndex, int *xres, int *yres,
		int *bitDepth);
};

// ?rva006EB3E0@W3DDisplay@@UAEXHPAH00@Z
void W3DDisplay::rva006EB3E0(int modeIndex, int *xres, int *yres,
	int *bitDepth)
{
	int numResolutions = 0;
	const RenderDeviceDescClass &devDesc = DX8Wrapper::Get_Render_Device_Desc(0);
	const Rva006EB3E0DynamicVector<Rva006EB3E0ResolutionDesc> &resolutions =
		devDesc.Enumerate_Resolutions();

	for (int res = 0; res < resolutions.Count(); ++res)
	{
		if (resolutions[res].BitDepth >= 24 && resolutions[res].Width >= 800 &&
			fabs((float)resolutions[res].Width /
				(float)resolutions[res].Height -
				RVA006EB3E0_DATA(float, 0x0111e368)) <
			RVA006EB3E0_DATA(float, 0x01076c24))
		{
			if (numResolutions == modeIndex)
			{
				*xres = resolutions[res].Width;
				*yres = resolutions[res].Height;
				*bitDepth = resolutions[res].BitDepth;
				return;
			}
			++numResolutions;
		}
	}
}
