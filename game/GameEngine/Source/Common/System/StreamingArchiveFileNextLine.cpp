// cl: /DNDEBUG /MD

// StreamingArchiveFile::nextLine, retail 0x009D20D0 (a lone `ret 8`), slot
// +0x08 after write in the StreamingArchiveFile vtable at rdata 0x00D43CB8
// (seek at 0x009D2260 sits between them).  ZH declares it inline in
// StreamingArchiveFile.h with only a DEBUG_CRASH, which leaves nothing in a
// release build; no ledger row covered it.

typedef char Char;
typedef int Int;

class StreamingArchiveFile
{
public:
	virtual void nextLine(Char *buf, Int bufSize);
};

void StreamingArchiveFile::nextLine(Char *buf, Int bufSize)
{
}
