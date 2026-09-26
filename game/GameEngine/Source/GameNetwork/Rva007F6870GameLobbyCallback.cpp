class Rva007E8810Message;
class Rva007F65E0Owner
{
public:
    void handleGameLobbyReply(Rva007E8810Message *message, int status);
};

void __cdecl rva007F6870GameLobbyCallback(Rva007E8810Message *message,
                                          Rva007F65E0Owner *owner)
{
    owner->handleGameLobbyReply(message, 0);
}
