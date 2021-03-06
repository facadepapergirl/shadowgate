//removed mention of non-specialized mages ~Circe~ 8/2/19
#include <std.h>
#include <priest.h>
inherit SPELL;

int timer,flag,stage,toggle,counter;

void create(){
    ::create();
    set_author("nienne");
    set_spell_name("fire shield");
    set_spell_level(([ "mage" : 4, "cleric" : 3 ]));
    set_spell_sphere("invocation_evocation");
    set_spell_domain("fire");
    set_syntax("cast CLASS fire shield");
    set_description("This spell will surround the caster's body in a roaring shield of flames.  It grants the caster a "
"slight bonus to their armor class, and any opponent striking the caster must make a saving throw or take damage from the "
"blistering heat.");
    set_verbal_comp();
    set_somatic_comp();
    set_components(([
      "mage" : ([ "phosphorus" : 1, ]),
    ]));
    set_save("fort");
    set_helpful_spell(1);
    traveling_aoe_spell(1);
}

string query_cast_string(){
   	tell_object(caster,"%^BOLD%^%^RED%^%^Circling your hands before "+
		"you, you begin to evoke the element of fire.");
    	tell_room(place,"%^BOLD%^%^RED%^Circling "+caster->QP+" hands "+
		"before "+caster->QO+", "+caster->QCN+" begins to evoke "+
		"the element of fire.",caster);
}

int preSpell(){
    if(caster->query_property("fire shield")){
        tell_object(caster,"You are already protected by a shield of fire.");
        return 0;
    }
    return 1;
}

void spell_effect(int prof){
    int duration;
    duration = (ROUND_LENGTH * 6) * clevel;
    tell_room(place,"%^YELLOW%^"+caster->QCN+" completes "+caster->QP+" evocation and is "
        "surrounded by roaring flames!",caster);
    tell_object(caster,"%^YELLOW%^You complete your evocation and are surrounded by "
        "roaring flames!");
    caster->set_property("fire shield",1);
    caster->set_property("spelled", ({TO}) );
    caster->add_ac_bonus(2);
    caster->set_property("added short",({"%^BOLD%^%^RED%^ (bathed in flames)"}));
    addSpellToCaster();
    spell_successful();
    counter = 6*clevel;
    execute_attack();
    call_out("room_check",ROUND_LENGTH);
}

void room_check()
{
    if(!objectp(caster) || !objectp(ENV(caster)))
    {
        dest_effect();
        return;
    }

    prepend_to_combat_cycle(ENV(caster));

    call_out("room_check",ROUND_LENGTH*2);
    return;
}

void execute_attack(){
    object *foes=({}),targ;
    int i;

    if(!flag)
    {
        flag = 1;
        ::execute_attack();
        return;
    }

    place = ENV(caster);

    if(!objectp(caster) || !objectp(place) || counter<0)
    {
        dest_effect();
        return;
    }

    foes = caster->query_attackers();

    if(sizeof(foes))
    {
        define_base_damage(0);//reroll each turn
        tell_room(place,"%^BOLD%^%^RED%^Flames around "+caster->QCN+" burn "+caster->QP+" enemies!",({caster,target}));
        tell_object(caster,"%^BOLD%^%^RED%^Flames of your shire field burn your enemies!");

        define_base_damage(0);
        for(i=0;i<sizeof(attackers);i++){
            if(SAVING_D->saving_throw(attackers[i],"spell",0)) { continue; }
            tell_object(attackers[i],"%^BOLD%^%^RED%^You are burned by the shield of flames as you strike "
                        ""+caster->QCN+"!");
            damage_targ(attackers[i],attackers[i]->return_target_limb(),sdamage,"fire");
        }
    }
    prepend_to_combat_cycle(place);
    counter--;
}

void dest_effect(){
    remove_call_out("room_check");
    if(objectp(caster)){
        tell_object(caster,"%^BOLD%^%^RED%^The shield of roaring flames flickers and fades away, "
            "leaving you vulnerable once again.");
        tell_room(environment(caster),"%^BOLD%^%^RED%^The shield of roaring flames flickers and "
            "fades away, leaving "+caster->QCN+" vulnerable once again.",caster);
        caster->remove_property("fire shield");
        caster->add_ac_bonus(-2);
	  caster->remove_property_value("added short",({"%^BOLD%^%^RED%^ (bathed in flames)"}));
    }
    ::dest_effect();
    if(objectp(TO)) TO->remove();

}
