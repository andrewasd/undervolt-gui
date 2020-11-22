#!/bin/bash

rm -rf bin
mkdir bin
qmake .
make 
mv *.o bin
mv undervolt bin
chmod +x run.sh


