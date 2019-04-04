{-# LANGUAGE DataKinds #-}
{-# LANGUAGE DeriveGeneric #-}
{-# LANGUAGE OverloadedStrings #-}
{-# LANGUAGE TypeOperators #-}

module Learn.Crypto.Server where

import Data.Proxy (Proxy(..))
import Network.Wai (Application)
import Network.Wai.Handler.Warp (runSettings, setPort, defaultSettings)
import Servant
import Servant.API

type Api = Raw

app :: Application
app = serve serverApi server

serverApi :: Proxy Api
serverApi = Proxy

server :: Server Api
server = serveDirectoryWebApp "static"

runServer :: IO ()
runServer = do
  let settings = setPort 8001 $ defaultSettings
  runSettings settings app
