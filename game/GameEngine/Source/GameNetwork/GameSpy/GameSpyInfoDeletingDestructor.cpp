// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: GameSpyInfo scalar-deleting destructor at retail RVA 0x00637C90
// (30 bytes).  GameSpyInfo's constructor at 0x00636D90 installs the BFME
// vtable 0x011188D0, and its complete virtual destructor is the matched body
// at 0x00637590 in PeerDefs.cpp.  That TU also carries the BFME 0x700-byte
// layout and the named virtual methods reached through the same vtable.

class GameSpyInfo
{
public:
	virtual ~GameSpyInfo();
};

void forceGameSpyInfoDeletingDestructor()
{
	GameSpyInfo value;
}
