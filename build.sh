#! /bin/bash
make
if [ $? == 0  ]; then
    ./mkdcdisc -e aos.elf -d assets -o aos.cdi
    flycast aos.cdi
else
    echo "Failed to compile."
fi
