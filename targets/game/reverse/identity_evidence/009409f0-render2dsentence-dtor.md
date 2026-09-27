# 0x009409F0 is ??1Render2DSentenceClass@@UAE@XZ, not UnicodeString::releaseBuffer

The lift row `?releaseBuffer@UnicodeString@@IAEXXZ` at 0x009409F0 is a
misnomer carried over from the Open-BFME5 naked `__emit` copy. The 334-byte
retail body is the BFME `Render2DSentenceClass` destructor:

- It installs vtable 0x0113CEAC (`??_7Render2DSentenceClass@@6B@`), whose
  slot 0 is `?Reset@Render2DSentenceClass@@UAEXXZ`.
- It calls `?Reset@Render2DSentenceClass@@UAEXXZ` (0x0093EA60) directly.
- It destroys three 0x18-byte DynamicVectorClass members with element sizes
  0x24/0x1C/8 and vtables 0x0113CE0C/0x0113CE74/0x0113CE24, matching the
  landed vector dtors 0x009409A0 and 0x00940810 in render2dsentence.cpp.
- It releases a RefCountClass-derived Font pointer at +0x4C (the ZH dtor
  prefix `REF_PTR_RELEASE(Font); Reset();`).
- Callers are `??1W3DDisplayString@@MAE@XZ` x2 (the two Render2DSentenceClass
  members m_textRenderer/m_textRendererHotKey), `??1User@@MAE@XZ` and
  `??1Rva0078D270GameWindowHost@@UAE@XZ`, all as member cleanup.
- The real UnicodeString release lives at 0x008881D0 (the
  `StringBase<unsigned short>` releaseBuffer fold); nothing in this body
  touches a string layout.

Replacement body: game/Libraries/Source/WWVegas/WW3D2/
Render2DSentenceClass_dtor.cpp, byte-exact 334/334 via probe, twin of the
landed constructor `??0Render2DSentenceClass@@QAE@XZ` at 0x00940BF0.
