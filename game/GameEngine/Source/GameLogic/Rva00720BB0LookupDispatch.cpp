// BFME shrub-buffer request lookup. Receiver identity follows the proven
// dispatch body and targets/game/reverse/identity_evidence/00720820.md.
// The opaque view preserves the wrapper's independently decoded offsets.

// The call uses ILT 0x00039680, which forwards to the byte-verified
// W3DShrubBuffer::dispatch body at 0x007202F0. Both arguments are 32-bit
// integers; the opaque request pointer below carries the second integer.
class W3DShrubBuffer
{
public:
	void dispatch(int index, int request);
};

class Rva00720BB0Context
{
public:
	char m_unknown0000[0x1E1CC8];
	int m_entryCount;
};

extern "C" bool __fastcall Rva00720BB0LookupDispatch( Rva00720BB0Context *self, void *, void *owner, void *request )
{
	if ( owner == 0 ) {
		return false;
	}

	int count = self->m_entryCount;
	int i = 0;
	void *payload;
	if ( count > 0 ) {
		char *entry = (char *)self + 0x15DC;
		do {
			if ( *(void **)(entry - 0x38) == owner && *(unsigned int *)entry <= 0 ) {
				payload = *(void **)(entry - 0xC);
				if ( payload == 0 ) {
					goto dispatch;
				}
			}
			++i;
			entry += 0xA4;
		} while ( i < count );
	}
	return false;

dispatch:
	reinterpret_cast<W3DShrubBuffer *>(self)->dispatch(
		i, reinterpret_cast<int>(request) );
	return true;
}
