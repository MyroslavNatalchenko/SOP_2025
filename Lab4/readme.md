# Zadanie 1
Uruchom program (np. openttd) w tle za pomocą polecenia nohup i zweryfikuj jego działanie za pomocą polecenia ps. Zmień jego priorytet za pomocą polecenia renice, aby porównać wpływ na wydajność programu. Następnie użyj polecenia kill, aby zabić proces.

**history:**
```bash
nohup openttd &
ps aux
ps aux | grep "openttd"
notice -n 1 -p 5776
kill 5776
```

![image](https://github.com/user-attachments/assets/c3ce6e46-27fb-4a28-8850-1ed3ce04e185)

---

# Zadanie 2
Uruchom program w tle za pomocą polecenia nohup i przekieruj jego wynik do pliku tekstowego.

**history:**
```bash
openttd 2> plik.txt &
cat plik.txt
```

![image](https://github.com/user-attachments/assets/ec85b3e3-33a7-4203-a4eb-63ff0725ef2e)

---

# Zadanie 3
Użyj polecenia top lub htop, aby monitorować wykorzystanie zasobów przez różne procesy na twoim systemie. Zidentyfikuj procesy, które zużywają najwięcej pamięci lub mocy obliczeniowej, i zmień ich priorytet za pomocą polecenia renice.

**history:**
```bash
top
renice -n 1 -p 2851
```

![image](https://github.com/user-attachments/assets/01a1d494-ef0d-4acb-8dd7-ad77baaedb71)
![image](https://github.com/user-attachments/assets/4a94b85f-dc3c-4e89-8f9a-e908509db8ea)

---

# Zadanie 4
Zastosuj polecenie nice do uruchomienia programu z niższym priorytetem niż standardowy. Następnie wykonaj inne zadanie na komputerze i zaobserwuj, jak program działa w tle z niższym priorytetem.

**history:**
```bash
nice -n 33 openttd &
top
```

![image](https://github.com/user-attachments/assets/0a347d28-4fa1-4425-a2e1-aaab9efb4069)

---

# Zadanie 5
Uruchom dowolny proces, a następnie wstrzymaj jego wykonywanie za pomocą polecenia kill -STOP. Następnie wznów jego wykonywanie za pomocą polecenia kill -CONT.

**history:**
```bash
openttd &
kill -STOP 7495
kill -CONT 7495
```

![image](https://github.com/user-attachments/assets/9b5cbce3-be93-432f-8bd3-017d22fde144)

---

# Zadanie 6 (https://askubuntu.com/questions/1423945/run-script-after-reboot)
Utwórz skrypt, który automatycznie uruchamia program po starcie systemu. Następnie zrestartuj system i upewnij się, że program uruchamia się automatycznie - wujek google albo prowadzący podpowiedzą, w razie czego.

```bash
crontab -e
@reboot /home/admin/skrypt.sh

sudo reboot
```
