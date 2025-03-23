#!/bin/bash

user=$(whoami)
date=$(date +"%Y-%m-%d_%H-%M")
backup_path="$HOME/.backups"
zip_name="${user}_backup_${date}.tar.gz"

find ~/Dokumenty -type f -name "*.txt" | tar -czf "$backup_path/$zip_name" -T -
