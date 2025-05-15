#!/bin/bash

# 🐧 Linux Basic Commands Demo Script

echo "📁 Current Directory:"
pwd

echo -e "\n📂 Listing files:"
ls -l

echo -e "\n📂 Create a new directory called 'demo-dir':"
mkdir demo-dir
ls -l

echo -e "\n📂 Change into the new directory:"
cd demo-dir
pwd

echo -e "\n📄 Create a new text file:"
touch example.txt
ls -l

echo -e "\n✏️ Write text to the file:"
echo "Hello from Linux!" > example.txt
cat example.txt

echo -e "\n🔙 Go back to previous directory:"
cd ..
pwd

echo -e "\n🗑️ Remove the directory and file:"
rm -r demo-dir
ls -l

echo -e "\n✅ Script complete!"
