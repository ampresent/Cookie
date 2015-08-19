bash -c "while :; do echo 1; echo 222222; done" | ./lotto | grep -v "bad" |grep -v "Exit"|grep -v "Help" |grep -v "Select Menu"|grep -v "invalid"|grep -v "Play"|grep -v "Lotto Start"
