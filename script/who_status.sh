log=/tmp/who.log

check_interval=60


while getopts ":h:t:" opt ; do
	case "$opt" in
	t)
		check_interval=$OPTARG
		;;
	h)
		echo "show current who is logged on"
		exit 0
		;;
	\?)
		echo "Invalid option: -$OPTARG" >&2
		exit 1
		;;
	:)
		echo "Option -$OPTARG requires an argument" >&2
		exit 1
		;;
	esac
done





who_last=""
while [ 1 ];do
	who_now="$(who -q | head -n 1 | sed "s/\ /\n/g" | sort | uniq -c |awk '{print "["$2"]*"$1" "}' | tr -d "\n")"

	if [ "$who_now" != "$who_last"  ];then
		date_str=$(date +'%F %T')
		echo "$date_str : $who_now"
		who_last=$who_now;
	fi

	sleep $check_interval;
done

