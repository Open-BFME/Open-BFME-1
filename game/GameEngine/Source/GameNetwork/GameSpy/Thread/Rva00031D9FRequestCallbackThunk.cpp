// cl: /O2 /DNDEBUG /MD /EHsc
// The five-byte ILT at 0x00031D9F forwards to the matched
// BuddyThreadClass::requestCallback body at 0x0063CA60.

class GPConnection;
struct GPRecvBuddyRequestArg;

class BuddyThreadClass
{
public:
	void requestCallback(GPConnection *connection, GPRecvBuddyRequestArg *argument);
};

class Rva00031D9FRequestCallbackThunk
{
public:
	void forward(GPConnection *connection, GPRecvBuddyRequestArg *argument);
};

void Rva00031D9FRequestCallbackThunk::forward(
	GPConnection *connection, GPRecvBuddyRequestArg *argument)
{
	((BuddyThreadClass *)this)->requestCallback(connection, argument);
}
