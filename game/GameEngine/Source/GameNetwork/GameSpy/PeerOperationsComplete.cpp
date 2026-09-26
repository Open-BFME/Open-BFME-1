// cl: /MD /DNDEBUG
// Address 0x0085F040 is in the peer operations TU.  It reports whether the
// peer has any queued operation whose owner field points back to that peer.

struct DArrayImplementation;
typedef DArrayImplementation *DArray;

extern "C" int ArrayLength(const DArray array);
extern "C" void *ArrayNth(DArray array, int index);

struct PeerOperation
{
	char unknown00[12];
	void *owner;
};

struct PeerState
{
	char unknown0000[0x1798];
	DArray operations;
};

extern "C" int PeerOperationsComplete(PeerState *peer, void *owner)
{
	PeerState *context = peer;
	if (context->operations == 0) {
		return 1;
	}

	int count = ArrayLength(context->operations);
	for (int i = 0; i < count; ++i) {
		PeerOperation **operation = (PeerOperation **)ArrayNth(context->operations, i);
		if ((*operation)->owner == owner) {
			return 0;
		}
	}
	return 1;
}
