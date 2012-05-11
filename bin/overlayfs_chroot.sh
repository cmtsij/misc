#!/bin/sh -e

pid=$$
export debian_chroot=chroot_$pid

shadow_root=/tmp/chroot/$pid

## remove last one if exist
if [ -d $shadow_root ];then
	rm -rf "$shadow_root";
fi

## create rootfs
mkdir -p $shadow_root

## chroot script
cat << EOF > $shadow_root/.chroot.sh
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
mount -t overlayfs -o lowerdir=/,upperdir=$shadow_root overlayfs $shadow_root
chroot $shadow_root sh -e /.chroot.sh

## exit
umount $shadow_root
