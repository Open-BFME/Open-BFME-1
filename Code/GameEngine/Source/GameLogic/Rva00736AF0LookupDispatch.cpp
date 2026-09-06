// BFME's tree-buffer request path.  The surrounding object stores its tree
// Open-BFME7: retail 0x00736AF0 (89 bytes) is the twin of Rva00720BB0LookupDispatch on a
// larger buffer object: the entry count sits at +0x2A7CB0, the record table starts at +0x284
// with 0xE8-byte records, and the owner pointer is 0x7C bytes before each record's request
// word (the payload stays 0xC bytes before it).  Same __fastcall shape.

class Rva00736AF0Context
{
public:
	void dispatch( int index, void *request );

	char m_unknown0000[0x2A7CB0];
	int m_entryCount;
};

extern "C" bool __fastcall Rva00736AF0LookupDispatch( Rva00736AF0Context *self, void *, void *owner, void *request )
{
	if ( owner == 0 ) {
		return false;
	}

	int count = self->m_entryCount;
	int i = 0;
	void *payload;
	if ( count > 0 ) {
		char *entry = (char *)self + 0x284;
		do {
			if ( *(void **)(entry - 0x7C) == owner && *(unsigned int *)entry <= 0 ) {
				payload = *(void **)(entry - 0xC);
				if ( payload == 0 ) {
					goto dispatch;
				}
			}
			++i;
			entry += 0xE8;
		} while ( i < count );
	}
	return false;

dispatch:
	self->dispatch( i, request );
	return true;
}
