set -xe
rm build/rkey
make 
LD_LIBRARY_PATH="$LD_LIBRARY_PATH:./raylib-5.0_linux_amd64/lib/" ./build/rkey $1
