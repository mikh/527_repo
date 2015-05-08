rm -rf p_all
rm -rf p_all.zip
mkdir p_all

./parta.sh
./partb.sh
./partc.sh
./partd.sh

cp p1.zip p_all
cp p2.zip p_all
cp p3.zip p_all
cp p4.zip p_all


zip -r p_all.zip p_all
git pull gg master
git add p_all.zip
git commit -m "testing data"
git push gg master
