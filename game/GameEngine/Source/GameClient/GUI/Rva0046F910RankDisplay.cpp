// cl: /DNDEBUG /MD /EHsc

class AsciiString
{
public:
	AsciiString( const char *text );
	~AsciiString()
	{
		releaseBuffer();
	}

	const char *str() const
	{
		return m_data ? (const char *)m_data + 8 : (const char *)0x0107388B;
	}

private:
	void releaseBuffer();
	void *m_data;
};

class Image;

class MappedImageCollection
{
public:
	const Image *findImageByName( const AsciiString &name );
};

extern MappedImageCollection *TheMappedImageCollection;

extern "C" __declspec( dllimport ) int __cdecl sprintf(
	char *buffer, const char *format, ... );

int __cdecl Rva0046F910( int rank, AsciiString *side )
{
	char imageNameBuffer[ 256 ];
	int image;

	sprintf( imageNameBuffer, "AptRankIcon%s%d", side->str(), rank );
	{
		AsciiString imageName( imageNameBuffer );
		image = (int)TheMappedImageCollection->findImageByName( imageName );
	}
	if ( image != 0 )
		return image;

	sprintf( imageNameBuffer, "AptRankIcon%d", rank );
	{
		AsciiString fallbackImageName( imageNameBuffer );
		return (int)TheMappedImageCollection->findImageByName( fallbackImageName );
	}
}
