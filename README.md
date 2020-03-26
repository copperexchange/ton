# Some helpful commands


Regerenate tonlib_api.tlo
```
tl-parser -e ./tl/generate/scheme/tonlib_api.tlo ./tl/generate/scheme/tonlib_api.tl
```


Build tl-parser
```
git clone git@github.com:vysheng/tl-parser.git
cd tl-parser
./configure
make all
cp tl-parser /usr/local/bin
```


Build on mac
```
brew install openssl
brew install libmicrohttpd

git clone git@github.com:copperexchange/ton.git
cd ton 
git submodule update --recursive
cd ../
mkdir ton-build
cd ton-build

OPENSSL_ROOT_DIR=/usr/local/Cellar/openssl@1.1/1.1.1d/ cmake -D DCMAKE_BUILD_TYPE=Release ../ton
cmake --build . --target tonlibjson
cmake --build . --target fiftlib
cmake --build . --target fift
cmake --build . --target func
```
