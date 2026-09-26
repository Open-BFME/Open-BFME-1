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
//
// Honesty note on the two handle predicates: what is WITNESSED here is only
// that the retail body calls 0x0090C620 and 0x0090C630 with the handle in ecx
// (tools/callees.py 0x00937CC0 159). Both targets are 3-byte `xor al,al; ret`
// stubs, carried in the function ledger under their address-derived names
// ?m@Gen_0090c620@@QAE_NXZ / ?m@Gen_0090c630@@QAE_NXZ. The pre-existing
// targets/game/reverse/symbols.csv pins that spell them Is_Lightmap / Is_Procedural are
// POSITIONAL INFERENCE from the Zero Hour statistics.cpp shape (first call
// gates lightmap_texture_count, second gates procedural_texture_count) -- the
// bodies themselves prove nothing about the names. Those spellings are kept
// because renaming a pin is out of scope for this TU, not because the identity
// is proven; a caller that names either symbol would outrank the inference.

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
// Hour statistics.cpp does it (tss.tex=t; tss.usage_count=1; ...), and then
// handed to DynamicVectorClass::Add, which retail calls out of line at
// 0x00937810 (tools/callees.py 0x00937CC0 159).
//
// That container lives in TextureStatisticsVector.cpp, which owns the
// 0x00937810 row and explicitly instantiates
// DynamicVectorClass<TextureStatisticsStruct>::Add. The retail source includes
// the vector header in both places, and MSVC 7.1 needs Add's body in scope
// here to keep the referent in edi across the call and fold the freshly
// default-constructed handle's release check -- that is what reproduces
// retail's 159 bytes, so the body below cannot be dropped to a declaration.
//
// Because the body IS here, this TU implicitly instantiates the same
// ?Add@?$DynamicVectorClass@UTextureStatisticsStruct@@@@QAE_NABU1@@Z the
// owning TU instantiates explicitly, so the class declarations and the Add
// body below are copied from TextureStatisticsVector.cpp token for token --
// in particular the SIX virtuals in the sibling's order (dtor, operator==,
// Resize, Clear, ID, ID), which puts Resize in slot 2. An abbreviated
// two-virtual shim here would compile Add's `Resize(...)` against slot 1 and
// emit a two-entry vftable under the sibling's mangled name: two different
// definitions of one entity, with the linker free to keep either.
//
// Nothing below is a new identity: every member is declared or defined exactly
// as the owning TU declares or defines it.
struct TextureStatisticsStruct
{
	RefCountPtr<TextureClass> tex;
	int usage_count;
	int change_count;

	bool operator==(TextureStatisticsStruct const &other) const
	{
		return tex == other.tex;
	}
	bool operator!=(TextureStatisticsStruct const &other) const
	{
		return tex != other.tex;
	}
};

template<class T>
class VectorClass
{
public:
	VectorClass(unsigned size, T const *array);
	VectorClass(VectorClass const &);
	virtual ~VectorClass();
	VectorClass &operator=(VectorClass const &);
	virtual bool operator==(VectorClass const &) const;
	virtual bool Resize(int size, T const *array = 0);
	virtual void Clear();
	virtual int ID(T const *ptr);
	virtual int ID(T const &object);
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
	DynamicVectorClass(unsigned size = 0, T const *array = 0);
	virtual ~DynamicVectorClass();
	virtual bool Resize(int size, T const *array = 0);
	virtual void Clear();
	virtual int ID(T const *ptr);
	virtual int ID(T const &object);
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
