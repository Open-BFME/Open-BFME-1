// cl: /DNDEBUG /MD /EHs-c-
// DynamicVectorClass::Add of an 8-byte record whose second word is a COM
// pointer (AddRef slot 1, Release slot 2).

struct SurfaceOps
{
	void (__stdcall *unused)(void *surface);
	void (__stdcall *add_ref)(void *surface);
	void (__stdcall *release)(void *surface);
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/surfaceclass.h
class SurfaceClass
{
public:
	SurfaceOps *ops;
};

struct Gen_0093E730_Elem
{
	void *first;
	SurfaceClass *surface;
};

class Gen_0093E730
{
public:
	virtual bool Equal(const Gen_0093E730 &that) const;
	virtual bool Unused(void);
	virtual bool Resize(int count, const Gen_0093E730_Elem *array);
	bool Add(const Gen_0093E730_Elem &object);

private:
	Gen_0093E730_Elem *vector;
	int vector_max;
	bool is_valid;
	bool is_allocated;
	bool pad[2];
	int active_count;
	int growth_step;
};

bool Gen_0093E730::Add(const Gen_0093E730_Elem &object)
{
	if (active_count >= vector_max) {
		if ((is_allocated || !vector_max) && growth_step > 0) {
			if (!Resize(vector_max + growth_step, 0))
				return false;
		} else {
			return false;
		}
	}

	int index = active_count;
	active_count = index + 1;
	Gen_0093E730_Elem *slot = &vector[index];
	slot->first = object.first;
	SurfaceClass *incoming = object.surface;
	if (incoming)
		incoming->ops->add_ref(incoming);
	SurfaceClass *outgoing = slot->surface;
	if (outgoing)
		outgoing->ops->release(outgoing);
	slot->surface = object.surface;
	return true;
}
