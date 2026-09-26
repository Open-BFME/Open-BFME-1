// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib

#include "ascii_string.h"

// Canonical ascii_string.cpp destructor body, visible for retail inlining.
inline AsciiString::~AsciiString()
{
	((StringBase<char> *)this)->releaseBuffer();
}

class __single_inheritance FunctorTargetSingle
{
};
typedef void (FunctorTargetSingle::*FunctorMethodSingle)( void );

struct FunctorBindingSingle
{
    FunctorBindingSingle( FunctorMethodSingle method,
        FunctorTargetSingle *target )
        : m_target( target ), m_method( method ) {}

    FunctorTargetSingle *m_target;
    FunctorMethodSingle m_method;
};

class FunctorSingleWrapperHead
{
public:
    FunctorSingleWrapperHead() : m_refCount( 0 ) {}
    virtual void anchor();

    unsigned int m_refCount;
};

class Rva00525A30FunctorSingleWrapper : public FunctorSingleWrapperHead
{
public:
    Rva00525A30FunctorSingleWrapper( const FunctorBindingSingle &binding )
        : m_binding( binding ) {}

    FunctorBindingSingle m_binding;
};

class Rva0050F840FunctorHolder
{
public:
    Rva0050F840FunctorHolder( FunctorBindingSingle binding )
    {
        m_ptr = new Rva00525A30FunctorSingleWrapper( binding );
        if( m_ptr != 0 )
            m_ptr->m_refCount++;
    }

    Rva0050F840FunctorHolder( const Rva0050F840FunctorHolder &other )
        : m_ptr( other.m_ptr ) {}

    ~Rva0050F840FunctorHolder() {}

private:
    Rva00525A30FunctorSingleWrapper *m_ptr;
};

class AptMapPreviewFunctorWrapper : public FunctorSingleWrapperHead
{
public:
    AptMapPreviewFunctorWrapper( const FunctorBindingSingle &binding )
        : m_binding( binding ) {}

    FunctorBindingSingle m_binding;
};

class AptMapPreviewFunctorHolder
{
public:
    AptMapPreviewFunctorHolder( FunctorBindingSingle binding )
    {
        m_ptr = new AptMapPreviewFunctorWrapper( binding );
        if( m_ptr != 0 )
            m_ptr->m_refCount++;
    }

    AptMapPreviewFunctorHolder( const AptMapPreviewFunctorHolder &other )
        : m_ptr( other.m_ptr ) {}

    ~AptMapPreviewFunctorHolder() {}

private:
    AptMapPreviewFunctorWrapper *m_ptr;
};

class WindowManager
{
public:
    void registerAptCallback( const AsciiString &name,
        AptMapPreviewFunctorHolder callback );
};


extern WindowManager *g_theWindowManager;

void _bfme_setAptScreenRef( const AsciiString &name,
    Rva0050F840FunctorHolder callback );

class AptMapPreview : public FunctorTargetSingle
{
public:
    void initGadgets();
};

// ?initGadgets@AptMapPreview@@QAEXXZ
void AptMapPreview::initGadgets()
{
    union
    {
        void (*raw)( void );
        FunctorMethodSingle member;
    } callback;
    callback.raw = (void (*)( void ))0x00436DF9;
    AptMapPreview *self = this;
    {
        AsciiString name( "AptMapPreview::MapGadgetInit" );
        _bfme_setAptScreenRef( name,
            Rva0050F840FunctorHolder(
                FunctorBindingSingle( callback.member, self ) ) );
    }

    callback.raw = (void (*)( void ))0x0040AFAB;
    {
        AsciiString name( "AptMapPreview::Picture" );
        g_theWindowManager->registerAptCallback( name,
            AptMapPreviewFunctorHolder(
                FunctorBindingSingle( callback.member, self ) ) );
    }
}
