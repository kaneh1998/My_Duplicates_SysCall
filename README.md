# Project 2 | CITS2002 | Duplicate Files in C

Created for project 2 of CITS2002 Systems Programming at UWA.

The aim of the program is to find duplicate files using a SHA2 hash function to check for duplicates in the C programming language.

USAGE
===================

compile with: make -f Makefile

run with: ./duplicates [option] [path]


OPTIONS
===================

**-a**    
Checks all hidden files for duplicates (default usage of program will ignore hidden files)

**-A**    
This option indicates if the program attempts the advanced version of the project.
      duplicates -A produces no output at all, simply terminating with EXIT_SUCCESS (for advanced) or with EXIT_FAILURE (for basic).
      
**-f** _filename_

find and list, one per line, the relative pathnames of all files whose SHA2 hash matches that of the indicated file. 
      The name of the indicated file is not listed.
      duplicates -f terminates with EXIT_SUCCESS if any matching files are found, or with EXIT_FAILURE otherwise.

**-h**   _hash_

find and list, one per line, the relative pathnames of all files with the indicated SHA2 hash.
      duplicates -h terminates with EXIT_SUCCESS if any matching files are found, or with EXIT_FAILURE otherwise.

**-l**	 
duplicates lists all duplicate files found. Each line of output consists of the relative pathnames of two or more files that are duplicates of each other. 
      The pathnames of duplicate files (on the same line line) must be separated by the TAB character.

**-q**	 
duplicates executes quietly, simply testing if the named directory contains any duplicate files.
      duplicates -q produces no output at all, simply terminating with EXIT_SUCCESS if there are no duplicates (i.e. storage is already minimized), 
      or with EXIT_FAILURE otherwise.

