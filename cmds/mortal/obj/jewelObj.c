
#include <std.h>
#include <standards.h>
#include <daemons.h>


inherit "/cmds/mortal/obj/genObj.c";


void finish_object(mapping keyMap, string template){
    int percent,i, weight;
    string l;

    keyMap["~TYPE~"] = "ring";
    keyMap["~LIMBS~"] = JEWELRY[type]["limbs"];
    
    percent = prof*10 - (random(40)-20);
    percent = percent - (10 - (int)materialObj[0]->query_quality_type())*10;

    if (percent < 0) {
        percent = 0;
    }
    keyMap["~AC~"] = 0;

    keyMap["~QUALITY~"] = percent;

    keyMap["~VALUE~"] = JEWELRY[type]["price"] * percent/100;
/* Was letting weight go to 1 for 100 or better roll on quality percent.  I'm sure T didn't mean that drastic of an effect since only magic could take all the natural weight out of something.  Adding () to be sure division occurs at the right place.  Leaving else case out entirely because over 100% would reduce weight below normal in the first function and I believe that's what was actually intended.  *Styx*  4/18/03
    if (percent <100) {
        keyMap["~WEIGHT~"] = JEWELRY[type]["weight"]+(JEWELRY[type]["weight"]-JEWELRY[type]["weight"] * percent/100);
    } else {
        keyMap["~WEIGHT~"] = JEWELRY[type]["weight"]-(JEWELRY[type]["weight"] * percent/100);
    }
*/
    weight = JEWELRY[type]["weight"]+JEWELRY[type]["weight"]-(JEWELRY[type]["weight"] * percent/100);
    if (weight < 0) {
        weight = 1;
    }
    keyMap["~WEIGHT~"] = weight;

    NWP_D->perform_nwp(TP,"jewelling");
    NWP_D->perform_nwp(TP,"jewelling");

    l = keyMap["~LONG~"];
    switch(percent){
    case 0..49:
        l+="\nVery poor quality";
        break;
    case 50..75:
        l += "\nLow quality";
        break;
    case 76..90:
        l += "\nBelow average quality";
        break;
    case 91..109:
        l += "\nAverage quality";
        break;
    case 110..124:
        l += "\nAbove average quality";
        break;
    case 125..151:
        l += "\nHigh quality";
        break; 
    default:
        l += "\nExcellent quality";
        break; 
    }

    keyMap["~LONG~"] = l;
     log_file("jewel",capitalize(TPQN)+" "+ctime(time())+" "+identify(keyMap)+"\n");
/* need to change back to this if/when smaller units of metal go in *Styx*
Also will need to change the _jewel.c command file to use the other amount
     for (i=0;i<sizeof(materialObj);i++) {
         materialObj[i]->use(size*(int)JEWELRY[type]["units"]);
     }
*/
    materialObj[i]->use(1);
    ETO->remove_property("working");
    tell_room(environment(ETO), ETO->query_cap_name()+" pauses from working on the new piece of jewelry.", ETO);
    tell_object(ETO,"You pause from working on the new piece of jewelry.");
    ::finish_object(keyMap,"/cmds/mortal/templates/armor.tpl");
}

