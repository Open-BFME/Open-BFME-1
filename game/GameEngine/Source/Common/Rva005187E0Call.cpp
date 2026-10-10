// cl: /O2 /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD

// Retail call +0 targets ILT 0x0003CD94 -> 0x00518350, whose
// verified provider is BfmeAptScreenLanLobby::sendChatRva00518350.
class BfmeAptScreenLanLobby
{
public:
	void sendChatRva00518350();
};

class Rva005187E0
{
public:
	void wrap(int a);
};

void Rva005187E0::wrap(int)
{
	((BfmeAptScreenLanLobby *)this)->sendChatRva00518350();
}
