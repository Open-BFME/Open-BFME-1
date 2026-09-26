// cl: /DNDEBUG /MD /EHsc

// Every W3D draw module's factory. They are three lines each -- allocate the
// module and construct it -- so no one of them can be named from its own code;
// what names them is the draw-module registration block, which builds the
// AsciiString for each class and pushes that class's factory address beside it.
// They also sit in one contiguous run of the image, in this order:
//
//   class                  retail       size
//   W3DDefaultDraw         0x006BEFC0    0x14
//   W3DScriptedModelDraw   0x006BF040   0x27C
//   W3DLaserDraw           0x006BF150    0x5C
//   W3DQuadrupedDraw       0x006BF260   0x27C
//   W3DSupplyDraw          0x006BF360   0x284
//   W3DTruckDraw           0x006BF470   0x3EC
//   W3DTankDraw            0x006BF580   0x2F8
//   W3DTreeDraw            0x006BF690    0x10
//   W3DBuffDraw            0x006BF7A0    0x10
//   W3DPropDraw            0x006BF8B0    0x10
//   W3DFloorDraw           0x006BF9C0    0x14
//   W3DLightDraw           0x006BFAD0    0x20
//   W3DHordeModelDraw      0x006BFBE0   0x288
//   W3DStreakDraw          0x006BFCF0    0x14
//
// Thirteen files meant thirteen copies of the same four declarations, and the
// only thing that differed between them was the allocation size -- which is the
// one piece of evidence each body actually carries, since `new` is what encodes
// sizeof(class). Collected here, the sizes can be read against each other:
// 0x10 for the three that hold nothing but their base, 0x14 for the three with
// one more field, and 0x27C to 0x3EC for the five that carry animation state.
// Reading any one file alone, that comparison is not available.
//
// These are all real registered classes, not borrowed Zero Hour names: the
// registration block pairs each factory address with a string literal, which is
// what identified them in the first place. Where a Zero Hour header describes
// the same class, the class carries its upstream-layout line.

class Module;
class Thing;
class ModuleData;

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/W3DDevice/GameClient/Module/W3DDefaultDraw.h
class W3DDefaultDraw
{
public:
	W3DDefaultDraw(Thing *, const ModuleData *);
	static Module *friend_newModuleInstance(Thing *, const ModuleData *);

private:
	unsigned char m_pad[0x14];
};

class W3DScriptedModelDraw
{
public:
	W3DScriptedModelDraw(Thing *, const ModuleData *);
	static Module *friend_newModuleInstance(Thing *, const ModuleData *);

private:
	unsigned char m_pad[0x27C];
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/W3DDevice/GameClient/Module/W3DLaserDraw.h
class W3DLaserDraw
{
public:
	W3DLaserDraw(Thing *, const ModuleData *);
	static Module *friend_newModuleInstance(Thing *, const ModuleData *);

private:
	unsigned char m_pad[0x5C];
};

class W3DQuadrupedDraw
{
public:
	W3DQuadrupedDraw(Thing *, const ModuleData *);
	static Module *friend_newModuleInstance(Thing *, const ModuleData *);

private:
	unsigned char m_pad[0x27C];
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/W3DDevice/GameClient/Module/W3DSupplyDraw.h
class W3DSupplyDraw
{
public:
	W3DSupplyDraw(Thing *, const ModuleData *);
	static Module *friend_newModuleInstance(Thing *, const ModuleData *);

private:
	unsigned char m_pad[0x284];
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/W3DDevice/GameClient/Module/W3DTruckDraw.h
class W3DTruckDraw
{
public:
	W3DTruckDraw(Thing *, const ModuleData *);
	static Module *friend_newModuleInstance(Thing *, const ModuleData *);

private:
	unsigned char m_pad[0x3EC];
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/W3DDevice/GameClient/Module/W3DTankDraw.h
class W3DTankDraw
{
public:
	W3DTankDraw(Thing *, const ModuleData *);
	static Module *friend_newModuleInstance(Thing *, const ModuleData *);

private:
	unsigned char m_pad[0x2F8];
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/W3DDevice/GameClient/Module/W3DTreeDraw.h
class W3DTreeDraw
{
public:
	W3DTreeDraw(Thing *, const ModuleData *);
	static Module *friend_newModuleInstance(Thing *, const ModuleData *);

private:
	unsigned char m_pad[0x10];
};

class W3DBuffDraw
{
public:
	W3DBuffDraw(Thing *, const ModuleData *);
	static Module *friend_newModuleInstance(Thing *, const ModuleData *);

private:
	unsigned char m_pad[0x10];
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/W3DDevice/GameClient/Module/W3DPropDraw.h
class W3DPropDraw
{
public:
	W3DPropDraw(Thing *, const ModuleData *);
	static Module *friend_newModuleInstance(Thing *, const ModuleData *);

private:
	unsigned char m_pad[0x10];
};

class W3DFloorDraw
{
public:
	W3DFloorDraw(Thing *, const ModuleData *);
	static Module *friend_newModuleInstance(Thing *, const ModuleData *);

private:
	unsigned char m_pad[0x14];
};

// The module registration table pairs the factory at 0x006BFAD0 with the
// "W3DLightDraw" name.  The 0x20-byte allocation in that factory independently
// supplies the retail class size.
class W3DLightDraw
{
public:
	W3DLightDraw(Thing *, const ModuleData *);
	static Module *friend_newModuleInstance(Thing *, const ModuleData *);

private:
	unsigned char m_pad[0x20];
};

class W3DHordeModelDraw
{
public:
	W3DHordeModelDraw(Thing *, const ModuleData *);
	static Module *friend_newModuleInstance(Thing *, const ModuleData *);

private:
	unsigned char m_pad[0x288];
};

class W3DStreakDraw
{
public:
	W3DStreakDraw(Thing *, const ModuleData *);
	static Module *friend_newModuleInstance(Thing *, const ModuleData *);

private:
	unsigned char m_pad[0x14];
};

// ?friend_newModuleInstance@W3DDefaultDraw@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *W3DDefaultDraw::friend_newModuleInstance(Thing *thing, const ModuleData *data)
{
	return (Module *)new W3DDefaultDraw(thing, data);
}

// ?friend_newModuleInstance@W3DScriptedModelDraw@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *W3DScriptedModelDraw::friend_newModuleInstance(Thing *thing, const ModuleData *data)
{
	return (Module *)new W3DScriptedModelDraw(thing, data);
}

// ?friend_newModuleInstance@W3DLaserDraw@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *W3DLaserDraw::friend_newModuleInstance(Thing *thing, const ModuleData *data)
{
	return (Module *)new W3DLaserDraw(thing, data);
}

// ?friend_newModuleInstance@W3DQuadrupedDraw@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *W3DQuadrupedDraw::friend_newModuleInstance(Thing *thing, const ModuleData *data)
{
	return (Module *)new W3DQuadrupedDraw(thing, data);
}

// ?friend_newModuleInstance@W3DSupplyDraw@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *W3DSupplyDraw::friend_newModuleInstance(Thing *thing, const ModuleData *data)
{
	return (Module *)new W3DSupplyDraw(thing, data);
}

// ?friend_newModuleInstance@W3DTruckDraw@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *W3DTruckDraw::friend_newModuleInstance(Thing *thing, const ModuleData *data)
{
	return (Module *)new W3DTruckDraw(thing, data);
}

// ?friend_newModuleInstance@W3DTankDraw@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *W3DTankDraw::friend_newModuleInstance(Thing *thing, const ModuleData *data)
{
	return (Module *)new W3DTankDraw(thing, data);
}

// ?friend_newModuleInstance@W3DTreeDraw@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *W3DTreeDraw::friend_newModuleInstance(Thing *thing, const ModuleData *data)
{
	return (Module *)new W3DTreeDraw(thing, data);
}

// ?friend_newModuleInstance@W3DBuffDraw@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *W3DBuffDraw::friend_newModuleInstance(Thing *thing, const ModuleData *data)
{
	return (Module *)new W3DBuffDraw(thing, data);
}

// ?friend_newModuleInstance@W3DPropDraw@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *W3DPropDraw::friend_newModuleInstance(Thing *thing, const ModuleData *data)
{
	return (Module *)new W3DPropDraw(thing, data);
}

// ?friend_newModuleInstance@W3DFloorDraw@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *W3DFloorDraw::friend_newModuleInstance(Thing *thing, const ModuleData *data)
{
	return (Module *)new W3DFloorDraw(thing, data);
}

// ?friend_newModuleInstance@W3DLightDraw@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *W3DLightDraw::friend_newModuleInstance(Thing *thing, const ModuleData *data)
{
	return (Module *)new W3DLightDraw(thing, data);
}

// ?friend_newModuleInstance@W3DHordeModelDraw@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *W3DHordeModelDraw::friend_newModuleInstance(Thing *thing, const ModuleData *data)
{
	return (Module *)new W3DHordeModelDraw(thing, data);
}

// ?friend_newModuleInstance@W3DStreakDraw@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *W3DStreakDraw::friend_newModuleInstance(Thing *thing, const ModuleData *data)
{
	return (Module *)new W3DStreakDraw(thing, data);
}
