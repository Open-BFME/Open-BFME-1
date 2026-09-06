// cl: /DNDEBUG /MD /EHsc
// Open-BFME: MeshClass's base (in-place) destructor at retail 0x0092D990.
// Retail body releases the Model ref (guarded decrement + virtual Delete_This,
// unconditional clear), then destroys an embedded member at this+0xD0 whose
// destructor is pinned as ??1Gen_uw_0094a880@@QAE@XZ, then chains to the
// RenderObjClass base destructor. Base/vtable shape copied verbatim from the
// already-landed RenderObjClass destructor (RenderObjClassDestructorThunk.cpp)
// so MSVC re-derives the same two vtable stores (primary 0x113C390 at offset0,
// secondary MultiListObjectClass vptr 0x113C388 at offset+8).

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib/refcount.h
class RefCountClass
{
public:
	virtual void Delete_This(void);

	void Release_Ref(void)
	{
		if (--m_numRefs == 0) {
			Delete_This();
		}
	}

	int m_numRefs;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad/persist.h
class PersistClass
{
public:
	virtual ~PersistClass() {}

private:
	int m_04;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib/multilist.h
class MultiListObjectClass
{
public:
	virtual ~MultiListObjectClass();

private:
	void *m_prev;
	void *m_next;
};

class RenderObjClass : public PersistClass, public MultiListObjectClass
{
public:
	virtual ~RenderObjClass();

private:
	unsigned char m_gap[0x88];
	RefCountClass *m_container;
};

// ??1Gen_uw_0094a880@@QAE@XZ -- embedded member destructor, identity not recovered
class Gen_uw_0094a880
{
public:
	~Gen_uw_0094a880();
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/mesh.h
class MeshClass : public RenderObjClass
{
public:
	virtual ~MeshClass();

private:
	unsigned char m_gap2[0x28];    // RenderObjClass ends at 0xA0; MeshClass-only fields to +0xC8
	RefCountClass *Model;          // this+0xC8
	unsigned char m_gap3[4];       // this+0xCC
	Gen_uw_0094a880 m_extra;       // this+0xD0
};

// ??1MeshClass@@UAE@XZ
MeshClass::~MeshClass()
{
	if (Model) {
		Model->Release_Ref();
		Model = 0;
	}
}
