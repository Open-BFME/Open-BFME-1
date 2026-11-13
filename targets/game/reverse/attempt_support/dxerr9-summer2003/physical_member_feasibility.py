import collections
import hashlib
import json
import struct
import subprocess
import sys
from pathlib import Path

ROOT = Path.cwd()
sys.path.insert(0, str(ROOT / 'tools'))
import build
import coffar
import link_cycle
import reloc_ledger
import pefile

OUT = ROOT / 'build/spike3/dxerr-feasibility'
OUT.mkdir(parents=True, exist_ok=True)

def inventory(data):
    sections, symbols = reloc_ledger.parse_coff(data)
    raw_sections, raw_symbols = link_cycle.parse_coff(data)
    result = []
    for sec, raw in zip(sections, raw_sections):
        result.append({
            'number': sec['number'], 'name': sec['name'], 'size': sec['size'],
            'flags': sec['flags'], 'selection': raw.sel,
            'sha256': hashlib.sha256(sec['body']).hexdigest() if sec['body'] is not None else None,
            'publics': [s for s in symbols.values() if s['section'] == sec['number'] and s['storage'] == 2],
            'relocations': [(w, k, symbols[i]['name'], symbols[i]['section'], symbols[i]['value']) for w, i, k in sec['relocs']],
            'directives': sec['body'].decode('latin1') if sec['name'] == '.drectve' else None,
        })
    return {'sha256': hashlib.sha256(data).hexdigest(), 'sections': result,
            'symbols': list(symbols.values()),
            'common': [s for s in symbols.values() if s['storage'] == 2 and s['section'] == 0 and s['value']],
            'undefined': [s['name'] for s in symbols.values() if s['storage'] == 2 and s['section'] == 0 and not s['value']]}

def public_sections(inv):
    return {s['name']: sec for sec in inv['sections'] for s in sec['publics']}

archive = ROOT / 'inputs/vendor/dxerr9/dxerr9.lib'
native = dict(coffar.read_archive(archive))[r'obj\i386\dxerr9.obj']
(OUT / 'dxerr9-native.obj').write_bytes(native)
report = {'head': subprocess.check_output(['git', 'rev-parse', 'HEAD'], text=True).strip(),
          'archive_sha256': hashlib.sha256(archive.read_bytes()).hexdigest(),
          'native': inventory(native), 'compiled': {}, 'links': []}
for filename in ['strsafe.cpp', 'dxerrstringa.cpp', 'dxerrstringw.cpp', 'dxerrdescriptiona.cpp', 'dxerrdescriptionw.cpp']:
    source = ROOT / 'game/Libraries/Source/DirectX' / filename
    obj = OUT / (source.stem + '.obj')
    build.compile_source(source, obj)
    report['compiled'][filename] = inventory(obj.read_bytes())

native_publics = public_sections(report['native'])
report['coexistence'] = []
for filename, inv in report['compiled'].items():
    for name, sec in public_sections(inv).items():
        if name in native_publics:
            original = native_publics[name]
            report['coexistence'].append({'name': name, 'source': filename,
                'native_size': original['size'], 'compiled_size': sec['size'],
                'native_selection': original['selection'], 'compiled_selection': sec['selection'],
                'same_raw_bytes': original['sha256'] == sec['sha256'],
                'same_relocations': original['relocations'] == sec['relocations']})

report['d3dx_intersection'] = []
report['d3dx_parse_errors'] = []
for member, data in coffar.read_archive(ROOT / 'inputs/vendor/d3dx9/d3dx9.lib'):
    try:
        inv = inventory(data)
    except ValueError as error:
        report['d3dx_parse_errors'].append({'member': member, 'error': str(error), 'header': data[:20].hex()})
        continue
    common = sorted(set(public_sections(inv)) & set(native_publics))
    if common:
        report['d3dx_intersection'].append({'member': member, 'symbols': common})

root = build.vc71_root()
env = build.compiler_environment(root)
libs = [root / 'Vc7/lib/msvcrt.lib', root / 'Vc7/PlatformSDK/Lib/Kernel32.Lib', root / 'Vc7/PlatformSDK/Lib/User32.Lib']
for base in (0x10000000, 0x20000000):
    for label, objects in [('original-only', []), ('mixed-baseline', [OUT / (Path(f).stem + '.obj') for f in report['compiled']])]:
        stem = f'{label}-{base:08x}'
        image = OUT / (stem + '.dll')
        command = ['wine', str(root / 'Vc7/bin/link.exe'), '/NOLOGO', '/DLL', '/NOENTRY', '/NODEFAULTLIB',
                   '/INCREMENTAL:NO', '/MACHINE:X86', '/OPT:REF', '/OPT:NOICF', '/VERBOSE:LIB',
                   '/INCLUDE:_DXTraceA@20', '/INCLUDE:_DXTraceW@20',
                   f'/BASE:{base:#x}', f'/OUT:{image.relative_to(ROOT)}', f'/MAP:{OUT.relative_to(ROOT) / (stem + ".map")}',
                   *[str(o.relative_to(ROOT)) for o in objects], str(archive.relative_to(ROOT)),
                   *[build.wine_path(lib) for lib in libs]]
        run = subprocess.run(command, env=env, cwd=ROOT, capture_output=True, text=True, errors='replace')
        (OUT / (stem + '.log')).write_text(run.stdout + run.stderr)
        result = {'label': label, 'base': base, 'command': command, 'exit': run.returncode,
                  'imports': [], 'valid_retail_boundary': False}
        if run.returncode == 0:
            pe = pefile.PE(str(image))
            result['imports'] = [{'dll': d.dll.decode(), 'name': i.name.decode() if i.name else None,
                                  'ordinal': i.ordinal, 'iat_va': i.address}
                                 for d in getattr(pe, 'DIRECTORY_ENTRY_IMPORT', []) for i in d.imports]
        report['links'].append(result)
(OUT / 'report.json').write_text(json.dumps(report, indent=2))
print(json.dumps({'coexistence': report['coexistence'], 'd3dx_intersection': report['d3dx_intersection'], 'links': report['links']}, indent=2))
