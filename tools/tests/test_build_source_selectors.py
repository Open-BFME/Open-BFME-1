"""A full Code path must not also verify its reference twin."""
import sys
import tempfile
import unittest
from pathlib import Path
from unittest.mock import patch

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import build


def check_complete_path_and_partial_selectors(tmp_path):
    source = "Code/WW3D2/dx8wrapper.cpp"
    twin = "reference/GeneralsMD/Code/WW3D2/dx8wrapper.cpp"
    rows = [{"source": source, "name": "?Set@DX8Wrapper@@SAXXZ"},
            {"source": twin, "name": "?Reset@DX8Wrapper@@SAXXZ"}]
    for name in (source, twin):
        path = tmp_path / name
        path.parent.mkdir(parents=True, exist_ok=True)
        path.write_text("// fixture\n")
    with patch.object(build, "ROOT", tmp_path):
        build.complete_source_selector.cache_clear()
        try:
            def selected(selector):
                return [r["source"] for r in rows if build.selector_matches_row(selector, r)]
            for selector in (source, "./" + source, source.replace("/", "\\"), str(tmp_path / source)):
                assert selected(selector) == [source]
            assert selected(twin) == [twin]
            assert selected("dx8wrapper.cpp") == [source, twin]
            assert selected("WW3D2") == [source, twin]
            assert selected("DX8Wrapper") == [source, twin]
            assert selected("?Set@DX8Wrapper") == [source]
            assert selected(rows[0]["name"]) == [source]
            assert selected("missing.cpp") == []
            with patch.object(build, "ensure_case_shims"), \
                 patch.object(build, "verify_source_claims"), \
                 patch.object(build, "verify_functions"), \
                 patch.object(build, "load_function_rows", return_value=rows), \
                 patch.object(build, "verify_string_refs") as strings:
                build.main([source])
                strings.assert_called_once_with([rows[0]])
        finally:
            build.complete_source_selector.cache_clear()


class BuildSourceSelectorTests(unittest.TestCase):
    def test_complete_path_and_partial_selectors(self):
        with tempfile.TemporaryDirectory() as directory:
            check_complete_path_and_partial_selectors(Path(directory))


if __name__ == "__main__":
    unittest.main()
