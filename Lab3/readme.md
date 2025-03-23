#### Zad 1
Napisz skrypt, który przeskanuje katalog Dokumenty i podkatalogi w poszukiwaniu plików .txt i wyświetli ich pełną listę
#!/bin/bash

find ~/Dokumenty -type f -name "*.txt"</code>

#### Zad 2
Poprzedni skrypt rozszerz o pakowanie tego zestawu do skompresowanego pliku o nazwie “[user]_backup_[data_wykonania]”. Takie backupy powinny być umieszczone w katalogu ~/.backups
#!/bin/bash

user=$(whoami)
date=$(date +"%Y-%m-%d_%H-%M")
backup_path="$HOME/.backups"
zip_name="${user}_backup_${date}.tar.gz"

find ~/Dokumenty -type f -name "*.txt" | tar -czf "$backup_path/$zip_name" -T -

#### Zad 3
Stwórz zadanie, które cyklicznie (np. raz dziennie) wykona ten skrypt
0 0 * * * cd ~/Dokumenty ./zip_2.sh

#### Zad 4
Napisz skrypt + crontaba, który cyklicznie sprawdzać będzie użycie przestrzeni dyskowej przez backupy w naszym katalogu i jeśli ta zużyta przestrzeń będzie większa niż X (do samodzielego ustalenia), to powiadomi użytkownika. Przydać się mogą polecenie df do sprawdzenia zajętego miejsca, awk do wyciągnięcia odpowiedniej wartości i pakiet mailx. To zadanie zrobimy wspólnie na zajęciach.
0 1 * * * cd ~/Dokumenty ./check_size.sh

#!/bin/bash

path_of_backup="$HOME/.backups"

max_size=100

used_kb=$(du -sk "$path_of_backup" | awk '{print $1}')

if [ "$used_kb" -gt "$max_size" ]
then
	echo "You use more then 100 kb for backups" | mailx -s "Size of backup" s30023@szuflandia22.pjwstk.edu.pl
else
	echo "Size of backups are fine" | mailx -s "Size of backup" s30023@szuflandia22.pjwstk.edu.pl
fi

