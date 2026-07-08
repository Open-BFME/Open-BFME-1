# PROGRESS port-ww3d2-1

DONE aabtree.cpp (4 header inlines matched, AABTreeClass methods present-unmatched)
DONE aabtreebuilder.cpp (20/20 matched)
SKIP agg_def.cpp — includes windows.h (system wall)
SKIP animatedsoundmgr.cpp — local rect.h lacks RectClass, simpleparameter.h read-only
DONE animobj.cpp (8/8 matched, rest present-unmatched)
SKIP assetmgr.cpp — widestring.h local drift + missing ini.h
PENDING assetstatus.cpp
SKIP bitmaphandler.cpp — colorspace.h needs DX8Wrapper/Vector4 (renderer wall)
SKIP bmp2d.cpp — dynamesh.h needs DX8Wrapper (renderer wall)
SKIP boxrobj.cpp — heavy DX8 rendering code
SKIP bw_render.cpp — 0 located, no distinctive strings in binary
SKIP bwrender.cpp — 0 located, no distinctive strings in binary
SKIP camera.cpp — full renderer recipe (DX8/Matrix4x4/viewport)
SKIP collect.cpp — 0 located, no distinctive strings in binary
PENDING coltest.cpp
DONE composite.cpp (5/5 matched, rest present-unmatched)
SKIP dazzle.cpp — mapper.h internal compiler error
SKIP ddsfile.cpp — needs d3d8.h (Direct3D wall)
SKIP decalmsh.cpp — rinfo.h Matrix4x4/CameraClass + dx8caps.h (renderer wall)
