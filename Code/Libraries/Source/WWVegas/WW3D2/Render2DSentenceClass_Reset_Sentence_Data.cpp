// cl: /DNDEBUG /MD /EHsc
// Clean BFME layout for Render2DSentenceClass::Reset_Sentence_Data.

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

struct SentenceDataStruct
{
	SurfaceClass *surface;
	unsigned char rectangles[0x20];
};

class SentenceDataVector
{
public:
	virtual ~SentenceDataVector(void);
	virtual bool Equal(const SentenceDataVector &that) const;
	virtual bool Resize(int size, const SentenceDataStruct *array = 0);
	virtual void Clear(void);

	int Count(void) const { return active_count; }
	SentenceDataStruct &operator[](int index) { return vector[index]; }
	SentenceDataStruct *Data(void) { return vector; }

	void Delete_All(void)
	{
		int len = vector_max;
		Clear();
		Resize(len);
	}

private:
	SentenceDataStruct *vector;
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
	void Reset_Sentence_Data(void);
	SentenceDataVector sentence_data;
};

// ?Reset_Sentence_Data@Render2DSentenceClass@@AAEXXZ
void Render2DSentenceClass::Reset_Sentence_Data(void)
{
	Render2DSentenceClass *owner = this;
	int index = 0;
	if (owner->sentence_data.Count() > 0) {
		int byte_offset = 0;
		do {
		SentenceDataStruct *entry = reinterpret_cast<SentenceDataStruct *>(
			reinterpret_cast<unsigned char *>(owner->sentence_data.Data()) +
			byte_offset);
		SurfaceClass *surface = entry->surface;
		if (surface != 0) {
			surface->ops->release_ref(surface);
			entry->surface = 0;
		}
		++index;
		byte_offset += sizeof(SentenceDataStruct);
		} while (index < owner->sentence_data.Count());
	}

	if (owner->sentence_data.Count() > 0)
		owner->sentence_data.Delete_All();
}
