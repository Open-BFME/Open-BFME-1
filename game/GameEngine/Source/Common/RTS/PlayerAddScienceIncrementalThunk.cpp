// ?Rva00036057PlayerAddScienceThunk@@YAXXZ
// Retail 0x00036057 is the Player::addScience ILT. Its five-byte tail jump
// reaches the matched PlayerAddScienceShim::add body at 0x000D5380.
// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

extern void rva00036057Target(void);

#pragma comment(linker, "/alternatename:?rva00036057Target@@YAXXZ=?add@PlayerAddScienceShim@@QAE_NW4ScienceType@@@Z")

void Rva00036057PlayerAddScienceThunk(void)
{
	rva00036057Target();
}
