// cl: /DNDEBUG /MD /EHsc

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/hlod.h
class HLodDefClass
{
public:
	// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/hlod.h
	class SubObjectArrayClass
	{
	public:
		~SubObjectArrayClass() throw();
	};

	~HLodDefClass();

private:
	void Free();
	unsigned char m_unreconstructed[0x10];
	SubObjectArrayClass m_aggregates;
};

HLodDefClass::~HLodDefClass()
{
	Free();
}
