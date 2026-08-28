// cl: /O2 /Ob0

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/UnicodeString.h
class UnicodeString
{
protected:
	void releaseBuffer();

	friend void __stdcall rva0042f160(UnicodeString other);
};

void __stdcall rva0042f160(UnicodeString other)
{
	other.releaseBuffer();
}
