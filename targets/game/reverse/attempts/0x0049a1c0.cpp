// ?bfmeDuplicateInto@Gen_0049A070@@QAE?AVRva00499F30Result@@XZ
// partial score=0.2121 date=2026-10-09
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib
// stlport
// Retail 0x0049A1C0, 99 bytes. Allocates a copy of *this via operator new
// (size 0xC, matching Gen_0049A070's layout) and the matched copy ctor at
// 0x0049A070, then stores the result through a caller-supplied out-pointer.
// No named caller or emitter recovers a real identity; the class itself
// (Gen_0049A070, BfmeWideCopyVY.cpp) is already an address-derived shim.

class BfmeWideVY
{
public:
	BfmeWideVY(const BfmeWideVY &other);
	~BfmeWideVY(void);

private:
	unsigned short *m_bfmeData;
};

class BfmeGuardVY
{
public:
	~BfmeGuardVY(void);
};

class Gen_0049A070;
class Rva00499F30Result {
public:
    Rva00499F30Result(Gen_0049A070 *p) : m_ptr(p) {}
    ~Rva00499F30Result();
    Gen_0049A070 *m_ptr;
};
class Gen_0049A070 : public BfmeGuardVY
{
public:
	Gen_0049A070(const Gen_0049A070 &other);
	Rva00499F30Result bfmeDuplicateInto();

	int *m_bfmeVtable;					// +0x00
	BfmeWideVY m_bfmeText;					// +0x04
	int m_bfmeValue;					// +0x08
};

// Open BFME 2 donor Code/Libraries/Source/WWVegas/WW3D2/Rva0015b110Cluster.cpp.
Rva00499F30Result Gen_0049A070::bfmeDuplicateInto() {
    Rva00499F30Result temp(new Gen_0049A070(*this));
    return temp;
}
