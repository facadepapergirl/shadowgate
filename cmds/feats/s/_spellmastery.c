#include <std.h>
#include <daemons.h>
#include <dirs.h>
inherit FEAT;

int FLAG;

int light_armor_filter(object ob) {
    if(!objectp(ob)) { return 0; }
    if(ob->query_armor_prof("light")) { return 0; }
    return 1;
}

int armor_filter(object ob) {
    if(!objectp(ob)) { return 0; }
    if(ob->query_armor_prof("light")) { return 1; }
    if(ob->query_armor_prof("medium")) { return 1; }
    if(ob->query_armor_prof("heavy")) { return 1; }
    return 0;
}

void create() {
    ::create();
    feat_type("premanent");
    feat_category("MagicDamage");
    feat_name("spellmastery");
    feat_syntax("spellmastery SPELLNAME");
    feat_prereq("Not warlock, Not psion, Not psywarrior, Not monk");
    feat_desc("When selecting the SpellMastery feat, the character will be prompted to pick a spell that they are able to cast. From that point forward the character will be able to cast that spell at will at any time without needing components or memorization. Only spells of 1st and 2nd level may be picked for SpellMastery. If you have more than one class able to use the same spell, the power of the SpellMastery (as well as armor checks, etc) will be based upon the highest of these.

%^BOLD%^N.B.%^RESET%^ Spellmastery is not connected to <master> in any way. It just allows you to cast the spell without memorization or component cost. You still have to know the spell to cast it, have it in your spellbook, mastered or in your spell list.");

    permanent(1);
    allow_tripped(1);
    set_required_for(({"spell power","improved spell power","greater spell power","hardenedminions","magic arsenal"}));
    set_replaces_feat("expanded knowledge 1");
}

int cmd_spellmastery(string args)
{
    int cancastflag;
    string * myclasses, myclass;

    if(TP->query("spellmastery_change") > time() - 60*60*24*3)
    {
        write("%^BOLD%^%^WHITE%^You can change your mastered spell only once in three days or by retaking this feat.");
        return 1;
    }

    if(FEATS_D->usable_feat(TP,"greater spell mastery"))
    {
        write("Use <greater_spell_mastery SPELL NAME>");
        return 1;
    }

    cancastflag = 0;
    myclasses = TP->query_classes();
    foreach(myclass in myclasses)
    {
        if(member_array(args,keys(MAGIC_D->index_spells_for_player(TP,myclass)))!=-1)
            cancastflag++;
    }

    if(!cancastflag)
    {
        write("None of your classes can cast this spell.");
        return 1;
    }

    TP->set("spellmastery_change",time());
    TP->set("spellmastery_spell",args);

    return 1;
}

int allow_shifted() { return 1; }

int prerequisites(object ob){
    string *classes,file;
    int i;
    if(!objectp(ob)) { return 0; }

    if(ob->is_class("warlock")||
       ob->is_class("monk")||
       ob->is_class("psion")||
       ob->is_class("psywarrior"))
    {
        return 0;
    }
    classes = (string *)ob->query_classes();
    for(i=0;i<sizeof(classes);i++)
    {
        file = DIR_CLASSES+"/"+classes[i]+".c";
        if(file->caster_class()) { return ::prerequisites(ob); }
    }
    return 0;
}

void permanent_effects(object ob) {
    ::permanent_effects(ob);
    dest_effect();
    return;
}

void reverse_permanent_effects(object ob) {
    ::reverse_permanent_effects(ob);
    dest_effect();
    return;
}

void execute_feat() {
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
