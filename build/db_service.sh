#!/bin/sh
#
# chkconfig: 2345  80 50
# description: engine_server is for testing how to write service in Linux 
#              
# processname: engine_server
# 
# Source function library.
. /etc/rc.d/init.d/functions

ret=0

start() {
    # check fdb status
    echo "start engine_server"
    ./engine_server &
    ret=$?
} 

stop() {
    echo "stop engine_server" 
    kill -9 $(ps -ef | grep engine_server | grep -v grep | awk '{print $2}')
    ret=$?
} 

status() {
    local result
    echo "check status of engine_server..."
    result=$( ps -ef | grep -v engine_server | grep -v grep | wc -l )
    if [ $result -gt 0 ] ; then
        echo "engine_server is up"
        ret=0
    else
        echo "engine_server is down"
        ret=1
    fi
    echo "check status of engine_server...done."
} 

# See how we were called.
case "$1" in
  start)
        start
        ;;
  stop)
        stop
        ;;
  status)
        status 
        ;;
  restart)
        stop
        start
        ;;
  *)
        echo $"Usage: $0 {start|stop|status}"
        exit 1
esac

exit $ret
