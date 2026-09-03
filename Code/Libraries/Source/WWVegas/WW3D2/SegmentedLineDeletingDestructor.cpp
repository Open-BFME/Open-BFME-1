// cl: /DNDEBUG /MD /EHsc

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/segline.h
class SegmentedLineClass
{
public:
	virtual ~SegmentedLineClass();
};

__declspec(noinline) SegmentedLineClass::~SegmentedLineClass() {}

void Force_SegmentedLine_Deleting_Destructor(SegmentedLineClass *line)
{
	delete line;
}
