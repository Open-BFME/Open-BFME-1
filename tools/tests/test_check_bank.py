"""A stash is reported by what it compiles to, and checking it never leaves a copy behind."""
from pathlib import Path
import sys

import pytest

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import check_bank

SYMBOL = '?Run@Worker@@QAEXXZ'


@pytest.fixture
def stash(tmp_path, monkeypatch):
    monkeypatch.setattr(check_bank, 'ATTEMPTS', tmp_path / 'attempts')
    monkeypatch.setattr(check_bank, 'WORK', tmp_path / 'work')
    check_bank.ATTEMPTS.mkdir()
    path = check_bank.ATTEMPTS / '0x00001000.cpp'
    path.write_text(f'// {SYMBOL}\n// partial score=0.7 date=2026-09-01\nvoid f() {{}}\n', encoding='utf-8')
    return path


def compiles_to(tmp_path, monkeypatch, names):
    obj = tmp_path / 'stash.obj'
    obj.write_bytes(b'object')
    monkeypatch.setattr(check_bank.build, 'read_object_symbols',
                        lambda _data: [{'name': name, 'section': 1} for name in names])
    return lambda _source: obj


def test_header_symbol_leads_the_first_line():
    assert check_bank.header_symbol(f'// {SYMBOL}\n// partial score=0.7\n') == SYMBOL
    assert check_bank.header_symbol(f'// {SYMBOL} (identity unknown)\n') == SYMBOL
    assert check_bank.header_symbol('// cl: /EHsc\n') is None
    assert check_bank.header_symbol('// Scratch body for the socket reader\n') is None
    assert check_bank.header_symbol('int x;\n') is None
    assert check_bank.header_symbol('') is None


def test_nearest_symbol_ignores_data_and_string_symbols():
    defined = ['$SG1234', '??_C@_05ABCDE@hello@', '.text', '?Run@Worker_Renamed@@QAEXXZ', '?Stop@Other@@QAEXXZ']
    assert check_bank.nearest_symbol(defined, SYMBOL) == '?Run@Worker_Renamed@@QAEXXZ'
    assert check_bank.nearest_symbol(['$SG1', '.data'], SYMBOL) is None


def test_first_error_prefers_the_compiler_diagnostic():
    printout = "x.cpp(3) : warning C4101: 'a'\nx.cpp(9) : error C2065: 'NULL' : undeclared identifier\ncompile failed\n"
    assert check_bank.first_error(printout) == "C2065: 'NULL' : undeclared identifier"
    assert check_bank.first_error("x.cpp(1) : fatal error C1083: Cannot open include file") \
        == 'C1083: Cannot open include file'
    assert check_bank.first_error('toolchain missing\n') == 'toolchain missing'
    assert check_bank.first_error('') == 'compile failed'


def test_missing_stash_and_bad_header(stash):
    assert check_bank.check(0x2000, 10)[0] == 'missing'
    stash.write_text('void f() {}\n', encoding='utf-8')
    assert check_bank.check(0x1000, 10)[0] == 'bad-header'


def test_compile_failure_reports_the_first_error(stash):
    def fails(_source):
        raise RuntimeError("x.cpp(9) : error C2065: 'NULL' : undeclared identifier\n")
    assert check_bank.check(0x1000, 10, fails) == ('no-compile', "C2065: 'NULL' : undeclared identifier")
    assert not list(check_bank.WORK.iterdir())


def test_body_under_another_name_is_named(stash, tmp_path, monkeypatch):
    compile_source = compiles_to(tmp_path, monkeypatch, ['?Run@Worker_Renamed@@QAEXXZ'])
    assert check_bank.check(0x1000, 10, compile_source) == ('other-symbol', '?Run@Worker_Renamed@@QAEXXZ')
    assert not list(check_bank.WORK.iterdir())


def test_matching_symbol_is_measured_on_a_copy(stash, tmp_path, monkeypatch):
    seen = []
    compile_source = compiles_to(tmp_path, monkeypatch, [SYMBOL])
    monkeypatch.setattr(check_bank, 'measure', lambda _obj, symbol, rva, size: seen.append((symbol, rva, size)) or (12, 3))
    before = stash.read_bytes()
    assert check_bank.check(0x1000, 10, compile_source) == ('ok', 'ours=12 retail=10 diffs=3')
    assert seen == [(SYMBOL, 0x1000, 10)]
    assert stash.read_bytes() == before
    assert not list(check_bank.WORK.iterdir())


def test_naming_nothing_is_a_usage_error(monkeypatch):
    monkeypatch.setattr(sys, 'argv', ['check_bank.py'])
    with pytest.raises(SystemExit) as result:
        check_bank.main()
    assert result.value.code == 2
