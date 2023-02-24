pushd
cd .\CFILES
..\cloc-1.96.1 --by-file --include-ext=c,cpp --csv --quiet --out=..\CLOC_OUTPUT.CSV .\
popd
