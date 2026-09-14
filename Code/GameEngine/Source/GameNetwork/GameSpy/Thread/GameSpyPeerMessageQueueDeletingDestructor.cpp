// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: GameSpyPeerMessageQueue scalar-deleting destructor at retail RVA
// 0x0064D750 (30 bytes). The exact constructor at 0x0064D650 installs vtable
// 0x01119688, whose slot zero routes through ILT 0x0001E12D to this wrapper.
// The recovered queue method family corroborates identity; dtor ILT 0x0002D93E.

class GameSpyPeerMessageQueue
{
public:
	virtual ~GameSpyPeerMessageQueue();
};

void forceGameSpyPeerMessageQueueDeletingDestructor()
{
	GameSpyPeerMessageQueue value;
}
