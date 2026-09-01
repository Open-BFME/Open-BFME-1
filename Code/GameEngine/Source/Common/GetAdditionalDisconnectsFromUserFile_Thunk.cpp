// cl: /DNDEBUG /MD /EHsc
// Open-BFME: GetAdditionalDisconnectsFromUserFile, retail 0x004DB4E0.

struct BfmeDisconnectQueue;

typedef int (__fastcall *BfmeGetDisconnectCount)( BfmeDisconnectQueue *queue );
typedef void (__fastcall *BfmeRefreshDisconnectCount)( BfmeDisconnectQueue *queue );

struct BfmeDisconnectQueueVtable
{
	void *m_beforeCount[ 0x170 / sizeof( void * ) ];
	BfmeGetDisconnectCount m_getCount;
	BfmeRefreshDisconnectCount m_refreshCount;
};

struct BfmeDisconnectQueue
{
	BfmeDisconnectQueueVtable *m_vtable;

	int getCount() { return m_vtable->m_getCount( this ); }
	void refreshCount() { m_vtable->m_refreshCount( this ); }
};

int __fastcall readAdditionalDisconnectsFromUserFile( int playerID );

static BfmeDisconnectQueue *getDisconnectQueue()
{
	return *reinterpret_cast<BfmeDisconnectQueue **>( 0x012F7194 );
}

// ?GetAdditionalDisconnectsFromUserFile@@YAHH@Z
int __cdecl GetAdditionalDisconnectsFromUserFile( int playerID )
{
	int fileCount = readAdditionalDisconnectsFromUserFile( playerID );
	if (playerID == 0)
		return 0;

	if (getDisconnectQueue()->getCount() > 0 && fileCount == 0)
		getDisconnectQueue()->refreshCount();

	if (getDisconnectQueue()->getCount() != -1)
		return getDisconnectQueue()->getCount();

	return fileCount;
}
