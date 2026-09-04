// Address-derived recovery: the surrounding type has not yet been identified.
// The body walks its fixed-stride entry table, finds the requested owner, and
// dispatches the associated non-null payload through the existing 0x39680
// transfer thunk.

#pragma comment(linker, "/alternatename:?dispatch@Rva00720BB0Context@@QAEXHPAX@Z=?j_00039680@@YAXXZ")

struct Rva00720BB0Context
{
	void dispatch( int index, void *request );
	char unknown0000[ 0x1E1CC8 ];
	int entryCount;
};

void Rva00720BB0Context::dispatch( int index, void *request )
{
	(void)index;
	(void)request;
}

extern "C" bool __fastcall Rva00720BB0LookupDispatch( Rva00720BB0Context *self, void *, void *owner, void *request )
{
	if ( owner == 0 ) {
		return false;
	}

	int count = self->entryCount;
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
	self->dispatch( i, request );
	return true;
}
