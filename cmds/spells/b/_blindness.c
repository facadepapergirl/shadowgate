//removed mention of non-specialized mages ~Circe~ 8/2/19
// midlevel necromancy school specialty spell. Nienne, 08/09.
#include <spell.h>
#include <magic.h>
#include <rooms.h>
#include <daemons.h>
inherit SPELL;

int clevel,bonus,i;

void create() {
    ::create();
    set_author("nienne");
    set_spell_name("blindness");
    set_spell_level(([ "mage" : 2, "bard" : 3 ]));
    set_spell_sphere("necromancy");
    set_syntax("cast CLASS blindness on TARGET");
    set_description("By means of this spell, the caster attempts to steal the target's vision for a short while. It is "
"not dispellable by normal magics, but will fade after only a short while.");
    set_verbal_comp();
    set_somatic_comp();
    set_target_required(1);
    set_save("will");
    set_components(([
      "mage" : ([ "bitumen" : 1, ]),
    ]));
}

string query_cast_string() {
    return "%^CYAN%^"+caster->QCN+" hisses the syllables of a spell.%^RESET%^";
}

void spell_effect(int prof) {
    int duration;
    if(target == caster) {
        tell_object(caster, "%^BLUE%^You realise the error in directing the spell at yourself, and let it fade.%^RESET%^");
        tell_room(place,"%^BLUE%^"+caster->QCN+"'s spell softly snuffs out.%^RESET%^",caster);
        TO->remove();
        return;
    }
    if(target->query_blind() || target->query_temporary_blinded()) {
        tell_object(caster,"%^BLUE%^The sight is already gone from "+target->QCN+"'s eyes!%^RESET%^");
        tell_room(place,"%^BLUE%^"+caster->QCN+"'s spell softly snuffs out.%^RESET%^",caster);
        TO->remove();
        return;
    }
    if(do_save(target)){
        tell_object(target,"%^BLUE%^Your vision becomes momentarily hazy, but you manage to re-focus.%^RESET%^");
        tell_room(place,"%^BLUE%^"+target->QCN+" hesitates, but then shakes off your spell.%^RESET%^",target);
        TO->remove();
        return;
    }
    tell_object(target,"%^BLUE%^Your vision becomes hazy and the world around you fades into gray.%^RESET%^");
    tell_room(place,"%^BLUE%^"+target->QCN+" blinks, and then stares around sightlessly.%^RESET%^",target);
    target->set_temporary_blinded(roll_dice(2,4));
    spell_successful();
    dest_effect();
}

void dest_effect() {
    ::dest_effect();
    if(objectp(TO)) TO->remove();
}
