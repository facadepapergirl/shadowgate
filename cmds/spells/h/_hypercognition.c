//  Modified from the wizard armor spell
//This one is 2nd level because its benefits stack with 
//mage armor or inertial armor
//  ~Circe~ 7/26/05
#include <spell.h>
#include <daemons.h>
inherit SPELL;

int mylevel;
void dest_effect();

void create() {
    ::create();
    set_spell_name("hypercognition");
    set_spell_level(([ "psion" : 2 ]));
    set_discipline("seer");
    set_spell_sphere("conjuration_summoning");
    set_syntax("cast CLASS hypercognition");
    set_description("Drawing upon the might of the inner eye, a seer can focus himself and gain an insight into battles "
"that lie ahead.  This insight translates itself into better protection for the seer.  The protection granted the seer "
"from this power can be used in conjunction with inertial armor.");
    set_verbal_comp();
    set_somatic_comp();
    set_property("keywords", ({ "defensive", "targeted", "personal" }));
	set_helpful_spell(1);
}

void spell_effect(int prof) {

    caster = CASTER;
    place = PLACE;
    target = TARGET;
   if(caster->is_class("psywarrior")){
      mylevel = caster->query_guild_level("psywarrior");
   }else{
      mylevel = caster->query_guild_level("psion");
   }

    if (!target)
        target=caster;
    if (target->query_property("add_armor")) {
        tell_object(caster,"You cannot be protected by this power and "+
           "another armor effect.");
        TO->remove();
        return;
    }
    if (!target->is_ok_armour("mage")) 
    {
        if(!FEATS_D->usable_feat(target,"armored caster"))
        {
            tell_object(caster,"The power cannot offer protection to those wearing armor.");
            TO->remove();
            return;
        }
    }
    spell_successful();
    if (target == caster) {
        tell_object(caster,"%^CYAN%^Your inner eye focuses upon "+
           "upcoming battles, offering you insight!");
        tell_room(place,"%^CYAN%^"+caster->QCN+"'s eyes flash "+
           "with a sudden insight.", caster );
    } else {
       tell_object(caster,"%^BOLD%^Your mental powers can protect "+
          "only you!");
       TO->remove();
       return;
    }
    target->add_ac_bonus(2);
    target->set_property("spelled", ({TO}) );
    target->set_property("add_armor",1);
    addSpellToCaster();
    call_out("test", 7);
    call_out("dest_effect", 1800 + (mylevel * 10));
}

void test() {
    
    int max_damage, add_tally, thp;
    
    if (!objectp(target)) {
        remove();
        return;
    }

    if (!target->is_ok_armour("mage")) 
    {
        if(!FEATS_D->usable_feat(target,"armored caster"))
        {
            tell_object(caster,"The power cannot offer protection to those wearing armor.");
            TO->dest_effect();
            return;
        }
    }
    if (!objectp(target))    // To avoid errors when player quits - Thorn
        dest_effect();
    call_out("test", 7);
    return 0;
}

void dest_effect() {

    if(!objectp(target)) return;
    if(objectp(target)) 
    {
	    target->add_ac_bonus(-2);
	    target->remove_property_value("spelled", ({TO}) );
          tell_object(target,"%^BOLD%^%^CYAN%^Your inner eye loses focus, "+
          "and you feel the insight it offered fade away.");
          target->remove_property("add_armor");
    }
    ::dest_effect();
    if(objectp(TO)) TO->remove();
}

string query_cast_string() {
    return "%^CYAN%^"+caster->QCN+" %^RESET%^%^CYAN%^concentrates deeply.";
}