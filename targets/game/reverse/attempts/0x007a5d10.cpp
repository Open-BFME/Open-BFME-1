// ?d_007a5d10@@YAXXZ
// partial score=0.68 date=2026-09-27
// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Igame/GameEngine/Source/Common/System /Igame/GameEngine/Include /Igame/GameEngine/Include/Precompiled /Igame/Libraries/Source/WWVegas/WWLib
// stlport

// Constructor 0x007A46E0 installs the vtable at 0x01128148. The scalar
// deleting destructor at 0x007A60F0 calls this complete destructor through
// ILT 0x00032DCB.

#include <list>
#include "ascii_string.h"

void W3DRadarResetLock(void);
char bfmeUnlock1179(void);

class BfmeBaseVUQ
{
public:
	virtual ~BfmeBaseVUQ(void) { }
};

class RefCountClass
{
public:
	virtual void Delete_This(void);
	int NumRefs;
};

class MultiListObjectClass
{
public:
	virtual ~MultiListObjectClass(void);
	void *ListNode;
};

class RenderObjClass : public RefCountClass, public MultiListObjectClass
{
public:
	virtual ~RenderObjClass(void);
	char m_pad[0xb8];
};

class WaterRefCount
{
public:
	virtual void Delete_This(void);
	int NumRefs;
};

class BfmeHandleCX
{
public:
	~BfmeHandleCX(void);

private:
	void *m_handle;
};

class TextureClass
{
public:
	void Release_Ref(void);
};

class WaterTracksRenderSystem
{
public:
	~WaterTracksRenderSystem(void);
};

class WaterDestructorGuard
{
public:
	~WaterDestructorGuard(void)
	{
		bfmeUnlock1179();
	}
};

class BfmeGlobal012F18F0
{
public:
	virtual void deleteInstance(int destroy);
};

extern BfmeGlobal012F18F0 *g_bfmeGlobal012F18F0;

class Rva0079EFD0WaterAssetCleanup
{
public:
	void release(void);
};

#pragma comment(linker, "/alternatename:?release@Rva0079EFD0WaterAssetCleanup@@QAEXXZ=??1WaterRenderObjClass@@QAE@XZ")

class BfmeItemVOL
{
public:
	virtual void bfmeDropVOL(int destroy);
};

struct Rva00EF1408Node
{
	Rva00EF1408Node *next;
	AsciiString key;
	BfmeItemVOL *item;
};

struct ListSlot4
{
	void *value;
};

class WaterRenderObjClass : public BfmeBaseVUQ, public RenderObjClass
{
public:
	struct Setting
	{
		class TextureRef
		{
		public:
			~TextureRef(void);

		private:
			TextureClass *m_texture;
		};

		~Setting(void);
		TextureRef skyTexture;
		TextureRef waterTexture;
		char m_pad[0x28];
	};

	virtual ~WaterRenderObjClass(void);
	void updateMapOverrides(void);

	char m_beforeD8[0xd8 - 0xcc];
	WaterRefCount *m_d8;
	WaterRefCount *m_dc;
	WaterRefCount *m_e0;
	BfmeHandleCX m_e4Handle;
	char m_before24C[0x24c - 0xe8];
	BfmeHandleCX m_reflectionHandle;
	WaterRefCount *m_250;
	WaterTracksRenderSystem *m_waterTrackSystem;
	char *m_meshData;
	int m_meshDataSize;
	char m_before2A8[0x2a8 - 0x260];
	BfmeHandleCX m_2a8Handle;
	_STL::list<ListSlot4> m_at2ac;
	char m_before2C8[0x2c8 - 0x2b0];
	AsciiString m_sky;
	AsciiString m_names[5];
	Setting m_settings[6];
	int m_400;
	char m_tail[0x11c];
};

static void releaseWaterRef(WaterRefCount *&object)
{
	if (object != 0) {
		--object->NumRefs;
		if (object->NumRefs == 0)
			object->Delete_This();
		object = 0;
	}
}

WaterRenderObjClass::~WaterRenderObjClass(void)
{
	W3DRadarResetLock();
	WaterDestructorGuard guard;

	releaseWaterRef(m_dc);
	releaseWaterRef(m_d8);
	releaseWaterRef(m_e0);
	releaseWaterRef(m_250);

	delete[] m_meshData;
	m_meshData = 0;
	m_meshDataSize = 0;

	char *settingStrings = (char *)0x012F1610;
	char *settingStringsEnd = (char *)0x012F18F8;
	do {
		((AsciiString *)(settingStrings - 4))->clear();
		((AsciiString *)settingStrings)->clear();
		settingStrings += 0x7c;
	} while (settingStrings < settingStringsEnd);

	if (g_bfmeGlobal012F18F0 != 0)
		g_bfmeGlobal012F18F0->deleteInstance(1);
	g_bfmeGlobal012F18F0 = 0;

	((Rva0079EFD0WaterAssetCleanup *)this)->release();

	Rva00EF1408Node ***beginAddress = (Rva00EF1408Node ***)0x012F1408;
	Rva00EF1408Node ***endAddress = (Rva00EF1408Node ***)0x012F140C;
	Rva00EF1408Node **begin = *beginAddress;
	Rva00EF1408Node **end = *endAddress;
	int count = ((char *)end - (char *)begin) >> 2;
	int index = 0;
	while (count > 0 && index < count) {
		Rva00EF1408Node *node = begin[index];
		if (node == 0) {
			++index;
			continue;
		}

		for (;;) {
			if (node->item != 0)
				node->item->bfmeDropVOL(1);

			begin = *beginAddress;
			end = *endAddress;
			Rva00EF1408Node *next = node->next;
			if (next != 0) {
				node = next;
				continue;
			}

			int oldCount = ((char *)end - (char *)begin) >> 2;
			unsigned int hash = 0;
			{
				AsciiString key(node->key);
				const char *text = key.str();
				if (text == 0)
					text = (const char *)0x0107388b;
				while (*text != 0) {
					hash = hash * 5 + (signed char)*text;
					++text;
				}
			}

			unsigned int slot = hash % oldCount + 1;
			begin = *beginAddress;
			end = *endAddress;
			int newCount = ((char *)end - (char *)begin) >> 2;
			while (slot < (unsigned int)newCount && begin[slot] == 0)
				++slot;
			if (slot >= (unsigned int)newCount)
				break;
			node = begin[slot];
		}
	}

	if (m_waterTrackSystem != 0)
		delete m_waterTrackSystem;
	updateMapOverrides();
}
