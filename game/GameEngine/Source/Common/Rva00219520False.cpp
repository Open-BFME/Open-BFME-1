// cl: /O2 /DNDEBUG /MD

// The carved body at 0x00219520 returns false and has no direct callees.
// Its generated thunk supplies no semantic owner, so the type keeps the address.
bool Rva00219520False()
{
    return false;
}
