// cl: /DNDEBUG /MD /EHsc

class GameSpyInfoInterface
{
public:
    static GameSpyInfoInterface *__cdecl createNewGameSpyInfoInterface();
};

class GameSpyInfo
{
public:
    GameSpyInfo();

private:
    unsigned char storage[0x700];
};

// ?createNewGameSpyInfoInterface@GameSpyInfoInterface@@SAPAV1@XZ
GameSpyInfoInterface *__cdecl GameSpyInfoInterface::createNewGameSpyInfoInterface()
{
    return reinterpret_cast<GameSpyInfoInterface *>(new GameSpyInfo);
}
