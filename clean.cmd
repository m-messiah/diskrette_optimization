@echo off
pushd %1
erase /F /S /Q *.obj *.~* *.tds *.dsk *.ncb *.pdb *.idb *.ilk *.pch 2>nul
popd
