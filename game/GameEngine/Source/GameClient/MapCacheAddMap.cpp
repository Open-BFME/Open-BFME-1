// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
// MapCache::addMap, RVA 004570F0. Whole-body reconstruction from retail.
// ZH MapUtil.cpp supplies the algorithm; BFME metadata ctor/assignment supply
// the 0xfc-byte layout. The standalone prologue and ret 16 prove the boundary.
#include <string.h>
#include "string_base.h"
template <class T> inline bool StringBase<T>::isEmpty() const { return !m_data || m_data->length == 0; }
template <class T> inline const T *StringBase<T>::reverseFind(T c) const {
 const T *start = str(); const T *p = start + getLength();
 while(p != start) { --p; if (*p == c) return p; } return 0;
}
template <class T> inline void StringBase<T>::concat(T c) { concat(&c,1); }
template <class T> inline void StringBase<T>::concat(const T *s) { concat(s,s ? strlen(s) : 0); }
#include "ascii_string.h"
class UnicodeString { public: void translate(const AsciiString &); private: void *m_data; };
struct Coord3D { float x,y,z; };
struct Region3D { Coord3D lo,hi; };
struct Rva004570F0Node { int color; Rva004570F0Node *parent,*left,*right; };
namespace _STL { struct _Rb_tree_node_base; template <class T> class _Rb_global; template <> class _Rb_global<bool> { public: static _Rb_tree_node_base *_M_increment(_Rb_tree_node_base *); }; }
class WaypointMap { public: Rva004570F0Node *m_header; int m_count,m_pad,m_numStartSpots; void update(); };
struct Rva004570F0List { void *m_header; };
class MapMetaData {
public:
 MapMetaData();
 ~MapMetaData();
 MapMetaData &operator=(const MapMetaData &);
 UnicodeString m_displayName,m_description;
 Region3D m_extent;
 int m_numPlayers;
 bool m_isMultiplayer,m_isScenarioMP,m_isOfficial;
 unsigned m_filesize,m_CRC,m_timestampLo,m_timestampHi;
 WaypointMap m_waypoints;
 Rva004570F0List m_supplyPositions,m_techPositions;
 AsciiString m_fileName;
 char m_players[0xa0];
 void *m_tailF4,*m_tailF8;
};
struct FileInfo { unsigned sizeHigh,sizeLow,timestampHigh,timestampLow; };
enum NameKeyType { Rva004570F0Key = 0 };
class StaticNameKey { public: NameKeyType key() const; };
class Dict { public: bool getBool(NameKeyType,bool *) const; AsciiString getAsciiString(NameKeyType,bool *) const; };
extern void j_000263d7();
extern void j_000331ef();
extern void j_0001c9c2();
extern void j_0002756b();
extern void j_00026bcf();
extern void j_000044f8();
extern void j_00031e99();
extern void resetMap();
extern unsigned calcCRC(AsciiString,AsciiString);
extern bool loadMap(AsciiString,MapMetaData *);
// Calls retain the already-ledgered ILT identities; typed views model the
// independently decoded ECX/stack ABI without inventing additional pins.
template <class F> inline F rvaCall(void (*raw)()) { union {void (*p)(); F f;} u; u.p=raw; return u.f; }
extern int Rva012F158C, Rva012F1590;
class Gen_00C6FFF0Target; class Gen_00C70010Target; class Gen_00C70020Target;
extern Gen_00C6FFF0Target TheBfmeObject_00C6FFF0;
extern Gen_00C70010Target TheBfmeObject_00C70010;
extern Gen_00C70020Target TheBfmeObject_00C70020;
extern StaticNameKey g_012A79A0, g_012A79A8, g_012A79E8;
class MapCache {
private:
 bool addMap(AsciiString dirName,AsciiString fname,FileInfo *fileInfo,bool isOfficial);
 Rva004570F0Node *m_header;
};
bool MapCache::addMap(AsciiString dirName,AsciiString fname,FileInfo *fileInfo,bool isOfficial)
{
 if(!fileInfo) return false;
 AsciiString lowerFname; lowerFname = fname; lowerFname.toLower();
 typedef Rva004570F0Node *(MapCache::*Find)(const AsciiString &);
 Rva004570F0Node *it = (this->*rvaCall<Find>(j_000263d7))(lowerFname);
 MapMetaData md;
 unsigned filesize=fileInfo->sizeLow;
 if(it != m_header) {
  md = *(MapMetaData *)((char *)it+0x14);
  if(md.m_filesize==filesize && md.m_CRC!=0) return false;
 }
 loadMap(fname,&md);
 md.m_fileName=lowerFname;
 md.m_filesize=filesize; md.m_isOfficial=isOfficial;
 typedef void (WaypointMap::*Update)();
 (md.m_waypoints.*rvaCall<Update>(j_00026bcf))();
 md.m_numPlayers=md.m_waypoints.m_numStartSpots;
 md.m_isMultiplayer=md.m_numPlayers>=2;
 if(strstr(md.m_fileName.str(),"\\map sps ")) md.m_isMultiplayer=false;
 md.m_timestampHi=fileInfo->timestampHigh; md.m_timestampLo=fileInfo->timestampLow;
 typedef Rva004570F0List &(Rva004570F0List::*Assign)(const Rva004570F0List &);
 (md.m_supplyPositions.*rvaCall<Assign>(j_000044f8))(*(Rva004570F0List *)&TheBfmeObject_00C70010);
 (md.m_techPositions.*rvaCall<Assign>(j_000044f8))(*(Rva004570F0List *)&TheBfmeObject_00C70020);
 md.m_CRC=calcCRC(dirName,fname);
 bool exists=false;
 md.m_isScenarioMP=((Dict *)&TheBfmeObject_00C6FFF0)->getBool(g_012A79E8.key(),&exists);
 if(!exists) md.m_isScenarioMP=false;
 AsciiString munkee=((Dict *)&TheBfmeObject_00C6FFF0)->getAsciiString(g_012A79A0.key(),&exists);
 if(!exists || munkee.isEmpty()) {
  AsciiString tempdisplayname(fname.reverseFind('\\')+1);
  const char *p=tempdisplayname.str();
  AsciiString lookup("$Map:");
  while(*p && *p!='.') { if(*p!=' ') lookup.concat(*p); ++p; }
  md.m_displayName.translate(lookup);
 } else md.m_displayName.translate(munkee);
 AsciiString description=((Dict *)&TheBfmeObject_00C6FFF0)->getAsciiString(g_012A79A8.key(),&exists);
 if(!exists || description.isEmpty()) {
  AsciiString tempdisplayname(fname.reverseFind('\\')+1);
  const char *p=tempdisplayname.str();
  AsciiString lookup("Map:");
  while(*p && *p!='.') { if(*p!=' ') lookup.concat(*p); ++p; }
  lookup.concat("/Desc");
  md.m_description.translate(lookup);
 } else md.m_description.translate(description);
 md.m_extent.lo.x=0; md.m_extent.lo.y=0;
 md.m_extent.hi.x=Rva012F158C * 10.0f;
 md.m_extent.hi.y=Rva012F1590 * 10.0f;
 md.m_extent.lo.z=0; md.m_extent.hi.z=0;
 typedef MapMetaData &(MapCache::*Index)(const AsciiString &);
 (this->*rvaCall<Index>(j_00031e99))(lowerFname)=md;
 Rva004570F0Node *node=md.m_waypoints.m_header->left;
 while(node!=md.m_waypoints.m_header) node=(Rva004570F0Node *)_STL::_Rb_global<bool>::_M_increment((_STL::_Rb_tree_node_base *)node);
 resetMap();
 return true;
}
