/*****************************************************************************\
*                                                                             *
* SpecStrings.h - additional markers for documenting the semantics of APIs    *
*                                                                             *
* Version 1.0                                                                 *
*                                                                             *
* Copyright (c) Microsoft Corporation. All rights reserved.                   *
*                                                                             *
\*****************************************************************************/

#if _MSC_VER > 1000
#pragma once
#endif  // #if _MSC_VER > 1000

#ifdef  __cplusplus
#ifndef __nothrow
# define __nothrow __declspec(nothrow)
#endif
extern "C" {
#else
#ifndef __nothrow
# define __nothrow
#endif
#endif  // #ifdef __cplusplus

#if (_MSC_VER >= 1000) && !defined(MIDL_PASS) && defined(_PREFAST_)

    // ----------------------------------------------------------------------------
    // The primitive MACRO definitations.  More complicated semantics such as
    // the meaning of an __in parameter are express in SpecStrings composed from
    // these primives.
    //
    // In the primitive __declspec("SAL_*") annotations "SAL" stands for SpecString
    // Annotation Language.  These __declspec("SAL_*") annotations are the
    // primivates the compiler understands and all higher-level SpecString MACROs
    // will decompose into these primivates.
    // ----------------------------------------------------------------------------

    // helper macro, do not use directly
    #define SPECSTRINGIZE( x ) #x

    //
    // __null p
    // __notnull p
    // __maybenull p
    //
    // Annotates a pointer p. States that pointer p is null. Commonly used
    // in the negated form __notnull or the possibly null form __maybenull.
    //
    #define __null                  __declspec("SAL_null")
    #define __notnull               __declspec("SAL_notnull")
    #define __maybenull             __declspec("SAL_maybenull")

    //
    // __reserved p or v
    //
    // Annotates a field that must be 0/null for future use.
    //
    #define __reserved              __declspec("SAL_pre") __declspec("SAL_null")

    //
    // __readonly l
    // __notreadonly l
    // __mabyereadonly l
    //
    // Annotates a location l. States that location l is not modified after
    // this point.  If the annotation is placed on the precondition state of
    // a function, the restriction only applies until the postcondition state
    // of the function.  __maybereadonly states that the annotated location
    // may be modified, whereas __notreadonly states that a location must be
    // modified.
    //
    #define __readonly              __declspec("SAL_readonly")
    #define __notreadonly           __declspec("SAL_notreadonly")
    #define __maybereadonly         __declspec("SAL_maybereadonly")
        
    //
    // __valid v
    // __notvalid v
    // __maybevalid v
    //
    // Annotates any value v. States that the value satisfies all properties of
    // valid values of its type. For example, for a string buffer, valid means
    // that the buffer pointer is not null, and the buffer is null terminated.
    //
    #define __valid                 __declspec("SAL_valid")
    #define __notvalid              __declspec("SAL_notvalid")
    #define __maybevalid            __declspec("SAL_maybevalid")

    //
    // __checkReturn v
    //
    // Annotates a return value v. States that the caller should not ignore
    // this value.
    //        
    #define __checkReturn           __declspec("SAL_checkReturn")
        
    //
    // __readableTo(size) p
    //
    // Annotates a buffer pointer p.  If the buffer can be read, size describes
    // how much of the buffer is readable. For a reader of the buffer, this is
    // an explicit permission to read upto size, rather than a restriction to
    // read only upto size.    
    //
    #define __readableTo(size)    __declspec("SAL_readableTo("SPECSTRINGIZE(size)")")
    
    //
    // __writableTo(size) p
    //
    // Annotates a buffer pointer p. If the buffer can be modified, size
    // describes how much of the buffer is writable (usually the allocation
    // size). For a writer of the buffer, this is an explicit permission to
    // write upto size, rather than a restriction to write only upto size.
    //
    #define __writableTo(size)   __declspec("SAL_writableTo("SPECSTRINGIZE(size)")")

    //
    // __typefix(ctype) p
    //
    // Annotates any value. States that if the value is annotated as valid,
    // then it satisfies all of the properties of valid ctype values. ctype
    // must be a visible C/C++ type at the program point where the annotation
    // is placed.
    //        
    #define __typefix(ctype)   __declspec("SAL_typefix("SPECSTRINGIZE(ctype)")")
        
    //
    // __deref p
    //
    // Annotates a pointer p. The next annotation applies one dereference down
    // in the type. If readableTo(p, size) then the next annotation applies to
    // all elements *(p+i) for which i satisfies the size. If p is a pointer
    // to a struct, the next annotation applies to all fields of the struct.
    //
    #define __deref                 __declspec("SAL_deref")
    
    //
    // __pre __next_annotation
    //
    // The next annotation applies in the precondition state
    //
    #define __pre                   __declspec("SAL_pre")
    
    //
    // __post __next_annotation
    //
    // The next annotation applies in the postcondition state
    //
    #define __post                  __declspec("SAL_post")
    
    //
    // __exceptthat
    //
    // Given a set of annotations Q containing __exceptthat maybeP, the effect of
    // the except clause is to erase any P or notP annotations (explicit or
    // implied) within Q at the same level of dereferencing that the except
    // clause appears, and to replace it with maybeP.
    //
    //  Example 1: __valid __exceptthat __maybenull on a pointer p means that the
    //             pointer may be null, and is otherwise valid, thus overriding
    //             the implicit notnull annotation implied by __valid on
    //             pointers.
    //
    //  Example 2: __valid __deref __exceptthat __maybenull on an int **p means
    //             that p is not null (implied by valid), but the elements
    //             pointed to by p could be null, and are otherwise valid. 
    //
    #define __exceptthat            __declspec("SAL_except")

    //
    // __override
    //
    // Use __override to specify C#-style 'override' behaviour for
    // overriding virtual methods.  It improves documentation of code and
    // helps to identify bugs caused by changes to overridden method
    // signatures. 
    //
    #define __override              __declspec("__override")

    //
    // __fallthrough
    //
    // Use __fallthrough before switch statement labels where fall-through
    // to distinguish from forgotten break statements.
    //

    __inline __nothrow void         __FallThrough() {}

    #define __fallthrough           __FallThrough();

    //
    // __callback
    //
    // Use __callback for functions that used as function pointers, the
    // keyword will silence various OACR checks on formal parameters of the
    // marked functions
    //
    #define __callback              __declspec("__callback")

    // ----------------------------------------------------------------------------
    // The high level MACRO definitations.  These are compose from the above
    // primitives and express common semantics in a compact MACRO.
    // ----------------------------------------------------------------------------

    //
    // __in p
    //
    // Specifices that the pointer p is a IN parameter.  It has the
    // precondition of being a valid pointer and the memory that is pointed
    // to is initialized in a valid manner for the datatype.  It has the
    // precondition that the memory it points to is readonly.
    //
    #define __in                    __pre __valid \
                                    __pre __deref __readonly

    //
    // __out p
    //
    // Specifices that the pointer p is an OUT paramters.  It has the
    // precodition that the pointer is not null.  The purpose of the
    // "__exceptthat __mabyereadonly" statement is to enable the common
    // annotation of "__in __out p".  The postcondition is the pointer
    // must be valid and the memory the pointer references must be
    // valid.
    // 
    #define __out                   __pre __notnull \
                                    __pre __deref __exceptthat __maybereadonly \
                                    __post __valid
    
    //
    // __inout p
    //
    // Precondition that p and *p are valid.
    // Postcondition that p and *p are valid.
    //
    // This is shorthand as the same annotation as "__in __out p" and
    // the annotations "__in __out p" and "__inout p" behave identically.
    //
    #define __inout                 __pre __valid \
                                    __post __valid 

    //
    // __opt p
    //
    // Adds the condition that it is valid for the pointer p to be NULL
    // It should be used in combination with a preceeding __in or __out
    // annotation as:
    //  __in __opt p   // means if p is not null then p and *p have the
    //                    precondition of being valid.
    //  __out __opt p  // means if p is not null then p and *p have the
    //                    postcondition of being valid.
    //
    #define __opt                   __pre __exceptthat __maybenull \
                                    __post __exceptthat __maybenull

    //
    // __out_ecount(size) p
    //
    // Pointer p is an OUT parameter.  The size of p is given in element
    // counts by size.
    //   
    #define __out_ecount(size)      __pre __notnull \
                                    __pre __deref __exceptthat __maybereadonly \
                                    __pre __declspec("SAL_writableTo(elementCount("SPECSTRINGIZE(size)"))") \
                                    __post __valid \
                                    __post __declspec("SAL_readableTo(elementCount("SPECSTRINGIZE(size)"))")
                       
    //
    // __in_ecount(size) p
    //
    // Pointer p is an IN parameter.  The size of p is given by in element
    // counts by size.
    //                                
    #define __in_ecount(size)       __pre __valid \
                                    __pre __deref __readonly \
                                    __pre __declspec("SAL_readableTo(elementCount("SPECSTRINGIZE(size)"))") \
                                    __post __declspec("SAL_readableTo(elementCount("SPECSTRINGIZE(size)"))")

    //
    // __inout_ecount(size) p
    //
    // Is shorthand for:  "__in_ecount(size) __out_ecount(size) p"
    //
    #define __inout_ecount(size)    __pre __valid \
                                    __post __valid \
                                    __pre __declspec("SAL_readableTo(elementCount("SPECSTRINGIZE(size)"))") \
                                    __post __declspec("SAL_readableTo(elementCount("SPECSTRINGIZE(size)"))") \
                                    __pre __declspec("SAL_writableTo(elementCount("SPECSTRINGIZE(size)"))")

    //
    // __out_bcount(size) p
    //
    // Pointer p is an OUT parameter.  The size of p is given in byte counts
    // by size.
    //
    #define __out_bcount(size)      __pre __notnull \
                                    __pre __deref __exceptthat __maybereadonly \
                                    __pre __declspec("SAL_writableTo(byteCount("SPECSTRINGIZE(size)"))") \
                                    __post __valid \
                                    __post __declspec("SAL_readableTo(byteCount("SPECSTRINGIZE(size)"))")

    //
    // __in_bcount(size) p
    //
    // Pointer p is an IN parameter.  The size of p is given in byte counts
    // by size.
    //                                   
    #define __in_bcount(size)       __pre __valid \
                                    __pre __deref __readonly \
                                    __pre __declspec("SAL_readableTo(byteCount("SPECSTRINGIZE(size)"))") \
                                    __post __declspec("SAL_readableTo(byteCount("SPECSTRINGIZE(size)"))")

    // 
    // __inout_bcount(size) p
    //
    // Is shorthand for:  "__in_bcount(size) __out_bcount(size) p"
    // 
    #define __inout_bcount(size)    __pre __valid \
                                    __post __valid \
                                    __pre __declspec("SAL_readableTo(byteCount("SPECSTRINGIZE(size)"))") \
                                    __post __declspec("SAL_readableTo(byteCount("SPECSTRINGIZE(size)"))") \
                                    __pre __declspec("SAL_writableTo(byteCount("SPECSTRINGIZE(size)"))")

    //
    // __format_string
    //
    #define __format_string

#else
    #define __null
    #define __notnull
    #define __maybenull
    #define __reserved
    #define __readonly
    #define __notreadonly
    #define __maybereadonly
    #define __valid
    #define __novalid
    #define __maybevalid
    #define __checkReturn
    #define __readableTo(size)
    #define __writableTo(size)
    #define __typefix(ctype)        
    #define __deref
    #define __pre
    #define __post
    #define __exceptthat
    #define __override
    #define __fallthrough
    #define __callback
    #define __in
    #define __out
    #define __inout
    #define __opt
    #define __out_ecount(size)
    #define __in_ecount(size)
    #define __inout_ecount(size)
    #define __out_bcount(size)
    #define __in_bcount(size)
    #define __inout_bcount(size)
    #define __format_string
#endif
#ifdef  __cplusplus
}
#endif

