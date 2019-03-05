# CommandControl
Provides a framework to implement command line interface. You need to register functions associated with a command. Now all the registered commands will be supported as per your custom implementation. To use the function, simply type the name of the command in the prompt. The prompt looks like a typical bash shell.


# Sample Output
View on raw mode for better display.


'help' already registered!

>> Launching terminal...
$
$
$
$ hello
'hello' command not found! Try 'help'
$ help
Usage:
--------
help                                : Displays the help
generate samples                    : Generate some sample strings
show     samples                    : Display sample strings
clear samples                       : Clear sample strings vector
exit                                : Terminate application
quit                                : Terminate application
show                                : Display list of registered commands
$ generate samples
$ show samples
Sample size: 5
rvvui qpmzs eetrl vwnuk zvdip
$ show samples
Sample size: 5
rvvui qpmzs eetrl vwnuk zvdip
$ show

Registered commands:
* show
* help
* quit
* clear samples
* generate samples
* exit
* show samples

$ generate samples
$ show samples
Sample size: 10
rvvui qpmzs eetrl vwnuk zvdip lzsmh rwvhh yznzl kmdot dlrqv
$ lkd
'lkd' command not found! Try 'help'
$ df
'df' command not found! Try 'help'
$
$
$
$ clear samples
$ show samples
Sample size: 0

$ generate samples
$ show samples
Sample size: 5
vfkrj ubpju mykxc oonrf vsqhi
