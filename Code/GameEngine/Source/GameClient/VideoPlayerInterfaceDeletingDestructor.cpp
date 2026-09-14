// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME5: VideoPlayerInterface scalar-deleting destructor at retail RVA
// 0x0081C530 (30 bytes).  The adjacent matched constructor and complete
// destructor at 0x0081C500/0x0081C520 install the base-interface vtable
// 0x0112CC60; VideoPlayer::~VideoPlayer later restores this same vtable before
// chaining through the interface destructor to SubsystemInterface.

class VideoPlayerInterface
{
public:
	virtual ~VideoPlayerInterface();
};

void forceVideoPlayerInterfaceDeletingDestructor()
{
	VideoPlayerInterface value;
}
