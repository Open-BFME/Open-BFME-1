// cl: /DNDEBUG /MD /EHsc
// Retail 0x00782ED0. Called by BfmeThingSGA::bfmeGoSGA through ILT 0x4A183.
// Renderer allocation size and constructor are witnessed at 0x782EF0/0x782F0E.
class Rva00785FD0Renderer {
public:
 Rva00785FD0Renderer();
 void initializeRva0078C070();
private:
 unsigned char storage_00[0xe0];
};
class BfmeThingSGA { public: void bfmeOneSGA(); };
class WW3D { public: static void Sync(unsigned int); };
extern "C" __declspec(dllimport) unsigned long __stdcall timeGetTime(void);
void bfmeResetGlobals(void);
Rva00785FD0Renderer *g_rva00785FD0Renderer = 0;
extern unsigned rva01346DD8, g_open2SyncB, g_open2SyncA, rva0133F420, rva0133F424;
extern unsigned rva01306968, g_open2Accumulated, g_open2Started;
extern unsigned char g_open2Running;
void BfmeThingSGA::bfmeOneSGA()
{
 if (!g_rva00785FD0Renderer) {
  g_rva00785FD0Renderer = new Rva00785FD0Renderer;
  if (!g_rva00785FD0Renderer) return;
 }
 g_rva00785FD0Renderer->initializeRva0078C070();
 bfmeResetGlobals();
 rva01346DD8 = 0;
 g_open2SyncB = rva0133F420;
 g_open2SyncA = rva0133F424;
 WW3D::Sync(rva01306968);
 unsigned time = g_open2Accumulated;
 if (g_open2Running) {
  time += timeGetTime() - g_open2Started;
  if (time - rva01306968 > 100) {
   time = rva01306968 + 100;
   g_open2Accumulated = time;
   g_open2Started = timeGetTime();
  }
 }
 WW3D::Sync(time);
 rva01306968 = time;
}

unsigned int g_open2SyncA;

unsigned int g_open2SyncB;
