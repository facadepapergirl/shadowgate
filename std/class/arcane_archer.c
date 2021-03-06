#include <std.h>
#include <dirs.h>
#include <daemons.h>

inherit DAEMON;

void create()
{
    ::create();
}

object base_class_ob(object ob)
{
    object class_ob;
    if(!objectp(ob) || !ob->query("arcane_archer_base_class")) { class_ob = find_object_or_load(DIR_CLASSES+"/mage.c"); }
    else { class_ob = find_object_or_load(DIR_CLASSES+"/"+ob->query("arcane_archer_base_class")+".c"); }
    if(!objectp(class_ob)) { class_ob = find_object_or_load(DIR_CLASSES+"/mage.c"); }
    return class_ob;
}

string *query_base_classes() { return ({ "mage","sorcerer","bard","druid","cleric","warlock","inquisitor" }); }

int has_base_class_set(object obj)
{
    if(!objectp(obj)) { return 0; }
    if(obj->query("arcane_archer_base_class")) { return 1; }
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
        "    20 Mage, Sorcerer, Bard, Cleric, Druid or Warlock levels (level adjustments considered part of required levels)\n"
        "    Preciseshot\n";

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

    if(!FEATS_D->usable_feat(player,"preciseshot")) { return 0; }
    if(player->is_class("sorcerer"))
    {
        if( (player->query_class_level("sorcerer") + adj) < 20) { return 0; }

        player->set("arcane_archer_base_class","sorcerer");
    }
    if(player->is_class("mage"))
    {
        if( (player->query_class_level("mage") + adj) < 20) { return 0; }
        player->set("arcane_archer_base_class","mage");
    }
    if(player->is_class("bard"))
    {
        if( (player->query_class_level("bard") + adj) < 20) { return 0; }
        player->set("arcane_archer_base_class","bard");
    }
    if(player->is_class("druid"))
    {
        if( (player->query_class_level("druid") + adj) < 20) { return 0; }
        player->set("arcane_archer_base_class","druid");
    }
    if(player->is_class("cleric"))
    {
        if( (player->query_class_level("cleric") + adj) < 20) { return 0; }
        player->set("arcane_archer_base_class","cleric");
    }
    return 1;
}

mapping stat_requirements(object ob) { return base_class_ob(ob)->stat_requirements(); }

int *saving_throws(object ob) { return base_class_ob(ob)->saving_throws(); }

string *combat_styles() { return ({}); }

string *class_feats(string myspec) { return base_class_ob(0)->class_feats(myspec); }

int caster_level_calcs(object player, string the_class)
{
    int level;
    string base;
    if(!objectp(player)) { return 0; }
    base = player->query("arcane_archer_base_class");

    level = player->query_class_level(base);
    level += player->query_class_level("arcane_archer");
    return level;
}

mapping class_featmap(string myspec) {
    return ([ 1 : ({ "arcane arrows" }), 4 : ({ "timestop volley" }), 7 : ({ "death arrow" }), ]);
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

int hit_dice(object ob) { return 8;}  // hit dice rolled for hitpoints each level

int default_hitpoints(object ob) { return base_class_ob(ob)->default_hitpoints(); } // hitpoints per level above level 20

string armor_allowed(object ob) { return base_class_ob(ob)->armor_allowed(); }

string weapons_allowed(object ob) { return base_class_ob(ob)->weapons_allowed(); }

int max_stance_offensive(object ob) { return base_class_ob(ob)->max_stance_offensive(); }

int max_stance_defensive(object ob) { return base_class_ob(ob)->max_stance_defensive(); }

int attack_bonus(object player) { return 6; }

int number_of_attacks(object player) { return base_class_ob(player)->number_of_attacks(player); }

string newbie_choice(object ob) { return base_class_ob(ob)->newbie_choice(); }

string *query_newbie_stuff(object ob) { return base_class_ob(ob)->query_newbie_stuff(); }

void process_newbie_choice(object who, string str) { return base_class_ob(who)->process_newbie_choice(who,str); }

string query_casting_stat(object ob) { return base_class_ob(ob)->query_casting_stat(); }

mapping query_class_spells(object ob) { return base_class_ob(ob)->query_class_spells(); }
