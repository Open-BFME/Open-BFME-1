// This is a part of the Active Template Library.
// Copyright (C) Microsoft Corporation
// All rights reserved.
//
// This source code is only intended as a supplement to the
// Active Template Library Reference and related
// electronic documentation provided with the library.
// See these sources for detailed information regarding the
// Active Template Library product.

#pragma once

#pragma warning(disable : 4668)	// is not defined as a preprocessor macro, replacing with '0' for '#if/#elif
#pragma warning(disable : 4820)	// padding added after member

#define __ATLMINCRT_H__

#ifdef _WIN64
#define DEFAULT_SECURITY_COOKIE 0x2B992DDFA23249D6
#else  /* _WIN64 */
#define DEFAULT_SECURITY_COOKIE 0xBB40E64E
#endif  /* _WIN64 */

typedef void (*_PVFV)(void);
