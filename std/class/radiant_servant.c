// will probably need a new function for guild level determination for spell casting, to add to existing caster class

#include <std.h>
#include <dirs.h>

inherit DAEMON;

#define BASE_CLASS find_object_or_load(DIR_CLASSES+"/cleric.c")

void create()
{
    ::create();
    //BASE_CLASS = find_object_or_load(DIR_CLASSES+"/cleric.c");
}

// when query_class_level("cleric") is called in /std/living/skills.c,
// the levels of the radiant_servant class are added to the levels in
// the cleric class.  The levels in a prestige class will be added to
// query_class_level for any classes that are present in this array.
// So for example if the base classes here were ({ "cleric","mage" })
// then both cleric and mage would add the levels of the prestige class to
// their cleric and mage levels.
string *query_base_classes() { return ({ "cleric" }); }

int is_prestige_class() { return 1; }

string *search_paths() { return BASE_CLASS->search_paths(); } // temporary

int caster_class() { return BASE_CLASS->caster_class(); }

string *restricted_races() { return BASE_CLASS->restricted_races(); }

string *restricted_classes() { return BASE_CLASS->restricted_classes(); }

int *restricted_alignments() { return BASE_CLASS->restricted_alignments(); }

string *restricted_gods() { return BASE_CLASS->restricted_gods(); }

string requirements() // string version, maybe we'll need this, maybe not, can remove later if not
{
    string str;
    str = "Prerequisites:\n"
        "    10 Skill points spent in the healing skill\n"
        "    20 Cleric levels (level adjustments considered part of cleric levels)\n"
        "    20 Wisdom skill, before equipment modifiers\n";

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

    if(skills["healing"] < 10) { return 0; }
    if( (player->query_class_level("cleric") + adj) < 20) { return 0; }
    if(player->query_base_stats("wisdom") < 20) { return 0; }
    return 1;
}

mapping stat_requirements() { return ([ "wisdom" : 20 ]); }

// strong & weak saving throws. Fort, Ref, Will
int *saving_throws() { return BASE_CLASS->saving_throws(); }

string *combat_styles() { return BASE_CLASS->combat_styles(); }

string *class_feats(string myspec) { return BASE_CLASS->class_feats(); }

int caster_level_calcs(object player, string the_class)
{
    int level;
    if(!objectp(player)) { return 0; }
    switch(the_class)
    {
        case "radiant_servant":
        case "radiant servant":
        case "cleric":
            level = player->query_class_level("cleric");
            level += player->query_class_level("radiant_servant");
            return level;

        default:
            return player->query_class_level(the_class);
    }
    return 0;
}

mapping class_featmap(string myspec) {
    return ([ 1 : ({ "contingent healing" }), 4 : ({ "radiant aura" }), 7 : ({ "supreme healer" }), ]);
}

string *class_skills()
{
    return BASE_CLASS->class_skills();
}

int skill_points() { return BASE_CLASS->skill_points(); }

string old_save_type() { return BASE_CLASS->old_save_type(); }

string new_save_type() { return BASE_CLASS->new_save_type(); }

// unsure on this one, will have to investigate
void advanced_func(object player) { return BASE_CLASS->advance_func(player); }

int hit_dice() { return BASE_CLASS->hit_dice(); }  // hit dice rolled for hitpoints each level

int default_hitpoints() { return BASE_CLASS->default_hitpoints(); } // hitpoints per level above level 20

string armor_allowed() { return BASE_CLASS->armor_allowed(); }

string weapons_allowed() { return BASE_CLASS->weapons_allowed(); }

int max_stance_offensive() { return BASE_CLASS->max_stance_offensive(); }

int max_stance_defensive() { return BASE_CLASS->max_stance_defensive(); }

int attack_bonus(object player) { return 0; }

int number_of_attacks(object player) { return BASE_CLASS->number_of_attacks(player); }

string newbie_choice() { return BASE_CLASS->newbie_choice(); }

string *query_newbie_stuff() { return BASE_CLASS->query_newbie_stuff(); }

void process_newbie_choice(object who, string str) { return BASE_CLASS->process_newbie_choice(who,str); }

string query_casting_stat() { return BASE_CLASS->query_casting_stat(); }

mapping query_class_spells() { return BASE_CLASS->query_class_spells(); }
