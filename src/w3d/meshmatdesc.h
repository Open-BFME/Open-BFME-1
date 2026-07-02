// Minimal shim of WW3D2/meshmatdesc.h — only the stage-count constant the texture
// mappers clamp against (MeshMatDescClass::MAX_TEX_STAGES). Value matches the retail
// engine's meshmatdesc.h (MAX_TEX_STAGES = 2).
#if defined(_MSC_VER)
#pragma once
#endif

#ifndef MESHMATDESC_H
#define MESHMATDESC_H

class MeshMatDescClass
{
public:
	enum { MAX_TEX_STAGES = 2 };
};

#endif
