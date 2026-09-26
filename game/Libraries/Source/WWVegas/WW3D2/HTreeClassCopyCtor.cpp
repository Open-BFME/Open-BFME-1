// cl: /DNDEBUG /MD /EHsc
// Clean C++ recovery of HTreeClass's retail copy constructor.
//
// The retail BFME ABI constructs a 0xB4-byte PivotClass array without an
// array cookie, then calls PivotClass::operator= for each element.  This TU
// keeps that ABI overlay local: the full WW3D2 header's inline destructor
// selects a different cookie-bearing new[] shape, while these declarations
// retain the real field offsets and the already-matched PivotClass callees.
// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/htree.h

struct PivotClass
{
public:
	PivotClass();
	PivotClass& operator=(const PivotClass&);

	char Name[16];
	PivotClass *Parent;
	unsigned char m_data[0x90];
	int Index;
	unsigned char m_tail[0x0c];
};

class HTreeClass
{
public:
	HTreeClass(const HTreeClass &);

private:
	char Name[16];
	int NumPivots;
	PivotClass *Pivot;
	float ScaleFactor;
};

extern "C" void *memcpy(void *destination, const void *source, unsigned int count);

HTreeClass::HTreeClass(const HTreeClass & src) :
	NumPivots(0),
	Pivot(0),
	ScaleFactor(1.0f)
{
	memcpy(&Name,&src.Name,sizeof(Name));

	NumPivots = src.NumPivots;
	if (NumPivots > 0) {
		Pivot = new PivotClass[NumPivots];
	}

	for (int pi = 0; pi < NumPivots; pi++) {
		Pivot[pi] = src.Pivot[pi];

		if (src.Pivot[pi].Parent != 0) {
			Pivot[pi].Parent = &(Pivot[src.Pivot[pi].Parent->Index]);
		} else {
			Pivot[pi].Parent = 0;
		}
	}

	ScaleFactor = src.ScaleFactor;
}
