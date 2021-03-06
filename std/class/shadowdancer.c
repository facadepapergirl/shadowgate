#include <std.h>
#include <dirs.h>

inherit DAEMON;


void create()
{
    ::create();
}

object base_class_ob(object ob)
{
    object class_ob;
    if(!objectp(ob) || !ob->query("shadowdancer_base_class")) { class_ob = find_object_or_load(DIR_CLASSES+"/thief.c"); }
    else { class_ob = find_object_or_load(DIR_CLASSES+"/"+ob->query("shadowdancer_base_class")+".c"); }
    if(!objectp(class_ob)) { class_ob = find_object_or_load(DIR_CLASSES+"/thief.c"); }
    return class_ob;
}


string *query_base_classes() { return ({ "thief","ranger" }); }

int is_prestige_class() { return 1; }

string *search_paths(object ob) { return base_class_ob(ob)->search_paths(); }

int caster_class() { return 0; }

string *restricted_races(object ob) { return base_class_ob(ob)->restricted_races(); }

string *restricted_classes(object ob) { return base_class_ob(ob)->restricted_classes(); }

int *restricted_alignments(object ob) { return base_class_ob(ob)->restricted_alignments(); }

string *restricted_gods(object ob) { return base_class_ob(ob)->restricted_gods(); }

string requirements() // string version, maybe we'll need this, maybe not, can remove later if not
{
    string str;
    str = "Prerequisites:\n"
        "    20 Ranger or Thief levels\n"
        "    20 Base Dexterity\n"
        "    10 Ranks spent in Stealth Skill\n";
        "    10 Ranks spent in Athletics Skill\n";

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

    if(!skills["stealth"] || skills["stealth"] < 10) { return 0; }
    if(!skills["athletics"] || skills["athletics"] < 10) { return 0; }
    if(player->is_class("ranger"))
    {
        if( (player->query_class_level("ranger") + adj) < 20) { return 0; }
        player->set("shadowdancer_base_class","ranger");
    }
    if(player->is_class("thief"))
    {
        if( (player->query_class_level("thief") + adj) < 20) { return 0; }
        player->set("shadowdancer_base_class","thief");
    }
    return 1;
}

mapping stat_requirements(object ob)
{
    return ([ "dexterity" : 20 ]);
}

int *saving_throws(object ob) { return base_class_ob(ob)->saving_throws(); }

string *combat_styles(object ob) { return base_class_ob(ob)->combat_styles(); }

string *class_feats(string myspec) { return base_class_ob(0)->class_feats(myspec); }

int caster_level_calcs(object player, string the_class)
{
    int level;
    if(!objectp(player)) { return 0; }
    switch(the_class)
    {
        case "thief":
            level = player->query_class_level("thief");
            level += player->query_class_level("shadowdancer");
            return level;
        case "ranger":
            level = player->query_class_level("ranger");
            level += player->query_class_level("shadowdancer");
            return level;
        case "shadowdancer":
            level = player->query_class_level("shadowdancer");
            level += player->query_class_level("thief");
            level += player->query_class_level("ranger");
            return level;

        default:
            return player->query_class_level(the_class);
    }
    return 0;
}

mapping class_featmap(string myspec) {
    return ([ 1 : ({ "one with the shadows" }), 4 : ({ "shadow master" }), 7 : ({ "shadow jump" }), ]);
}

string *class_skills(object ob) { return base_class_ob(ob)->class_skills(); }

int skill_points(object ob) { return base_class_ob(ob)->skill_points(); }

string old_save_type(object ob) { return base_class_ob(ob)->old_save_type(); }

string new_save_type(object ob) { return base_class_ob(ob)->new_save_type(); }

// unsure on this one, will have to investigate
void advanced_func(object player) { return base_class_ob(player)->advance_func(player); }

int hit_dice(object ob) { return base_class_ob(ob)->hit_dice(); }  // hit dice rolled for hitpoints each level

int default_hitpoints(object ob) { return base_class_ob(ob)->default_hitpoints(); } // hitpoints per level above level 20

string armor_allowed(object ob) { return base_class_ob(ob)->armor_allowed(); }

string weapons_allowed(object ob) { return base_class_ob(ob)->weapons_allowed(); }

int max_stance_offensive(object ob) { return base_class_ob(ob)->max_stance_offensive(); }

int max_stance_defensive(object ob) { return base_class_ob(ob)->max_stance_defensive(); }

int attack_bonus(object player) { return 0; }

int number_of_attacks(object player) { return base_class_ob(player)->number_of_attacks(player); }

string newbie_choice(object ob) { return base_class_ob(ob)->newbie_choice(); }

string *query_newbie_stuff(object ob) { return base_class_ob(ob)->query_newbie_stuff(); }

void process_newbie_choice(object who, string str) { return base_class_ob(who)->process_newbie_choice(who,str); }

string query_casting_stat(object ob) { return base_class_ob(ob)->query_casting_stat(); }

mapping query_class_spells(object ob) { return base_class_ob(ob)->query_class_spells(); }
