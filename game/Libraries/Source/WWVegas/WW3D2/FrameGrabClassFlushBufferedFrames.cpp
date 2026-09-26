// cl: /DNDEBUG /MD /EHs-c-

extern void ji_00afd528();

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

typedef int (__stdcall *AviStreamWrite)( void *stream, long start,
	long samples, void *buffer, long bytes, long flags,
	long *samples_written, long *bytes_written );

// Address-derived spelling: the body is proven to flush FrameGrabClass's
// buffered frames, but no surviving named caller proves the historical name.
void FrameGrabClass::Rva00958570_Flush_Buffered_Frames()
{
	if( AVIStream != 0 && Buffer != 0 )
	{
		register int frame = 0;
		if( BufferedFrames > 0 )
		{
			int (__cdecl *format)( char *, const char *, ... ) =
				*(int (__cdecl **)( char *, const char *, ... ))0x0135948C;
			void (__stdcall *print)( const char * ) =
				*(void (__stdcall **)( const char * ))0x01358EA8;
			char error[ 0x100 ];
			for( ; frame < BufferedFrames; ++frame )
			{
				int result = ((AviStreamWrite)ji_00afd528)( AVIStream,
					WrittenFrames + frame, 1,
					(char *)Buffer + FrameSize * frame,
					FrameSize, 0x10, 0, 0 );
				if( result != 0 )
				{
					format( error, "avi write error %x/%d\n", result, result );
					print( error );
				}
			}
		}
	}

	int count = BufferedFrames;
	WrittenFrames += count;
	BufferedFrames = 0;
}
