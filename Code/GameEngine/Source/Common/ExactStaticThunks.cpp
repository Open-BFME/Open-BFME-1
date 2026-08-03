// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/GameEngine/Source/Common/System /ICode/GameEngine/Include /ICode/GameEngine/Include/Precompiled /ICode/Libraries/Source/WWVegas/WWLib

class AsciiString
{
};

class Object
{
};

class MemoryPool
{
};

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

class AI
{
public:
    __declspec(dllexport) static float getAdjustedVisionRangeForObject(const Object *, int);
};

class AIAdjustedVisionRangeForObjectShim
{
public:
    static float getAdjustedVisionRangeForObject(const Object *, int);
};

float AI::getAdjustedVisionRangeForObject(const Object *object, int value)
{
    return AIAdjustedVisionRangeForObjectShim::getAdjustedVisionRangeForObject(object, value);
}

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

class ObjectDefectionHelper
{
public:
    __declspec(dllexport) static MemoryPool *getClassMemoryPool();
};

class ObjectDefectionHelperPoolBody
{
public:
    static MemoryPool *getClassMemoryPool();
};

MemoryPool *ObjectDefectionHelper::getClassMemoryPool()
{
    return ObjectDefectionHelperPoolBody::getClassMemoryPool();
}

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
