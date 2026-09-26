// cl: /DNDEBUG /MD -Iinputs/reference/shims/gamespy
/* GameSpy SDK, 2004 vintage -- pristine upstream C source.
   Sourced from the Area 51 (Inevitable Entertainment / Midway) source release,
   github.com/bisc67/Area51, Support/NetworkMgr/GameSpy -- the only public
   carrier found with the pre-2005 SDK layout (top-level nonport.c, no common/).
   Dated by nonport.h's own marker "Added by Saad Nader on 08-02-2004".
   That vintage is not assumed, it is measured: against lotrbfme.exe this tree
   scores 440 byte-exact whole functions where the 2007 SDK (nitrocaster/GameSpy,
   GS_Aluigi) scores 51 and 48 on the same TUs.
   Retail linked the DLL CRT, so libc calls are __imp__ indirect -- /MD is what
   makes those call sites byte-exact -- and built the SDK __cdecl: /Gz collapses
   the qr2+GP+ghttp core from 108 exact hits to 6.
   Win32 headers come from inputs/reference/shims/gamespy (see its windows.h): the
   toolchain ships no PlatformSDK, and the sweep shim next door is C++-only. */

#include "qr2regkeys.h"

#if defined(applec) || defined(THINK_C) || defined(__MWERKS__) && !defined(__mips64) && !defined(_WIN32)
	#include "::stringutil.h" 
#else
	#include "../stringutil.h"
#endif

#ifdef __MWERKS__ // CodeWarrior requires prototypes
void qr2_register_keyW(int keyid, const unsigned short *key);
void qr2_register_keyA(int keyid, const char *key);
#endif

const char *qr2_registered_key_list[64] =
{
	"", //0 is reserved
		"hostname",	//1
		"gamename",	//2
		"gamever",	//3
		"hostport",	//4
		"mapname",	//5
		"gametype",	//6
		"gamevariant",	//7
		"numplayers",	//8
		"numteams",	//9
		"maxplayers",	//10
		"gamemode",	//11
		"teamplay",	//12
		"fraglimit",	//13
		"teamfraglimit",//14
		"timeelapsed",	//15
		"timelimit",	//16
		"roundtime",	//17
		"roundelapsed",	//18
		"password",	//19
		"groupid",	//20
		"player_",	//21
		"score_",	//22
		"skill_",	//23
		"ping_",	//24
		"team_",	//25
		"deaths_",	//26
		"pid_",		//27
		"team_t",	//28
		"score_t",	//29
        NULL, NULL, NULL, NULL,
        NULL, NULL, NULL, NULL,
        NULL, NULL, NULL, NULL,
        NULL, NULL, NULL, NULL,
        NULL, NULL, NULL, NULL,
        NULL, NULL, NULL, NULL,
        NULL, NULL, NULL, NULL,
        NULL, NULL, NULL, NULL,
        NULL, NULL,
};


///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
// Keep a list of the unicode keys we've allocated internally so that we can free
// them when qr2 is shutdown
typedef struct QR2KeyListNodeS
{
	char* mKeyData;
	struct QR2KeyListNodeS*	mNextKey;
} QR2KeyListNode;

typedef struct QR2KeyListS
{
	struct QR2KeyListNodeS* mHead;
} QR2KeyList;

static QR2KeyList qr2_internal_key_list = { NULL };

void qr2_internal_key_list_append(char* theKey)
{
	QR2KeyListNode* aNewNode;

	assert(theKey != NULL);

	// Init the new node
	aNewNode = (QR2KeyListNode*)gsimalloc(sizeof(QR2KeyListNode));
	aNewNode->mKeyData = theKey;
	aNewNode->mNextKey = NULL;

	// Check for a NULL head
	if (qr2_internal_key_list.mHead == NULL)
		qr2_internal_key_list.mHead = aNewNode;
	else
	{
		// Find the end of the list and append this node
		QR2KeyListNode* aInsertPlace = qr2_internal_key_list.mHead;
		while(aInsertPlace->mNextKey != NULL)
			aInsertPlace = aInsertPlace->mNextKey;

		aInsertPlace->mNextKey = aNewNode;
	}
}

void qr2_internal_key_list_free()
{
	QR2KeyListNode* aNodeToFree;
	QR2KeyListNode* aNextNode;

	// Free the nodes
	aNodeToFree = qr2_internal_key_list.mHead;
	while (aNodeToFree != NULL)
	{
		aNextNode = aNodeToFree->mNextKey;	// Get a ptr to the next node (or will be lost)
		gsifree(aNodeToFree->mKeyData);		// free the string we allocated in qr2_register_keyW
		gsifree(aNodeToFree);				// free the current node
		aNodeToFree = aNextNode;			// set the current node to the next node
	}
	
	// Initialize the list back to NULL
	qr2_internal_key_list.mHead = NULL;
}


///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
void qr2_register_keyA(int keyid, const char *key)
{
	if (keyid < NUM_RESERVED_KEYS || keyid > MAX_REGISTERED_KEYS)
		return;
	qr2_registered_key_list[keyid] = key;
}
void qr2_register_keyW(int keyid, const unsigned short *key)
{
	char* key_A = UCS2ToUTF8StringAlloc(key);

	// Register the ascii version
	qr2_register_keyA(keyid, key_A);

	// Keep track of the unicode version so we can delete it later
	qr2_internal_key_list_append(key_A);
}
