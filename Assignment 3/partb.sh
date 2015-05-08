rm -rf p2
rm -rf p2.zip
mkdir p2
echo "Part II script start"

echo "P1"
gcc -w -O1 -o test_combine8 test_combine8.c -lrt -lm
./test_combine8 > p2/pb_1.txt

echo "P2"
gcc -w -O1 -o test_combine8_2 test_combine8_2.c -lrt -lm
./test_combine8_2 > p2/pb_2.txt

echo "P3"
gcc -w -O1 -o test_dot8 test_dot8.c -lrt -lm
./test_dot8 > p2/pb_3.txt

echo "P4"
gcc -w -O1 -o test_dot8_2 test_dot8_2.c -lrt -lm
./test_dot8_2 > p2/pb_4.txt

echo "Part II script done"

zip -r p2.zip p2
