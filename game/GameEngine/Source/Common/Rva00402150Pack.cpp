// cl: /O2 /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD

unsigned __stdcall rva00402150Pack(unsigned short hi, unsigned short lo)
{
	return ((unsigned)hi << 16) | lo;
}
