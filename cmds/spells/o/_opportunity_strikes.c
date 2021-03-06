#include <std.h>
#include <daemons.h>
#include <dirs.h>

inherit FEAT;

void create() 
{
    ::create();
    feat_type("permanent");
    feat_category("Duelist");
    feat_name("opportunity strikes");
    feat_desc("This feat will allow the character to move into a better position in combat and to strike with greater strength. It will increase damage done if they wield one one-handed weapon.");
    permanent(1);
}

int allow_shifted() { return 0; }

int prerequisites(object ob)
{
    if(!objectp(ob)) { return 0; }
    return ::prerequisites(ob);
}

void execute_feat()
{
    ::execute_feat();
    dest_effect();
    return;
}

void dest_effect()
{
    ::dest_effect();
    remove_feat(TO);
    return;
}
