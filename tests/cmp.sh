if [ "$(cat $1)" = "$(./a.out)" ]
then
	echo "pass"
else
	echo "fail"
fi
