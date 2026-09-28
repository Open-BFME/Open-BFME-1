// ?d_00881dc0@@YAIPAX@Z
// partial score=0.6 date=2026-09-28
// Candidate halves for the 38B row at 0x00881DC0 (int3-split: 15B msize-wrap + 23B realloc-wrap).
// Half1 as (block,ignored-extra) is byte-exact for its 15B (diffs 0); native 1-arg form
// tail-jmps (6B). Boundary/signature lever unknown: banked, not landed.
// Half2 matches landed ?d_00881df0@@YAPAXPAXI@Z (realloc through g_rva0130E9A0, flags 0).
unsigned int d_00881dc0_half1( void *block, unsigned int ignored )
{
	return g_rva0130E9B0( block );
}
