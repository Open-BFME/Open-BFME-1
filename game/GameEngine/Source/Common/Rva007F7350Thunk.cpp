// Retail RVA 0x007F7350 is the cdecl callback adapter for the game-browser
// message handler at 0x007F72D0. Both arguments are pointers; the adapter
// passes the message on the stack and loads the browser receiver into ECX.
// Keep the existing address-derived export's opaque 32-bit argument ABI,
// but decode its message address and call the recovered member normally.

class Rva007E8810Message;
struct Rva007F72D0Obj;

class BfmeThingZI
{
public:
	void Rva007F72D0(Rva007E8810Message *message);
};

void Rva007F7350Thunk(int messageAddress, Rva007F72D0Obj *opaqueObject)
{
	Rva007E8810Message *message =
		reinterpret_cast<Rva007E8810Message *>(messageAddress);
	BfmeThingZI *object = reinterpret_cast<BfmeThingZI *>(opaqueObject);
	object->Rva007F72D0(message);
}
