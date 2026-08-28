// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/GameEngine/Source/Common/System /ICode/GameEngine/Include /ICode/GameEngine/Include/Precompiled /ICode/Libraries/Source/WWVegas/WWLib
// readable body of ?Set_DX8_Texture_Stage_State@DX8Wrapper@@SAXIKI@Z: Code/GameEngineDevice/Source/W3DDevice/GameClient/Water/W3DWaterTracks.cpp
// readable body of ?startRenderToTexture@W3DShaderManager@@SAXXZ: Code/GameEngineDevice/Source/W3DDevice/GameClient/W3DShaderManager.cpp

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
};

class MemoryPool
{
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/MessageStream.h
class GameMessage
{
public:
    enum Type
    {
        Type_Thunk
    };

    __declspec(dllexport) static AsciiString getCommandTypeAsAsciiString(Type);
};

__declspec(naked) AsciiString GameMessage::getCommandTypeAsAsciiString(Type)
{
    __asm {
        _emit 0E9h
        _emit 0E0h
        _emit 0ABh
        _emit 004h
        _emit 000h
    }
}

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/W3DDevice/GameClient/W3DShaderManager.h
class W3DShaderManager
{
public:
    __declspec(dllexport) static void startRenderToTexture();
};

class W3DShaderManagerStartRenderToTextureShim
{
public:
    static void start();
};

void W3DShaderManager::startRenderToTexture()
{
    W3DShaderManagerStartRenderToTextureShim::start();
}

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/ObjectDefectionHelper.h
class ObjectDefectionHelper
{
public:
    __declspec(dllexport) static MemoryPool *getClassMemoryPool();
};

class ObjectDefectionHelperPoolShim
{
public:
	static MemoryPool *get();
};

MemoryPool *ObjectDefectionHelper::getClassMemoryPool()
{
	return ObjectDefectionHelperPoolShim::get();
}

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/dx8wrapper.h
class DX8Wrapper
{
public:
    __declspec(dllexport) static void Set_DX8_Texture_Stage_State(unsigned int, unsigned long, unsigned int);
};

class DX8TextureStageStateShim
{
public:
    static void set(unsigned int, unsigned long, unsigned int);
};

void DX8Wrapper::Set_DX8_Texture_Stage_State(unsigned int stage, unsigned long state, unsigned int value)
{
    DX8TextureStageStateShim::set(stage, state, value);
}
