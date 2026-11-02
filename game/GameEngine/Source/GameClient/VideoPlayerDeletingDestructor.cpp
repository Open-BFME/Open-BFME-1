// cl: /DNDEBUG /MD /EHsc

class VideoPlayer
{
	friend void forceVideoPlayerDeletingDestructorCopy(const VideoPlayer &that);
public:
	virtual ~VideoPlayer();
};


void Force_VideoPlayer_Deleting_Destructor(VideoPlayer *p)
{
	delete p;
}

// ~VideoPlayer is matched out of line (VideoPlayerDestructorThunk.cpp). The implicit copy constructor (no
// retail twin) emits the vftable and with it ??_G without a second destructor body.
void forceVideoPlayerDeletingDestructorCopy(const VideoPlayer &that)
{
	VideoPlayer value(that);
}
