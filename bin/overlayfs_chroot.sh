#!/bin/sh -e

pid=$$
export debian_chroot=chroot_$pid

upper_root=/tmp/chroot/$pid
shadow_root=/tmp/chroot/.$pid

## remove last one if exist
if [ -d $upper_root ];then
	rm -rf "$upper_root";
fi

## create rootfs
mkdir -p $upper_root
mkdir -p $shadow_root

## chroot script
cat << EOF > $upper_root/.chroot.sh
mount -t proc proc /proc
mount -t sysfs sysfs /sys
mount -t devtmpfs devtmpfs /dev
mkdir -p /dev/pts
mount -t devpts devpts /dev/pts
bash
umount /dev/pts 
umount /dev 
umount /sys 
umount /proc
EOF

#### START CHROOT HERE ####
mount -t overlayfs -o lowerdir=/,upperdir=$upper_root overlayfs $shadow_root
chroot $shadow_root sh -e /.chroot.sh

## exit
if (umount $shadow_root > /dev/null 2>&1) ; then
	echo -n "umount safe: "
else
	echo -n "umount fail: "
fi

echo "checkout [$upper_root]."
