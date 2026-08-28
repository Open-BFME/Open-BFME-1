// cl: /DNDEBUG /MD /EHsc

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/GameSpy/LadderDefs.h
class LadderList
{
public:
    ~LadderList();
};

void destroyLadderListForThunk(LadderList *list)
{
    delete list;
}
