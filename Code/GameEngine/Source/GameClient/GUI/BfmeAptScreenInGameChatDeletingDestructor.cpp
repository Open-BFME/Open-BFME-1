// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: BfmeAptScreenInGameChat scalar-deleting destructor at retail RVA
// 0x00512860 (30 bytes).  The exact InGameChat.apt constructor at 0x005160E0
// carries primary table 0x01105384, and the matched complete destructor at
// 0x00511F50 resets both screen vtables and destroys the chat controls.

class BfmeAptScreenInGameChat
{
public:
	virtual ~BfmeAptScreenInGameChat();
};

void forceBfmeAptScreenInGameChatDeletingDestructor()
{
	BfmeAptScreenInGameChat value;
}
