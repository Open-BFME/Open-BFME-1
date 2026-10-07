// cl: /DNDEBUG /MD /GX- /O2 /Ob2

// Open-BFME5: Add_Prototype thin wrapper.
// Null-check global AssetManagerImpl then thiscall Add_Prototype_Impl.

class AssetManagerImpl
{
public:
	void Add_Prototype_Impl(void *proto);
};

class AssetRegistry;
extern AssetRegistry *g_theAssetRegistry;

// ?Add_Prototype@@YAXPAX@Z
void Add_Prototype(void *proto)
{
	if (g_theAssetRegistry)
		((AssetManagerImpl *)g_theAssetRegistry)->Add_Prototype_Impl(proto);
}
