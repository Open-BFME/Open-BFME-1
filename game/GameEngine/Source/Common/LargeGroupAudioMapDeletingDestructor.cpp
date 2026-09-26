// cl: /DNDEBUG /MD /EHsc
// Scalar wrapper 0x003D2F10 calls LargeGroupAudioMap::~LargeGroupAudioMap through ILT 0x00019B19.

class LargeGroupAudioMap
{
public:
	virtual ~LargeGroupAudioMap();
};

__declspec(noinline) LargeGroupAudioMap::~LargeGroupAudioMap() {}

void Force_LargeGroupAudioMap_Deleting_Destructor(LargeGroupAudioMap *map)
{
	delete map;
}
