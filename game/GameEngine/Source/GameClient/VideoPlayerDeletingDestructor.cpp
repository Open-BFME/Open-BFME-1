// cl: /DNDEBUG /MD /EHsc

class VideoPlayer
{
public:
	virtual ~VideoPlayer();
};

__declspec(noinline) VideoPlayer::~VideoPlayer() {}

void Force_VideoPlayer_Deleting_Destructor(VideoPlayer *p)
{
	delete p;
}
