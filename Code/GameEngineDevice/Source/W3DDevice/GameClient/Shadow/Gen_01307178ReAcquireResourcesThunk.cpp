typedef bool Bool;

class W3DVolumetricShadowManager
{
public:
    Bool ReAcquireResources(void);
};

class Gen_01307178
{
public:
    Bool ReAcquireResources(void);
};

Bool Gen_01307178::ReAcquireResources(void)
{
    return reinterpret_cast<W3DVolumetricShadowManager *>(this)->ReAcquireResources();
}
