#pragma once
// BFME shim of WW3D2 dx8list.h: the polygon-renderer list typedefs, which the mesh
// headers embed as members. MultiListClass<T> stores only T* so a forward-declared
// element gives the correct member size without the DX8 renderer definition.
#ifndef DX8LIST_H_SHIM
#define DX8LIST_H_SHIM
#include "multilist.h"
class DX8PolygonRendererClass;
class DX8TextureCategoryClass;
class DX8FVFCategoryContainer;
typedef MultiListClass<DX8PolygonRendererClass>       DX8PolygonRendererList;
typedef MultiListIterator<DX8PolygonRendererClass>    DX8PolygonRendererListIterator;
typedef MultiListClass<DX8TextureCategoryClass>       DX8TextureCategoryList;
typedef MultiListIterator<DX8TextureCategoryClass>    DX8TextureCategoryListIterator;
typedef MultiListClass<DX8FVFCategoryContainer>       DX8FVFCategoryContainerList;
typedef MultiListIterator<DX8FVFCategoryContainer>    DX8FVFCategoryContainerListIterator;
#endif
