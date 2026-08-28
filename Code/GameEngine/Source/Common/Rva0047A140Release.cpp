// cl: /O2 /Ob0

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/UnicodeString.h
class UnicodeString
{
protected:
	void releaseBuffer();

	friend void __stdcall rva0047a140(int, UnicodeString, int, int, int, int, int);
};

void __stdcall rva0047a140(int, UnicodeString other, int, int, int, int, int)
{
	other.releaseBuffer();
}
