// cl: /DNDEBUG /MD /EHsc

class AudioEventRTS
{
public:
	virtual ~AudioEventRTS();
};

class Rva0002671FAudioEventRTSDestructorThunk
{
public:
	void forward();
};

void Rva0002671FAudioEventRTSDestructorThunk::forward()
{
	AudioEventRTS *event = (AudioEventRTS *)this;
	event->AudioEventRTS::~AudioEventRTS();
}
