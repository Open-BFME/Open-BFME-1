// cl: /DNDEBUG /MD /EHsc

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
