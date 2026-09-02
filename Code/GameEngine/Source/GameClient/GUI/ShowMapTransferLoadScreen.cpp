// cl: /DNDEBUG /MD /EHsc
//
// Retail 0x00510A10: create the APT-era MapTransfer load screen singleton at
// 0x012F496C.  Returns false if it already exists; otherwise drops any live
// window layout and constructs the 0x58-byte screen from the incoming
// context.  Always returns true after the allocation attempt.

class WindowLayout;

void ReleaseWindowLayout( WindowLayout *layout );

// APT-era FileTransfer load screen; 0x58 bytes.  Distinct from the ZH
// MapTransferLoadScreen at 0x0049xxxx.
class BfmeAptScreenMapTransfer
{
public:
	BfmeAptScreenMapTransfer( void *context );

private:
	char m_unmodelled[ 0x58 ];
};

extern BfmeAptScreenMapTransfer *TheBfmeAptScreenMapTransfer;

// ?_bfme_showMapTransferLoadScreen@@YA_NPAX@Z
bool _bfme_showMapTransferLoadScreen( void *context )
{
	if( !TheBfmeAptScreenMapTransfer )
	{
		ReleaseWindowLayout( 0 );
		TheBfmeAptScreenMapTransfer = new BfmeAptScreenMapTransfer( context );
		return true;
	}
	return false;
}
