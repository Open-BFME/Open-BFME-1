// cl: /O2 /DNDEBUG /MD /EHsc
// The owner remains address-derived. Retail counts HLOD array payload bytes.

extern "C" unsigned int __cdecl strlen(const char *text);
#pragma intrinsic(strlen)

struct Rva009794F0SubObjectArray
{
    float maxScreenSize;
    int modelCount;
    char **modelName;
    int *boneIndex;
};

struct Rva009794F0ProxyArray
{
    char pad[8];
    int vectorMax;
};

class Gen009794F0
{
public:
    int handle();

private:
    char *name;
    char *hierarchyName;
    int lodCount;
    Rva009794F0SubObjectArray *lod;
    Rva009794F0SubObjectArray aggregates;
    Rva009794F0ProxyArray *proxyArray;
};

int Gen009794F0::handle()
{
    int total = 0x124;

    if (lodCount > 0) {
        int *array = &lod->modelCount;
        int count = lodCount;
        do {
            int modelCount = *array;
            int size = modelCount * 8 + 0x10;
            if (modelCount > 0) {
                char **names = (char **)*(array + 1);
                for (int i = modelCount; i > 0; --i, ++names) {
                    size += (int)strlen(*names) + 1;
                }
            }
            total += size;
            array += 4;
        } while (--count);
    }

    int modelCount = aggregates.modelCount;
    int size = modelCount * 8 + 0x10;
    if (modelCount > 0) {
        char **names = aggregates.modelName;
        for (int i = modelCount; i > 0; --i, ++names) {
            size += (int)strlen(*names) + 1;
        }
    }
    total += size;

    if (proxyArray != 0) {
        total += proxyArray->vectorMax * 36;
    }
    return total;
}
