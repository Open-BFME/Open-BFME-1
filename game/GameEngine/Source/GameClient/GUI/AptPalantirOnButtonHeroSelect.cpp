class AptPalantirHeroSelector
{
};

// Retail calls ILT 0x00002383 (tail thunk 0x005954D0), not a named member body;
// spell the call through the ledgered ?j_00002383 thunk as a member-pointer call
// so the receiver stays in ECX and the index on the stack.
extern void j_00002383();
typedef void (AptPalantirHeroSelector::*SelectHeroFn)( int );

// Retail 0x012F4B98: use the existing data owner; retain the local pointee view.
extern class AptPalantir *TheAptPalantir;
extern "C" __declspec(dllimport) int __cdecl strncmp( char *left, char *right, int count );
extern "C" __declspec(dllimport) int __cdecl atoi( char *text );

// ?aptPalantirOnButtonHeroSelect@@YAXPAD@Z
void aptPalantirOnButtonHeroSelect( char *hero )
{
	if( strncmp( hero, "Hero", 4 ) != 0 )
		return;

	union { void (*fn)(); SelectHeroFn call; } target = { j_00002383 };
	( reinterpret_cast<AptPalantirHeroSelector *>(TheAptPalantir)->*target.call )( atoi( hero + 4 ) - 1 );
}
