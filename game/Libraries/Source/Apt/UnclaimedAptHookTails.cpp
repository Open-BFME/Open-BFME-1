// cl: /O2 /DNDEBUG /MD /EHsc
//
// Unclaimed six-byte bodies in the Apt/EA library run, each alone in a .text
// gap no ledger row covered: a 16-byte-aligned start after int3 padding, one
// `jmp dword ptr [cell]` through one of the three allocator hook cells the
// matched installer bfmeInstallHandlersVB (0x00789440) fills, then int3
// padding.  No call, jump, table slot or dir32 name reaches any of them, so
// they are the out-of-line copies of class-scope allocation wrappers that
// nothing in the image calls.
//
//   jmp [0x01337828]  Rva008C5D70Alloc  void *(unsigned int)
//   jmp [0x0133782C]  g_bfmeFreeDWF     void (void *)
//   jmp [0x01337830]  TheBfmeFree       void (void *, unsigned int)
//
// IDENTITY IS NOT RECOVERED.  Every name is derived from an address.

extern void *(__cdecl *Rva008C5D70Alloc)(unsigned int bytes);
extern void (__cdecl *g_bfmeFreeDWF)(void *block);
extern void (__cdecl *TheBfmeFree)(void *block, unsigned int bytes);

void *Rva00891680Alloc(unsigned int bytes)
{
	return Rva008C5D70Alloc(bytes);
}

void Rva008916A0Free(void *block)
{
	g_bfmeFreeDWF(block);
}

void *Rva008916B0Alloc(unsigned int bytes)
{
	return Rva008C5D70Alloc(bytes);
}

void Rva008916C0SizedFree(void *block, unsigned int bytes)
{
	TheBfmeFree(block, bytes);
}

void *Rva008916F0Alloc(unsigned int bytes)
{
	return Rva008C5D70Alloc(bytes);
}

void *Rva00891740Alloc(unsigned int bytes)
{
	return Rva008C5D70Alloc(bytes);
}

void *Rva008917E0Alloc(unsigned int bytes)
{
	return Rva008C5D70Alloc(bytes);
}

void *Rva00891A70Alloc(unsigned int bytes)
{
	return Rva008C5D70Alloc(bytes);
}

void Rva008925D0Free(void *block)
{
	g_bfmeFreeDWF(block);
}

void Rva008925E0Free(void *block)
{
	g_bfmeFreeDWF(block);
}

void Rva008926A0SizedFree(void *block, unsigned int bytes)
{
	TheBfmeFree(block, bytes);
}

void *Rva008926B0Alloc(unsigned int bytes)
{
	return Rva008C5D70Alloc(bytes);
}

void *Rva00894C40Alloc(unsigned int bytes)
{
	return Rva008C5D70Alloc(bytes);
}

void *Rva00894C60Alloc(unsigned int bytes)
{
	return Rva008C5D70Alloc(bytes);
}

void *Rva00894CF0Alloc(unsigned int bytes)
{
	return Rva008C5D70Alloc(bytes);
}

void Rva00894D00SizedFree(void *block, unsigned int bytes)
{
	TheBfmeFree(block, bytes);
}

void *Rva00894D40Alloc(unsigned int bytes)
{
	return Rva008C5D70Alloc(bytes);
}

void *Rva00894F20Alloc(unsigned int bytes)
{
	return Rva008C5D70Alloc(bytes);
}

void *Rva00894F30Alloc(unsigned int bytes)
{
	return Rva008C5D70Alloc(bytes);
}

void *Rva00897490Alloc(unsigned int bytes)
{
	return Rva008C5D70Alloc(bytes);
}

void Rva008974A0SizedFree(void *block, unsigned int bytes)
{
	TheBfmeFree(block, bytes);
}

void *Rva008976C0Alloc(unsigned int bytes)
{
	return Rva008C5D70Alloc(bytes);
}

void *Rva00897720Alloc(unsigned int bytes)
{
	return Rva008C5D70Alloc(bytes);
}

void Rva00897730SizedFree(void *block, unsigned int bytes)
{
	TheBfmeFree(block, bytes);
}

void *Rva00897740Alloc(unsigned int bytes)
{
	return Rva008C5D70Alloc(bytes);
}

void Rva00897750SizedFree(void *block, unsigned int bytes)
{
	TheBfmeFree(block, bytes);
}

void *Rva008979A0Alloc(unsigned int bytes)
{
	return Rva008C5D70Alloc(bytes);
}

void Rva008A0590SizedFree(void *block, unsigned int bytes)
{
	TheBfmeFree(block, bytes);
}

void *Rva008A05A0Alloc(unsigned int bytes)
{
	return Rva008C5D70Alloc(bytes);
}

void *Rva008A05C0Alloc(unsigned int bytes)
{
	return Rva008C5D70Alloc(bytes);
}

void Rva008A05D0Free(void *block)
{
	g_bfmeFreeDWF(block);
}

void *Rva008A05E0Alloc(unsigned int bytes)
{
	return Rva008C5D70Alloc(bytes);
}

void Rva008A05F0Free(void *block)
{
	g_bfmeFreeDWF(block);
}

void *Rva008A3100Alloc(unsigned int bytes)
{
	return Rva008C5D70Alloc(bytes);
}

void Rva008A3110SizedFree(void *block, unsigned int bytes)
{
	TheBfmeFree(block, bytes);
}

void *Rva008AB8A0Alloc(unsigned int bytes)
{
	return Rva008C5D70Alloc(bytes);
}

void *Rva008BD030Alloc(unsigned int bytes)
{
	return Rva008C5D70Alloc(bytes);
}

void *Rva008BD050Alloc(unsigned int bytes)
{
	return Rva008C5D70Alloc(bytes);
}

void Rva008BD060SizedFree(void *block, unsigned int bytes)
{
	TheBfmeFree(block, bytes);
}

void *Rva008BD070Alloc(unsigned int bytes)
{
	return Rva008C5D70Alloc(bytes);
}

void Rva008BD080SizedFree(void *block, unsigned int bytes)
{
	TheBfmeFree(block, bytes);
}

void *Rva008BD090Alloc(unsigned int bytes)
{
	return Rva008C5D70Alloc(bytes);
}

void Rva008BD0A0SizedFree(void *block, unsigned int bytes)
{
	TheBfmeFree(block, bytes);
}

void *Rva008BD0B0Alloc(unsigned int bytes)
{
	return Rva008C5D70Alloc(bytes);
}

void *Rva008BD0D0Alloc(unsigned int bytes)
{
	return Rva008C5D70Alloc(bytes);
}

void Rva008BD0E0SizedFree(void *block, unsigned int bytes)
{
	TheBfmeFree(block, bytes);
}

void Rva008C3E00SizedFree(void *block, unsigned int bytes)
{
	TheBfmeFree(block, bytes);
}

void *Rva008C44A0Alloc(unsigned int bytes)
{
	return Rva008C5D70Alloc(bytes);
}

void Rva008C44B0SizedFree(void *block, unsigned int bytes)
{
	TheBfmeFree(block, bytes);
}

void *Rva008C44C0Alloc(unsigned int bytes)
{
	return Rva008C5D70Alloc(bytes);
}

void Rva008C44D0SizedFree(void *block, unsigned int bytes)
{
	TheBfmeFree(block, bytes);
}
