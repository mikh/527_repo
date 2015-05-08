rm -rf p4
rm -rf p4.zip
mkdir p4

echo "Part IV script start"

echo "P1"
gcc -w -O1 -o test_transpose test_transpose.c -lrt
./test_transpose > p4/pd_1.txt


echo "P2"
gcc -w -O1 -o test_transpose_2 test_transpose_2.c -lrt -lm
./test_transpose_2 > p4/pd_2.txt


echo "P3"
gcc -w -O2 -o test_transpose test_transpose.c -lrt
./test_transpose > p4/pd_3.txt


echo "P4"
gcc -w -O3 -o test_transpose test_transpose.c -lrt
./test_transpose > p4/pd_4.txt


echo "Part IV script done"

zip -r p4.zip p4
