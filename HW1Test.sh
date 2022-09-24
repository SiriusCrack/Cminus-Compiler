TESTBATCH=testDataA1

for i in ./TestData/$TESTBATCH/*.c-; do
	i=${i%.c-}
	echo $i
	diff <(./src/c- $i.c-) $i.out
done
