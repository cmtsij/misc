#check parameter
if [ "$#" != "1"  ];then
	echo "Usage: $0 [ipk_file]"
	exit
fi

#check ar file type
if ! ar t $1 > /dev/null 2>&1 ;then 
	echo "ERROR: file type error: $1"
	exit
fi

#parse parameter
ipkfile=$1
package=`basename $ipkfile | sed -e "s/_[0-9]*\.[0-9]*\.[0-9]*\.[0-9a-zA-Z_]*\.ipk//"`
version=`basename $ipkfile | sed -e 's/[^0-9]*\([0-9\.]*\)[^0-9]*/\1/'`

if [ "$package" == "" ];then
	echo "ERROR: failed to parse package."
	exit
fi

ipkdir=$PWD/$package

#delete old target
rm -rf $ipkdir
mkdir $ipkdir

#backup original ipk, and unpack it
echo "==== unpack ipkg ===="
cp $ipkfile $ipkdir
cd $ipkdir
ar xv `basename $ipkfile`

echo "==== unpack control.tar.gz ===="
mkdir $ipkdir/control
cd $ipkdir/control
tar zxvf $ipkdir/control.tar.gz

echo "==== unpack data.tar.gz ===="
mkdir $ipkdir/data
cd $ipkdir/data
tar zxvf $ipkdir/data.tar.gz

#echo "==== remove unnecessary files ===="
cd $ipkdir
rm -f *.ipk control.tar.gz data.tar.gz sign ipkginfo

echo "==== update and show ipkg info ===="
sed -i -e "s/^Package:.*/Package:\ $package/" -e "s/^Version:.*/Version:\ $version/" $ipkdir/control/control
cat $ipkdir/control/control

