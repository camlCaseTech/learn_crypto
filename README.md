# learn_crypto

## Pre-requisites

### yarn

Install yarn:

[How to Install Yarn on Ubuntu 18.04](https://linuxize.com/post/how-to-install-yarn-on-ubuntu-18-04/)

```
curl -sS https://dl.yarnpkg.com/debian/pubkey.gpg | sudo apt-key add -
echo "deb https://dl.yarnpkg.com/debian/ stable main" | sudo tee /etc/apt/sources.list.d/yarn.list
sudo apt update
sudo apt install yarn
```

### stack

[The Haskell Tool Stack](https://docs.haskellstack.org/en/stable/README/)

```
curl -sSL https://get.haskellstack.org/ | sh
```


## build and run

Open two command line interfaces and `cd frontend`. In the first run:

```
yarn 
yarn start
```

In the second run:

```
yarn server
```

And go to `localhost:8001`.



## ignore rest for now


## build

The build script: 
- builds `frontend` with `yarn && yarn build`
- copies the output files from `frontend/build` to `server/static`
- build `server` with `stack build`

```
bash build.sh
```

## run

Once the server has been built. You can run it with the following commands:

```
cd server
stack exec server
```

Now you can see it running at: http://localhost:8001/index.html
