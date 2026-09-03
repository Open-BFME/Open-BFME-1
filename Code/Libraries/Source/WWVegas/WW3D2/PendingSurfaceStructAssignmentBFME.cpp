// cl: /DNDEBUG /MD /EHsc
// BFME-flavoured PendingSurfaceStruct assignment with the retail vector layout.

class SurfaceClass;

struct SurfaceOps
{
	void (__stdcall *unused)(SurfaceClass *surface);
	void (__stdcall *add_ref)(SurfaceClass *surface);
	void (__stdcall *release_ref)(SurfaceClass *surface);
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/surfaceclass.h
class SurfaceClass
{
public:
	SurfaceOps *ops;
};

class BfmeRendererVectorBase
{
public:
	virtual ~BfmeRendererVectorBase(void);
	virtual bool Equal(const BfmeRendererVectorBase &that) const;
	virtual bool Resize(int count, void *array = 0);
	virtual void Clear(void);

	BfmeRendererVectorBase &operator=(const BfmeRendererVectorBase &that);

protected:
	void **vector;
	int vector_max;
	bool is_valid;
	bool is_allocated;
	bool pad[2];
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

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/render2dsentence.h
class Render2DSentenceClass
{
public:
	// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/render2dsentence.h
	struct PendingSurfaceStruct
	{
		SurfaceClass *surface;
		BfmeRendererVector renderers;

		PendingSurfaceStruct &operator=(const PendingSurfaceStruct &that);
	};
};

Render2DSentenceClass::PendingSurfaceStruct &
Render2DSentenceClass::PendingSurfaceStruct::operator=(
	const Render2DSentenceClass::PendingSurfaceStruct &that)
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
