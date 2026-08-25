#!/bin/bash

## =================================================================
## BUSTUB PACKAGE INSTALLATION
## This script downloads the sql dataset and set it up in sqlite
## =================================================================

pushd ./sql
if [[ ! -e imdb-cmudb2022.db.gz && ! -e imdb-cmudb2022.db ]]
then 
  wget https://15445.courses.cs.cmu.edu/fall2022/files/imdb-cmudb2022.db.gz
  gunzip imdb-cmudb2022.db.gz
  sqlite3 imdb-cmudb2022.db < setup.sql
fi
popd
