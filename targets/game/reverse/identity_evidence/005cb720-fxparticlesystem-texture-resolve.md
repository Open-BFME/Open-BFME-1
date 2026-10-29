# 0x005CB720: FXParticleSystem::ParticleSystemManager vtable slot 14

Facts from BFME 1 retail:

- Vtable 0x0110FDCC slot 14 (+0x38) points at this body through ILT 0x000031FC.
  The vtable is installed by the constructor 0x005CBF60 and destructor
  0x005CB360, whose ILT slots confirm `??0ParticleSystemManager@FXParticleSystem@@QAE@XZ`
  and `??1ParticleSystemManager@FXParticleSystem@@UAE@XZ` (tools/ilt_oracle.py check).
- The body is 460 bytes and ends with a plain `ret` at +0x1CB: it takes no stack
  argument, so it is not Zero Hour's `preloadAssets(TimeOfDay)` (which would end
  `ret 4`). The ILT contradicts `?preloadAssets@ParticleSystemManager@@UAEXW4TimeOfDay@@@Z`
  and its FXParticleSystem-namespace spelling.
- Behaviour: it iterates the template map at manager +0x9C (begin via ILT 0x0001ABD1,
  the increment inlined with the AsciiString string hash), and for each template of
  type 1 (+0x0C) with a non-empty texture name (getTextureFilename, ILT 0x00018755)
  strips four characters, looks the result up in TheMappedImageCollection
  (findImageByName, ILT 0x0001D606), copies the image's UV region (+0x14) into the
  template (+0x84) and assigns the image's file name (Image::getFilename, ILT
  0x000336AE) to the template's texture name (+0x10).

No semantic method name is proven, so the method keeps the address-derived name
`?rva005CB720@ParticleSystemManager@FXParticleSystem@@UAEXXZ`. Source:
game/GameEngine/Source/GameClient/System/FXParticleSystem/ParticleSystemManagerResolveTextures.cpp.
