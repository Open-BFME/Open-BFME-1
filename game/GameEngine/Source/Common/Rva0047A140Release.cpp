// cl: /O2 /Ob0

class UnicodeString;

// The release is the wide StringBase body at 0x008881D0.
template <typename T>
class StringBase
{
	void releaseBuffer();

	friend void __stdcall rva0047a140(int, UnicodeString, int, int, int, int, int);
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/UnicodeString.h
class UnicodeString : public StringBase<unsigned short>
{
};

void __stdcall rva0047a140(int, UnicodeString other, int, int, int, int, int)
{
	other.StringBase<unsigned short>::releaseBuffer();
}
