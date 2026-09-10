// ?init@VideoPlayer@@UAEXXZ
// partial score=0.62 date=2026-09-10
// cl: /DNDEBUG /MD /EHsc /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib
// stlport
/*
**	Command & Conquer Generals Zero Hour(tm)
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

////////////////////////////////////////////////////////////////////////////////
//																																						//
//  (c) 2001-2003 Electronic Arts Inc.																				//
//																																						//
////////////////////////////////////////////////////////////////////////////////

//----------------------------------------------------------------------------
//                                                                          
//                       Westwood Studios Pacific.                          
//                                                                          
//                       Confidential Information                           
//                Copyright (C) 2001 - All Rights Reserved                  
//                                                                          
//----------------------------------------------------------------------------
//
// Project:   Generals
//
// Module:    GameClient
//
// File name: VideoPlayer.cpp
//
// Created:   10/22/01	TR
//
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
//         Includes                                                      
//----------------------------------------------------------------------------

#include "PreRTS.h"	// This must go first in EVERY cpp file int the GameEngine

#include "Lib/BaseType.h"
#include "GameClient/VideoPlayer.h"

// BFME adds the callback-taking INI entry point to the retail class.  The
// vendored ZH header only declares the three-argument entry point, so keep the
// independently pinned ABI view local to this TU rather than changing the
// shared header and every consumer of it.
typedef void (*BfmeVideoIniBlockParse)(INI *ini);

extern void parseSubtitle(INI *ini, void *, void *, const void *);

// The BFME INI object is 0x848 bytes.  The vendored ZH declaration is a much
// larger parser object, so use the retail-sized storage while retaining the
// exact constructor/destructor addresses already identified in the INI family.
class BfmeVideoIniStorage
{
public:
	BfmeVideoIniStorage(void);
	~BfmeVideoIniStorage(void);

	unsigned char m_storage[0x848];
};

// This is the BFME 0x1c-byte video record consumed by VideoPlayer::init.  The
// public ZH Video declaration is only the first three strings; the additional
// fields are visible at the retail loop's +0xc/+0x18 accesses and in the
// existing INI field parser reconstruction.
struct BfmeVideoRecord
{
	AsciiString m_filename;
	AsciiString m_internalName;
	AsciiString m_commentForWB;
	unsigned char m_isLooping;
	float m_volume;
	unsigned char m_isDefault;
	unsigned char m_padding[3];
	void *m_subtitleManager;
};

extern BfmeVideoRecord *g_bfmeVideoTableBegin; // retail 0x0130B19C
extern BfmeVideoRecord *g_bfmeVideoTableEnd;   // retail 0x0130B1A0

// The movie-path helper is implemented and pinned in
// Common/BfmeMoviePathAB.cpp.  These declarations preserve its proven object
// layout and its exact StringBaseNarrowAB/AsciiStringAB ABI.
class StringBaseNarrowAB
{
public:
	void __cdecl format(class AsciiStringAB text, ...);

protected:
	StringBaseNarrowAB(void) : m_bfmeNarrowAB(0) { }
	StringBaseNarrowAB(const char *text);
	StringBaseNarrowAB(const StringBaseNarrowAB &other);
	~StringBaseNarrowAB(void);

	char *m_bfmeNarrowAB;
};

class AsciiStringAB : public StringBaseNarrowAB
{
public:
	AsciiStringAB(void) { }
	AsciiStringAB(const char *text) : StringBaseNarrowAB(text) { }
	AsciiStringAB(const AsciiStringAB &other);
	~AsciiStringAB(void) { }

	const char *bfmeTextAB(void) const
	{
		return (m_bfmeNarrowAB != 0) ? m_bfmeNarrowAB + 8 : "";
	}
};

// A local ABI view is required because the vendored INI declaration has only
// the ZH three-argument load.  The member is pinned to BFME's callback-taking
// INI::load body after its exact ABI is verified.
class BfmeVideoLoadView
{
public:
	void load(AsciiStringAB filename, int loadType, void *xfer,
		BfmeVideoIniBlockParse parse);
};

class BfmeHookAB
{
public:
	void bfmeMakeNameAB(AsciiStringAB &out);

	char m_bfmePadAB[8];
	AsciiStringAB (__cdecl *m_bfmeFuncAB)(void);
};

// Retail calls StringBase<char>::concat(const char *, int) directly on the
// path object after the BFME movie-path helper fills it.  This declaration is
// the already pinned retail helper, not a local implementation.
template <typename T> class StringBase
{
public:
	struct Data
	{
		int m_refCount;
		unsigned short m_length;
		unsigned short m_capacity;
		T m_text[1];
	};

	StringBase(void) : m_data(0) { }
	StringBase(const StringBase<T> &other);
	StringBase(const T *text);
	~StringBase(void);
	void concat(const T *text, int length);

	Data *m_data;
};

inline StringBaseNarrowAB::StringBaseNarrowAB(const StringBaseNarrowAB &other)
{
	((StringBase<char> *)this)->StringBase<char>::StringBase(
		*(const StringBase<char> *)&other);
}

inline AsciiStringAB::AsciiStringAB(const AsciiStringAB &other)
	: StringBaseNarrowAB(other)
{
}

typedef class SubtitleEntry *(__cdecl *BfmeCreateSubtitleEntry)(
	AsciiString *, int, const AsciiString &, unsigned int, int, int, int, int, int);

class SubtitleManager
{
public:
	SubtitleManager(BfmeCreateSubtitleEntry createEntry, int second,
		const AsciiString &name);
};

struct BfmeVideoPlayerLayout
{
	unsigned char m_padding[0x0c];
	BfmeHookAB *m_moviePathHook;
	BfmeCreateSubtitleEntry m_createSubtitleEntry;
};

//----------------------------------------------------------------------------
//         Externals                                                     
//----------------------------------------------------------------------------



//----------------------------------------------------------------------------
//         Defines                                                         
//----------------------------------------------------------------------------



//----------------------------------------------------------------------------
//         Private Types                                                     
//----------------------------------------------------------------------------



//----------------------------------------------------------------------------
//         Private Data                                                      
//----------------------------------------------------------------------------

static unsigned char s_bfmeVideoInit;



//----------------------------------------------------------------------------
//         Public Data                                                      
//----------------------------------------------------------------------------

VideoPlayerInterface *TheVideoPlayer = NULL;

//----------------------------------------------------------------------------
//         Private Prototypes                                               
//----------------------------------------------------------------------------



//----------------------------------------------------------------------------
//         Private Functions                                               
//----------------------------------------------------------------------------



//----------------------------------------------------------------------------
//         Public Functions                                                
//----------------------------------------------------------------------------

//============================================================================
// VideoBuffer::VideoBuffer
//============================================================================

// ??0VideoBuffer@@QAE@W4Type@0@@Z present-unmatched
VideoBuffer::VideoBuffer( Type format)
: m_width(0),
	m_height(0),
	m_textureWidth(0),
	m_textureHeight(0),
	m_format(format),
	m_pitch(0),
	m_xPos(0),
	m_yPos(0)
{

	if ( m_format >= NUM_TYPES || m_format < 0 )
	{
		m_format = TYPE_UNKNOWN;
	}

}

//============================================================================
// VideoBuffer::Rect
//============================================================================

// ?Rect@VideoBuffer@@QAE?AVRectClass@@MMMM@Z present-unmatched
RectClass VideoBuffer::Rect( Real x1, Real y1, Real x2, Real y2 )
{
	RectClass rect(0,0,0,0);

	if ( valid() )
	{
		rect.Set( 
						((Real)m_width/(Real)m_textureWidth)*x1, ((Real)m_height/(Real)m_textureHeight)*y1, 
						((Real)m_width/(Real)m_textureWidth)*x2, ((Real)m_height/(Real)m_textureHeight)*y2
					);
	}

	return rect;

}

//============================================================================
// VideoBuffer::free
//============================================================================

// ?free@VideoBuffer@@UAEXXZ present-unmatched
void	VideoBuffer::free( void )
{
	m_width = 0;
	m_height = 0;
	m_textureWidth = 0;
	m_textureHeight = 0;
}

//============================================================================
// VideoPlayer::VideoPlayer
//============================================================================

VideoPlayer::VideoPlayer()
: m_firstStream(NULL)
{

}

//============================================================================
// VideoPlayer::~VideoPlayer
//============================================================================

// byte-exact reconstruction: Code/GameEngine/Source/GameClient/VideoPlayerDestructorThunk.cpp
// ??1VideoPlayer@@UAE@XZ present-unmatched
// This destructor cannot come home: class shape, and the evidence is worth
// keeping because it also settles a behaviour question.
//
// Retail's 35 bytes at 0x0081C590 account for themselves exactly: a vptr store
// (6), the singleton compare (6), a jne (2), the clear (10), the interim vptr
// store (6) and a tail jump into ~SubsystemInterface at 0x009A1A40 (5). There is
// no room for anything else, so BFME does NOT call deinit() here -- a
// VideoPlayer destroyed in BFME does not tear its streams down first -- and it
// has no destructible members, where the vendored class carries
// VecVideo mVideosAvailableForPlay and the compiler emits that vector's
// destructor from the CLASS. This tree compiles an SEH frame and a member
// destructor call before it reaches the first vptr store; no cast in a .cpp
// reaches either, and the deinit() line is left in place because removing it
// would put an unverified behaviour change where the next agent reads it as
// fact. Unblocking this means the class, not the body.
VideoPlayer::~VideoPlayer()
{
	deinit();
	// Set the video player to null if its us. (WB requires this.)
	if (this == TheVideoPlayer) {
		TheVideoPlayer = NULL;
	}
}

//============================================================================
// VideoPlayer::init
//============================================================================

// ?init@VideoPlayer@@UAEXXZ
void	VideoPlayer::init( void )
{
	VideoPlayer *self = this;
	if (s_bfmeVideoInit == 0)
	{
		BfmeVideoIniStorage ini;
		reinterpret_cast<BfmeVideoLoadView *>(&ini)->load(
			AsciiStringAB("Data\\INI\\Default\\Video.ini"),
			INI_LOAD_OVERWRITE, NULL, INI::parseVideoDefinition);
		reinterpret_cast<BfmeVideoLoadView *>(&ini)->load(
			AsciiStringAB("Data\\INI\\Video.ini"),
			INI_LOAD_OVERWRITE, NULL, INI::parseVideoDefinition);

		BfmeVideoRecord *begin = g_bfmeVideoTableBegin;
		BfmeVideoRecord *end = g_bfmeVideoTableEnd;
		int count = end - begin;

		BfmeVideoRecord *video = begin;
		for (int index = 0; index < count; ++index, ++video)
		{
			if (video->m_isLooping != 0)
			{
				BfmeVideoPlayerLayout *player =
					reinterpret_cast<BfmeVideoPlayerLayout *>(self);
				if (player->m_createSubtitleEntry != 0 &&
					player->m_moviePathHook != 0)
				{
					AsciiStringAB path;
					player->m_moviePathHook->bfmeMakeNameAB(path);

					struct BfmeVideoStringData
					{
						int m_refCount;
						unsigned short m_length;
						unsigned short m_capacity;
						char m_text[1];
					};
					struct BfmeVideoStringObject
					{
						BfmeVideoStringData *m_data;
					};

					BfmeVideoStringData *data =
						reinterpret_cast<BfmeVideoStringObject *>(
							&video->m_internalName)->m_data;
					int length = 0;
					const char *text = (const char *)0x0107388B;
					if (data != 0)
					{
						length = data->m_length;
						text = data->m_text;
					}
					((StringBase<char> *)&path)->concat(text, length);
					((StringBase<char> *)&path)->concat(".ini", 4);

					void *storage = ::operator new(0x64);
					SubtitleManager *manager = 0;
					if (storage != 0)
					{
						manager = new (storage) SubtitleManager(
							player->m_createSubtitleEntry,
							(int)player->m_moviePathHook,
							*(const AsciiString *)&path);
					}
					video->m_subtitleManager = manager;

					BfmeVideoIniStorage subtitleIni;
					reinterpret_cast<BfmeVideoLoadView *>(&subtitleIni)->load(path,
						INI_LOAD_OVERWRITE, NULL,
						(BfmeVideoIniBlockParse)parseSubtitle);
				}
			}
		}

		s_bfmeVideoInit = 1;
	}
}

//============================================================================
// VideoPlayer::deinit
//============================================================================

// ?deinit@VideoPlayer@@UAEXXZ present-unmatched
void VideoPlayer::deinit( void )
{
}

//============================================================================
// VideoPlayer::reset
//============================================================================

// ?reset@VideoPlayer@@UAEXXZ present-unmatched
void	VideoPlayer::reset( void )
{
	closeAllStreams();
}

//============================================================================
// VideoPlayer::update
//============================================================================

// ?update@VideoPlayer@@UAEXXZ present-unmatched
void	VideoPlayer::update( void )
{

	VideoStreamInterface *stream = firstStream();

	while ( stream )
	{
		stream->update();
		stream = stream->next();
	}

}

//============================================================================
// VideoPlayer::loseFocus
//============================================================================

// ?loseFocus@VideoPlayer@@UAEXXZ present-unmatched
void	VideoPlayer::loseFocus( void )
{

}

//============================================================================
// VideoPlayer::regainFocus
//============================================================================

// ?regainFocus@VideoPlayer@@UAEXXZ present-unmatched
void	VideoPlayer::regainFocus( void )
{

}

//============================================================================
// VideoPlayer::open
//============================================================================

// ?open@VideoPlayer@@UAEPAVVideoStreamInterface@@VAsciiString@@@Z present-unmatched
VideoStreamInterface*	VideoPlayer::open( AsciiString movieTitle )
{
	return NULL;
}

//============================================================================
// VideoPlayer::load
//============================================================================

// ?load@VideoPlayer@@UAEPAVVideoStreamInterface@@VAsciiString@@@Z present-unmatched
VideoStreamInterface*	VideoPlayer::load( AsciiString movieTitle )
{
	return NULL;
}

//============================================================================
// VideoPlayer::firstStream
//============================================================================

// ?firstStream@VideoPlayer@@UAEPAVVideoStreamInterface@@XZ present-unmatched
VideoStreamInterface* VideoPlayer::firstStream( void )
{
	return m_firstStream;
}

//============================================================================
// VideoPlayer::closeAllStreams
//============================================================================

// ?closeAllStreams@VideoPlayer@@UAEXXZ present-unmatched
void	VideoPlayer::closeAllStreams( void )
{
	VideoStreamInterface *stream ;

	while ( (stream = firstStream()) != 0 )
	{
		stream->close();
	}
}

//============================================================================
// VideoPlayer::remove
//============================================================================

// ?remove@VideoPlayer@@QAEXPAVVideoStream@@@Z present-unmatched
void VideoPlayer::remove( VideoStream *stream_to_remove )
{
	VideoStream *last = NULL;
	VideoStream *stream = (VideoStream*) firstStream();

	while ( stream != NULL && stream != stream_to_remove )
	{
		last = stream;
		stream = (VideoStream*) stream->next();
	}

	if ( stream )
	{
		if ( last )
		{
			last->m_next = stream->m_next;
		}
		else
		{
			m_firstStream = stream->m_next;
		}
	}
}

//============================================================================
// VideoPlayer::addVideo
//============================================================================
// ?addVideo@VideoPlayer@@UAEXPAUVideo@@@Z present-unmatched
void VideoPlayer::addVideo( Video* videoToAdd )
{
	for (VecVideoIt it = mVideosAvailableForPlay.begin(); it != mVideosAvailableForPlay.end(); ++it) {
		if (it->m_internalName == videoToAdd->m_internalName) {
			(*it) = (*videoToAdd);
			return;
		}
	}

	// That internal name hasn't been used, so push a new entry on the back
	mVideosAvailableForPlay.push_back(*videoToAdd);
}

//============================================================================
// VideoPlayer::removeVideo
//============================================================================
// ?removeVideo@VideoPlayer@@UAEXPAUVideo@@@Z present-unmatched
void VideoPlayer::removeVideo( Video* videoToRemove )
{
	for (VecVideoIt it = mVideosAvailableForPlay.begin(); it != mVideosAvailableForPlay.end(); ++it) {
		if (it->m_internalName == videoToRemove->m_internalName) {
			mVideosAvailableForPlay.erase(it);
			return;
		}
	}
}

//============================================================================
// VideoPlayer::getNumVideos
//============================================================================
// ?getNumVideos@VideoPlayer@@UAEHXZ present-unmatched
Int VideoPlayer::getNumVideos( void )
{
	return mVideosAvailableForPlay.size();
}

//============================================================================
// VideoPlayer::removeVideo
//============================================================================
// ?getVideo@VideoPlayer@@ present-unmatched
const Video* VideoPlayer::getVideo( AsciiString movieTitle )
{
	for (VecVideoIt it = mVideosAvailableForPlay.begin(); it != mVideosAvailableForPlay.end(); ++it) {
		if (it->m_internalName == movieTitle) {
			return &(*it);
		}
	}
	return NULL;
}

//============================================================================
// VideoPlayer::getVideo
//============================================================================
// ?getVideo@VideoPlayer@@ present-unmatched
const Video* VideoPlayer::getVideo( Int index )
{
	if (index < 0 || index >= mVideosAvailableForPlay.size()) {
		return NULL;
	}

	return &mVideosAvailableForPlay[index];
}

//============================================================================
// VideoStream::VideoStream
//============================================================================

// ??0VideoStream@@IAE@XZ present-unmatched
VideoStream::VideoStream()
: m_next(NULL),
	m_player(NULL)
{

}

//============================================================================
// VideoStream::~VideoStream
//============================================================================

// ??1VideoStream@@MAE@XZ present-unmatched
VideoStream::~VideoStream()
{

	if ( m_player )
	{
		m_player->remove( this );
		m_player = NULL;
	}

}

//============================================================================
// VideoStream::next
//============================================================================

// ?next@VideoStream@@UAEPAVVideoStreamInterface@@XZ present-unmatched
VideoStreamInterface* VideoStream::next( void )
{
	return m_next;
}

//============================================================================
// VideoStream::update
//============================================================================

// ?update@VideoStream@@UAEXXZ present-unmatched
void VideoStream::update( void )
{
}

//============================================================================
// VideoStream::close
//============================================================================

// ?close@VideoStream@@UAEXXZ present-unmatched
void VideoStream::close( void )
{
	delete this;
}

//============================================================================
// VideoStream::isFrameReady
//============================================================================

// ?isFrameReady@VideoStream@@UAE_NXZ present-unmatched
Bool VideoStream::isFrameReady( void )
{
	return TRUE;
}

//============================================================================
// VideoStream::frameDecompress
//============================================================================

// ?frameDecompress@VideoStream@@UAEXXZ present-unmatched
void VideoStream::frameDecompress( void )
{

}

//============================================================================
// VideoStream::frameRender
//============================================================================

// ?frameRender@VideoStream@@UAEXPAVVideoBuffer@@@Z present-unmatched
void VideoStream::frameRender( VideoBuffer *buffer )
{

}

//============================================================================
// VideoStream::frameNext
//============================================================================

// ?frameNext@VideoStream@@UAEXXZ present-unmatched
void VideoStream::frameNext( void )
{

}

//============================================================================
// VideoStream::frameIndex
//============================================================================

Int VideoStream::frameIndex( void )
{
	return 0;
}

//============================================================================
// VideoStream::totalFrames
//============================================================================

Int	VideoStream::frameCount( void )
{
	return 0;
}

//============================================================================
// VideoStream::frameGoto
//============================================================================

// ?frameGoto@VideoStream@@UAEXH@Z present-unmatched
void VideoStream::frameGoto( Int index )
{

}

//============================================================================
// VideoStream::height
//============================================================================

Int		VideoStream::height( void )
{
	return 0;
}

//============================================================================
// VideoStream::width
//============================================================================

Int		VideoStream::width( void )
{
	return 0;
}


const FieldParse VideoPlayer::m_videoFieldParseTable[] = 
{
	{ "Filename",								INI::parseAsciiString,							NULL, offsetof( Video, m_filename) },
	{ "Comment",								INI::parseAsciiString,							NULL, offsetof( Video, m_commentForWB) },
	{ NULL,											NULL,																NULL, 0 },
};
