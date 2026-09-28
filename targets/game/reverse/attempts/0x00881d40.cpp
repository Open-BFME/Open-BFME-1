// ?d_00881d40@@YAXPAX@Z
// partial score=0.7 date=2026-09-28
// Candidate for ?d_00881d40@@YAXPAX@Z at 0x00881D40 (35B): guarded free with TAIL JMP.
// Closest pure-C: guards match, arg order matches, but MSVC emits call+add esp
// (29B) where retail writes outgoing slots and jmps (35B). Tail-jmp lever unknown.
void d_00881d40( void *ptr )
{
	if ( ptr == 0 || ptr == Rva01357214Onexitbegin )
		return;
	__gameMemFreePtr( ptr, 0 );
}
