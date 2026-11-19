#pragma once

// Shared existing BFME1 declaration values. Consumers prove their original native
// enum primitive, size, members and runtime independently; no new recovery is claimed.
enum waveType
{
    WaveTypeFirst = 0,
    WaveTypePond = 0,
    WaveTypeOcean = 1,
    WaveTypeCloseOcean = 2,
    WaveTypeCloseOceanDouble = 3,
    WaveTypeLast = 4,
    WaveTypeRadial = 4,
    WaveTypeStationary = 5,
    WaveTypeMax = 6,
};
