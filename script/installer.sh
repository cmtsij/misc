#!/bin/bash -x

self=$0
line=$(grep --text -n "^LINE:" $0 | grep -o "^[0-9]\+")


pack_self()
{
	local ofile=$1
	shift
	if ( tar zcf .$$.tar.gz $* ); then
		head -n $((line)) $self > $ofile
		cat .$$.tar.gz >> $ofile
		rm .$$.tar.gz -f
		chmod 755 $ofile
	else
		echo "tar fail"
	fi
}


unpack_self()
{
	tail -n +$((line+1)) $self | tar zxf -

}

if [ "$1" == "pack" ]; then
	shift
	pack_self $*
elif [ "$1" == "unpack" ]; then
	shift
	unpack_self
else
	exit 1
fi

exit 0


LINE:
