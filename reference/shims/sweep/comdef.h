/*
**  comdef.h shim — minimal for sweep compilation
*/

#pragma once

#include <windows.h>

class _bstr_t {
public:
    _bstr_t(const char*) {}
    operator const wchar_t*() const { return L""; }
};

