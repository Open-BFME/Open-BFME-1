// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// Retail 0x005F5430 is a one-byte empty body. The carved boundary proves the
// extent, but no caller or owner proves a semantic function name.

__declspec(noinline) void Rva005F5430()
{
}

// Retail 0x005F5440 is another one-byte empty body.  Its carved boundary and
// one generated thunk caller prove the extent, but no owner proves a semantic
// name.
__declspec(noinline) void Rva005F5440()
{
}
