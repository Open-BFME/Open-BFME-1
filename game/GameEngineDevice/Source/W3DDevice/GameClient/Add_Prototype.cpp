// cl: /DNDEBUG /MD /GX- /O2 /Ob2

// Open-BFME5: Add_Prototype thin wrapper.
// Null-check global AssetRegistry then thiscall Add_Prototype_Impl.

class AssetRegistry
{
public:
	void Add_Prototype_Impl(void *proto);
};

extern AssetRegistry *g_theAssetRegistry;

// ?Add_Prototype@@YAXPAX@Z
void Add_Prototype(void *proto)
{
	if (g_theAssetRegistry)
		g_theAssetRegistry->Add_Prototype_Impl(proto);
}
