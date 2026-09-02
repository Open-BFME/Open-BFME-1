// cl: /DNDEBUG /MD /EHsc
// Clean BFME layout for Render2DSentenceClass::Release_Pending_Surfaces.

class SurfaceClass;

struct SurfaceOps
{
	void (__stdcall *unused)(SurfaceClass *surface);
	void (__stdcall *add_ref)(SurfaceClass *surface);
	void (__stdcall *release_ref)(SurfaceClass *surface);
};

class SurfaceClass
{
public:
	SurfaceOps *ops;
};

struct PendingSurfaceStruct
{
	SurfaceClass *surface;
	unsigned char renderers[0x18];
};

class PendingSurfaceVector
{
public:
	virtual ~PendingSurfaceVector(void);
	virtual bool Equal(const PendingSurfaceVector &that) const;
	virtual bool Resize(int size, const PendingSurfaceStruct *array = 0);
	virtual void Clear(void);

	int Count(void) const { return active_count; }
	PendingSurfaceStruct *Data(void) { return vector; }

	void Delete_All(void)
	{
		int len = vector_max;
		Clear();
		Resize(len);
	}

private:
	PendingSurfaceStruct *vector;
	int vector_max;
	bool is_valid;
	bool is_allocated;
	bool pad[2];
	int active_count;
	int growth_step;
};

class Render2DSentenceClass
{
public:
	virtual ~Render2DSentenceClass(void);

private:
	void Release_Pending_Surfaces(void);
	unsigned char sentence_data[0x18];
	PendingSurfaceVector pending_surfaces;
};

// ?Release_Pending_Surfaces@Render2DSentenceClass@@AAEXXZ
void Render2DSentenceClass::Release_Pending_Surfaces(void)
{
	Render2DSentenceClass *owner = this;
	int index = 0;
	if (owner->pending_surfaces.Count() > 0) {
		int byte_offset = 0;
		do {
			PendingSurfaceStruct *entry =
				reinterpret_cast<PendingSurfaceStruct *>(
					reinterpret_cast<unsigned char *>(
						owner->pending_surfaces.Data()) + byte_offset);
			SurfaceClass *surface = entry->surface;
			if (surface != 0) {
				surface->ops->release_ref(surface);
				entry->surface = 0;
			}
			++index;
			byte_offset += sizeof(PendingSurfaceStruct);
		} while (index < owner->pending_surfaces.Count());
	}

	if (owner->pending_surfaces.Count() > 0)
		owner->pending_surfaces.Delete_All();
}
