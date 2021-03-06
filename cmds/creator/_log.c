//      /bin/dev/_log.c
//      from the Nightmare Mudlib
//      tails a given log
//      created by Brian@TMI 920128

#include <std.h>
#include <dirs.h>

inherit DAEMON;

int cmd_log(string str) {
    if(!str) {
        notify_fail("Correct syntax: <log [log file]>\n");
        return 0;
    }
    write(str+":\n");
    if(!tail("/log/"+str)) write("No such log file: "+str+"\n");
    return 1;
}

void help() {
    write("Syntax: <log [log file]>\n\n"
      "Tails the log file named (i.e. a file in the mud log directory).\n\n"
      "See also:\nelog, replog\n"
    );
}
