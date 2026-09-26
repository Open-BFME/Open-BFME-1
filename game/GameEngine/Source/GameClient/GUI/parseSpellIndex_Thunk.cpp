// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// Retail RVA 0x005990A0. The outlined "SpellNN" name parser that sits one
// slot above the three BfmeAptScreenSpellStore callbacks at 0x005990E0,
// 0x00599180 and 0x005991E0, each of which spells the same test inline.
// Nothing in the image calls this copy, so it keeps a descriptive free name.

extern "C" __declspec(dllimport) int __cdecl atoi( const char * );
extern "C" __declspec(dllimport) int __cdecl strncmp(
	const char *, const char *, unsigned int );

// @?parseSpellIndex@@YAHPBD@Z 0x005990A0
static __declspec(noinline) int parseSpellIndex( const char *name )
{
	if( strncmp( name, "Spell", 5 ) != 0 )
		return -1;
	return atoi( name + 5 ) - 1;
}

int parseSpellIndexCall( const char *name )
{
	return parseSpellIndex( name );
}
