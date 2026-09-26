// cl: /O2
// The shared GameLODManager field at +0x170C is one-based; clamp to [0,2].
class GameLODManager;
extern GameLODManager *TheGameLODManager;

int Rva00752E10LODIndex()
{
    int level = *(const int *)((const char *)TheGameLODManager + 0x170C) - 1;
    if (level < 0)
        return 0;
    if (level > 2)
        return 2;
    return level;
}
