#include <std.h>
#include <daemons.h>

string *VALID_SETTINGS = ({"hints","logon_notify","simpleinv","brief","persist","brief_combat","expgain","taxperc","term","scrlines","scrwidth"});

int cmd_set(string args)
{
    string setting,value;
    if(!stringp(args))
    {
        string stng;
        write("%^BLUE%^--=%^BOLD%^<%^WHITE%^ Settings %^BLUE%^>%^RESET%^%^BLUE%^=--%^RESET%^");
        foreach(stng in VALID_SETTINGS)
        {
            write("%^BOLD%^%^WHITE%^"+arrange_string(stng,14)+": %^RESET%^"+(string)call_other(TO,"get_"+stng));
        }
        return 1;
    }
    if(sscanf(args,"%s %s",setting,value)!=2)
    {
        write("You must specify both setting and value.");
        return 1;
    }
    if(member_array(setting,VALID_SETTINGS)==-1)
    {
        write("Invalid setting.");
        return 1;
    }
    if(!call_other(TO,"set_"+setting,value))
    {
        write("%^WHITE%^%^BOLD%^Unable to set %^RED%^"+setting+"%^WHITE%^ to %^RED%^"+value+"%^WHITE%^.");
        return 1;
    }
    else
    {
        write("%^WHITE%^%^BOLD%^Setting %^GREEN%^"+setting+"%^WHITE%^ to %^CYAN%^"+value+"%^WHITE%^.");
        return 1;
    }
    return 1;
}

int set_simpleinv(string val)
{
    string *valid_values = ({"on","off"});
    if(member_array(val,valid_values)==-1)
    {
        write("%^BOLD%^%^RED%^Invalid value, valid values are:%^RESET%^ "+implode(valid_values,", "));
        return 0;
    }
    if (val == "off")
        TP->delete("simple inventory");
    else
        TP->set("simple inventory", 1);
    return 1;
}

string get_simpleinv()
{
    if(TP->query("simple inventory"))
        return "on";
    else
        return "off";
}

int set_hints(string val)
{
    string *valid_values = ({"on","off"});
    if(member_array(val,valid_values)==-1)
    {
        write("%^BOLD%^%^RED%^Invalid value, valid values are:%^RESET%^ "+implode(valid_values,", "));
        return 0;
    }
    if (val == "on")
        TP->delete("no hints");
    else
        TP->set("no hints", 1);
    return 1;
}

string get_hints()
{
    if(TP->query("no hints"))
        return "off";
    else
        return "on";
}

int set_term(string val)
{
    string *valid_values;
    valid_values = TERMINAL_D->query_terms();
    if(member_array(val,valid_values)==-1)
    {
        write("%^BOLD%^%^RED%^Invalid value, valid values are:%^RESET%^ "+implode(valid_values,", "));
        return 0;
    }
    TP->setenv("TERM", val);
    TP->reset_terminal();
    return 1;
}

string get_term()
{
    return TP->getenv("TERM");
}

int set_scrlines(string val)
{
    if(!atoi(val))
    {
        write("%^BOLD%^%^RED%^Invalid value, must provide a number.%^RESET%^");
        return 0;
    }
    if(atoi(val)<2)
    {
        write("%^BOLD%^%^RED%^Invalid value, must be bigger than 2.%^RESET%^");
        return 0;
    }
    TP->setenv("LINES", val);
    return 1;
}

string get_scrlines()
{
    return TP->getenv("LINES");
}

int set_scrwidth(string val)
{
    if(!atoi(val))
    {
        write("%^BOLD%^%^RED%^Invalid value, must provide a number.%^RESET%^");
        return 0;
    }
    if(atoi(val)<2)
    {
        write("%^BOLD%^%^RED%^Invalid value, must be bigger than 2.%^RESET%^");
        return 0;
    }
    TP->setenv("SCREEN", val);
    return 1;
}

string get_scrwidth()
{
    return TP->getenv("SCREEN");
}

int set_logon_notify(string val)
{
    string *valid_values = ({"on","off"});
    if(member_array(val,valid_values)==-1)
    {
        write("%^BOLD%^%^RED%^Invalid value, valid values are:%^RESET%^ "+implode(valid_values,", "));
        return 0;
    }
    if(val == "off")
        this_player()->set_logon_notify(0);
    else
        this_player()->set_logon_notify(0);
    return 1;
}

string get_logon_notify()
{
    if(TP->query_logon_notify())
        return "on";
    else
        return "off";
}

int set_brief(string val)
{
    string *valid_values = ({"on","off"});
    if(member_array(val,valid_values)==-1)
    {
        write("%^BOLD%^%^RED%^Invalid value, valid values are:%^RESET%^ "+implode(valid_values,", "));
        return 0;
    }
    if(this_player()->query_verbose()&&val=="on")
        this_player()->set_brief();
    if(!this_player()->query_verbose()&&val=="off")
        this_player()->set_brief();
    return 1;
}

string get_brief()
{
    if(this_player()->query_verbose())
        return "off";
    else
        return "on";
}

int set_persist(string val)
{
    string *valid_values = ({"on","off"});
    if(member_array(val,valid_values)==-1)
    {
        write("%^BOLD%^%^RED%^Invalid value, valid values are:%^RESET%^ "+implode(valid_values,", "));
        return 0;
    }
    if(val=="on")
        this_player()->set("persist_login",1);
    if(val=="off")
        this_player()->delete("persist_login");
    return 1;
}

int get_persist(string val)
{
    if(this_player()->query("persist_login"))
        return "on";
    else
        return "off";
}

int set_brief_combat(string val)
{
    string *valid_values = ({"on","off"});
    if(member_array(val,valid_values)==-1)
    {
        write("%^BOLD%^%^RED%^Invalid value, valid values are:%^RESET%^ "+implode(valid_values,", "));
        return 0;
    }
    if(TP->query_verbose_combat()&&val=="on")
        TP->set_brief_combat();
    if(!TP->query_verbose_combat()&&val=="off")
        TP->set_brief_combat();
    return 1;
}

string get_brief_combat()
{
    if(this_player()->query_verbose_combat())
        return "off";
    else
        return "on";
}

int set_expgain(string val)
{
    string *valid_values = ({"on","off"});
    if(member_array(val,valid_values)==-1)
    {
        write("%^BOLD%^%^RED%^Invalid value, valid values are:%^RESET%^ "+implode(valid_values,", "));
        return 0;
    }
    if(val=="on"&&(USER_D->no_exp(TP)))
        USER_D->toggle_no_exp(TP);
    if(val=="off"&&(!USER_D->no_exp(TP)))
        USER_D->toggle_no_exp(TP);
    return 1;
}

string get_expgain()
{
    if(USER_D->no_exp(TP))
        return "off";
    else
        return "on";
}

int set_taxperc(string val)
{
    int perc;
    if(!atoi(val))
    {
        write("%^BOLD%^%^RED%^Invalid value, must provide a number.%^RESET%^");
        return 0;
    }
    perc = atoi(val);
    if(USER_D->set_character_improvement_tax_percent(TP,perc))
        return 1;
    else
        return 0;
}

int get_taxperc()
{
    return sprintf("%d",USER_D->get_character_improvement_tax_percent(TP));
}

void help()
{
    //NOTE: PRESERVE FORMAT OF THIS HELPFILE FOR SORTING PURPOSES.
    //Use M-x sort-lines if you're using emacs or |sort in vim.
    write("
%^CYAN%^NAME%^RESET%^

set - manipulate various mud settings

%^CYAN%^SYNTAX%^RESET%^

set %^ORANGE%^%^ULINE%^SETTING%^RESET%^ %^ORANGE%^%^ULINE%^VALUE%^RESET%^

%^CYAN%^DESCRIPTION%^RESET%^

You can manipulate numerous mud settings:

%^ULINE%^%^CYAN%^Notifications and messages:%^RESET%^

%^CYAN%^hints %^GREEN%^on|off%^RESET%^\n  This will turn on or off display of periodic hints. %^MAGENTA%^Default value is on.%^RESET%^\n
%^CYAN%^logon_notify %^GREEN%^on|off%^RESET%^\n  This will turn on or off display of people joining the game. %^MAGENTA%^Default value is on.%^RESET%^\n
%^CYAN%^simpleinv %^GREEN%^on|off%^RESET%^\n  This will turn on or off displaying equipped inventory items in %^ORANGE%^<inventory>%^RESET%^ command. When it is toggled off, you can see equipped inventory in %^ORANGE%^<eq>%^RESET%^. %^MAGENTA%^Default value is off.%^RESET%^\n
%^CYAN%^brief %^GREEN%^on|off%^RESET%^\n  This will turn on or off display of room's long description. Useful for screenreaders. %^MAGENTA%^Default value is off.%^RESET%^\n
%^CYAN%^brief_combat %^GREEN%^on|off%^RESET%^\n  This will turn on or off display of verbose combat. %^MAGENTA%^Default value is on.%^RESET%^\n
%^CYAN%^persist %^GREEN%^on|off%^RESET%^\n  Turning persistent login will allow you not to idle out upon reaching a timeout. %^MAGENTA%^Default value is off.%^RESET%^\n
%^ULINE%^%^CYAN%^Experience points and tax:%^RESET%^

%^CYAN%^expgain %^GREEN%^on|off%^RESET%^\n  This will turn on or off experience gain for your character. While it is off, you will get NO EXPERIENCE. %^MAGENTA%^Default value is on.%^RESET%^\n
%^CYAN%^taxperc %^GREEN%^%^ULINE%^NUMBER%^RESET%^\n  This will define how much of your experience gain goes towards paying off your experience tax. This value will grow with your levels, but you may force its increase via this setting. %^MAGENTA%^Default value is on.%^RESET%^\n
%^ULINE%^%^CYAN%^Terminal and display:%^RESET%^

%^CYAN%^term %^GREEN%^"+implode(sort_array(TERMINAL_D->query_terms(),1),"|")+"%^RESET%^\n  This will set your current terminal to a given value. The value 'unknown' sets terminal to the one without colors. %^MAGENTA%^Default value is set on first login.%^RESET%^\n
%^CYAN%^scrlines %^GREEN%^%^ULINE%^NUMBER%^RESET%^\n  Set how many lines appear for paged information. %^MAGENTA%^Default value: 20%^RESET%^\n
%^CYAN%^scrwidth %^GREEN%^%^ULINE%^NUMBER%^RESET%^\n  Set screen width for text wrapping. %^MAGENTA%^Default value: 75%^RESET%^\n
To see current values use %^ORANGE%^<set>%^RESET%^ without arguments.

%^CYAN%^SEE ALSO%^RESET%^

adjective, background, chfn, colors, describe, flag, lines, message, passwd, prompt, speech, history
");
}
