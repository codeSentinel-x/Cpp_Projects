#!/bin/bash

# Check if a commit message was provided
if [ -z "$1" ]; then
    echo -e "\033[31mError: No commit message provided.\033[0m"
    exit 1
fi

# Stage all changes
git add --all

# Commit changes with the provided message
git commit -m "$1"

# Push changes to the remote repository
git push -u origin master > /dev/null 2>&1

# Construct the commit URL
repo_url=$(git config --get remote.origin.url)
commit_hash=$(git log -1 --pretty=format:"%H")

# Convert .git to /commit/
commit_url=$(echo "$repo_url" | sed 's/\.git$/\/commit\/'"$commit_hash"'/')

# Output the commit URL
echo "Commit URL: $commit_url"
