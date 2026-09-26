// cl: /DNDEBUG /MD /EHsc
// stlport
#include "../../Include/GameClient/Video.h"
#include <vector>

// Retail VideoPlayer vtable 0x0112CCC0 slot 15 (+0x3c) points here.
// INI::parseVideoDefinition at 0x000C3480 calls this slot with its 28-byte
// Video record. The global table is also used by removeVideo and getVideo.
extern _STL::vector<Video> Rva0130B19CVideoTable;

class VideoPlayer
{
public:
    virtual void addVideo(Video *video);
};

void VideoPlayer::addVideo(Video *video)
{
    for (_STL::vector<Video>::iterator it = Rva0130B19CVideoTable.begin();
         it != Rva0130B19CVideoTable.end(); ++it)
    {
        if (it->m_internalName.compare(video->m_internalName) == 0)
        {
            *it = *video;
            return;
        }
    }

    Rva0130B19CVideoTable.push_back(*video);
}
