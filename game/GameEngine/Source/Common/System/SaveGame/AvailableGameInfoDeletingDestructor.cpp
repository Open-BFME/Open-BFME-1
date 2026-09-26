// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: AvailableGameInfo scalar-deleting destructor at retail RVA
// 0x0010DF90 (30 bytes). The wrapper calls the canonical AvailableGameInfo
// destructor through ILT 0x0001CFFD, then conditionally invokes operator
// delete. The exact copy constructor and GameState's recovered available-game
// list ownership establish the non-virtual value type.

class AvailableGameInfo
{
public:
	~AvailableGameInfo();
};

void forceAvailableGameInfoDelete(AvailableGameInfo *info)
{
	delete info;
}
