// cl: /DNDEBUG /MD /EHsc
// Open-BFME: S4ModuleData00116D80::S4ModuleData00116D80, retail 0x0024F390,
// 28 bytes.
//
// The same shape as S4ModuleData00116640 three kilobytes earlier: run
// ContestableContainModuleData, put this class's own vftable down, and set the
// word at +0x1A8. Here it is a float, 0.5.

typedef float Real;

// Retail's base ctor is the 5-byte ILT thunk at 0x00031142
// (?j_00031142@@YAXXZ), defined only as j_00031142 in
// game/gen_small/thunks_023.cpp, so the mem-init below is a direct call to
// that thunk with ecx == this.
void j_00031142();

class ContestableContainModuleData
{
public:
	// Retail installs this class's own vftable right after the thunk call, so
	// this local view of the base deliberately carries no virtual function: a
	// base vptr store of its own would be wrong bytes.  Virtualness, and with
	// it the vftable this ctor installs, lives on the derived class below.
	ContestableContainModuleData()
	{
		j_00031142();
	}

private:
	unsigned char m_unmodelled_004[0x1A8 - 0x04];
};

class S4ModuleData00116D80 : public ContestableContainModuleData
{
public:
	S4ModuleData00116D80();

	virtual ~S4ModuleData00116D80();

	Real m_fraction;					// +0x1A8
};

S4ModuleData00116D80::S4ModuleData00116D80()
{
	m_fraction = 0.5f;
}
