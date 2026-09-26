// cl: /DNDEBUG /MD /GX /Od /GZ

// EA's DirtySock middleware -- see commudp.cpp for why this directory name is an
// inference. Every function name here is retail's own: each body logs it.
// Parameter lists are not recovered yet; these are naked bodies and the
// extern "C" __cdecl name does not encode them.

extern "C" {
	int CommTCPResolve();
	struct CommTCPRef;
	int CommTCPUnlisten(CommTCPRef *ref);
}

int Rva007FE780Printf(const char *format, ...);

struct CommTCPRef
{
	char m_prefix[0x90];
	int m_state;
	int m_listenSocket;
};

int CommTCPUnlisten(CommTCPRef *ref)
{
	if (ref->m_state != 4) {
		return 0;
	}
	ref->m_listenSocket = 0;
	ref->m_state = 5;
	return 0;
}

// Always fails: "Resolve functionality not supported by CommTCP".
int CommTCPResolve()
{
	Rva007FE780Printf("Resolve functionality not supported by CommTCP\n");
	return -1;
}
