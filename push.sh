#!/bin/bash

if [ -z "$1" ]; then
    echo -e "\033[31m No commit message provided.\033[0m"
    exit 1
fi

git add --all
git commit -m "$1"


echo "Commit URL: "$(git config --get remote.origin.url)" | sed 's/\.git$/\/commit\/'"$(git log -1 --pretty=format:"%H")
"'/'"
