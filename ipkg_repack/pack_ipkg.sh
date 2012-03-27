#!/bin/sh

# $1: folder
# $2: ipkg file name

if [ "$#" != "3"  ];then
	echo "Usage: $0 [folder_name] [version] [platform]"
	exit
fi


dst=$PWD
package=$1
version=$2
platform=$3

prikey=$dst/prikey
passwd=gemtek

arlist="debian-binary data.tar.gz control.tar.gz openwmx.bin"


sign()
{
	if [ "$#" != "3"  ];then
		echo "sign invalid parameter";
		return
	fi
	
	ipkgfile=$1
	prikey=$2
	passwd=$3
	
	if $dst/signtool $ipkgfile $prikey $passwd ;then
		mv $ipkgfile.sign sign
		du -b $ipkgfile | cut -f 1 > ipkginfo
		ar r $ipkgfile ipkginfo sign
		rm -f ipkginfo sign
	else
		echo "sign failed";
	fi
}


ipkdir=$(cd $package;pwd)
ipkfile=$dst/$(basename $package)_${version}_${platform}.ipk

#clear old ipk
rm -f $ipkfile

#overwrite version
sed -i	-e "s/^Package:.*/Package:\ $(basename $ipkdir)/" \
		-e "s/^Version:.*/Version:\ $version/" \
		-e "s/^Architecture:.*/Architecture:\ $platform/" \
		$ipkdir/control/control


echo "==== ipkg info ===="
cat $ipkdir/control/control


echo "==== create control.tar.gz ===="
cd $ipkdir/control
tar zcvf ../control.tar.gz ./ --exclude "\.svn"


echo "==== create control.tar.gz ===="
cd $ipkdir/data
tar zcvf ../data.tar.gz ./ --exclude "\.svn"


echo "==== create ipk ===="
cd $ipkdir
for file in $arlist ;
do
	if [ -e "$file" ];then
		ar qv $ipkfile $file
	fi
done

echo "==== sign ipk ===="
sign $ipkfile $prikey $passwd


#echo "==== clean ===="
rm $ipkdir/control.tar.gz $ipkdir/data.tar.gz

