## Description

Makefile suitable for the following project structure:
 src
 |_dir-1
     |_1.h
     |_1.c
 
 |_dir-2
     |_2.h
     |_2.c
 
 |_dir-3
     |_3.h
     |_3.c
 |
 |file-1.c
 |file-1.h
 |file-2.c
 |
 |_obj
     |_src + including corresponding '.o' files
 |
 |_build
      |_executable
 makefile

## Usage

+ make clean - delete all object and exe files
+ make - compile src
