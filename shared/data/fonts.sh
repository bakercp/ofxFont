#!/usr/bin/env bash

THIS_PATH=$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)
THIS_NAME=$(basename "${BASH_SOURCE[0]%.*}")
INSTALL_PATH=${THIS_PATH}/${THIS_NAME}
mkdir -p ${INSTALL_PATH}

echo "Installing ${THIS_NAME} data ..."

INSTALL_PATH=${INSTALL_PATH}
mkdir -p ${INSTALL_PATH}
BASE_URL="https://fonts.google.com/download?family="
FILES=(
  "Roboto"
  "Lato"
  "Raleway"
  "Oswald"
  "Playfair+Display"
)

for file in "${FILES[@]}"
do
  # See if the directories exist.
  if ! [ -d ${INSTALL_PATH}/${file} ]; then
    echo "Downloading ${file}"
    curl -L --progress-bar "${BASE_URL}${file}" > "${INSTALL_PATH}/${file}.zip"
    unzip "${INSTALL_PATH}/${file}.zip" -d "${INSTALL_PATH}/${file}"
    rm ${INSTALL_PATH}/${file}.zip
  fi
  echo "✅ ${INSTALL_PATH}/${file}"
done
