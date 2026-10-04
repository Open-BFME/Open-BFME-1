// Retail RVA 0x0002CCA5 is a five-byte tail jump to the matched
// GetGameLogicRandomValueReal body at RVA 0x00096DD0.
// The retail ILT pin and its callers prove this forwarding identity.
// cl: /DNDEBUG /MD /EHsc /O2

// Real body at RVA 0x00096DD0; declared here as float so the definition and
// callers share one identity (Real is a typedef for float).
extern float GetGameLogicRandomValueReal(float low, float high, char *file, int line);

float Rva0002CCA5GetGameLogicRandomValueRealThunk(
	float low, float high, char *file, int line)
{
	return GetGameLogicRandomValueReal(low, high, file, line);
}
