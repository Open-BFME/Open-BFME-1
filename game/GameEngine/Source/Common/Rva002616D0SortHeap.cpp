// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Iinputs/reference/shims/campaignmanagerascii /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Igame/Libraries/Source/WWVegas/WWLib

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
