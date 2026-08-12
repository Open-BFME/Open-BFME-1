// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: lift MASM dump to standalone C++ thunk.

class Object;

class ObjectDefectionWakeFrameShim
{
public:
    void setWakeFrame(Object *, unsigned int);
};

class ObjectDefectionHelper
{
    unsigned char padding0[8];
    Object *object;
    unsigned char padding1[20];
    unsigned int detectionStart;
    unsigned int detectionEnd;
    unsigned int unknown;
    bool doDefectorFX;

public:
	void startDefectionTimer(unsigned int, bool);
};

// ?startDefectionTimer@ObjectDefectionHelper@@QAEXI_N@Z
void ObjectDefectionHelper::startDefectionTimer(unsigned int numFrames, bool withDefectorFX)
{
	if (!(reinterpret_cast<const unsigned char *>(object)[0x344] & 2)) {
		reinterpret_cast<ObjectDefectionWakeFrameShim *>(this)->setWakeFrame(object, 0x3fffffff);
		return;
	}

	unsigned int now = *reinterpret_cast<const unsigned int *>(
		*reinterpret_cast<const unsigned int *>(0x012f0898) + 0x3c);
	detectionStart = now;
	detectionEnd = now + numFrames;
	unknown = 0;
	doDefectorFX = withDefectorFX;
	reinterpret_cast<ObjectDefectionWakeFrameShim *>(this)->setWakeFrame(object, 1);
}
