// ?d_0049a1c0@@YAXXZ
// partial score=0.55 date=2026-09-10
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib
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

class Gen_0049A070 : public BfmeGuardVY
{
public:
	Gen_0049A070(const Gen_0049A070 &other);
	Gen_0049A070 **bfmeDuplicateInto(Gen_0049A070 **result);

	int *m_bfmeVtable;					// +0x00
	BfmeWideVY m_bfmeText;					// +0x04
	int m_bfmeValue;					// +0x08
};

// ?bfmeDuplicateInto@Gen_0049A070@@QAEPAPAV1@PAPAV1@@Z present-unmatched
Gen_0049A070 **Gen_0049A070::bfmeDuplicateInto(Gen_0049A070 **result)
{
	Gen_0049A070 *temp = new Gen_0049A070(*this);
	*result = temp;
	return result;
}
