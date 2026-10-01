// getMapPreviewImage at RVA 0x004516E0: 1212 retail bytes.
// Identity: ZH MapUtil.cpp counterpart and named load-screen callers through ILT.
// BFME strings use StringBase<char>; _art.tga previews flip the vertical UVs.
// The static file-copy helper must remain visible: VC7.1 gives a function it
// compiles beside its caller an EAX register convention, so the first
// reference arrives in EAX and the second on the stack, and the body therefore
// opens with mov eax,[eax]. Across a TU boundary the same pair is a plain cdecl
// push/push, which is why these 303 retail bytes at 0x004508D0 (last
// instruction is the noreturn call ending 0x004509FE; 0x004509FF is padding)
// can only live beside the one caller at 0x00451A37. ZH MapUtil.cpp
// copyFromBigToDir is the twin.
// Rva0044F4D0 is the existing opaque one-pointer texture-reference constructor;
// its argument carries the filename pointer through the historical int ABI.
// No layout or semantic identity is inferred from the old constructor name.
// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
#include "ascii_string.h"
#include <string.h>
template<typename T> inline T StringBase<T>::getCharAt(int i) const {return m_data ? m_data->data[i] : 0;}
template<typename T> inline void StringBase<T>::concat(T c) {concat(&c,1);}
template<typename T> inline void StringBase<T>::concat(const T *s) {concat(s,s ? strlen(s) : 0);}
template<typename T> inline void StringBase<T>::concat(const StringBase<T> &s) {concat(s.str(),s.getLength());}
template<typename T> inline void StringBase<T>::set(const T *s) {set(s,s ? strlen(s) : 0);}
template<typename T> inline const T *StringBase<T>::reverseFind(T c) const {
 const T *start=m_data ? m_data->data : (const T *)"";
 const T *p=start+(m_data ? m_data->length : 0);
 while(p!=start) {--p; if(*p==c) return p;}
 return 0;
}
inline AsciiString &AsciiString::operator=(const char *s) {StringBase<char>::set(s);return *this;}
extern AsciiString Rva01336e50;
class File {
public:
 virtual void slot0();virtual void slot4();virtual void close();
 virtual int read(void *,int);virtual int write(const void *,int);virtual int seek(int,int);
};
class FileSystem {
public:
 File *openFile(const char *,int);
 bool doesFileExist(const char *) const;
 bool createDirectory(AsciiString);
};
extern FileSystem *TheFileSystem;
// Retail's global at 0x012ED5C8 is EA's GlobalData *TheWritableGlobalData, defined
// once in Common/GlobalData.cpp. This opaque TU-local class names the
// getPath_UserData call target only; the real header's class is not redeclared.
class GlobalData {public: AsciiString getPath_UserData() const;};
extern GlobalData *TheWritableGlobalData;
class GameState {public: AsciiString realMapPathToPortableMapPath(const AsciiString &) const;};
extern GameState *TheGameState;
class TextureClass {public: void Release_Ref();};
class Rva0044F4D0 {
public:
 Rva0044F4D0(int);
 ~Rva0044F4D0() { if(ptr) ptr->Release_Ref(); }
private: TextureClass *ptr;
};
struct Coord2D { float x,y; };
struct Region2D {Coord2D lo,hi;};
struct ICoord2D {int x,y;};
class Image {
public:
 virtual void slot0();
 Image();
 void setName(AsciiString);
 void setFilename(AsciiString);
 unsigned int setStatus(unsigned int);
 void _bfme_setTexture(const Rva0044F4D0 &);
 void setUV(const Region2D *uv) {m_UVCoords=*uv;}
 void setTextureHeight(int h) {m_textureSize.y=h;}
 void setTextureWidth(int w) {m_textureSize.x=w;}
private:
 AsciiString m_name,m_filename;
 ICoord2D m_textureSize;
 Region2D m_UVCoords;
 ICoord2D m_imageSize;
 void *field2c;
 unsigned int m_status;
};
class ImageCollection {public: const Image *findImageByName(const AsciiString &); void addImage(Image *);};
extern ImageCollection *TheMappedImageCollection;
class XferException {
public:
 XferException(int,const char *,...);
 XferException(const XferException &);
 ~XferException();
private: char *text;int tag;
};
// Retail allocates and frees the copy buffer through the array operators
// (??_U@YAPAXI@Z at 0x00881F70, ??_V@YAXPAX@Z at 0x00881EF0). Without these
// declarations cl binds new char[] and delete[] to the scalar operators, which
// are different bodies at 0x00881F30 and 0x00881EB0.
void * __cdecl operator new[](unsigned int bytes);
void __cdecl operator delete[](void *block);
static void copyFromBigToDir(const AsciiString &infile,const AsciiString &outfile) {
 File *file=TheFileSystem->openFile(infile.str(),0x41);
 if(!file) throw XferException(5,0);
 int fileSize=file->seek(0,2);
 file->seek(0,0);
 char *buffer=new char[fileSize];
 if(!buffer) throw XferException(5,0);
 if(file->read(buffer,fileSize)<fileSize) throw XferException(5,0);
 file->close();
 File *filenew=TheFileSystem->openFile(outfile.str(),0x4a);
 if(!filenew || filenew->write(buffer,fileSize)<fileSize) throw XferException(5,0);
 filenew->close();
 delete [] buffer;
}
Image *getMapPreviewImage(AsciiString mapName) {
 if(!TheWritableGlobalData) return 0;
 AsciiString tgaName=mapName;
 AsciiString name;
 AsciiString tempName;
 AsciiString filename;
 tgaName.removeLastChar();tgaName.removeLastChar();tgaName.removeLastChar();tgaName.removeLastChar();
 name=tgaName;
 filename=tgaName.reverseFind('\\')+1;
 filename.concat(".tga");tgaName.concat(".tga");
 AsciiString portableName=TheGameState->realMapPathToPortableMapPath(name);
 tempName.set(Rva01336e50);
 for(int i=0;i<portableName.getLength();++i) {
  char c=portableName.getCharAt(i);
  if(c=='\\' || c==':') tempName.concat('_'); else tempName.concat(c);
 }
 name=tempName;
 name.concat(".tga");
 Image *image=(Image *)TheMappedImageCollection->findImageByName(tempName);
 if(!image) {
  Region2D uv;
  uv.hi.x=1.0f;uv.hi.y=1.0f;uv.lo.x=0.0f;uv.lo.y=0.0f;
  AsciiString artName=tgaName;
  artName.removeLastChar();artName.removeLastChar();artName.removeLastChar();artName.removeLastChar();
  artName.concat("_art.tga");
  if(TheFileSystem->doesFileExist(artName.str())) {tgaName=artName;uv.hi.y=0.0f;uv.lo.y=1.0f;}
  else if(!TheFileSystem->doesFileExist(tgaName.str())) return 0;
  AsciiString mapPreviewDir;
  mapPreviewDir.format("%sMapPreviews/",TheWritableGlobalData->getPath_UserData().str());
  TheFileSystem->createDirectory(mapPreviewDir);
  mapPreviewDir.concat(name);
  bool success=false;
  try {copyFromBigToDir(tgaName,mapPreviewDir);success=true;} catch(...) {success=false;}
  if(success) {
   image=new Image;
   image->setName(tempName);
   image->setFilename(tgaName);
   image->_bfme_setTexture(Rva0044F4D0((int)mapPreviewDir.str()));
   image->setStatus(2);
   image->setUV(&uv);
   image->setTextureHeight(128);image->setTextureWidth(128);
   TheMappedImageCollection->addImage(image);
  } else image=0;
 }
 return image;
}
