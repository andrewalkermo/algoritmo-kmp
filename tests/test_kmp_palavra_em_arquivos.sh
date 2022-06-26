#!/bin/bash
result=0
cp -r src/ tests/src_temp/

rm -f arvore.dat
gcc tests/src_temp/kmp/kmp.c tests/src_temp/utils/utils.c tests/src_temp/arvore_obras/arvore_obras.c tests/src_temp/consultas/consultas.c tests/src_temp/operacoes_arquivo/operacoes_arquivo.c tests/src_temp/main.c -std=c99 -Wall -o main
cd tests/kmp/arquivos/
../../../main < 1.in > test.out
diff -w -u1 --color=auto --palette='ad=1;3;38;5;154:de=1;3;38;5;9' test.out 1.out && echo "OK" || result=1
rm -f arvore.dat
rm -f test.out
cd ../../../
rm -f main
rm -rf tests/src_temp/
exit $result
