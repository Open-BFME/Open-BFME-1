// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
//
// Retail 0x0091F5B0, 384 bytes. ZH Allocate_DX8_Dynamic_Buffer, with BFME's
// per-FVF slot arrays: in-use / buffer / offset / size indexed by the FVF
// member at +0x08. The matched constructor at 0x0091F730 calls this when
// Type == BUFFER_TYPE_DYNAMIC_DX8 (2). After the buffer exists it writes
// (Start != 0) to the extra BFME byte at VertexBuffer+0x18.

class W3DMPO
{
};

class RefCountClass
{
public:
	RefCountClass() : NumRefs(1) {}

	void Add_Ref() const
	{
		++NumRefs;
	}

	void Release_Ref() const
	{
		--NumRefs;
		if (NumRefs == 0) {
			const_cast<RefCountClass *>(this)->Delete_This();
		}
	}

	virtual void Delete_This();

protected:
	virtual ~RefCountClass();

private:
	mutable int NumRefs;
};

class VertexBufferClass : public W3DMPO, public RefCountClass
{
protected:
	virtual ~VertexBufferClass();

	int engine_refs;
	unsigned short vertex_count;
	unsigned type;
	void *fvf_info;

public:
	bool bfme_field18;
};

class DX8VertexBufferClass : public VertexBufferClass
{
public:
	enum UsageType {
		USAGE_DEFAULT = 0,
		USAGE_DYNAMIC = 1,
		USAGE_SOFTWAREPROCESSING = 2,
		USAGE_NPATCHES = 4
	};

	DX8VertexBufferClass(unsigned FVF, unsigned short vertex_count, UsageType usage, unsigned vertex_size);

protected:
	void *dx8_buffer;
};

class BoxDynamicVBAccessClass
{
public:
	void Allocate_DX8_Dynamic_Buffer();

private:
	const void *FVFInfo;
	unsigned Type;
	unsigned FVF;
	unsigned Start;
	unsigned short VertexCount;
	unsigned short VertexBufferOffset;
	VertexBufferClass *VertexBuffer;
};

#define DEFAULT_VB_SIZE 5000
#define BFME_DYNAMIC_SLOTS 16

static bool _DynamicDX8VertexBufferInUse[BFME_DYNAMIC_SLOTS];
static DX8VertexBufferClass *_DynamicDX8VertexBuffer[BFME_DYNAMIC_SLOTS];
static unsigned short _DynamicDX8VertexBufferOffset[BFME_DYNAMIC_SLOTS];
static unsigned short _DynamicDX8VertexBufferSize[BFME_DYNAMIC_SLOTS];
static unsigned _DynamicFVFTable[BFME_DYNAMIC_SLOTS];
extern unsigned char *TheDX8Caps;

#define REF_PTR_RELEASE(x) { if (x) { x->Release_Ref(); x = 0; } }
#define REF_PTR_SET(dst, src) { if (src) (src)->Add_Ref(); if (dst) (dst)->Release_Ref(); (dst) = (src); }

void BoxDynamicVBAccessClass::Allocate_DX8_Dynamic_Buffer()
{
	_DynamicDX8VertexBufferInUse[FVF] = true;

	if (VertexCount > _DynamicDX8VertexBufferSize[FVF]) {
		REF_PTR_RELEASE(_DynamicDX8VertexBuffer[FVF]);
		_DynamicDX8VertexBufferSize[FVF] = VertexCount;
		if (_DynamicDX8VertexBufferSize[FVF] < DEFAULT_VB_SIZE) {
			_DynamicDX8VertexBufferSize[FVF] = DEFAULT_VB_SIZE;
		}
	}

	if (!_DynamicDX8VertexBuffer[FVF]) {
		unsigned usage = DX8VertexBufferClass::USAGE_DYNAMIC;
		if (TheDX8Caps[0x13b]) {
			usage |= DX8VertexBufferClass::USAGE_NPATCHES;
		}
		_DynamicDX8VertexBuffer[FVF] = ::new DX8VertexBufferClass(
			_DynamicFVFTable[FVF],
			_DynamicDX8VertexBufferSize[FVF],
			(DX8VertexBufferClass::UsageType)usage,
			0);
		_DynamicDX8VertexBufferOffset[FVF] = 0;
	}

	_DynamicDX8VertexBuffer[FVF]->bfme_field18 = (Start != 0);

	if ((unsigned)VertexCount + _DynamicDX8VertexBufferOffset[FVF]
			> _DynamicDX8VertexBufferSize[FVF]) {
		_DynamicDX8VertexBufferOffset[FVF] = 0;
	}

	REF_PTR_SET(VertexBuffer, _DynamicDX8VertexBuffer[FVF]);
	VertexBufferOffset = _DynamicDX8VertexBufferOffset[FVF];
}
