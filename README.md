# RenameFileForWeb

RenameFileForWeb is a little program I wrote to strip special characters out of filenames in preparation for being uploaded to Microsoft SharePoint.  SharePoint has (or had, they may have fixed it now) a linitation that it didn't recognise files with certain characters in the name.  RenameFilesForWeb goes through every file in a specified path and renames them according to this rule.

RenameFileForWeb outputs results to the standard output, therefore it is worth running it from the command prompt and redirecting the output to a file for review later, since if it cannot rename a file (maybe there's already a file with its intended name) it will flag this in the results.  These flagged files must then be renamed manually.

RenameFileForWeb is a Windows program (since the equivalent functionality for OS/X or Linux could be done in a shell script).  It can be compiled using MinGW's gcc or the Tiny C Compiler very simply (there is a "make.bat" for this purpose).  If you have a different compiler, you will need to work out your own commands to compile it.  RenameFilesForWeb uses the "kernel32" windows library, so be sure to have that for your preferred compiler.

## Characters removed

RenameFileForWeb removes the following characters from filenames:

* "&"
* "#"
* "@"
* "+"
* "\" (not that this is allowed in windows anyway.)

## Program Usage

rffw.exe [/r] <directory name>

Parameter | Use
--------- | ---
<directory name> | The directory path in which to rename files.
/r | Optional parameter.  With this, RenameFilesForWeb will go through the directory and specified subdirectories recursively.  Without it, the files in any subdirectories within the specified path will remain untouched.

The recursive ("/r") option is recommended for actual use since this will do all renames automatically.  Remember to redirect program output into a file in case of any files that are unable to be renamed.

### Important Note

Even _with_ the recursive option, RenameFilesForWeb will ignore files in any subdirectory beginning with a full stop ("."), since these directories are often used for system functionality.

## Credits

RenameFilesForWeb was originally created by DHeadshot (as part of DHSC) in 2016 and has been made available as open-source in 2017.

## Version History

* Version 1.20.00 - First version made open-source.  Added extra files for ease of compilation.
* Version 1.10.01 - Added usage information to program.
* Version 1.10.00 - Added the Recursive mode to rename all files in a directory tree.
* Version 1.00.00 - Initial version of the program.