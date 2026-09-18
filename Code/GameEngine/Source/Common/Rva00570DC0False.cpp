// cl: /DNDEBUG /MD /EHsc

// The carved three-byte body returns false. The ILT thunk proves the address,
// but no caller proves a semantic owner or function name.
bool Rva00570DC0()
{
	return false;
}
