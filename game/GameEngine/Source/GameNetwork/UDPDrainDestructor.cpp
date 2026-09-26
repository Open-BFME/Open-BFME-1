// cl: /DNDEBUG /MD /EHsc

typedef unsigned int SOCKET;

extern "C" __declspec(dllimport) int __stdcall shutdown(SOCKET socket, int how);
extern "C" __declspec(dllimport) int __stdcall recvfrom(
	SOCKET socket, char *buffer, int length, int flags, void *from, int *fromLength);
extern "C" __declspec(dllimport) int __stdcall closesocket(SOCKET socket);

// A distinct source identity is required because retail links another UDP destructor body.
class UDPDrain
{
public:
	~UDPDrain();

private:
	SOCKET fd;
};

UDPDrain::~UDPDrain()
{
	char pending[1024];
	if (fd != static_cast<SOCKET>(-1)) {
		shutdown(fd, 2);
		while (recvfrom(fd, pending, sizeof(pending), 0, 0, 0) > 0) {
		}
		closesocket(fd);
	}
}
