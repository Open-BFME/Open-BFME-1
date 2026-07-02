// Minimal shim of WW3D2/ww3d.h — only the timing accessor the texture mappers need.
// WW3D::Get_Sync_Time() is inline (reads the static SyncTime); the DIR32 reference to
// SyncTime is relocation-masked by the byte matcher, so no definition is required here.
#if defined(_MSC_VER)
#pragma once
#endif

#ifndef WW3D_H
#define WW3D_H

class WW3D
{
	static unsigned int SyncTime;
public:
	static unsigned int Get_Sync_Time(void) { return SyncTime; }
};

#endif
