// cl: /O2 /MD
// Retail 0x00C6B140 is the namespace-scope dynamic initializer for the
// ShellGameLoadScreen global at 0x012F0770: default-constructs it and
// registers the TU-local atexit cleanup. Defining the global here lets MSVC
// emit those bytes as its compiler-local _$E1; the ledger row names that
// COFF symbol via object-symbol=_$E1. The constructor and destructor are
// only declared here (defined by LoadScreen.cpp's ledgered bodies), so this
// TU emits no named function of its own.
// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/LoadScreen.h
class ShellGameLoadScreen
{
public:
	ShellGameLoadScreen();
	virtual ~ShellGameLoadScreen();
	void *m_loadScreen;
	void *m_progressBar;
};
ShellGameLoadScreen g_rva012F0770;
