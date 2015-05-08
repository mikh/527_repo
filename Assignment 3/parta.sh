rm -rf p1
rm -rf p1.zip
mkdir p1

echo "Part I script start"

echo "P1"
gcc -w -o -march=native test_align test_align.c -lrt
./test_align > p1/pa_1.txt

echo "P2"
gcc -w -o -march=native test_align_2 test_align_2.c -lrt
./test_align_2 > p1/pa_2.txt

echo "Part I script done"

zip -r p1.zip p1
