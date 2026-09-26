// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: protected scalar-deleting destructor for EstablishConnectionsMenu.
// Vtable 0x00D1A394 slots name this class (?setPlayerName@EstablishConnectionsMenu@@); its slot zero routes
// through ILT 0x00049792 to this 30-byte wrapper, whose complete destructor
// route ILT 0x000403E0 reaches cleanup body 0x004B2CA0.

class EstablishConnectionsMenu
{
protected:
	virtual ~EstablishConnectionsMenu();
private:
	friend void forceEstablishConnectionsMenuDeletingDestructor();
};

void forceEstablishConnectionsMenuDeletingDestructor()
{
	EstablishConnectionsMenu value;
}
