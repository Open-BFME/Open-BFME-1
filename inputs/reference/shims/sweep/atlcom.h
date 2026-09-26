/*
**  ATL atlcom.h shim — minimal declarations for sweep compilation
*/

#pragma once

#include <objbase.h>

template <class ThreadModel>
class CComObjectRootEx {};

template <class T>
class CComCoClass {};

class CComSingleThreadModel {};

template <class T>
class CComObject : public T {};

#define BEGIN_COM_MAP(x) public:
#define COM_INTERFACE_ENTRY(x)
#define COM_INTERFACE_ENTRY_AGGREGATE(x, y)
#define END_COM_MAP()
