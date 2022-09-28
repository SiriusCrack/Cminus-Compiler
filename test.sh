TESTBATCH=testDataA2

for i in ./TestData/$TESTBATCH/*.c-; do
	echo $i
	#j=${i##*/}
	j=${i%.c-}
	j=$j.out
	diff -rs <(./src/c- -p $i) $j | egrep '^Files .+ and .+ are identical$' | awk -F '(Files | and | are identical)' '{print "MATCH"}'
done
