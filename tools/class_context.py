"""Locate a class definition, not the first header that forward-declares it."""
import re
import subprocess
from pathlib import Path


def class_virtuals(text, name):
    # Ignore comment/string braces; preserve newlines for readable diagnostics.
    clean = re.sub(r'//[^\n]*|/\*.*?\*/|"(?:\\.|[^"\\])*"', '', text, flags=re.S)
    match = re.search(r'\bclass\s+' + re.escape(name) + r'\b[^;{}]*\{', clean)
    if not match:
        return None
    depth, end = 1, match.end()
    while end < len(clean) and depth:
        depth += (clean[end] == '{') - (clean[end] == '}')
        end += 1
    if depth:
        return None
    body = clean[match.end():end - 1]
    return re.findall(r'\bvirtual\s+[^;{}]*?(?<!\w)(~?\w+)\s*\(', body)


def find_header(root, name):
    if name == '?':
        return '', []
    search = subprocess.run(['rg', '-l', rf'\bclass\s+{re.escape(name)}\b',
                             str(root / 'reference/CnC_Generals_Zero_Hour/GeneralsMD'),
                             '--iglob', '*.h'], capture_output=True, text=True)
    if search.returncode not in (0, 1):
        raise RuntimeError(search.stderr.strip())
    for text in search.stdout.splitlines():
        path = Path(text)
        virtuals = class_virtuals(path.read_text(encoding='utf-8', errors='replace'), name)
        if virtuals is not None:
            return path.relative_to(root).as_posix(), virtuals
    return '', []
