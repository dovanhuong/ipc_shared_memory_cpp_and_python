#!/bin/bash
git pull
git add .
git commit -m "$1"
git branch -M main
#git remote add origin https://github.com/dovanhuong/ipc_shared_memory_cpp_and_python.git
git push -u origin main
echo "complted commit source ...\n"
