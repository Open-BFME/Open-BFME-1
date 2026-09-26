// cl: /O2
class AssetRegistry {
public:
 const char *Rva009EEDF0Lookup(unsigned int key);
};
extern AssetRegistry *g_theAssetRegistry;
const char *Rva009EC0D0AssetRegistryName(unsigned int key)
{
 if (!g_theAssetRegistry)
  return "<no asset manager>";
 return g_theAssetRegistry->Rva009EEDF0Lookup(key);
}
