rm -rf p3
rm -rf p3.zip
mkdir p3

echo "Part III script start"

echo "P1"
gcc -w -O1 -o test_sse test_intrinsics.c -lrt -lm
./test_sse > p3/pc_1.txt

echo "P2"
gcc -w -O1 -o test_sse_2 test_intrinsics_2.c -lrt -lm
./test_sse_2 > p3/pc_2.txt

echo "P3"
gcc -w -O1 -o test_sse_3 test_intrinsics_3.c -lrt -lm
./test_sse_3 > p3/pc_3.txt

echo "Part III script done"

zip -r p3.zip p3
