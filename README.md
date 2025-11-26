Simplified command line interpreter built using C++.
_____________________________________________________

command options are represented inside brackets - (option)
Commands: 

echo
date
time
head (-nX)
wc (-c or -w)
touch
rm
tr
truncate
prompt
batch

_____________________________________________________

Examples:

Simple echo commands:
echo "Hello!"

Pipeline example:
echo "hello!" | echo

Creating a file that displays current date:
date >output.txt

Count the number of characters in a text file:
wc -c <input.txt

_____________________________________________________




