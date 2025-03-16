--- ZADANIE 1 ---

Napisz wyrażenia regularne, które sprawdzą:

- Czy podany tekst jest adresem e-mail:
grep -E "[a-z0-9._]{1,40}@[a-z0-9.-]+\.[a-z]{2,4}" email.txt
- Czy podany tekst jest prawidłowym imieniem (zaczyna się od wielkiej litery i zawiera tylko litery):
 grep -E "^[A-ZĄĆĘŁŃÓŚŹŻ][a-ząćęłńóśźż]{1,1018}$" names.txt 
 - Czy podany teks jest prawidłowym polskim kodem pocztowym (69-420):
 grep -E "^[0-9]{2}-[0-9]{3}$" indexes.txt

 --- ZADANIE 2 ---
 
