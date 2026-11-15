// cl: /DNDEBUG /MD /EHsc

// Retail 0x00710E30. Store a byte into a global. cdecl (ret not ret 4).

// dir32_addresses.csv records this datum as ?HighlightRendering@@3_NA at
// VA 0x0133F42C (retail zero-filled .data); the byte-true setter, getter and
// filter consumers all reference that recorded name.

bool HighlightRendering;

// ?set_00710e30@@YAX_N@Z
void set_00710e30(bool v)
{
	HighlightRendering = v;
}
