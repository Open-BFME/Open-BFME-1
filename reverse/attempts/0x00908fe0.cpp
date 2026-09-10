// ?End_Scene@DX8Wrapper@@SAX_N@Z
// partial score=0.82 date=2026-09-10
// ?End_Scene@DX8Wrapper@@SAX_N@Z
// Best bounded reconstruction banked by lane20; source fragment only.
struct BfmeEndSceneDeviceVtable { void *slots0to2[3]; long (__stdcall *TestCooperativeLevel)(void *); void *slots4to16[13]; long (__stdcall *Present)(void *, const void *, const void *, void *, const void *); void *slots18to41[24]; long (__stdcall *EndScene)(void *); };
struct BfmeEndSceneDevice { BfmeEndSceneDeviceVtable *vtable; };
class BfmeAwakenLog { public: virtual BfmeAwakenLog *slot00(int); virtual void slot04(void); virtual void slot08(void); virtual void slot0c(void); virtual void slot10(void); virtual void slot14(void); virtual void slot18(void); virtual void slot1c(void); virtual void slot20(void); virtual void slot24(void); virtual void slot28(void); virtual void slot2c(void); virtual void slot30(void); virtual void slot34(void); virtual BfmeAwakenLog *slot38(const char *); virtual void slot3c(void); virtual void slot40(void); virtual void slot44(void); virtual void slot48(void); virtual BfmeAwakenLog *slot4c(int); };
class BfmeAwakenDebug { public: virtual void slot00(void); virtual void slot04(void); virtual void slot08(void); virtual void slot0c(void); virtual void slot10(void); virtual void slot14(void); virtual void slot18(void); virtual void slot1c(void); virtual void slot20(void); virtual void slot24(void); virtual void slot28(void); virtual void slot2c(void); virtual void slot30(void); virtual void slot34(void); virtual void slot38(void); virtual void slot3c(void); virtual void slot40(void); virtual void slot44(void); virtual void slot48(void); virtual void slot4c(void); virtual void slot50(void); virtual void slot54(void); virtual void slot58(void); virtual void slot5c(void); virtual void slot60(void); virtual void slot64(void); virtual void slot68(void); virtual BfmeAwakenLog *slot6c(int, int); };
extern BfmeAwakenDebug *TheBfmeAwakenDebug;
extern void _bfme_debugRecordCallsite(int);
extern void __cdecl Rva009DB560Sleep(unsigned int);
extern VertexBufferClass *Rva01341120VertexBuffers[];
extern IndexBufferClass *Rva01341128IndexBuffer;

void DX8Wrapper::End_Scene(bool flip_frames)
{
    unsigned saved_scene_state = *reinterpret_cast<unsigned *>(0x013405c4);
    *reinterpret_cast<unsigned *>(0x013405c8) = saved_scene_state;
    *reinterpret_cast<unsigned *>(0x013405c4) = 0;
    reinterpret_cast<BfmeEndSceneDevice *>(D3DDevice)->vtable->EndScene(reinterpret_cast<BfmeEndSceneDevice *>(D3DDevice));
    ++number_of_DX8_calls;
    DX8WebBrowser::Render(0);
    if (flip_frames) {
        int result = reinterpret_cast<BfmeEndSceneDevice *>(D3DDevice)->vtable->Present(reinterpret_cast<BfmeEndSceneDevice *>(D3DDevice), 0, 0, 0, 0);
        ++number_of_DX8_calls;
        if (result >= 0) { ++FrameCount; IsDeviceLost = false; } else IsDeviceLost = true;
        if (result == D3DERR_DEVICELOST) {
            result = reinterpret_cast<BfmeEndSceneDevice *>(D3DDevice)->vtable->TestCooperativeLevel(reinterpret_cast<BfmeEndSceneDevice *>(D3DDevice));
            if (result == D3DERR_DEVICENOTRESET) Reset_Device(true); else Rva009DB560Sleep(200);
        } else if (result != 0) {
            _bfme_debugRecordCallsite(1);
            TheBfmeAwakenDebug->slot60();
            TheBfmeAwakenDebug->slot6c(0, 0)->slot38("DX8 error ")->slot00(result)->slot4c(1);
        }
    }
    if (Rva01341120VertexBuffers[0]) Rva01341120VertexBuffers[0]->Release_Engine_Ref();
    *reinterpret_cast<unsigned short *>(0x01341118) = 0;
    *reinterpret_cast<unsigned short *>(0x0134111a) = 0;
    if (Rva01341120VertexBuffers[0]) Rva01341120VertexBuffers[0]->Release_Ref();
    *reinterpret_cast<unsigned *>(0x0133f49c) |= 0x10000;
    IndexBufferClass *index_buffer = Rva01341128IndexBuffer;
    if (index_buffer) Rva01341128IndexBuffer->Release_Engine_Ref();
    Rva01341120VertexBuffers[0] = 0;
    *reinterpret_cast<unsigned *>(0x0134110c) = 4;
    *reinterpret_cast<unsigned short *>(0x0134111c) = 0;
    if (index_buffer) index_buffer->Release_Ref();
    *reinterpret_cast<unsigned *>(0x01341114) = 4;
    Rva01341128IndexBuffer = 0;
    *reinterpret_cast<unsigned short *>(0x0134112c) = 0;
    *reinterpret_cast<unsigned *>(0x0133f49c) |= 0x20000;
    TextureBaseClass **textures = reinterpret_cast<TextureBaseClass **>(0x01340ec8);
    for (int i = 0; i < CurrentCaps->Get_Max_Textures_Per_Pass(); ++i) {
        if (textures[i]) textures[i]->Release_Ref();
        textures[i] = 0;
        *reinterpret_cast<unsigned *>(0x0133f49c) |= 0x40 << i;
    }
    VertexMaterialClass **material = reinterpret_cast<VertexMaterialClass **>(0x01340ec4);
    if (*material) (*material)->Release_Ref();
    *reinterpret_cast<unsigned *>(0x0133f49c) |= 0x4000;
    *material = 0;
    *reinterpret_cast<unsigned *>(0x0134051c) = 0;
}
