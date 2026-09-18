// cl: /O2

// The retail body at 0x003D6200 returns through its one four-byte stack
// argument without reading it. The thunk at ILT 0x00032C4F reaches this body.

// ?Rva003D6200@@YGXPAX@Z
void __stdcall Rva003D6200(void *)
{
}
