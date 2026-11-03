# W7 adjustor thunk of HCompressedAnimClass (s549)

Retail 0x00956CF0 and 0x0095B820 are 8-byte this-adjusting entries
(`83 E9 08` sub ecx,8; `E9 rel32` jmp) referenced from secondary vtables
(VA 0x0113D7E8 and 0x0113E02C hold 0x00D56CF0 / 0x00D5B820). Their jumps land on
the scalar deleting destructors ??_GBoxRenderObjClass@@UAEPAXI@Z (0x00956D10)
and ??_GHCompressedAnimClass@@UAEPAXI@Z (0x0095C4A0), both matched in the same
units. boxrobj.cpp and hcanim.cpp emit ??_E<Class>@@W7AEPAXI@Z whose REL32 names
the vector deleting destructor ??_E<Class>@@UAEPAXI@Z, a weak external that
defaults to ??_G in those objects (storage class 105). The ??_E pins below are
that weak alias, not a second identity: the bodies stay ??_G.

pin-identity-override: ??_EHCompressedAnimClass@@UAEPAXI@Z 0x0095C4A0 caller=0x0095B820 the W7 adjustor thunk 0x0095B820 (hcanim.cpp) jumps to 0x0095C4A0 through the weak alias ??_E that defaults to ??_GHCompressedAnimClass in the same object

The BoxRenderObjClass twin (0x00956CF0 -> 0x00956D10, boxrobj.cpp) is identical but
not landed: the commit hook cannot judge boxrobj.cpp's object current (include
search roots unknown), so its override is not applied.
