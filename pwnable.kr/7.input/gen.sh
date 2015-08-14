#!/usr/bin/zsh
print -n '' > arglist

for i in {1..64}
do
	print -n '1%' >> arglist
done
print -n '\x00\x00%' >> arglist
print -n '\x20\n\r%' >> arglist
print -n '4569%' >> arglist
for i in {1..31}
do
	print -n 'D%' >> arglist
done
print -n 'D' >> arglist

print -n '' > ./in
print -n '' > ./errin

print -n "\x00\x0a\x00\xff" >> ./in
print -n "\x00\x0a\x02\xff" >> ./errin
