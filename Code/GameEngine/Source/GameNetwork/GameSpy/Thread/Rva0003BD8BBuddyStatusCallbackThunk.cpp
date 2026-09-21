// cl: /O2 /DNDEBUG /MD /EHsc

// Retail RVA 0x0003BD8B is a five-byte ILT jump to
// BuddyThreadClass::statusCallback at 0x0063A9F0. The pin and the callback
// wrapper caller identify the target, while this wrapper keeps the thunk name
// address-derived.
class GPConnection;

struct GPRecvBuddyStatusArg
{
};

class BuddyThreadClass
{
public:
	void statusCallback(GPConnection *connection,
		GPRecvBuddyStatusArg *arg);
};

class Rva0003BD8BBuddyStatusCallbackThunk : public BuddyThreadClass
{
public:
	void forward(GPConnection *connection, GPRecvBuddyStatusArg *arg);
};

void Rva0003BD8BBuddyStatusCallbackThunk::forward(
	GPConnection *connection, GPRecvBuddyStatusArg *arg)
{
	statusCallback(connection, arg);
}
