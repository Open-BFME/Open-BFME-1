// cl: /O2 /Ob0

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/UnicodeString.h
class UnicodeString
{
protected:
	void releaseBuffer();

	friend void __stdcall rva00558d90(int, UnicodeString);
};

void __stdcall rva00558d90(int, UnicodeString other)
{
	other.releaseBuffer();
}
