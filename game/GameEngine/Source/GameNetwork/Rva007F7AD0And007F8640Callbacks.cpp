// The generated dumps at these addresses ran past the first ret into the
// following function. Each callback below is the first 15-byte body only;
// the int3 at +15 pads the next function's 16-byte alignment.
class Rva007E8810Message;
class Rva007F7980Browser
{
public:
	void onLobbyCount(Rva007E8810Message *message);
};

void __cdecl Rva007F7AD0Callback(Rva007E8810Message *message,
	Rva007F7980Browser *browser)
{
	browser->onLobbyCount(message);
}

class BfmeHostBT
{
public:
	void bfmeCloseBT(void *payload);
};

void __cdecl Rva007F8640Callback(void *payload, BfmeHostBT *host)
{
	host->bfmeCloseBT(payload);
}
