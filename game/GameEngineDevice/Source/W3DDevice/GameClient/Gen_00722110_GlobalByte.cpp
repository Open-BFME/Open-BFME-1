// cl: /DNDEBUG /MD /EHsc

// Retail 0x00722110. Return a global byte.

class W3DShaderManager
{
protected:
	static bool m_renderingToTexture;
	friend unsigned char get_00722110(void);
};

// ?get@Gen_00722110@@YAEXZ
unsigned char get_00722110(void)
{
	return W3DShaderManager::m_renderingToTexture;
}
