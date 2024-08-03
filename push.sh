#!/bin/bash

if [ -z "$1" ]; then
    echo -e "\033[31mNo commit message provided.\033[0m"
    exit 1
fi

git add --all
git commit -m "$1"

commit_url=$(git config --get remote.origin.url)
commit_hash=$(git log -1 --pretty=format:"%H")
commit_url="${commit_url/.git/}/commit/${commit_hash}"

echo "Commit URL: $commit_url"
