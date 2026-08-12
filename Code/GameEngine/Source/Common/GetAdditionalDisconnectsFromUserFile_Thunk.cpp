// cl: /DNDEBUG /MD /EHsc

int __fastcall getTotalDisconnectsFromFile(int playerID);

class GameSpyInfo;

struct GameSpyInfoVTable
{
    void *slots[92];
    int (__fastcall *getAdditionalDisconnects)(GameSpyInfo *self);
    void (__fastcall *clearAdditionalDisconnects)(GameSpyInfo *self);
};

class GameSpyInfo
{
public:
    GameSpyInfoVTable *vtable;
};

extern GameSpyInfo *TheGameSpyInfo;

// ?GetAdditionalDisconnectsFromUserFile@@YAHH@Z
int __cdecl GetAdditionalDisconnectsFromUserFile(int playerID)
{
    int result = getTotalDisconnectsFromFile(playerID);
    if (playerID == 0) {
        return 0;
    }

    if (TheGameSpyInfo->vtable->getAdditionalDisconnects(TheGameSpyInfo) > 0 && result == 0) {
        TheGameSpyInfo->vtable->clearAdditionalDisconnects(TheGameSpyInfo);
    }

    if (TheGameSpyInfo->vtable->getAdditionalDisconnects(TheGameSpyInfo) != -1) {
        return TheGameSpyInfo->vtable->getAdditionalDisconnects(TheGameSpyInfo);
    }
    return result;
}
