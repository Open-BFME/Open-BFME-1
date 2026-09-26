// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: GameSpyConfig scalar-deleting destructor at retail RVA 0x00629F60
// (30 bytes). The exact constructor at 0x00628BA0 installs vtable 0x01118050,
// whose slot zero routes through ILT 0x000362F5 to this wrapper. The recovered
// GameSpyConfig method family corroborates identity; dtor ILT 0x00008FB7.

class GameSpyConfig
{
public:
	virtual ~GameSpyConfig();
};

void forceGameSpyConfigDeletingDestructor()
{
	GameSpyConfig value;
}
