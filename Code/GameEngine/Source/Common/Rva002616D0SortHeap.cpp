// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/campaignmanagerascii /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WWLib

struct Gen8ByteElement
{
	int m_00;
	int m_04;
};

typedef bool ( *Gen8ByteElementLess )(
	const Gen8ByteElement &, const Gen8ByteElement & );

void GenAdjust00260D80( Gen8ByteElement *first, int holeIndex, int len,
	Gen8ByteElement value, Gen8ByteElementLess compare );

void gen002616d0( void *firstArgument, void *lastArgument, void *compareArgument )
{
	Gen8ByteElement *first = (Gen8ByteElement *)firstArgument;
	Gen8ByteElement *last = (Gen8ByteElement *)lastArgument;
	Gen8ByteElementLess compare = (Gen8ByteElementLess)compareArgument;

	while( last - first > 1 )
	{
		Gen8ByteElement value = *( last - 1 );
		*( last - 1 ) = *first;
		GenAdjust00260D80( first, 0, (int)( ( last - 1 ) - first ), value, compare );
		--last;
	}
}
