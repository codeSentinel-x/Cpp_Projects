#!/bin/bash

# Check if a commit message is provided
if [ -z "$1" ]; then
    echo -e "\033[31m No commit message provided.\033[0m"
    exit 1
fi

# Add all changes to the staging area
git add --all

# Commit changes with the provided message
git commit -m "$1"

# Get the remote URL and format it for the commit link
REMOTE_URL=$(git config --get remote.origin.url)
COMMIT_HASH=$(git log -1 --pretty=format:"%H")

# Adjust URL for web-based repository (assuming GitHub, GitLab, etc.)
COMMIT_URL=$(echo "$REMOTE_URL" | sed 's/\.git$/\/commit\/'"$COMMIT_HASH"'/')

echo "Commit URL: $COMMIT_URL"
