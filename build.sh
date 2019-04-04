#!/bin/bash
# file: build.sh

cd frontend
yarn && yarn build
cd ..

rm -rf server/static
cp -rf frontend/build server/static

cd server
stack build
