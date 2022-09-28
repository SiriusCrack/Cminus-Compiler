TESTBATCH=testDataA2

for i in ./TestData/$TESTBATCH/*.c-; do
	echo $i
	./src/c- -p $i
done
