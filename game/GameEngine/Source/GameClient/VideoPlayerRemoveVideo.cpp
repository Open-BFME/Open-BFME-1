// cl: /DNDEBUG /MD /EHsc
// stlport
#include "../../Include/GameClient/Video.h"
#include <vector>

// Retail 0x0081CF40 uses the same global 28-byte Video table as the
// landed getVideo queries. The upstream removeVideo loop identifies the
// operation; BFME keeps this table globally rather than in the player.
// VideoPlayer vtable 0x0112CCC0 slot 16 (+0x40) points at this body.
// The existing VideoPlayer destructor installs that table; the neighboring
// slot 19 is the already matched VideoPlayer::getVideo(AsciiString).
extern _STL::vector<Video> Rva0130B19CVideoTable;

class VideoPlayer
{
public:
    virtual void removeVideo(Video *video);
};

void VideoPlayer::removeVideo(Video *video)
{
    for (_STL::vector<Video>::iterator it = Rva0130B19CVideoTable.begin();
         it != Rva0130B19CVideoTable.end(); ++it)
    {
        if (it->m_internalName.compare(video->m_internalName) == 0)
        {
            Rva0130B19CVideoTable.erase(it);
            return;
        }
    }
}
