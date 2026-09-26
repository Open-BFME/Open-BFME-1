// cl: /DNDEBUG /MD /EHsc
// Scalar wrapper 0x002C2400 calls GiantBirdNested::~GiantBirdNested through ILT 0x000357A6.

class GiantBirdNested
{
public:
	virtual ~GiantBirdNested();
};

__declspec(noinline) GiantBirdNested::~GiantBirdNested() {}

void Force_GiantBirdNested_Deleting_Destructor(GiantBirdNested *nested)
{
	delete nested;
}
