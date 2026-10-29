// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// Retail00494EC0,62B. Global map atVA012F3354 has an identity-hashed
// four-byte key and a pointer mapped value (the caller dereferences that value).
// Keep the key as the bank's opaque pointer ABI; no concrete owner is known.
// operator[]494E40 and erase494A20 independently match99B and146B.
// Native const-reference calls reproduce the ECX/count-store order absent
// from the bank's opaque pointer-to-key method declarations. Keep its local
// key copy/reassignment; passing the parameter directly emits a shorter body.
#define _STLP_NO_EXCEPTIONS 1
#include <hash_map>
#include "../../../Libraries/Source/WWVegas/WWLib/ascii_string.h"
// Retail00494FA0,447B, reached through ILT00020C5C from matched callers
// 00493EA0 and 00592D60 (two-argument thiscall, ret 8). It opens a stream
// through TheVideoPlayer slot +0x30, stores it at +0x08, registers this
// object in the map below under the stream key and installs Rva00494EC0 as
// the stream's +0x10 callback, the same entry Rva00494EC0 clears. The object
// is the vtable-0x010FA1CC subsystem (slots +0x10 and +0x14 called here);
// method and owner names stay address-derived.
class Rva00494FA0Frame
{
public:
 unsigned char m_at00[0x18];
 void *m_at18;
};
class Rva00494FA0Stream
{
public:
 virtual void slot00(); virtual void slot04(); virtual void slot08(); virtual void slot0c();
 virtual void slot10(); virtual void slot14(); virtual void slot18();
 virtual void close();
 virtual void slot20(); virtual void slot24(); virtual void slot28(); virtual void slot2c();
 virtual void slot30(); virtual void slot34();
 virtual bool attach(void *buffer);
 unsigned char m_at04[4];
 Rva00494FA0Frame *m_at08;
 unsigned char m_at0c[4];
 void (__cdecl *m_callback)(void *);
};
class Rva00494FA0PlayerView
{
public:
 virtual void slot00(); virtual void slot04(); virtual void slot08(); virtual void slot0c();
 virtual void slot10(); virtual void slot14(); virtual void slot18(); virtual void slot1c();
 virtual void slot20(); virtual void slot24(); virtual void slot28(); virtual void slot2c();
 virtual Rva00494FA0Stream *open(AsciiString name, int flag);
};
class Rva00494FA0DisplayView
{
public:
 virtual void slot00(); virtual void slot04(); virtual void slot08(); virtual void slot0c();
 virtual void slot10(); virtual void slot14(); virtual void slot18(); virtual void slot1c();
 virtual void slot20(); virtual void slot24(); virtual void slot28();
 virtual unsigned int getWidth();
 virtual unsigned int getHeight();
 virtual void slot34(); virtual void slot38(); virtual void slot3c();
 virtual void slot40(); virtual void slot44(); virtual void slot48(); virtual void slot4c();
 virtual void slot50(); virtual void slot54(); virtual void slot58();
 virtual void slot5c(void *frame, float x, float y, int width, int a, int b, int c);
 virtual void slot60(); virtual void slot64(); virtual void slot68(); virtual void slot6c();
 virtual void slot70(); virtual void slot74(); virtual void slot78(); virtual void slot7c();
 virtual void slot80();
 virtual void *createBuffer(bool flag);
};
class Glo012F1028Type
{
public:
 unsigned char m_before2c[0x2c];
 unsigned char m_2c;
 unsigned char m_2d;
};
class VideoPlayerInterface;
extern VideoPlayerInterface *TheVideoPlayer;
class Display;
extern Display *TheDisplay;
// Retail 0x012F1028 is EA's TheLivingWorldLogic (data_rows.csv owns
// ?TheLivingWorldLogic@@3PAVLivingWorldLogic@@A, LivingWorldLogic.cpp); the
// Glo012F1028 spelling is only a pin nothing defines.
class LivingWorldLogic;
extern LivingWorldLogic *TheLivingWorldLogic;
#define Glo012F1028 ( reinterpret_cast<Glo012F1028Type *>( TheLivingWorldLogic ) )
extern float g_010FA1F8;
extern float g_010FA1FC;
void __cdecl Rva00494EC0(void *p);
class Rva00494EC0EntryView
{
public:
 virtual void slot00(); virtual void slot04(); virtual void slot08(); virtual void slot0c();
 virtual void stop();
 virtual void update();
 void rva00494FA0(const AsciiString &name, unsigned int flags);
 unsigned char m_at04[4];
 Rva00494FA0Stream *m_at08;
 unsigned char m_at0c[0x10];
 unsigned int m_at1c;
 unsigned char m_at20;
 unsigned char m_at21[3];
 int m_at24;
};
struct Rva00494EC0Hash
{
 unsigned operator()(void *key) const { return (unsigned)key; }
};
typedef _STL::hash_map<void *, Rva00494EC0EntryView *, Rva00494EC0Hash> Rva00494EC0MapView;
Rva00494EC0MapView g_rva00494EC0Map;
// ?Rva00494EC0@@YAXPAX@Z
void __cdecl Rva00494EC0(void *p)
{
 void *key = p;
 Rva00494EC0EntryView *entry=g_rva00494EC0Map[key];
 if (entry != 0)
 {
  entry->m_at20 &= 0xfc;
  entry->m_at08 = 0;
  key = p;
  g_rva00494EC0Map.erase(key);
 }
}

// ?rva00494FA0@Rva00494EC0EntryView@@QAEXABVAsciiString@@I@Z
void Rva00494EC0EntryView::rva00494FA0(const AsciiString &name, unsigned int flags)
{
 stop();
 m_at20 &= 0xfb;
 m_at24 = -1;
 m_at1c = flags;
 Rva00494FA0Stream *stream = ((Rva00494FA0PlayerView *)TheVideoPlayer)->open(name, flags & 0x40);
 m_at08 = stream;
 if (stream == 0)
  return;
 if (stream->m_at08 != 0 && stream->m_at08->m_at18 != 0)
 {
  float scale;
  if (Glo012F1028->m_2c)
  {
   scale = 0.9765625f;
   if (!Glo012F1028->m_2d)
    scale = 0.88932294f;
  }
  else
   scale = 0.88932294f;
  int x = (int)((float)((Rva00494FA0DisplayView *)TheDisplay)->getWidth() * g_010FA1FC);
  int y = (int)((float)((Rva00494FA0DisplayView *)TheDisplay)->getHeight() * scale);
  int width = (int)((float)((Rva00494FA0DisplayView *)TheDisplay)->getWidth() * g_010FA1F8);
  ((Rva00494FA0DisplayView *)TheDisplay)->slot5c(m_at08->m_at08->m_at18,
   (float)x, (float)y, width, 8, 25000, 0x3f3f3f3f);
 }
 stream = m_at08;
 if (!stream->attach(((Rva00494FA0DisplayView *)TheDisplay)->createBuffer((flags & 0x40) != 0)))
 {
  if (m_at08 != 0)
   m_at08->close();
  m_at08 = 0;
  m_at20 &= 0xfc;
  return;
 }
 void *key = m_at08;
 g_rva00494EC0Map[key] = this;
 m_at08->m_callback = Rva00494EC0;
 m_at20 = (m_at20 & 0xfd) | 1;
 update();
}

// Retail 0x00C6B9E0 (29 B) is the next CRT initializer after this unit's
// _$E1 above: it builds an AudioEventRTS in place in the 0x70-byte global at
// 0x012F3370 (the data row g_q3IndexedFallback) from the shared empty string
// and 0 through ILT 0x00025306 (matched ??0AudioEventRTS 0x000B2CC0), then
// registers the matched teardown forwarder 0x00C70110 (~AudioEventRTS on the
// same global) with atexit. The global is defined as an opaque byte record
// elsewhere, so the construction is spelled as placement new rather than as
// a second definition.
class AudioEventRTS
{
public:
	AudioEventRTS(const AsciiString &eventName, int ownerID) throw();
private:
	char m_storage[0x70];
};
struct Q3IndexedItem { char m_bytes[ 0x70 ]; };
extern Q3IndexedItem g_q3IndexedFallback;
void bfmeForward_00C70110(void);
extern "C" int __cdecl atexit(void (__cdecl *callback)());

void Rva00C6B9E0Initialize()
{
	new (&g_q3IndexedFallback) AudioEventRTS(AsciiString::TheEmptyString, 0);
	atexit(bfmeForward_00C70110);
}
