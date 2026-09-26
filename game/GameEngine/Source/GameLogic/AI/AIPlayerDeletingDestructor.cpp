// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: protected scalar-deleting destructor for AIPlayer.
// Vtable 0x00C968B0 slots name this class (?newMap@AIPlayer@@UAEXXZ and
// ?onUnitProduced@AIPlayer@@UAEXPAVObject@@0@Z); its slot zero routes
// through ILT 0x00046CDB to this 30-byte wrapper, whose complete destructor
// route ILT 0x0003692B reaches cleanup body 0x001613C0.

class AIPlayer
{
protected:
	virtual ~AIPlayer();
private:
	friend void forceAIPlayerDeletingDestructor();
};

void forceAIPlayerDeletingDestructor()
{
	AIPlayer value;
}
