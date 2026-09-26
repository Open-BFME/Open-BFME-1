// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// Retail 0x00958600: BFME's buffered FrameGrabClass frame accessor.

// TU-scoped BFME FrameGrabClass ABI.  The shared reference header describes
// the older Generals object and cannot represent BFME's buffered frame ring.
class FrameGrabClass
{
public:
	enum MODE
	{
		RAW,
		AVI
	};

	FrameGrabClass(const char *filename, MODE mode, int width, int height,
		int bitdepth, float framerate);
	FrameGrabClass(const char *filename, int width, int height, int bitdepth,
		float framerate, int buffer_count, bool compressed);
	virtual ~FrameGrabClass();

	long *GetBuffer();
	float GetFrameRate() { return FrameRate; }

protected:
	// Address-derived spelling: no surviving named caller proves the original.
	void Rva00958570_Flush_Buffered_Frames();

	int FrameSize;
	union
	{
		int BufferCount;
		float FrameRate;
	};
	long *Buffer;
	int WrittenFrames;
	int BufferedFrames;
	void *AVIFile;
	void *AVIStream;
};

long *FrameGrabClass::GetBuffer()
{
	if (BufferedFrames >= BufferCount)
	{
		Rva00958570_Flush_Buffered_Frames();
	}

	int frame = BufferedFrames;
	int frame_size = FrameSize;
	long *buffer = Buffer;
	long *result = (long *)((char *)buffer + frame_size * frame);
	++BufferedFrames;
	return result;
}
