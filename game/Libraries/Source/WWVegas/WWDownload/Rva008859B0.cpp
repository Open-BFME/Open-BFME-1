// cl: /DNDEBUG /MD /EHs-c-
// Retail 0x008859B0: recv wrapper on the socket class shared with
// Rva00885980.cpp (m_socket at +0x4, second socket at +0x8). The
// twin 0x00885990 body takes (this+8, buf, len) through _send@16;
// this one takes the same triple through _recv@16 (vendored
// gamespy-2004 pin at 0x0081BE74).

extern "C" int __stdcall recv(unsigned int s, char *buf, int len, int flags);

class Rva008859B0Class
{
public:
	char m_pad0[4];
	int m_socket; // at 0x4
	int m_socket8; // at 0x8

	int d_008859b0(char *buf, int len);
};

int Rva008859B0Class::d_008859b0(char *buf, int len)
{
	return recv(m_socket8, buf, len, 0);
}
