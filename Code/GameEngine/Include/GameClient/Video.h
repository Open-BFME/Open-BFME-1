#pragma once

#include "../../../Libraries/Source/WWVegas/WWLib/ascii_string.h"

class SubtitleManager;

// BFME Video records are 0x1c bytes. INI::parseVideoDefinition (0x000C3480)
// passes this layout to VideoPlayer::addVideo; destructor 0x000C3410 releases
// the three strings. Retail FieldParse table RVA 0x00D2CBD8 witnesses Filename,
// Comment, HasSubtitles, Volume and IsDefault at offsets 0, 8, C, 10, 14.
// VideoPlayer::init stores a newly constructed SubtitleManager at +18
// (0x0081CC94/0x0081CCAC); getSubTitleMgrForVideo 0x0081CA10 reads it.
struct Video
{
    AsciiString m_filename;
    AsciiString m_internalName;
    AsciiString m_commentForWB;
    unsigned char m_hasSubtitles;
    float m_volume;
    unsigned char m_isDefault;
    SubtitleManager *m_subtitleManager;

    Video()
        : m_hasSubtitles(0), m_volume(1.0f), m_isDefault(0),
          m_subtitleManager(0)
    {
    }

    ~Video();

    __forceinline Video &operator=(const Video &other)
    {
        m_filename.set(other.m_filename);
        m_internalName.set(other.m_internalName);
        m_commentForWB.set(other.m_commentForWB);
        m_hasSubtitles = other.m_hasSubtitles;
        m_volume = other.m_volume;
        m_isDefault = other.m_isDefault;
        m_subtitleManager = other.m_subtitleManager;
        return *this;
    }
};
