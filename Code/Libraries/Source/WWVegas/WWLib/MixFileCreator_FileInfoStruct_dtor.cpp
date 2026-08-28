// cl: /DNDEBUG /MD /EHsc

// MixFileCreator::FileInfoStruct's destructor, retail 0x003F6EA0. Seventeen
// bytes: the buffer at +0x00 is released back to the pool at 0x012F1094, and a
// struct that never got one is left alone.

class MixFileInfoBuffer
{
public:
	void releaseInto( void *pool );
};

extern int TheMixFileInfoPool;				// 0x012F1094

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib/mixfile.h
class MixFileCreator
{
public:
	// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib/mixfile.h
	struct FileInfoStruct
	{
		~FileInfoStruct();

		MixFileInfoBuffer *m_buffer;		// +0x00
	};
};

// ??1FileInfoStruct@MixFileCreator@@QAE@XZ
MixFileCreator::FileInfoStruct::~FileInfoStruct()
{
	if( m_buffer )
		m_buffer->releaseInto( &TheMixFileInfoPool );
}
