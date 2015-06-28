#!/bin/sh

tests="$(find suites -name '*.mk')"

# build and run tests
for t in ${tests}
do
	make -f $t clean all
	if [ $? -ne 0 ]; then
		echo "ERROR building test: $t"
		exit 1
	fi
done

# combine test results
result="result.xml"
rm -f result.xml
results="$(echo ${tests} | sed 's#suites/\([^.]*\)\.mk#testobj/\1/test-\1.xml#g')"
echo "<?xml version=\"1.0\"?>" > ${result}
echo "<testsuites>" >> ${result}
cat ${results} >> ${result}
echo "</testsuites>" >> ${result}
