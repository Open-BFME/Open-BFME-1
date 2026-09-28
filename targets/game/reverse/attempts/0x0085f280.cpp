// ?d_0085f280@@YAXXZ
// partial score=0.93 date=2026-09-28
// _Rva0085F280NickError (partial score=0.93 date=2026-09-28)
// piAddNickErrorCallback result-forwarder: native piOperation prefix
// (peer@0, type@+4, id@+0xC, callback@+0x10, param@+0x18) matches the
// witnessed piOperation layout in BOTH neighbouring TUs (peerCallbacks.c
// and peerOperationsListGroupRooms.c). Shape 1.000, 3 stack-slot diffs.

typedef struct Rva0085F280Operation
{
	void *peer;
	int type;
	char m_08[4];
	int id;
	void *callback;
	char m_14[4];
	void *param;
} Rva0085F280Operation;
void piAddNickErrorCallback(void *, int, const char *, int, char **, void *, int);

void Rva0085F280NickError(Rva0085F280Operation *operation, const char *nick, int type,
	int numSuggested, char **suggested)
{
	piAddNickErrorCallback(operation->peer, type, nick, numSuggested, suggested, operation->param, operation->id);
}
