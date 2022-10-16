TESTBATCH=working

for i in ./TestData/$TESTBATCH/*.c-; do
	echo $i
	#j=${i##*/}
	j=${i%.c-}
	j=$j.out
	diff -rs <(./src/c- -P $i) $j | egrep '^Files .+ and .+ are identical$' | awk -F '(Files | and | are identical)' '{print "MATCH"}'
done
