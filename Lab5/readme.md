Dzisiejsze zadanie polega na stworzeniu skryptu (albo kilku poleceń niezależnych od siebie) generującego wykres kursu USD do złotego w całym 2024 roku. Dodatkowo, jeśli skrypt będzie uruchomiony z 3 argumentami, to:

pierwszy powinien określać walutę (USD, EUR, CHF), której wykres do złotówki będziemy wyświetlać;  
drugi powinien określać datę początkową  
trzeci powinien określać datę końcową  

Skrypy.sh:
```bash
#!/bin/bash

WALUTA=${1:-USD}
DATA_OD=${2:-2024-01-01}
DATA_DO=${3:-2024-12-31}

curl -s "http://api.nbp.pl/api/exchangerates/rates/A/$WALUTA/$DATA_OD/$DATA_DO/?format=json" | jq -r '.rates[] | "\(.effectiveDate) \(.mid)"' > dane.txt

gnuplot -persist <<EOF
set xdata time
set timefmt "%Y-%m-%d"
set format x "%d.%m"
set title "Kurs $WALUTA do PLN"
set xlabel "Data"
set ylabel "Kurs"
set grid
plot "dane.txt" using 1:2 with lines title "$WALUTA"
EOF
```
