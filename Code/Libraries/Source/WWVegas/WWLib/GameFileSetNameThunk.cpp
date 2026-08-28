// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/W3DDevice/GameClient/W3DFileSystem.h
class GameFileClass
{
public:
    virtual const char *Set_Name(const char *);
};

class GameFileSetNameShim
{
public:
    const char *set(const char *name);
};

const char *GameFileClass::Set_Name(const char *name)
{
    return ((GameFileSetNameShim *)this)->set(name);
}
