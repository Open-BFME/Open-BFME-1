// cl: /DNDEBUG /MD /EHsc
// BFME-flavoured PendingSurfaceStruct assignment with the retail vector layout.

class SurfaceClass;

struct SurfaceOps
{
	void (__stdcall *unused)(SurfaceClass *surface);
	void (__stdcall *add_ref)(SurfaceClass *surface);
	void (__stdcall *release_ref)(SurfaceClass *surface);
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/surfaceclass.h
class SurfaceClass
{
public:
	SurfaceOps *ops;
};

// The Renderers base's assignment is the trivial 4-byte VectorClass<T>::operator=
// at 0x0093CEA0 (dup_0093cea0). PendingSurfaceStructResizeThunk.cpp reaches the
// same body from the vtable-proven VectorClass<PendingSurfaceStruct>::Resize
// (0x00940450) as VectorClassDummy::operator=, the name pinned at 0x0093CEA0, so
// the vector state and its assignment live in that base here too.
class VectorClassDummy
{
public:
	virtual ~VectorClassDummy(void);

	VectorClassDummy &operator=(const VectorClassDummy &that);

protected:
	void **vector;
	int vector_max;
	bool is_valid;
	bool is_allocated;
	bool pad[2];
};

class BfmeRendererVectorBase : public VectorClassDummy
{
public:
	virtual ~BfmeRendererVectorBase(void);
	virtual bool Equal(const BfmeRendererVectorBase &that) const;
	virtual bool Resize(int count, void *array = 0);
	virtual void Clear(void);
};

class BfmeRendererVector : public BfmeRendererVectorBase
{
public:
	BfmeRendererVector &operator=(const BfmeRendererVector &that)
	{
		BfmeRendererVectorBase::operator=(that);
		active_count = that.active_count;
		growth_step = that.growth_step;
		return *this;
	}

private:
	int active_count;
	int growth_step;
};

// Retail 0x0093E8E0 (71 bytes) has the shape of ZH's
// Render2DSentenceClass::PendingSurfaceStruct::operator= (upstream layout:
// inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/render2dsentence.h)
// over the BFME renderer vector, but the matched 47-byte
// PendingSurfaceStructAssignThunk.cpp row at 0x0036DAF0 already carries that
// name and nothing in retail calls this body, so it keeps an address-derived
// name instead of emitting a second definition of the same symbol.
struct Rva0093E8E0PendingSurface
{
	SurfaceClass *surface;
	BfmeRendererVector renderers;

	Rva0093E8E0PendingSurface &operator=(const Rva0093E8E0PendingSurface &that);
};

Rva0093E8E0PendingSurface &Rva0093E8E0PendingSurface::operator=(
	const Rva0093E8E0PendingSurface &that)
{
	SurfaceClass *incoming = that.surface;
	if (incoming != 0)
		incoming->ops->add_ref(incoming);

	SurfaceClass *outgoing = surface;
	if (outgoing != 0)
		outgoing->ops->release_ref(outgoing);

	surface = that.surface;
	renderers = that.renderers;
	return *this;
}
