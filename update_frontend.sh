#!/bin/bash
# file: update_frontend.sh

cd frontend
yarn build
cd ..

rm -rf server/static
cp -rf frontend/build server/static
