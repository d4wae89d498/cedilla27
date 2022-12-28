echo "____________COMPILING...____________\n"
make -C ../../ re && make -C . re 
echo "____________TEST 1________\n"
./../../compiler -E --EXTS="ext.so" test/file.c > test/file_tmp.c && cc ../../lib/ft/libft.a test/file_tmp.c &&  ./a.out
echo "____________TEST 2________\n"
./../../compiler -E --EXTS="ext.so" test/define.c > test/define_tmp.c && cc ../../lib/ft/libft.a test/define_tmp.c &&  ./a.out

#./../../compiler -E --EXTS="ext.so" test/define.c 