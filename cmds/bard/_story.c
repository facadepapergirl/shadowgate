#include <std.h>
#include <objects.h>

inherit DAEMON;

int help();

int cmd_story(string str) {
    object ob;
    if(!str) return help();
    ob = new("/cmds/bard/storyobj");
    ob->set_name(str);
    ob->move(this_player());

    return 1;
}

int help() {
    write(
@OLI
   story:
        Usage: story <name>
       This opens an editor area for you to input a new story.  
       The name is the name of the story <one word> and will be 
       used to reference it later.  Emoteat can now be used 
       with stories and songs, the target of the emoteat is 
       always assumed to be yourself.


          Syntax:
             The commands song recognizes are say, speech and emote.
             you can write the following:
               say come to me my love
               come see my joy
               emote drops his voice to a whisper
               speech whisper
               say come closer my love...
               emoteat A woman from the audience blows a kiss to $M
             and your audience will see:
               Joe says come to me my love
               Joe says come see my joy.
               Joe drops his voice to a whisper.
               Joe whispers come closer my love...
               A woman from the audience blows a kiss to Joe
   
OLI
    );
    return 1;
}

