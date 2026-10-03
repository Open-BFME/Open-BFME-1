// Open-BFME5: clean C++ conversion of the transformed-threshold comparison.

// Retail calls the transformed-value helper through the incremental-link
// thunk at RVA 0x000190AB, whose body is the matched thunk
// `void j_000190ab(void)` (game/gen_small/thunks_011.cpp); the thunk ignores
// its arguments, so the stdcall signature the helper is given here only
// describes the pushes retail makes before the jump.
extern void j_000190ab();

class Rva007E4AA0Threshold
{
public:
	bool isBelowTransformed(int value) const;

private:
	char m_pad00[0x4C];
	int m_threshold;
};

bool Rva007E4AA0Threshold::isBelowTransformed(int value) const
{
	return m_threshold < ((int(__stdcall *)(int))j_000190ab)(value);
}
