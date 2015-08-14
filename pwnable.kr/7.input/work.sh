#!/bin/bash
#export '\xde\xad\xbe\xef'='\xca\xfe\xba\xbe'
#export "$(echo '\xde\xad\xbe\xef')"="$(echo '\xca\xfe\xba\xbe')"
cd `dirname $0`
#echo '\x00\x00\x00\x00' > $'\n'
./gen.sh > arglist
xargs -a arglist -0 -d '%' ~/input_try <./in 2<./errin  #| sed -f ./empty > /tmp/wtf 
