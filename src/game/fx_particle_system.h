#pragma once

namespace FXParticleSystem {

class ButterflyDrawModuleInfo {
public:
    virtual ~ButterflyDrawModuleInfo();
    virtual const char *GetSnapshotName();
};

class DefaultAlphaModuleInfo {
public:
    virtual ~DefaultAlphaModuleInfo();
    virtual const char *GetSnapshotName();
};

class DefaultColorModuleInfo {
public:
    virtual ~DefaultColorModuleInfo();
    virtual const char *GetSnapshotName();
};

class DefaultDrawModuleInfo {
public:
    virtual ~DefaultDrawModuleInfo();
    virtual const char *GetSnapshotName();
};

class DefaultPhysicsModuleInfo {
public:
    virtual ~DefaultPhysicsModuleInfo();
    virtual const char *GetSnapshotName();
};

class DefaultUpdateModuleInfo {
public:
    virtual ~DefaultUpdateModuleInfo();
    virtual const char *GetSnapshotName();
};

class EmissionVelocityInfo {
public:
    EmissionVelocityInfo();
    virtual ~EmissionVelocityInfo();
    virtual const char *GetSnapshotName();
};

class EmissionVolumeInfo {
public:
    EmissionVolumeInfo();
    virtual ~EmissionVolumeInfo();
    virtual const char *GetSnapshotName();

    bool m_flag;
};

class LifeEventModuleInfo {
public:
    virtual const char *GetSnapshotName();
};

class LightningDrawModuleInfo {
public:
    virtual ~LightningDrawModuleInfo();
    virtual const char *GetSnapshotName();
};

class ParticleSystemInfo {
public:
    virtual const char *GetSnapshotName();
};

class QuadDrawModuleInfo {
public:
    QuadDrawModuleInfo();
    virtual ~QuadDrawModuleInfo();
    virtual const char *GetSnapshotName();
};

class RenderObjectDrawModuleInfo {
public:
    virtual const char *GetSnapshotName();
};

class RenderObjectUpdateModuleInfo {
public:
    virtual ~RenderObjectUpdateModuleInfo();
    virtual const char *GetSnapshotName();
};

class StreakDrawModuleInfo {
public:
    virtual ~StreakDrawModuleInfo();
    virtual const char *GetSnapshotName();
};

class TerrainCollisionModuleInfo {
public:
    virtual const char *GetSnapshotName();
};

class WindModuleInfo {
public:
    virtual ~WindModuleInfo();
    virtual const char *GetSnapshotName();
};

}
