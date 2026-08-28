// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHs-c-
// Lift the DynamicVectorClass<VehicleCurveClass::_ArcInfoStruct>::Add raw
// machine-code dump to clean C++ (packet 009347c0).
//
// Retail folded the general DynamicVectorClass<T>::Add<T> body (WWLib
// vector.h) onto this address for a T of size 0x74 (116) bytes. This repo's
// own Code/Libraries/.../vehiclecurve.h defines _ArcInfoStruct as only 0x34
// (52) bytes (3 Vector3 + 4 floats), and that 52-byte version is already the
// correct source for the OTHER matched rows on this class (constructor,
// assignment, comparator, Clear, Delete_All, ID -- all matched against their
// own retail addresses using the 52-byte layout). So this is a *second*,
// larger copy of the same nested-struct name compiled elsewhere in BFME's
// tree with extra trailing members ZH's vehiclecurve.h does not carry -- the
// mangled name ??4_ArcInfoStruct@VehicleCurveClass@@... is identical either
// way since C++ name mangling does not encode member layout, only the
// identifier. Rather than touching the shared vehiclecurve.h (which the other
// matched rows on that class depend on), this is an isolated local replica
// carrying the extra 0x40 bytes as unreconstructed padding, so the pointer
// arithmetic (stride 0x74) and the out-of-line call to the *pinned* second
// copy of the assignment operator (0x00933C60, additive pin alongside its
// existing 0x006098D0 row) both land correctly.
//
// Retail pins the layout: Vector at this+0x04, VectorMax at this+0x08,
// IsValid/IsAllocated at this+0x0C/0x0D, ActiveCount at this+0x10,
// GrowthStep at this+0x14 -- the standard VectorClass/DynamicVectorClass
// layout from WWLib's vector.h, unchanged here.

class Vector3
{
public:
	float X;
	float Y;
	float Z;

	Vector3 &operator=(const Vector3 &v) { X = v.X; Y = v.Y; Z = v.Z; return *this; }
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath/vehiclecurve.h
class VehicleCurveClass
{
public:
	typedef struct _ArcInfoStruct
	{
		Vector3	center;
		Vector3	point_in;
		Vector3	point_out;
		float		point_angle;
		float		radius;
		float		angle_in_delta;
		float		angle_out_delta;

		// BFME's build of this struct carries additional trailing bytes that
		// ZH's vehiclecurve.h does not declare -- unreconstructed, only their
		// combined size (making sizeof(_ArcInfoStruct) == 0x74) matters here.
		unsigned char m_unreconstructed_tail[0x74 - 0x34];

	} ArcInfoStruct;
};

template <class T> class VectorClass
{
public:
	virtual ~VectorClass(void);								///< vtable +0x00
	virtual bool operator==(const VectorClass<T> &) const;	///< vtable +0x04
	virtual bool Resize(int newsize, T const *array = 0);		///< vtable +0x08
	virtual void Clear(void);									///< vtable +0x0C
	virtual int ID(T const *ptr);								///< vtable +0x10
	virtual int ID(T const &ptr);								///< vtable +0x14

	T &operator[](int index) { return Vector[index]; }

protected:
	T *Vector;						///< retail this+0x04
	int VectorMax;					///< retail this+0x08
	bool IsValid;					///< retail this+0x0C
	bool IsAllocated;				///< retail this+0x0D
	bool VectorClassPad[2];
};

template <class T> class DynamicVectorClass : public VectorClass<T>
{
public:
	int Length(void) const { return this->VectorMax; }

	// ?Add@?$DynamicVectorClass@U_ArcInfoStruct@VehicleCurveClass@@@@QAE_NABU_ArcInfoStruct@VehicleCurveClass@@@Z
	bool Add(T const &object)
	{
		if (ActiveCount >= Length()) {
			if ((this->IsAllocated || !this->VectorMax) && GrowthStep > 0) {
				if (!this->Resize(Length() + GrowthStep)) {
					return false;
				}
			} else {
				return false;
			}
		}

		(*this)[ActiveCount++] = object;
		return true;
	}

protected:
	int ActiveCount;				///< retail this+0x10
	int GrowthStep;					///< retail this+0x14
};

// Force emission of the Add instantiation even though nothing else in this
// isolated TU calls it.
template bool DynamicVectorClass<VehicleCurveClass::_ArcInfoStruct>::Add(VehicleCurveClass::_ArcInfoStruct const &);
