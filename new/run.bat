@echo off
flex lexer.l
bison -dy parser.y
gcc y.tab.c lex.yy.c sym_tab.c -o symbol_table.exe
symbol_table.exe < sample_input1.c
echo Output saved to output1.txt
type output1.txt
pause