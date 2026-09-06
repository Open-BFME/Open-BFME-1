// cl: /DNDEBUG /MD /EHsc
// Open-BFME: MeshGeometryClass's base (in-place) destructor at retail 0x00927880.
// Retail body: Reset_Geometry(0,0), then the implicit base-destructor chain in
// reverse declaration order -- MultiListObjectClass (out-of-line call, "this"
// adjusted to the +8 subobject), then RefCountClass (trivial, inlined, which
// is why its own vtable identity re-stamp appears without a separate call).
// W3DMPO is empty and contributes nothing.

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib/refcount.h
class RefCountClass
{
public:
	virtual void Delete_This(void) { delete this; }
protected:
	virtual ~RefCountClass(void) {}
private:
	int NumRefs;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib/multilist.h
class MultiListObjectClass
{
public:
	virtual ~MultiListObjectClass();
private:
	void *ListNode;
};

class W3DMPO
{
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/meshgeometry.h
class MeshGeometryClass : public W3DMPO, public RefCountClass, public MultiListObjectClass
{
public:
	virtual ~MeshGeometryClass();

	void Reset_Geometry(int polycount, int vertcount, bool keepAlloc = true);
};

// ??1MeshGeometryClass@@UAE@XZ
MeshGeometryClass::~MeshGeometryClass()
{
	Reset_Geometry(0, 0, true);
}
