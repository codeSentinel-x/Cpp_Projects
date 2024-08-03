#!/bin/bash

    if [ -z "$1" ]; then
        echo "\033[31;No commit message provided."
        exit 1
    fi

    git add --all
    git commit -m "$1"
    git push -u origin master #--force 
    echo "https://github.com/codeSentinel-x/Cpp_Projects/commit/$(git log -1 --pretty=format:"%H")"

