#!/bin/bash
# file: build.sh

cd learn-crypto-frontend
yarn && yarn build
cd ..

rm -rf learn-crypto-server/static
cp -rf learn-crypto-frontend/build learn-crypto-server/static

cd learn-crypto-server
stack build
