// cl: /DNDEBUG /MD /EHsc

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib/wwstring.h
class StringClass
{
public:
	~StringClass();

private:
	char *m_data;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/rddesc.h
struct ResolutionDescClass
{
	int width;
	int height;
	int bitDepth;
	int refreshRate;
};

template <class T> class DynamicVectorClass
{
public:
	virtual void slot0();

	// The retail unwind states prove this cleanup cannot propagate an exception:
	// the first StringClass member reuses the vector's state instead of advancing it.
	~DynamicVectorClass() throw()
	{
		if (m_vector)
		{
			if (m_isAllocated)
			{
				delete[] m_vector;
				m_vector = 0;
			}
		}
		m_isAllocated = false;
		m_vectorMax = 0;
	}

private:
	T *m_vector;
	int m_vectorMax;
	bool m_isValid;
	bool m_isAllocated;
	char m_pad0E[2];
	int m_activeCount;
	int m_growthStep;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/rddesc.h
class RenderDeviceDescClass
{
public:
	~RenderDeviceDescClass();

private:
	StringClass m_deviceName;
	StringClass m_deviceVendor;
	StringClass m_devicePlatform;
	StringClass m_driverName;
	StringClass m_driverVendor;
	StringClass m_driverVersion;
	StringClass m_hardwareName;
	StringClass m_hardwareVendor;
	StringClass m_hardwareChipset;
	char m_capsAndAdapterIdentifier[0x57C];
	DynamicVectorClass<ResolutionDescClass> m_resolutions;
};

// ??1RenderDeviceDescClass@@QAE@XZ
RenderDeviceDescClass::~RenderDeviceDescClass()
{
}
