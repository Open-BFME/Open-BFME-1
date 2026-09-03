// cl: /DNDEBUG /MD /EHsc

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/dx8caps.h
class DX8Caps
{
public:
	~DX8Caps();
};

void Force_DX8Caps_Deleting_Destructor(DX8Caps *caps)
{
	delete caps;
}
