// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
// Native BFME GameInfo::setMap, 00620510/1213 bytes.
// Derived from GameInfo.cpp, Copyright 2025 Electronic Arts Inc., GPL-3.0-or-later.
// Evidence: targets/game/reverse/identity_evidence/00620510-gameinfo-set-map.md.
#include "ascii_string.h"
// BFME retains two map metadata predicates not named by the existing layout
// witness.
#define NULL 0
template <> inline const char *StringBase<char>::str() const {
  return m_data ? m_data->data : "";
}
template <> inline int StringBase<char>::getLength() const {
  return m_data ? m_data->length : 0;
}
template <> inline const char *StringBase<char>::find(char c) const {
  const char *start = m_data ? m_data->data : "";
  const char *end = start + (m_data ? m_data->length : 0);
  for (const char *p = start; p != end; ++p)
    if (*p == c)
      return p;
  return 0;
}
template <> inline void StringBase<char>::concat(char c) { concat(&c, 1); }
template <> inline void StringBase<char>::concat(const StringBase<char> &s) {
  concat(s.str(), s.getLength());
}
class File {
public:
  virtual ~File();
  virtual bool open(const char *, int);
  virtual void close();
};
class FileSystem {
public:
  File *openFile(const char *, int = 0);
};
extern FileSystem *TheFileSystem;
class MapMetaData {
public:
  char m_unrecovered00[0x25];
  bool m_bfme25, m_bfme26;
};
class MapCache {
public:
  const MapMetaData *findMap(AsciiString);
};
extern MapCache *TheMapCache;
AsciiString GetStrFileFromMap(AsciiString);
AsciiString GetSoloINIFromMap(AsciiString);
AsciiString GetAssetUsageFromMap(AsciiString);
AsciiString GetReadmeFromMap(AsciiString);
AsciiString GetArtPreviewFromMap(AsciiString);
AsciiString GetPicPreviewFromMap(AsciiString);
class GameInfo {
public:
  virtual void slot00();
  virtual void slot04();
  virtual void slot08();
  virtual void slot0c();
  virtual bool amIHost() const;
  void setMap(AsciiString);

private:
  char m_unrecovered04[8];
  bool m_inGame;
  char m_unrecovered0d[0x2f];
  AsciiString m_mapName;
  unsigned int m_mapCRC, m_mapSize;
  int m_mapMask;
};
void GameInfo::setMap(AsciiString mapName) {
  m_mapName = mapName;
  if (m_inGame && amIHost()) {
    const MapMetaData *mapData = TheMapCache->findMap(mapName);
    if (mapData) {
      m_mapMask = 1;
      AsciiString path = mapName;
      path.removeLastChar();
      path.removeLastChar();
      path.removeLastChar();
      path.concat("tga");
      File *fp = TheFileSystem->openFile(path.str());
      if (fp) {
        m_mapMask |= 2;
        fp->close();
        fp = NULL;
      }

      AsciiString newMapName;
      if (mapName.getLength() > 0) {
        AsciiString token;
        mapName.nextToken(&token, "\\/");
        // add all the tokens except the last one.
        // that way we don't add the filename, just the
        // directory name, we can do this since the filename
        // is just the directory name with the file extention
        // added onto it.
        while (mapName.find('\\') != NULL) {
          if (newMapName.getLength() > 0) {
            newMapName.concat('/');
          }
          newMapName.concat(token);
          mapName.nextToken(&token, "\\/");
        }
      }
      newMapName.concat("/map.ini");
      fp = TheFileSystem->openFile(newMapName.str());
      if (fp) {
        m_mapMask |= 4;
        fp->close();
        fp = NULL;
      }

      path = GetStrFileFromMap(m_mapName);
      fp = TheFileSystem->openFile(path.str());
      if (fp) {
        m_mapMask |= 8;
        fp->close();
        fp = NULL;
      }

      path = GetSoloINIFromMap(m_mapName);
      fp = TheFileSystem->openFile(path.str());
      if (fp) {
        m_mapMask |= 16;
        fp->close();
        fp = NULL;
      }

      path = GetAssetUsageFromMap(m_mapName);
      fp = TheFileSystem->openFile(path.str());
      if (fp) {
        m_mapMask |= 32;
        fp->close();
        fp = NULL;
      }

      path = GetReadmeFromMap(m_mapName);
      fp = TheFileSystem->openFile(path.str());
      if (fp) {
        m_mapMask |= 64;
        fp->close();
        fp = NULL;
      }
      path = GetArtPreviewFromMap(m_mapName);
      fp = TheFileSystem->openFile(path.str());
      if (fp) {
        m_mapMask |= 128;
        fp->close();
        fp = 0;
      }
      path = GetPicPreviewFromMap(m_mapName);
      fp = TheFileSystem->openFile(path.str());
      if (fp) {
        m_mapMask |= 256;
        fp->close();
        fp = 0;
      }
      if (mapData->m_bfme25 || mapData->m_bfme26)
        m_mapMask |= 512;

    } else {
      m_mapMask = 0;
    }
  }
}
