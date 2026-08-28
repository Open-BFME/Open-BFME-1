// cl: /DNDEBUG /MD /EHsc
// VectorClass<ProxyClass>::Clear, retail 0x00934780 -- the COMDAT immediately
// after ?Resize@?$VectorClass@VProxyClass@@@@UAE_NHPBVProxyClass@@@Z, which
// occupies 0x00934630..0x00934773.
//
// This body was previously landed as
// ?Clear@?$VectorClass@UFileInfoStruct@MixFileCreator@@@@UAEXXZ, on the
// strength of it matching ZH's VectorClass<T>::Clear with an 0x74-byte
// element. It is the same instantiation as the Resize above it:
//
//   - both hand the element destructor 0x0041AAD2 to ??_M, and 0x74 as the
//     element size (Resize at 0x0093469C and 0x00934722, Clear at 0x00934799);
//   - MixFileCreator::FileInfoStruct is 0x10 bytes, not 0x74 -- its own vector
//     deleting destructor ??_EFileInfoStruct@MixFileCreator@@QAEPAXI@Z at
//     0x003D5710 pushes 0x10 as the element size and 0x00436AB1 as the
//     destructor, and 0x00436AB1 and 0x0041AAD2 are different ILT thunks
//     reaching different bodies (0x003F6EA0 and 0x0005DBE0).
//
// So the 0x74 here is not evidence that BFME's StringClass grew to 104 bytes;
// it is ProxyClass, whose 0x40 bytes past ZH's StringClass + Matrix3D are
// unreconstructed exactly as the Resize TU next door already records. The
// replica below is that TU's, unchanged, so both rows resolve
// ??1ProxyClass@@QAE@XZ to the same 0x0041AAD2.
//
// VectorClass's layout is ZH's: the retail bytes read Vector at +0x04,
// VectorMax at +0x08 and IsAllocated at +0x0d.

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib/wwstring.h
class StringClass
{
public:
	StringClass() : m_Buffer(0) {}
	~StringClass() {}
	char *m_Buffer;
};

class Matrix3D
{
public:
	float Row[3][4];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/proxy.h
class ProxyClass
{
public:
	ProxyClass(void) {}
	~ProxyClass();									///< out of line: retail 0x0041AAD2

	StringClass	Name;
	Matrix3D	Transform;

	// BFME's build carries trailing bytes ZH's proxy.h does not declare;
	// only their size matters here, and it is what makes sizeof 0x74.
	unsigned char m_unreconstructed_tail[0x74 - 0x34];
};

template<class T>
class VectorClass
{
public:
	virtual void Clear(void);

protected:
	T *Vector;										///< retail this+0x04
	int VectorMax;									///< retail this+0x08
	bool IsValid;									///< retail this+0x0c
	bool IsAllocated;								///< retail this+0x0d
};

// ?Clear@?$VectorClass@VProxyClass@@@@UAEXXZ
template<class T>
void VectorClass<T>::Clear(void)
{
	if (Vector && IsAllocated) {
		delete[] Vector;
		Vector = 0;
	}
	IsAllocated = false;
	VectorMax = 0;
}

template class VectorClass<ProxyClass>;
