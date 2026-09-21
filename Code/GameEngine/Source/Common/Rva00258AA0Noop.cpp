// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

// The carved boundary at 0x00258AA0 contains only a return.
void Rva00258AA0Noop()
{
}

// A separate carved return boundary reached through the generated thunk at
// 0x000025C2. Its address-qualified name deliberately makes no owner claim.
void Rva00258AD0Noop()
{
}
