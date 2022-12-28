echo "____________COMPILING...____________\n"
make -C ../../ re && make -C . re  && make -C ../position re
echo "____________TEST 1 [test/file.c]________\n"
./../../compiler -E --EXTS="../position/ext.so ext.so" test/file.c > test/file_tmp.c && cc ../../lib/ft/libft.a test/file_tmp.c &&  ./a.out
echo "____________TEST 2 [test/define.c]______\n"
./../../compiler -E --EXTS="../position/ext.so ext.so" test/define.c > test/define_tmp.c && cc ../../lib/ft/libft.a test/define_tmp.c &&  ./a.out
echo "____________TEST 2 [test/line.c]______\n"
./../../compiler -E --EXTS="../position/ext.so ext.so" test/line.c > test/line_tmp.c && cc ../../lib/ft/libft.a test/line_tmp.c &&  ./a.out
#./../../compiler -E --EXTS="ext.so" test/define.c 