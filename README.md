# Project 2 | CITS2002 | Duplicate Files in C

Created for project 2 of CITS2002 Systems Programming at UWA.

The aim of the program is to find duplicate files using a SHA2 hash function to check for duplicates in the C programming language.

Checking for duplicates can be done within files.c - as each file is processed, its SHA256 can be checked against all other SHA256s seen so far.
If strcmp == 0 on any others seen so far -- we knwo there is a duplicate file.

same for checking hashes with -h

figure out hidden file stuff
