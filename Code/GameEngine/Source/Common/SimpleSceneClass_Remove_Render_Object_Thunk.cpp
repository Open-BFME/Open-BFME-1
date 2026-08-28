// cl: /DNDEBUG /MD /EHsc
// readable body of ?Remove_Render_Object@SimpleSceneClass@@UAEXPAVRenderObjClass@@@Z: Code/Libraries/Source/WWVegas/WW3D2/scene.cpp
// Open-BFME5: lift MASM dump to standalone C++ thunk.
//
// Re-identified from ?Unregister@SimpleSceneClass@@. That name's arguments size
// to 8 bytes and this body ends in ret 4, so the pair was impossible. Slot 3 of
// the SimpleSceneClass vtable, paired with Add_Render_Object at slot 2, and the
// body opens by inlining SceneClass::Remove_Render_Object -- the 15-byte
// tail-call to the object's virtual at +0x68 -- then removes it from the scene
// lists and releases its references.

class RenderObjClass;
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/scene.h
class SimpleSceneClass
{
public:
	virtual void Remove_Render_Object(RenderObjClass *);
};

// ?Remove_Render_Object@SimpleSceneClass@@UAEXPAVRenderObjClass@@@Z
__declspec(naked) void SimpleSceneClass::Remove_Render_Object(RenderObjClass *)
{
	__asm {
		__emit 0x53
		__emit 0x56
		__emit 0x8b
		__emit 0x74
		__emit 0x24
		__emit 0x0c
		__emit 0x8b
		__emit 0x06
		__emit 0x57
		__emit 0x8b
		__emit 0xf9
		__emit 0x57
		__emit 0x8b
		__emit 0xce
		__emit 0xff
		__emit 0x50
		__emit 0x68
		__emit 0x8d
		__emit 0x5e
		__emit 0x08
		__emit 0x53
		__emit 0x8d
		__emit 0x8f
		__emit 0xbc
		__emit 0x00
		__emit 0x00
		__emit 0x00
		__emit 0xe8
		__emit 0x20
		__emit 0x88
		__emit 0x09
		__emit 0x00
		__emit 0x8b
		__emit 0x16
		__emit 0x8b
		__emit 0xce
		__emit 0xff
		__emit 0x92
		__emit 0x9c
		__emit 0x01
		__emit 0x00
		__emit 0x00
		__emit 0x85
		__emit 0xc0
		__emit 0x74
		__emit 0x0c
		__emit 0x53
		__emit 0x8d
		__emit 0x8f
		__emit 0xd4
		__emit 0x00
		__emit 0x00
		__emit 0x00
		__emit 0xe8
		__emit 0x06
		__emit 0x88
		__emit 0x09
		__emit 0x00
		__emit 0x53
		__emit 0x8d
		__emit 0x8f
		__emit 0xec
		__emit 0x00
		__emit 0x00
		__emit 0x00
		__emit 0xe8
		__emit 0xfa
		__emit 0x87
		__emit 0x09
		__emit 0x00
		__emit 0x84
		__emit 0xc0
		__emit 0x74
		__emit 0x0b
		__emit 0xff
		__emit 0x4e
		__emit 0x04
		__emit 0x75
		__emit 0x06
		__emit 0x8b
		__emit 0x06
		__emit 0x8b
		__emit 0xce
		__emit 0xff
		__emit 0x10
		__emit 0x8b
		__emit 0x86
		__emit 0x94
		__emit 0x00
		__emit 0x00
		__emit 0x00
		__emit 0x85
		__emit 0xc0
		__emit 0x7c
		__emit 0x09
		__emit 0x56
		__emit 0x8d
		__emit 0x4f
		__emit 0x34
		__emit 0xe8
		__emit 0x08
		__emit 0xfb
		__emit 0xff
		__emit 0xff
		__emit 0x53
		__emit 0x8d
		__emit 0x4f
		__emit 0x5c
		__emit 0xe8
		__emit 0xcf
		__emit 0x87
		__emit 0x09
		__emit 0x00
		__emit 0x84
		__emit 0xc0
		__emit 0x74
		__emit 0x0b
		__emit 0xff
		__emit 0x4e
		__emit 0x04
		__emit 0x75
		__emit 0x06
		__emit 0x8b
		__emit 0x16
		__emit 0x8b
		__emit 0xce
		__emit 0xff
		__emit 0x12
		__emit 0x5f
		__emit 0x5e
		__emit 0x5b
		__emit 0xc2
		__emit 0x04
		__emit 0x00
	}
}
