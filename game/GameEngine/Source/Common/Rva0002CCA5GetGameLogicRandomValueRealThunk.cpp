// Retail RVA 0x0002CCA5 is a five-byte tail jump to the matched
// GetGameLogicRandomValueReal body at RVA 0x00096DD0.
// The retail ILT pin and its callers prove this forwarding identity.
// cl: /DNDEBUG /MD /EHsc /O2

extern float rva0002cca5Target(float low, float high, char *file, int line);

#pragma comment(linker, "/alternatename:?rva0002cca5Target@@YAMMMPADH@Z=?GetGameLogicRandomValueReal@@YAMMMPADH@Z")

float Rva0002CCA5GetGameLogicRandomValueRealThunk(
	float low, float high, char *file, int line)
{
	return rva0002cca5Target(low, high, file, line);
}
