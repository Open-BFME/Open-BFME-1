// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: protected scalar-deleting destructor for Player.
// Vtable 0x00C840CC slots name this class (?checkBridges@Player@@UAE_NPAVObject@@PAVWaypoint@@@Z and ?getAiBaseCenter@Player@@UAE_NPAUCoord3D@@@Z); its slot zero routes
// through ILT 0x000167C0 to this 30-byte wrapper, whose complete destructor
// route ILT 0x0003C038 reaches cleanup body 0x000DD440.

class Player
{
protected:
	virtual ~Player();
private:
	friend void forcePlayerDeletingDestructor();
};

void forcePlayerDeletingDestructor()
{
	Player value;
}
