// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Igame/GameEngine/Source/Common/System /Igame/GameEngine/Include /Igame/GameEngine/Include/Precompiled /Igame/Libraries/Source/WWVegas/WWLib

class WindowLayout;

void ReleaseWindowLayout(WindowLayout *);

class ReleaseWindowLayoutShim
{
public:
    static void run(WindowLayout *layout);
};

void ReleaseWindowLayout(WindowLayout *layout)
{
    ReleaseWindowLayoutShim::run(layout);
}
