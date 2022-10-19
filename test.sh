TESTBATCH=working

for i in ./TestData/$TESTBATCH/*.c-; do
	echo $i
	#j=${i##*/}
	j=${i%.c-}
	j=$j.out
	diff -rs <(./src/c- -P $i) $j | grep -E '^Files .+ and .+ are identical$' | awk -F '(Files | and | are identical)' '{print "MATCH"}'
done
