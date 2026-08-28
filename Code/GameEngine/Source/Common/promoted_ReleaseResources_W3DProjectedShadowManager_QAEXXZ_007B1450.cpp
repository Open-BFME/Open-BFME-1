// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// readable body of ?ReleaseResources@W3DProjectedShadowManager@@QAEXXZ: Code/GameEngineDevice/Source/W3DDevice/GameClient/Shadow/W3DProjectedShadow.cpp
// Grok promote from masm_dumps — retail 0x007B1450 size 58
// was: Code/masm_dumps/ReleaseResources_W3DProjectedShadowManager_QAEXXZ_007B1450_28d95344.asm

class W3DShadowContainerShim { public: void release(void); };

class W3DShadowResourceShim {
};

typedef void (__stdcall *W3DShadowReleaseCallback)(W3DShadowResourceShim *);

class W3DProjectedShadowManager { public: void ReleaseResources(void); };

// ?ReleaseResources@W3DProjectedShadowManager@@QAEXXZ
void W3DProjectedShadowManager::ReleaseResources(void)
{
	W3DShadowContainerShim *container =
		*(W3DShadowContainerShim **)((unsigned char *)this + 0x24C);
	container->release();
	W3DShadowResourceShim *first =
		*(W3DShadowResourceShim **)0x01306E08;
	if (first)
		((W3DShadowReleaseCallback)(*(void ***)first)[2])(first);
	W3DShadowResourceShim *second =
		*(W3DShadowResourceShim **)0x01306E04;
	if (second)
		((W3DShadowReleaseCallback)(*(void ***)second)[2])(second);
	*(W3DShadowResourceShim **)0x01306E08 = 0;
	*(W3DShadowResourceShim **)0x01306E04 = 0;
}

