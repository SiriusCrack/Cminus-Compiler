TESTBATCH=testDataA2

for i in ./TestData/$TESTBATCH/*.c-; do
	echo $i
	./src/c- $i
done
