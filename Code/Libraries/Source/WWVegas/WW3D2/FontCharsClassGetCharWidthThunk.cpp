// cl: /DNDEBUG /MD /EHsc
// readable body of ?Get_Char_Width@FontCharsClass@@QAEHG@Z: Code/Libraries/Source/WWVegas/WW3D2/render2dsentence.cpp

// Get_Char_Data returns a pointer to the per-character record. The vendored
// render2dsentence.h declares FontCharsClassCharDataStruct as
//   WCHAR Value; short Width; uint16* Buffer;
// which would put Width at offset 2. Retail instead reads Width from
// offset+4, so the real record carries two bytes we don't have a name for
// between Value and Width (this is the "changed constant / extra member"
// gap the work packet points at). Only Width is ever touched here, so a
// local replica with the extra padding is enough to reproduce retail
// byte-for-byte without editing the shared vendored header.
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/render2dsentence.h
struct FontCharsClassCharDataStruct
{
	unsigned short Value;
	unsigned short Unknown04;
	short Width;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/render2dsentence.h
class FontCharsClass
{
public:
	const FontCharsClassCharDataStruct * Get_Char_Data(unsigned short ch);
	int Get_Char_Width(unsigned short ch);
};

// ?Get_Char_Width@FontCharsClass@@QAEHG@Z
int FontCharsClass::Get_Char_Width(unsigned short ch)
{
	const FontCharsClassCharDataStruct *data = Get_Char_Data(ch);
	if (data != 0)
	{
		return data->Width;
	}

	return 0;
}
