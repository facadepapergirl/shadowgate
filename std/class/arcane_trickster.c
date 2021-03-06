#include <std.h>
#include <dirs.h>
#include <daemons.h>

inherit DAEMON;

/**
 * Just like with assassin an arcane trickster has some kind of
 * "special behavior": for her 10 levels of arcane trickstery she'll
 * get both caster and stab levels.
 */

void create()
{
    ::create();
}

object base_class_ob(object ob)
{
    object class_ob;
    if(!objectp(ob) || !ob->query("arcane_trickster_base_class")) { class_ob = find_object_or_load(DIR_CLASSES+"/mage.c"); }
    else { class_ob = find_object_or_load(DIR_CLASSES+"/"+ob->query("arcane_trickster_base_class")+".c"); }
    if(!objectp(class_ob)) { class_ob = find_object_or_load(DIR_CLASSES+"/mage.c"); }
    return class_ob;
}

string *query_base_classes() { return ({ "mage","sorcerer","cleric","druid","thief", "bard","inquisitor" }); }

int has_base_class_set(object obj)
{
    if(!objectp(obj)) { return 0; }
    if(obj->query("arcane_trickster_base_class")) { return 1; }
    return 0;
}

int is_prestige_class() { return 1; }

string *search_paths(object ob) { return base_class_ob(ob)->search_paths(); }

int caster_class() { return 1; }

string *restricted_races(object ob) { return base_class_ob(ob)->restricted_races(); }

string *restricted_classes(object ob) { return base_class_ob(ob)->restricted_classes(); }

int *restricted_alignments() { return ({}); }

string *restricted_gods() { return ({}); }

string requirements() // string version, maybe we'll need this, maybe not, can remove later if not
{
    string str;
    str = "Prerequisites:\n"
        "    10 Mage, Sorcerer, Cleric, Druid, Bard levels (level adjustments considered part of required levels)\n"
        "    10 Thief (level adjustments considered part of required levels)\n"
        "    10 Points Spent in Stealth Skill\n"
        "    10 Points Spent in Spellcraft Skill\n";
    return str;
}

int prerequisites(object player)
{
    mapping skills;
    object race_ob;
    string race;
    int adj;
    if(!objectp(player)) { return 0; }

    race = player->query("subrace");
    if(!race) { race = player->query_race(); }
    race_ob = find_object_or_load(DIR_RACES+"/"+player->query_race()+".c");
    if(!objectp(race_ob)) { return 0; }
    adj = race_ob->level_adjustment(race);
    skills = player->query_skills();

    if(player->is_class("sorcerer"))
    {
        if( (player->query_class_level("sorcerer") + adj) < 10) { return 0; }

        player->set("arcane_trickster_base_class","sorcerer");
    }
    if(player->is_class("mage"))
    {
        if( (player->query_class_level("mage") + adj) < 10) { return 0; }
        player->set("arcane_trickster_base_class","mage");
    }
    if(player->is_class("bard"))
    {
        if( (player->query_class_level("cleric") + adj) < 10) { return 0; }
        player->set("arcane_trickster_base_class","bard");
    }
    if(player->is_class("druid"))
    {
        if( (player->query_class_level("druid") + adj) < 10) { return 0; }
        player->set("arcane_trickster_base_class","druid");
    }
    if(player->is_class("cleric"))
    {
        if( (player->query_class_level("cleric") + adj) < 10) { return 0; }
        player->set("arcane_trickster_base_class","cleric");
    }
    if( (player->query_class_level("thief") + adj) < 10) { return 0; }
    if(skills["stealth"] < 10) { return 0; }
    if(skills["spellcraft"] < 10) { return 0; }
    return 1;
}

mapping stat_requirements(object ob) { return base_class_ob(ob)->stat_requirements(); }

int *saving_throws(object ob) { return ({0,1,1}); }

string *combat_styles() { return ({}); }

string *class_feats(string myspec) { return base_class_ob(0)->class_feats(myspec); }

int caster_level_calcs(object player, string the_class)
{
    int level;
    string base;
    if(!objectp(player)) { return 0; }
    base = player->query("arcane_trickster_base_class");

    level = player->query_class_level(base)+player->query_class_level("thief");
    level += player->query_class_level("arcane_trickster");
    return level;
}

mapping class_featmap(string myspec) {
    return ([ 1 : ({ "tricky spells" }), 4 : ({ "invisible thief" }), 7 : ({ "surprise spells" }), ]);
}

string *class_skills(object ob)
{
    return base_class_ob(ob)->class_skills();
}

int skill_points(object ob) { return base_class_ob(ob)->skill_points(); }

string old_save_type(object ob) { return base_class_ob(ob)->old_save_type(); }

string new_save_type(object ob) { return base_class_ob(ob)->new_save_type(); }

// unsure on this one, will have to investigate
void advanced_func(object player) { return base_class_ob(player)->advance_func(player); }

int hit_dice(object ob) { return 8; }  // hit dice rolled for hitpoints each level

int default_hitpoints(object ob) { return base_class_ob(ob)->default_hitpoints(); } // hitpoints per level above level 20

string armor_allowed(object ob) { return "thief"; }

string weapons_allowed(object ob) { return "thief"; }

int max_stance_offensive(object ob) { return base_class_ob(ob)->max_stance_offensive(); }

int max_stance_defensive(object ob) { return base_class_ob(ob)->max_stance_defensive(); }

int attack_bonus(object player) { return 6; }

int number_of_attacks(object player) { return base_class_ob(player)->number_of_attacks(player); }

string newbie_choice(object ob) { return base_class_ob(ob)->newbie_choice(); }

string *query_newbie_stuff(object ob) { return base_class_ob(ob)->query_newbie_stuff(); }

void process_newbie_choice(object who, string str) { return base_class_ob(who)->process_newbie_choice(who,str); }

string query_casting_stat(object ob) { return base_class_ob(ob)->query_casting_stat(); }

mapping query_class_spells(object ob) { return base_class_ob(ob)->query_class_spells(); }
