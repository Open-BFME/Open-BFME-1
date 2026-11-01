// BFME ThingTemplate asset collection, retail RVA 0x00143580.
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport

#include <set>
#include <vector>

template <typename T>
class StringBase
{
public:
	StringBase() {}
	StringBase(const StringBase<T> &other);

	char *m_data;
private:
	void releaseBuffer(void);
	friend class AsciiString;
};

class AsciiString : private StringBase<char>
{
public:
	AsciiString(const AsciiString &other)
	{
		((StringBase<char> *)this)->StringBase<char>::StringBase(
			*(const StringBase<char> *)&other);
	}
	~AsciiString() { ((StringBase<char> *)this)->releaseBuffer(); }

	bool isNotEmpty() const
	{
		return m_data != 0 && *(const unsigned short *)(m_data + 4) != 0;
	}
};

struct Rva001408C0Target;

typedef Rva001408C0Target *Rva001408C0Key;
typedef _STL::set<Rva001408C0Key, _STL::less<Rva001408C0Key>,
	_STL::allocator<Rva001408C0Key> > Rva001408C0Set;

class AssetList
{
public:
	AssetList &operator<<(const AsciiString &name);
	AssetList &operator<<(const AssetList &other)
	{
		m_prototypes.insert(other.m_prototypes.begin(),
			other.m_prototypes.end());
		m_changed = true;
		return *this;
	}
	bool empty() const { return m_prototypes.empty(); }

private:
	Rva001408C0Set m_prototypes;
	unsigned int m_treeLayoutPad;
	bool m_changed;
};

AsciiString operator+(AsciiString left, const char *right);

class Gen_001D5EE0Target
{
public:
	void bfmeForward(void *first, void *second);
};

class BfmeObj412
{
public:
	void call(void *first, void *second);
};

class CommandSet : public BfmeObj412
{
};

class ControlBar
{
public:
	const CommandSet *findCommandSet(const AsciiString &name);
};

extern ControlBar *TheControlBar;

struct BfmeWritableGlobalData
{
	char m_padding[0x11fc];
	unsigned char m_flag;
};

class GlobalData;
extern GlobalData *TheWritableGlobalData;
#define TheWritableGlobalData ((BfmeWritableGlobalData *)TheWritableGlobalData)

struct BfmeModuleInfo
{
	void *m_begin;
	void *m_end;
	void *m_capacity;
};

typedef void (__cdecl *BfmeModuleAssetListFunction)(
	BfmeModuleInfo *, int, AssetList *, void *);

extern void j_0001d881();

struct BfmeAssetBlock
{
	char m_padding[8];
	Gen_001D5EE0Target *m_targets[4];
	char m_remaining[0xd4];
};

struct BfmeAssetBlockVector
{
	BfmeAssetBlock *m_begin;
	BfmeAssetBlock *m_end;
	BfmeAssetBlock *m_capacity;
};

class ThingTemplate;

class ThingFactory
{
public:
	ThingTemplate *findTemplate(const AsciiString &name);
};

extern ThingFactory *TheThingFactory;

class ThingTemplate
{
public:
	// Retail reaches this collector through ILT 0x00004B92; the thunk table
	// contradicts every GetAssetList decoration tried at that slot, so the
	// body keeps its address (identity_evidence/00143580-ilt-contradiction.md).
	void rva00143580(AssetList &assets, void *context) const;
	void rva00144DC0(AssetList &assets, void *context);

private:
	char m_padding00[0x2c];
	AsciiString m_commandSetString;
	char m_padding30[0x1c];
	AsciiString m_shadowTextureName;
	char m_padding50[0x244];
	BfmeModuleInfo m_behaviorModuleInfo;
	BfmeModuleInfo m_drawModuleInfo;
	BfmeModuleInfo m_clientUpdateModuleInfo;
	BfmeModuleInfo m_clientBehaviorModuleInfo;
	char m_padding2c4[0xc];
	_STL::vector<AsciiString> m_buildVariations;
	char m_padding2dc[0x1c];
	BfmeAssetBlockVector m_assetBlocks;
	char m_padding304[0x60];
	AssetList m_assetCache[2];
};

// ?rva00143580@ThingTemplate@@QBEXAAVAssetList@@PAX@Z
void ThingTemplate::rva00143580(AssetList &assets, void *context) const
{
	BfmeModuleAssetListFunction collectModuleAssets =
		(BfmeModuleAssetListFunction)j_0001d881;
	collectModuleAssets((BfmeModuleInfo *)&m_behaviorModuleInfo, 0, &assets, context);
	collectModuleAssets((BfmeModuleInfo *)&m_drawModuleInfo, 1, &assets, context);
	collectModuleAssets((BfmeModuleInfo *)&m_clientUpdateModuleInfo, 2, &assets, context);
	collectModuleAssets((BfmeModuleInfo *)&m_clientBehaviorModuleInfo, 3, &assets, context);

	if (m_shadowTextureName.isNotEmpty())
		assets << (m_shadowTextureName + ".tga");

	for (BfmeAssetBlock *assetBlock = m_assetBlocks.m_begin;
		assetBlock != m_assetBlocks.m_end; ++assetBlock)
	{
		for (int targetIndex = 0; targetIndex < 4; ++targetIndex)
		{
			if (assetBlock->m_targets[targetIndex])
				assetBlock->m_targets[targetIndex]->bfmeForward(&assets, context);
		}
	}

	if (!TheWritableGlobalData->m_flag)
	{
		const CommandSet *commandSet =
			TheControlBar->findCommandSet(m_commandSetString);
		if (commandSet)
			((BfmeObj412 *)commandSet)->call(&assets, context);
	}
}

// Retail 0x00144DC0 (177 bytes, ret 8): a cached form of the 0x00143580 collector. The
// byte at *context selects one of two AssetList caches at +0x364 (20 bytes
// each). An empty cache is filled from every build variation template
// (vector<AsciiString> at +0x2D0, looked up through TheThingFactory), or from
// this template when it has none; the cache is then merged into `assets` with
// the inline AssetList::operator<<(const AssetList &) (the out-of-line copy is
// 0x00141CD0). The method's real name is not proven, so it keeps the address.
// ?rva00144DC0@ThingTemplate@@QAEXAAVAssetList@@PAX@Z
void ThingTemplate::rva00144DC0(AssetList &assets, void *context)
{
	int index = *(bool *)context != 0;
	if (!m_assetCache[index].empty())
	{
		assets << m_assetCache[index];
		return;
	}
	_STL::vector<AsciiString>::const_iterator it = m_buildVariations.begin();
	if (it != m_buildVariations.end())
	{
		do
		{
			const ThingTemplate *variation = TheThingFactory->findTemplate(*it);
			if (variation)
				variation->rva00143580(m_assetCache[index], context);
		} while (++it != m_buildVariations.end());
	}
	else
	{
		rva00143580(m_assetCache[index], context);
	}
	assets << m_assetCache[index];
}
