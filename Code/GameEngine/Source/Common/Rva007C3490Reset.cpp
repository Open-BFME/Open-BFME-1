// cl: /O2 /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/W3DDevice/GameClient/W3DShaderManager.h
class W3DShaderManager
{
public:
	enum ShaderTypes
	{
		kSlot0B = 0x0B
	};
	static void resetShader(ShaderTypes type);
};

void Rva007C3490()
{
	W3DShaderManager::resetShader(W3DShaderManager::kSlot0B);
}
