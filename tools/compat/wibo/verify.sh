#!/usr/bin/env bash
# Small, isolated MSVC7.1 checks. Does not install a runner or change build.py.
set -euo pipefail
if [ "$#" -ne 3 ]; then
    echo "usage: bash tools/compat/wibo/verify.sh WIBO PATCHED_SOURCE OUTPUT_DIR" >&2
    exit 2
fi
package=$(cd -- "$(dirname -- "$0")" && pwd)
repo=$(cd -- "$package/../../.." && pwd)
fixtures="$repo/tools/tests/fixtures/wibo"
runner=$(realpath -- "$1")
source=$(realpath -- "$2")
mkdir -p -- "$3"
out=$(cd -- "$3" && pwd)
vsbase="$repo/inputs/toolchains/vs2003"
vs="$vsbase/Program Files/Microsoft Visual Studio .NET 2003"
vc="$vs/Vc7"
test -x "$runner"
test -f "$source/test/test_mapview_fixed.c"
test -f "$source/test/test_stringfromguid2.c"
test -f "$vc/bin/link.exe"

# Use this Wibo's path conversion directly; never resolve a wine executable.
winpath() { "$runner" path -w "$1"; }
export WINEPATH="$(winpath "$vc/bin");$(winpath "$vs/Common7/IDE");$(winpath "$vsbase")"
export INCLUDE="$(winpath "$vc/PlatformSDK/Include");$(winpath "$vc/include")"
export LIB="$(winpath "$vc/lib");$(winpath "$vc/PlatformSDK/Lib")"
mkdir -p "$out/tmp"
export TMP="$out/tmp" TEMP="$out/tmp" TMPDIR="$out/tmp"
ulimit -c 0
cd "$out"
cp "$fixtures/minimal-map.c" "$fixtures/smoke.cpp" \
   "$fixtures/strict-import.c" "$source/test/test_mapview_fixed.c" \
   "$source/test/test_stringfromguid2.c" .

for name in minimal-map test_mapview_fixed test_stringfromguid2; do
    "$runner" "$vc/bin/cl.exe" /nologo /c /O2 /DWIBO_TEST_NO_CRT \
        /DWIBO_TEST_HOST_LAYOUT "/Fo$name.obj" "$name.c"
    entry=map_test_entry
    libs=(kernel32.lib)
    if [ "$name" = test_stringfromguid2 ]; then
        entry=guid_test_entry
        libs+=(ole32.lib)
    fi
    "$runner" "$vc/bin/link.exe" /nologo /nodefaultlib /incremental:no \
        /machine:x86 /subsystem:console "/entry:$entry" "/out:$name.exe" \
        "$name.obj" "${libs[@]}"
    "$runner" "$name.exe"
done

"$runner" "$vc/bin/cl.exe" /nologo /c /O2 /MD /Fosmoke.obj smoke.cpp
"$runner" "$vc/bin/link.exe" /nologo /incremental:no /machine:x86 \
    /subsystem:console /out:smoke.exe smoke.obj
"$runner" smoke.exe

"$runner" "$vc/bin/cl.exe" /nologo /c /O2 /Oi- /MD /Fostrict-import.obj strict-import.c
"$runner" "$vc/bin/link.exe" /nologo /nodefaultlib /incremental:no /machine:x86 \
    /dll /noentry /opt:noref /out:strict-import.dll strict-import.obj msvcrt.lib
"$runner" "$vc/bin/link.exe" /dump /imports strict-import.dll > strict-import.imports.txt
grep -qi 'MSVCR71.dll' strict-import.imports.txt
grep -qw 'memmove' strict-import.imports.txt
printf 'PASS: native minimal, mapping, GUID, CRT smoke, and strict memmove import links\n'
