— ZADANIE 1 —

mkdir Dokumenty 
cd Dokumenty/
mkdir JAZ Przepisy SOP PRI
ls
cd Przepisy/
mkdir Kolacje Obiady Sniadania
ls
cd ~
history >> his_1.txt

— ZADANIE 2 —

wget mhyla.com/repo/cars.txt

sort -r cars.txt | nl | head -n 20 > lista.txt

— ZADANIE 3 —

read index

grep "^ *$index\s" lista.txt

^ - szuka na początku linii
" *" - wszazuje, że mogą być puste przed liczbą
\s - tabulacja po liczbue
