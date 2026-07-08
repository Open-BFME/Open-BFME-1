# PROGRESS: port-ww3d2-5

## Done (pre-existing on branch)
DONE rendobj.cpp
DONE segline.cpp
DONE seglinerenderer.cpp

## Skipped
SKIP render2dsentence.cpp — includes dx8wrapper.h
SKIP renderobjectrecycler.cpp — only 1 shared list method locates; recycler functions absent
SKIP rinfo.cpp — SpecialRenderInfoClass syntax error (shared rinfo.h drift)
SKIP ringobj.cpp — heavy DX8 chain
SKIP scene.cpp — includes dx8renderer.h / dx8wrapper.h
SKIP shader.cpp — includes Dx8Wrapper.h / dx8caps.h
SKIP shattersystem.cpp — needs dynamesh.h / vp.h (DX8 chain)
SKIP snappts.cpp — 0 located; functions absent from binary
SKIP sortingrenderer.cpp — includes dx8wrapper.h / d3d8.h
SKIP soundrobj.cpp — pulls in WWAudio headers (audiblesound.h / wwaudio.h)
SKIP sphereobj.cpp — heavy DX8 chain
SKIP sr_util.cpp — requires external sr* headers
SKIP static_sort_list.cpp — includes dx8renderer.h
SKIP statistics.cpp — heavy DX8 chain
SKIP streak.cpp — includes dx8wrapper.h
SKIP streakRender.cpp — includes dx8wrapper.h
