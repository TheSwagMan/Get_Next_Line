rm tests/*
for ch in `echo {a..f}`
	do LC_CTYPE=C tr -dc 'A-Za-z0-9\n' < /dev/urandom | head -c 1024 > tests/"$ch"
done
