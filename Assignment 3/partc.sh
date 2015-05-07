rm -rf p3
rm -rf p3.zip
mkdir p3

gcc -O1 -o test_sse test_intrinsics.c -lrt -lm
./test_sse > p3/pc_1.txt

gcc -O1 -o test_sse_2 test_intrinsics_2.c -lrt -lm
./test_sse_2 > p3/pc_2.txt

gcc -O1 -o test_sse_3 test_intrinsics_3.c -lrt -lm
./test_sse_3 > p3/pc_3.txt

zip -r p3.zip p3
git add p3.zip