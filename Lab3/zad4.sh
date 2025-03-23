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
