#!/bin/bash
arr=("24060123140130" "24060123130052" "24060123120043" "24060122140185" "24060123140123" "24060123140188" "24060123120010" "24060123130059" "24060123140153" "24060123130114" "24060123120007" "24060123120018" "24060123140145" "24060123130071" "24060123140053" "24060122140181")
echo "# **Kumpulin sesuai folder NIM yaaaaaaaaa**" > "readme.md"
for i in ${arr[@]}; do
	mkdir -p $i
	for x in {1..6}; do
		mkdir -p "$i/Pertemuan $x"
		echo "# **Jangan salah folder -__-**" > "$i/Pertemuan $x/readme.md"
	done
done
