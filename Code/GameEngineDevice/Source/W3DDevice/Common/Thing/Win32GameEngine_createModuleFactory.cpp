// Retail 0x006BAEE0. The Win32 game-engine factory allocates the 0x24-byte
// W3DModuleFactory, runs ModuleFactory's constructor, and installs both
// derived vtable pointers for its multiple-inheritance layout.

class ModuleFactory
{
public:
    ModuleFactory();

private:
    unsigned char m_storage[0x20];
};

class W3DModuleFactory : public ModuleFactory
{
public:
    W3DModuleFactory() : ModuleFactory()
    {
        *(volatile unsigned int *)this = 0x0111CAAC;
        *(volatile unsigned int *)((unsigned char *)this + 0x08) = 0x0111CA98;
    }

private:
    unsigned char m_padding[4];
};

class Win32GameEngine
{
public:
    virtual ModuleFactory *createModuleFactory();
};

ModuleFactory *Win32GameEngine::createModuleFactory()
{
    return new W3DModuleFactory;
}
