// BFME ThingTemplate asset collection, retail RVA 0x00143580.

template <typename T>
class StringBase
{
public:
	StringBase() {}
	StringBase(const StringBase<T> &other);

	char *m_data;
};

class AsciiString : private StringBase<char>
{
public:
	AsciiString(const AsciiString &other)
	{
		((StringBase<char> *)this)->StringBase<char>::StringBase(
			*(const StringBase<char> *)&other);
	}
	~AsciiString();

	bool isNotEmpty() const
	{
		return m_data != 0 && *(const unsigned short *)(m_data + 4) != 0;
	}
};

class AssetList
{
public:
	AssetList &operator<<(const AsciiString &name);
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

#define TheControlBar (*(ControlBar **)0x012F33F8)

struct BfmeWritableGlobalData
{
	char m_padding[0x11fc];
	unsigned char m_flag;
};

#define TheWritableGlobalData (*(BfmeWritableGlobalData **)0x012ED5C8)

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

class ThingTemplate
{
public:
	void GetAssetList(AssetList &assets, void *context) const;

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
	char m_padding2c4[0x34];
	BfmeAssetBlockVector m_assetBlocks;
};

void ThingTemplate::GetAssetList(AssetList &assets, void *context) const
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
