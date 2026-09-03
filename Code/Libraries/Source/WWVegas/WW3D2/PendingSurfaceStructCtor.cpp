// cl: /DNDEBUG /MD /EHsc
// Compiler-generated Render2DSentenceClass::PendingSurfaceStruct constructor.
// VectorClass<PendingSurfaceStruct> at 0x0093FEE0 constructs elements with this
// body. Unwind state 0 destroys this via ??1W3DRadarResetSurface@@QAE@XZ
// (0x008FC5B0), so that wrapper is the first base; Renderers is the
// DynamicVectorClass at +4.

class W3DRadarResetSurface
{
public:
	W3DRadarResetSurface(void);
	~W3DRadarResetSurface(void);

	void *m_surface;
};

inline W3DRadarResetSurface::W3DRadarResetSurface(void)
	: m_surface(0)
{
}

class VectorClassDummy
{
public:
	VectorClassDummy(int size = 0, void *const *array = 0);
	virtual ~VectorClassDummy(void);
	virtual bool operator==(VectorClassDummy const &) const;
	virtual bool Resize(int newsize, void *const *array = 0);
	virtual void Clear(void);
	virtual int ID(void *const *ptr);
	virtual int ID(void *const &ptr);

	void **Vector;
	int VectorMax;
	bool IsValid;
	bool IsAllocated;
	bool VectorClassPad[2];
};

inline VectorClassDummy::VectorClassDummy(int size, void *const *array) :
	Vector(0),
	VectorMax(size),
	IsValid(true),
	IsAllocated(false)
{
	(void)array;
	if (size) {
		if (array)
			Vector = (void **)array;
		else {
			Vector = new void *[size];
			IsAllocated = true;
		}
	}
}

class DynamicVectorDummy : public VectorClassDummy
{
public:
	DynamicVectorDummy(int size = 0, void *const *array = 0);
	int ActiveCount;
	int GrowthStep;
};

inline DynamicVectorDummy::DynamicVectorDummy(int size, void *const *array)
	: VectorClassDummy(size, array)
{
	GrowthStep = 10;
	ActiveCount = 0;
}

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/render2dsentence.h
class Render2DSentenceClass
{
public:
	// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/render2dsentence.h
	struct PendingSurfaceStruct : public W3DRadarResetSurface
	{
		PendingSurfaceStruct(void);
		DynamicVectorDummy Renderers;
	};
};

Render2DSentenceClass::PendingSurfaceStruct::PendingSurfaceStruct(void)
{
}
