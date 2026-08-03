// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: create the retail GameSpyInfo implementation through C++ new.

class GameSpyInfoInterface
{
public:
    virtual ~GameSpyInfoInterface() {}
    static GameSpyInfoInterface * __cdecl createNewGameSpyInfoInterface();
};

class GameSpyInfo : public GameSpyInfoInterface
{
    unsigned char m_padding04[0x6fc];

public:
    GameSpyInfo();
};

// ?createNewGameSpyInfoInterface@GameSpyInfoInterface@@SAPAV1@XZ
GameSpyInfoInterface * __cdecl GameSpyInfoInterface::createNewGameSpyInfoInterface()
{
    return new GameSpyInfo;
}
