// cl: /O2 /DNDEBUG /MD
// Retail 0x00205E50 copies the first fastcall argument to EAX and returns.
// The carved body and its generated thunk do not prove a semantic owner.
// The symbol therefore keeps its address.

extern "C" int __fastcall Rva00205E50(int value)
{
	return value;
}
