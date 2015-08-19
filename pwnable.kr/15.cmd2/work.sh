# I don't really need backslash /, because I have PATH env variable.

./cmd2 'cd ..;cd ..;cd bin;export PATH=$(pwd);cd ..;cd home;cd cmd2;cat *|less'
