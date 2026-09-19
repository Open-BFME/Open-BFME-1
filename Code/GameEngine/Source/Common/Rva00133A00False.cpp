// cl: /O2 /DNDEBUG /MD

// The carved body at 0x00133A00 returns false and has no direct callees.
// Its generated thunk supplies no semantic owner, so the type keeps the address.
bool Rva00133A00False()
{
    return false;
}
