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
extern Rva00785FD0Renderer *g_rva00785FD0Renderer;
extern unsigned rva01346DD8, rva0130695C, rva01306958, rva0133F420, rva0133F424;
extern unsigned rva01306968, rva01306960, rva01306964;
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
 rva0130695C = rva0133F420;
 rva01306958 = rva0133F424;
 WW3D::Sync(rva01306968);
 unsigned time = rva01306960;
 if (g_open2Running) {
  time += timeGetTime() - rva01306964;
  if (time - rva01306968 > 100) {
   time = rva01306968 + 100;
   rva01306960 = time;
   rva01306964 = timeGetTime();
  }
 }
 WW3D::Sync(time);
 rva01306968 = time;
}
