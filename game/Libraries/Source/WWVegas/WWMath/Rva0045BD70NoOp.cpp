// cl: /O2 /Ob2 /DNDEBUG /MD /GX- /EHs-c-

// The carved boundary at 0x0045BD70 contains only ret 4. The export and
// incremental-link thunk do not agree on a semantic owner, so this source
// keeps the address-derived owner and records the one stack argument shown by
// the instruction.

class Rva0045BD70
{
public:
	void reset(unsigned int value);
};

void Rva0045BD70::reset(unsigned int value)
{
}
