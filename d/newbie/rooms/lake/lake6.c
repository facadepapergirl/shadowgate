#include <std.h>
#include "../../newbie.h"
inherit "/d/newbie/rooms/lake/lakeinherit";

// Aquatic Quest - Offestry Valley - Created in March 2009 by Ari
// For inclusion into the Offestry Valley Upgrade by Nienne

void create(){
  ::create();

  set_exits(([
    "north":"lake8",
    "east":"lake5",
    "south":"lake4",
    "west":"lake7"
  ]));
}

