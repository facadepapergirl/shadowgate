#include <std.h>
#include <daemons.h>
#include <party.h>
#include <spell.h>
inherit SPELL;

#define DELAY 300 //5min delay between uses

void create() {
    ::create();
    set_author("nienne");
    set_spell_name("planar beacon");
    set_spell_level(([ "mage" : 6 ]));
    set_spell_sphere("conjuration_summoning");
    set_syntax("cast CLASS planar beacon on TARGET");
    set_description("This spell pinpoints a foe, regardless of what plane they are on, making them glow like a beacon within the weave. They can then attempt to draw this beacon to their current location. However, a foe with the strength of mind to resist may cause the spell to backfire, instead sending the caster to his or her target. Once this spell is used, the caster must rest for a short while before attempting its use again.spell.");
    set_verbal_comp();
    set_somatic_comp();
    set_arg_needed();
    set_components(([
      "mage" : ([ "sand" : 1, "pinch of special dust" : 1, ]),
    ]));
    set_save("will");
}

string query_cast_string() {
    return "%^BOLD%^%^BLUE%^"+caster->QCN+" snarls the first syllables of a summoning.";
}

int preSpell(){
   if((int)caster->query_property("spell summon time")+DELAY > time()){
      tell_object(caster,"You cannot summon anyone to you again so quickly.");
      return 0;
   }
   return 1;
}

void spell_effect(int prof) {
    int i, matches;
    string real;
    object targ;
    mapping map;
    string *map_keys;

    if (!objectp(caster)){
        dest_effect();
        return;
    }
    if(!stringp(arg))
    {
        tell_object(CASTER, "You must specific a target for this spell.");
        TO->remove();
        return;
    }
    arg = lower_case(arg);
    if (!(targ = find_player(caster->realName(arg)))) {
        tell_object(CASTER,capitalize(targ)+" cannot be found to establish a link.\n");
        TO->remove();
        return;
    }
    tell_object(caster,"%^BOLD%^%^CYAN%^You cast out tendrils of seeking energy, and in your mind you can see the weave "
"energies around "+targ->QCN+" flare brightly with magical energy!");
    call_out("do_summon",6,targ);
}

void do_summon(object target) {
    object *party,endplace;
    int i,success,fail,targlevel,mylevel;
    int mypower,startpower,endpower,bonus;

    if (!objectp(caster) || !objectp(target)) {
        dest_effect();
        return;
    }
    if (!objectp(environment(caster)) || !objectp(environment(target))) {
        tell_object(caster,"The summoning has failed.");
        dest_effect();
        return;
    }
    if ((int)environment(caster)->query_property("no teleport") || (int)environment(target)->query_property("no teleport")) {
        tell_object(caster,"You try to tug the beacon through the weave to you, but interference causes you to fail.");
        dest_effect();
        return;
    }
   endplace = environment(target);
   if(endplace &&
      (endplace->query_property("teleport proof") || place->query_property("teleport proof") || !endplace->is_room())){
      startpower = place->query_property("teleport proof");
      endpower = endplace->query_property("teleport proof");
      bonus = caster->query_stats("intelligence");
      bonus = (bonus -10)/2;
      mypower = CLEVEL + bonus + random(6) + 5;
      if((mypower < startpower) || (mypower < endpower)){
        tell_object(caster,"You try to tug the beacon through the weave to you, but interference causes you to fail.");
        dest_effect();
        return;
      }
   }
   caster->set_property("spell summon time",time());
   success = 0;

   if(!do_save(target,-2)) success = 1;
   else {
     success = 0;
     if(do_save(caster,bonus*(-1))) fail = 1;
   }
   if(fail){
     tell_object(target,"%^CYAN%^You feel a strange tugging at your soul before it ceases.%^RESET%^");
     tell_object(caster,"%^CYAN%^You try to forcefully yank the glowing magical beacon to you, but the spell turns upon "
"you and it is all you can do to resist being thrown through the weave at "+target->QCN+"!%^RESET%^",target);
     dest_effect();
     return;
   }
   if (success) {
        tell_object(target,"%^BOLD%^%^CYAN%^You feel a rough tug on your soul, and suddenly you find yourself standing "
"before "+caster->QCN+"!");
        tell_object(caster,"%^BOLD%^%^CYAN%^You forcefully yank forward the glowing magical beacon, drawing "
+target->QCN+" through the weave to appear before you!");
        target->move_player(environment(caster));
        dest_effect();
        return;
    }
    else {
        tell_object(target,"%^BOLD%^%^BLUE%^You feel a strange tugging at your soul, before "+caster->QCN+" suddenly "
"appears before you!");
        tell_object(caster,"%^BOLD%^%^BLUE%^You try to forcefully drag "+target->QCN+" through the weave to you, but the "
"spell backfires and you are thrown forward to appear before "+target->QO+"!");
        tell_object(caster,"%^BOLD%^You are transported to another place!");
        caster->move_player(environment(target));
        dest_effect();
        return;
    }
}

void dest_effect() {
    ::dest_effect();
    if(objectp(TO)) TO->remove();
}
