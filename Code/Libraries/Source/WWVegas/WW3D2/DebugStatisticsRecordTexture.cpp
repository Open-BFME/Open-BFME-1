// cl: /DNDEBUG /EHsc
// Open-BFME7: WW3D2 statistics.cpp texture recording cluster from dump
// d_00930e00.asm: Debug_Statistics::Record_Texture (0x00937D60, 335 B) and the
// two file-static helpers it is the only caller of, Find_Record_Texture
// (0x00937320, 85 B, argument in ebx) and Add_Record_Texture (0x00937CC0,
// 159 B, argument in esi). The helpers carry MSVC's private register
// conventions, so they must be compiled in the same TU as their caller.
//
// BFME differences from the ZH source: textures travel as a ref-counted
// handle (RefCountPtr<TextureClass>, the same 4-byte wrapper
// TextureStatisticsVector.cpp uses for TextureStatisticsStruct::tex), the
// handle itself answers Is_Lightmap/Is_Procedural/Get_Texture_Memory_Usage,
// latest_texture is such a handle, and the RECORD_TEXTURE_NONE path clears it
// instead of copying t. The statics live in this TU's .data in the retail
// order (texture_change_count 0x01346DF8 ... texture_statistics 0x01346E78).

class TextureBaseClass
{
public:
	void Add_Ref();
	void Release_Ref();
};

class TextureClass : public TextureBaseClass
{
};

inline void TextureBaseClass::Add_Ref()
{
	++*reinterpret_cast<unsigned short *>(reinterpret_cast<char *>(this) + 4);
}

template<class T>
class RefCountPtr
{
public:
	RefCountPtr() : Referent(0) {}
	RefCountPtr(T *referent) : Referent(referent)
	{
		if (Referent != 0)
			Referent->Add_Ref();
	}
	RefCountPtr(RefCountPtr const &other)
	{
		if (other.Referent != 0)
			other.Referent->Add_Ref();
		Referent = other.Referent;
	}
	~RefCountPtr()
	{
		if (Referent != 0)
		{
			Referent->Release_Ref();
			Referent = 0;
		}
	}
	RefCountPtr const &operator=(RefCountPtr const &other)
	{
		if (other.Referent != 0)
			other.Referent->Add_Ref();
		if (Referent != 0)
			Referent->Release_Ref();
		Referent = other.Referent;
		return *this;
	}
	bool operator==(RefCountPtr const &other) const { return Referent == other.Referent; }
	bool operator!=(RefCountPtr const &other) const { return Referent != other.Referent; }
	T *Peek() const { return Referent; }

	// BFME handle queries, answered by the handle itself (this = the handle).
	bool Is_Lightmap() const;
	bool Is_Procedural() const;
	unsigned Get_Texture_Memory_Usage() const;
private:
	T *Referent;
};

// The record is default-constructed and then assigned, exactly as the Zero
// Hour statistics.cpp does it (tss.tex=t; tss.usage_count=1; ...).  The
// DynamicVectorClass template body is visible here because the retail source
// includes the vector header: with Add's body in scope MSVC 7.1 keeps the
// referent in edi across the call and folds the freshly default-constructed
// handle's release check, which is what reproduces retail's 159 bytes.
struct TextureStatisticsStruct
{
	RefCountPtr<TextureClass> tex;
	int usage_count;
	int change_count;
};

template<class T>
class VectorClass
{
public:
	virtual ~VectorClass();
	virtual bool Resize(int size, T const *array = 0);
	int Length() const { return VectorMax; }
	T &operator[](int index) { return Vector[index]; }
protected:
	T *Vector;
	int VectorMax;
	bool IsValid;
	bool IsAllocated;
	bool VectorClassPad[2];
};

template<class T>
class DynamicVectorClass : public VectorClass<T>
{
public:
	virtual bool Resize(int size, T const *array = 0);
	bool Add(T const &object);
protected:
	int ActiveCount;
	int GrowthStep;
};

template<class T>
bool DynamicVectorClass<T>::Add(T const &object)
{
	if (ActiveCount >= this->Length())
	{
		if ((this->IsAllocated || !this->VectorMax) && GrowthStep > 0)
		{
			if (!Resize(this->Length() + GrowthStep))
				return false;
		}
		else
		{
			return false;
		}
	}
	(*this)[ActiveCount++] = object;
	return true;
}

class Debug_Statistics
{
public:
	enum RecordTextureMode
	{
		RECORD_TEXTURE_NONE,
		RECORD_TEXTURE_SIMPLE,
		RECORD_TEXTURE_DETAILS
	};
	static void Record_Texture(RefCountPtr<TextureClass> const &t);
};

static int procedural_texture_memory;
static int texture_change_count;
static int lightmap_texture_memory;
static int record_count;
static int texture_count;
static int texture_memory;
static int lightmap_texture_count;
static Debug_Statistics::RecordTextureMode record_texture_mode;
static int procedural_texture_count;
static RefCountPtr<TextureClass> latest_texture;
static DynamicVectorClass<TextureStatisticsStruct> texture_statistics;

static bool Find_Record_Texture(RefCountPtr<TextureClass> const &t)
{
	for (int i = 0; i < texture_count; ++i)
	{
		if (texture_statistics[i].tex == t)
		{
			if (record_texture_mode == Debug_Statistics::RECORD_TEXTURE_DETAILS)
			{
				texture_statistics[i].usage_count++;
				if (t != latest_texture)
					texture_statistics[i].change_count++;
			}
			return true;
		}
	}
	return false;
}

static void Add_Record_Texture(RefCountPtr<TextureClass> const &t)
{
	TextureStatisticsStruct s;
	s.tex = t;
	s.usage_count = 1;
	s.change_count = 1;
	texture_statistics.Add(s);
	texture_count++;
	if (t.Is_Lightmap()) lightmap_texture_count++;
	if (t.Is_Procedural()) procedural_texture_count++;
}

void Debug_Statistics::Record_Texture(RefCountPtr<TextureClass> const &t)
{
	record_count++;
	if (t != latest_texture)
	{
		texture_change_count++;
	}

	if (record_texture_mode == RECORD_TEXTURE_NONE)
	{
		latest_texture = 0;
		return;
	}
	if (t.Peek() == 0)
	{
		latest_texture = t;
		return;
	}

	if (Find_Record_Texture(t))
	{
		latest_texture = t;
		return;
	}
	Add_Record_Texture(t);

	texture_memory += t.Get_Texture_Memory_Usage();
	latest_texture = t;
	if (t.Is_Lightmap()) lightmap_texture_memory += t.Get_Texture_Memory_Usage();
	if (t.Is_Procedural()) procedural_texture_memory += t.Get_Texture_Memory_Usage();
}
