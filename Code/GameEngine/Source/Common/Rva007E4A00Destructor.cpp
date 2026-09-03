// ??1Rva007E4A00@@QAE@XZ present-unmatched
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

extern "C" void *bfmeVft1050F[];

class Gen009A4D60_0081C330
{
public:
	void gen009A4D60( void );
	void gen0081C330( void );
};

class VideoPlayer
{
public:
	virtual ~VideoPlayer( void );
};

class Rva007E4A00 : public VideoPlayer
{
public:
	virtual ~Rva007E4A00( void );
};

Rva007E4A00::~Rva007E4A00( void )
{
	((Gen009A4D60_0081C330 *)this)->gen009A4D60();
	((Gen009A4D60_0081C330 *)this)->gen0081C330();
}
