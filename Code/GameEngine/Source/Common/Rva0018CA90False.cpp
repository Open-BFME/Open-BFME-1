// cl: /O2 /Ob2 /DNDEBUG /MD /GX- /EHs-c-

// The carved boundary at 0x0018CA90 is the three-byte false-return body
// xor eax,eax; ret. No caller or symbol table proves a semantic owner.

int rva0018ca90()
{
	return false;
}
