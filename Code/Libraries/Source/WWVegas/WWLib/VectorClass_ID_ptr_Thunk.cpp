// cl: /DNDEBUG /MD /EHsc

// Slot 5 of VectorClass<RenderDeviceDescClass>'s vtable, after the ID overload
// taking a const reference at slot 4. This is the pointer overload: it checks
// IsValid at +0x0C, then divides the byte distance from Vector at +0x04 by the
// element size.
//
// That element size is not a guess. The divide is the usual reciprocal
// multiply -- magic 0xB30F6353, take the high dword, shift right by 10 -- and
// 1464 is the only divisor for which that sequence reproduces integer division
// exactly, so sizeof(RenderDeviceDescClass) is 1464.
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/rddesc.h
class RenderDeviceDescClass
{
	unsigned char m_body[1464];
};

template <class T>
class VectorClass
{
public:
	virtual ~VectorClass(void);
	virtual bool operator==(const VectorClass<T> &that) const;
	virtual bool Resize(int newsize, const T *array = 0);
	virtual void Clear(void);
	virtual int ID(const T &object);
	virtual int ID(const T *ptr);

	T *Vector;
	int VectorMax;
	bool IsValid;
	bool IsAllocated;
};

// ?ID@?$VectorClass@VRenderDeviceDescClass@@@@UAEHPBVRenderDeviceDescClass@@@Z
template <class T>
int VectorClass<T>::ID(const T *ptr)
{
	if (!IsValid)
		return 0;
	return ((unsigned long)ptr - (unsigned long)Vector) / sizeof(T);
}

template int VectorClass<RenderDeviceDescClass>::ID(const RenderDeviceDescClass *);
