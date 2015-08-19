while :
do
	ulimit -s unlimited
	ldd ./ascii_easy
	ulimit -s 1024
done
