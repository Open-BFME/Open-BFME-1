// cl: /O2
class AssetManagerImpl {
public:
 const char *GetString(unsigned int key);
};
class AssetRegistry;
extern AssetRegistry *g_theAssetRegistry;
const char *Rva009EC0D0AssetRegistryName(unsigned int key)
{
 if (!g_theAssetRegistry)
  return "<no asset manager>";
 return ((AssetManagerImpl *)g_theAssetRegistry)->GetString(key);
}
