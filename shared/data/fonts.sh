#!/usr/bin/env bash

THIS_PATH=$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)
THIS_NAME=$(basename "${BASH_SOURCE[0]%.*}")
INSTALL_PATH=${THIS_PATH}/${THIS_NAME}
mkdir -p ${INSTALL_PATH}

echo "Installing ${THIS_NAME} data ..."

echo ${INSTALL_PATH}

URL="https://fonts.google.com/download?family=Roboto|Lato|Raleway|Oswald|Playfair%20"
FILE="fonts.zip"
if ! [ -f ${INSTALL_PATH}/${FILE} ]; then
  echo "Downloading ${URL}"
  curl -L --progress-bar ${URL} > ${INSTALL_PATH}/${FILE}
  pushd ${INSTALL_PATH}
  unzip ${FILE}
  popd
fi

echo "✅ ${INSTALL_PATH}/${URL}"
