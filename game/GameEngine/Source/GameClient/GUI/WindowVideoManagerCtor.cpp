// cl: /Igame/GameEngine/Include /DNDEBUG /DWIN32 /MD /EHsc /Iinputs/reference/shims/zhcanonascii /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Igame/GameEngine/Source/Common/System /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /D_STLP_USE_STATIC_LIB /Igame/Libraries/Source/WWVegas/WWLib /D_STLP_USE_NEWALLOC 
// stlport
/*
**	Command & Conquer Generals(tm)
**	Copyright 2025 Electronic Arts Inc.
**
**	This program is free software: you can redistribute it and/or modify
**	it under the terms of the GNU General Public License as published by
**	the Free Software Foundation, either version 3 of the License, or
**	(at your option) any later version.
**
**	This program is distributed in the hope that it will be useful,
**	but WITHOUT ANY WARRANTY; without even the implied warranty of
**	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**	GNU General Public License for more details.
**
**	You should have received a copy of the GNU General Public License
**	along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

// WindowVideoManager's constructor, verbatim from the Zero Hour reference
// (GameClient/GUI/WindowVideoManager.cpp). It is carried in its own TU for the
// same reason as the other *Ctor.cpp files here: retail linked the STLport
// static library, so the map's node allocation is a direct call, and that only
// reproduces with /D_STLP_USE_STATIC_LIB.

// BFME's canonical string/subsystem types retain its by-value copy ABI.
typedef bool Bool;
typedef int Int;
typedef unsigned int UnsignedInt;
#include <hash_map>
#include <map>
#include "../../../../Libraries/Source/WWVegas/WWLib/ascii_string.h"
#include "../../Common/System/subsystem_interface.h"
#include "../window_video_manager.h"

WindowVideoManager::WindowVideoManager( void )
{
	WindowVideoMap::iterator it = m_playingVideos.begin();
	while(it != m_playingVideos.end())
	{
		WindowVideo *winVid = it->second;
		if(winVid)
			delete winVid;
		it++;
	}
	m_playingVideos.clear();
	
	m_stopAllMovies = false;
	m_pauseAllMovies = false;

}


// BFME1's constructor owns 20 bytes; the covered ZH header describes 24.
// Keep storage opaque across the verified constructor and init thunk ABIs.
// A local guard implements the native new-expression cleanup lifetime.
class Rva004991D0ConstructorReceiver {};
class WindowVideoAllocationGuard004991D0
{
public:
    __forceinline WindowVideoAllocationGuard004991D0(void *p) : m_storage(p) {}
    __forceinline ~WindowVideoAllocationGuard004991D0() { if (m_storage) ::operator delete(m_storage); }
    __forceinline void release() { m_storage = 0; }
private:
    void *m_storage;
};
extern void j_0002a685();

class VideoPlayer;
class Display;
extern VideoPlayer *TheVideoPlayer;
extern Display *TheDisplay;
extern void j_00027a2f();

template<int N> class Rva004991D0Slots : public Rva004991D0Slots<N - 1>
{
public: virtual void slot(char (*)[N]);
};
template<> class Rva004991D0Slots<0> {};
class Rva004991D0Player : public Rva004991D0Slots<12>
{
public: virtual VideoBuffer *open(AsciiString, int);
};
class Rva004991D0Display : public Rva004991D0Slots<33>
{
public: virtual void *createVideoBuffer(bool);
};
class Rva004991D0Stream : public Rva004991D0Slots<7>
{
public:
    virtual void close();
    virtual void slot08(); virtual void slot09(); virtual void slot10();
    virtual void slot11(); virtual void slot12(); virtual void slot13();
    virtual bool attach(void *);
};
enum Gen_e_00498c40 { Rva004991D0MappedZero = 0 };
namespace _STL {
template<> Gen_e_00498c40 &hash_map<int, Gen_e_00498c40>::operator[](const int &);
}

void WindowVideoManager::playMovie(GameWindow *win, AsciiString movieName,
                                  WindowVideoPlayType playType)
{
    stopAndRemoveMovie(win);
    VideoBuffer *videoStream =
        reinterpret_cast<Rva004991D0Player *>(TheVideoPlayer)->open(movieName, 0);
    if (!videoStream)
        return;
    Rva004991D0Stream *stream = reinterpret_cast<Rva004991D0Stream *>(videoStream);
    if (!stream->attach(
            reinterpret_cast<Rva004991D0Display *>(TheDisplay)->createVideoBuffer(false))) {
        stream->close();
        return;
    }
    WindowVideo *winVid;
    {
        void *storage = ::operator new(20);
        WindowVideoAllocationGuard004991D0 guard(storage);
        if (storage) {
            typedef WindowVideo *(Rva004991D0ConstructorReceiver::*Construct)();
            union { void (*entry)(); Construct method; } construct;
            construct.entry = j_0002a685;
            winVid = (reinterpret_cast<Rva004991D0ConstructorReceiver *>(storage)->*construct.method)();
        } else {
            winVid = 0;
        }
        guard.release();
    }

    typedef void (WindowVideo::*BFMEInit)(GameWindow *, AsciiString,
                                         WindowVideoPlayType, VideoBuffer *);
    union { void (*entry)(); BFMEInit method; } init;
    init.entry = j_00027a2f;
    (winVid->*init.method)(win, movieName, playType, videoStream);
    reinterpret_cast<_STL::hash_map<int, Gen_e_00498c40> &>(m_playingVideos)
        [(const int &)win] = (Gen_e_00498c40)(int)winVid;
    m_pauseAllMovies = false;
    m_stopAllMovies = false;
}
