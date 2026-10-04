#!/bin/sh

set -e
sudo apt-get update
sudo apt-get install -y build-essential wget
mkdir -p /tmp/inetutils-build
wget -O /tmp/inetutils-build/inetutils-2.0.tar.gz https://ftp.gnu.org/gnu/inetutils/inetutils-2.0.tar.gz
tar xzf /tmp/inetutils-build/inetutils-2.0.tar.gz -C /tmp/inetutils-build
cd /tmp/inetutils-build/inetutils-2.0
./configure --prefix=/usr/local/inetutils-2.0
make
sudo make install
echo 'export PATH="/usr/local/inetutils-2.0/bin:$PATH"' >> ~/.bashrc
