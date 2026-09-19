// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Oy- /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug

#include <string.h>

struct _EXCEPTION_RECORD
{
    unsigned long ExceptionCode;
    unsigned long ExceptionFlags;
    _EXCEPTION_RECORD *ExceptionRecord;
    void *ExceptionAddress;
    unsigned long NumberParameters;
    unsigned long ExceptionInformation[15];
};

struct _EXCEPTION_POINTERS
{
    _EXCEPTION_RECORD *ExceptionRecord;
    void *ContextRecord;
};

extern "C" __declspec(dllimport) int __cdecl wsprintfA(
    char *, const char *, ...);

#define EXCEPTION_ACCESS_VIOLATION       0xC0000005UL
#define EXCEPTION_ARRAY_BOUNDS_EXCEEDED  0xC000008CUL
#define EXCEPTION_BREAKPOINT              0x80000003UL
#define EXCEPTION_DATATYPE_MISALIGNMENT   0x80000002UL
#define EXCEPTION_FLT_DENORMAL_OPERAND    0xC000008DUL
#define EXCEPTION_FLT_DIVIDE_BY_ZERO      0xC000008EUL
#define EXCEPTION_FLT_INEXACT_RESULT      0xC000008FUL
#define EXCEPTION_FLT_INVALID_OPERATION   0xC0000090UL
#define EXCEPTION_FLT_OVERFLOW            0xC0000091UL
#define EXCEPTION_FLT_STACK_CHECK         0xC0000092UL
#define EXCEPTION_FLT_UNDERFLOW           0xC0000093UL
#define EXCEPTION_GUARD_PAGE              0x80000001UL
#define EXCEPTION_ILLEGAL_INSTRUCTION     0xC000001DUL
#define EXCEPTION_IN_PAGE_ERROR            0xC0000006UL
#define EXCEPTION_INT_DIVIDE_BY_ZERO      0xC0000094UL
#define EXCEPTION_INT_OVERFLOW            0xC0000095UL
#define EXCEPTION_INVALID_DISPOSITION     0xC0000026UL
#define EXCEPTION_INVALID_HANDLE          0xC0000008UL
#define EXCEPTION_NONCONTINUABLE_EXCEPTION 0xC0000025UL
#define EXCEPTION_PRIV_INSTRUCTION        0xC0000096UL
#define EXCEPTION_SINGLE_STEP              0x80000004UL
#define EXCEPTION_STACK_OVERFLOW           0xC00000FDUL

class DebugExceptionhandler
{
public:
    static const char *GetExceptionType(
        _EXCEPTION_POINTERS *, char *);
};

const char *DebugExceptionhandler::GetExceptionType(
    _EXCEPTION_POINTERS *exptr, char *explanation)
{
#define EX(code, text) \
    case EXCEPTION_##code: strcpy(explanation, text); return "EXCEPTION_" #code;

    switch (exptr->ExceptionRecord->ExceptionCode)
    {
    case EXCEPTION_ACCESS_VIOLATION:
        wsprintfA(explanation,
            "The thread tried to read from or write to a virtual\n"
            "address for which it does not have the appropriate access.\n"
            "Access address 0x%08x was %s.",
            exptr->ExceptionRecord->ExceptionInformation[1],
            exptr->ExceptionRecord->ExceptionInformation[0] ?
                "written to" : "read from");
        return "EXCEPTION_ACCESS_VIOLATION";
        EX(ARRAY_BOUNDS_EXCEEDED,
            "The thread tried to access an array element that\n"
            "is out of bounds and the underlying hardware\n"
            "supports bounds checking.")
        EX(BREAKPOINT, "A breakpoint was encountered.")
        EX(DATATYPE_MISALIGNMENT,
            "The thread tried to read or write data that is\n"
            "misaligned on hardware that does not provide alignment.\n"
            "For example, 16-bit values must be aligned on\n"
            "2-byte boundaries; 32-bit values on 4-byte\n"
            "boundaries, and so on.")
        EX(FLT_DENORMAL_OPERAND,
            "One of the operands in a floating-point operation is\n"
            "denormal. A denormal value is one that is too small\n"
            "to represent as a standard floating-point value.")
        EX(FLT_DIVIDE_BY_ZERO,
            "The thread tried to divide a floating-point\n"
            "value by a floating-point divisor of zero.")
        EX(FLT_INEXACT_RESULT,
            "The result of a floating-point operation\n"
            "cannot be represented exactly as a decimal fraction.")
        EX(FLT_INVALID_OPERATION,
            "Some strange unknown floating point operation was attempted.")
        EX(FLT_OVERFLOW,
            "The exponent of a floating-point operation is greater\n"
            "than the magnitude allowed by the corresponding type.")
        EX(FLT_STACK_CHECK,
            "The stack overflowed or underflowed as the result\n"
            "of a floating-point operation.")
        EX(FLT_UNDERFLOW,
            "The exponent of a floating-point operation is less\n"
            "than the magnitude allowed by the corresponding type.")
        EX(GUARD_PAGE, "A guard page was accessed.")
        EX(ILLEGAL_INSTRUCTION,
            "The thread tried to execute an invalid instruction.")
        EX(IN_PAGE_ERROR,
            "The thread tried to access a page that was not\n"
            "present, and the system was unable to load the page.\n"
            "For example, this exception might occur if a network "
            "connection is lost while running a program over the network.")
        EX(INT_DIVIDE_BY_ZERO,
            "The thread tried to divide an integer value by\n"
            "an integer divisor of zero.")
        EX(INT_OVERFLOW,
            "The result of an integer operation caused a carry\n"
            "out of the most significant bit of the result.")
        EX(INVALID_DISPOSITION,
            "An exception handler returned an invalid disposition\n"
            "to the exception dispatcher. Programmers using a\n"
            "high-level language such as C should never encounter\n"
            "this exception.")
        EX(INVALID_HANDLE, "An invalid Windows handle was used.")
        EX(NONCONTINUABLE_EXCEPTION,
            "The thread tried to continue execution after\n"
            "a noncontinuable exception occurred.")
        EX(PRIV_INSTRUCTION,
            "The thread tried to execute an instruction whose\n"
            "operation is not allowed in the current machine mode.")
        EX(SINGLE_STEP,
            "A trace trap or other single-instruction mechanism\n"
            "signaled that one instruction has been executed.")
        EX(STACK_OVERFLOW, "The thread used up its stack.")
    case 0xE06D7363UL:
        strcpy(explanation, "Microsoft C++ Exception");
        return "EXCEPTION_MS";
    default:
        wsprintfA(explanation, "Unknown exception code 0x%08x",
            exptr->ExceptionRecord->ExceptionCode);
        return "EXCEPTION_UNKNOWN";
    }

#undef EX
}
