#include <spell.h>
#include <magic.h>
#include <rooms.h>
inherit "/cmds/spells/m/_monster_summoning_1.c";

create() {
    ::create();
    set_spell_name("monster summoning 5");
    set_spell_level(([ "mage" : 5, "bard" : 5, "cleric" : 5 ]));
    set_syntax("cast CLASS monster summoning 5");
}
