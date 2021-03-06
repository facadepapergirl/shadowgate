string * MAGE_COMPONENTS = ({
"aluminum chaff",
"amber rod",
"bat guano",
"beeswax",
"bit of bone",
"bitumen",
"blessed leather",
"carbon",
"charcoal",
"citric acid",
"clay model ziggurat",
"clear crystal",
"copper",
"corn extract",
"crane's feather",
"crushed black pearl",
"crystal",
"dart",
"diamond dust",
"diamond",
"disc of bronze",
"dragon scale",
"drop of blood",
"dung scrapings",
"emerald",
"eye of roc",
"eyelash of ogre-mage",
"eyelash",
"feather",
"firefly",
"flint",
"fur",
"glass rod",
"granite dust",
"gum arabic",
"incense stick",
"ivory portal",
"jade circlet",
"large diamond",
"lodestone",
"magnets",
"mini platinum sword",
"mini shovel",
"minute tarts",
"nitric acid",
"onyx dust",
"owlfeather",
"parchment",
"pearl",
"phosphorus",
"piece of iron",
"piece of mirror",
"piece of reed",
"pinch of special dust",
"powdered amber",
"powdered chalk",
"powdered diamond",
"powdered silver",
"quicksilver",
"rose petals",
"ruby dust",
"sack of salt",
"sand",
"sapphire dust",
"sesame seeds",
"silver pin",
"slug",
"small candle",
"small diamond",
"small drum",
"small silver mirror",
"smoky quartz",
"snakes tongue",
"soft clay",
"spider web",
"spider",
"sulfur",
"sunstone",
"talc",
"tiny bag",
"tiny chest",
"tiny hearing trumpet",
"vermilion",
"water",
"white feather",
"will o wisp essence",
"wing feather",
"zinc",
});

string *PSI_COMPONENTS = ({"adamite", "blue lace agate", "gray agate", "leopard agate", "banded amethyst", "amethyst", "blue amethyst"});

// had to be split into two defs; mud cannot handle the size of it in a single one.
// any new components should be added to COMPONENTS2 in future. N, 5/14.
// Just a note to anyone who comes by: what do you think compiller macro in c does? -- Il
mapping COMPONENTS1 = ([
"adamite" : 100,
"adders stomach" : 25,
"alkaline salt" : 1,
"alliteration" : 87,
"alum" : 8,
"aluminum chaff" : 50,
"amber rod" : 75,
"amethyst" : 17,
"animal hair" : 5,
"apatite" : 5,
"aquamarine" : 40,
"aventurine" : 55,
"azurite" : 80,
"ballad" : 47,
"banded amethyst" : 75,
"bark chips" : 1,
"bat fur" : 25,
"bat guano" : 10,
"beeswax" : 45,
"beryl" : 10,
"bit of bone" : 30,
"bit of seashell" : 62,
"bitumen" : 35,
"black silk" : 100,
"black star sapphire" : 5000,
"blessed leather" : 50,
"blood of umber hulk" : 150,
"bloodstone" : 8,
"blue amethyst" : 125,
"blue calcite" : 13,
"blue diamond" : 2000,
"blue lace agate" : 2550,
"blue spinel" : 40,
"blue tigers eye" : 250,
"butter" : 5,
"carbon" : 15,
"carnelian" : 50,
"caterpillar cocoon" : 20,
"chalcopyrite" : 30,
"chalk" : 3,
"charcoal" : 20,
"charoite" : 27,
"chord" : 62,
"citric acid" : 5,
"citrine quartz" : 3,
"clay model ziggurat" : 50,
"clear crystal" : 20,
"clear quartz" : 3,
"coal" : 3,
"colored sand" : 1,
"conceit" : 60,
"copper wire" : 10,
"copper" : 5,
"corn extract" : 5,
"couplet" : 376,
"crane's feather" : 30,
"cricket" : 1,
"crushed black pearl" : 1000,
"crushed pearls" : 1000,
"crystal" : 10,
"dallyhanite" : 14,
"danburite" : 310,
"dart" : 1,
"dialogue" : 45,
"diamond dust" : 1250,
"diamond" : 1000,
"dirge" : 41,
"disc of bronze" : 50,
"dragon scale" : 500,
"drop of blood" : 10,
"drop of oil" : 1,
"dung scrapings" : 5,
"earth from grave" : 1,
"ebony canine statuette" : 250,
"ectoplasmic crystal" : 1000,
"elegy" : 33,
"emerald dust" : 500,
"emerald" : 300,
"epic" : 72,
"epithet" : 120,
"exotic feather" : 75,
"eye of roc" : 2500,
"eyelash of ogre-mage" : 150,
"eyelash" : 3,
"feather" : 1,
"fine cloth" : 5,
"fire opal" : 180,
"firefly" : 10,
"fleece" : 8,
"flint" : 1,
"flowstone" : 42,
"forked twig" : 1,
"fur" : 100,
"garnet" : 37,
"glass rod" : 25,
"gloworm" : 25,
"gold tube" : 1000,
"golden needle" : 100,
"grain of salt" : 1,
"granite block" : 20,
"granite dust" : 50,
"grasshopper leg" : 1,
"gray agate" : 8,
"green fluorite" : 18,
"green moss agate" : 9,
"ground mica" : 5,
"gum arabic" : 20,
"haiku" : 17,
"hematite" : 70,
"honey" : 1,
"honeycomb" : 3,
"hymn" : 3405,
"hyperbole" : 24,
"incense stick" : 1,
"invective" : 14,
"iron blade" : 2,
"iron rod" : 50,
"ivory canine statuette" : 200,
"ivory plaque" : 150,
"ivory portal" : 50,
"jade circlet" : 200,
"jade" : 83,
"joke" : 3,
"lament" : 24,
"lapiz lazuli" : 68,
"large diamond" : 3000,
"larvikite" : 12,
"lead based ink" : 300,
"leather glove" : 20,
"leather loop" : 3,
"legume seed" : 5,
"leopard agate" : 21,
"licorice root" : 2,
"lime" : 3,
"limerick" : 15,
"lodestone" : 1,
"lodestone" : 12,
"lullaby" : 10,
"lyric" : 43,
"magnetic needle" : 2,
"magnets" : 10,
"malachite" : 43,
"mercury" : 85,
"metal rod" : 10,
"metaphor" : 267,
"mini brass trumpet" : 200,
"mini platinum sword" : 500,
"mini shovel" : 50,
"minute tarts" : 3,
"moonstone" : 16,
"mottled jasper" : 11,
"multi-colored silk" : 100,
"narrative" : 23,
"nitric acid" : 75,
"note" : 7,
"nutshells" : 1,
"oak leaf" : 1,
"obsidian" : 7,
"octave" : 245,
"ode" : 34,
"ogre's eyelash" : 25,
"oil" : 5,
"onyx dust" : 500,
"opal" : 65,
"orange calcite" : 14,
"owlfeather" : 10,
"parchment" : 2,
"parody" : 61,
"pearl" : 100,
"peridot" : 55,
"phosphorescent moss" : 20,
"phosphorus" : 90,
"piece of bone" : 30,
"piece of glass" : 2,
"piece of iron" : 1,
"piece of mirror" : 1,
"piece of mirror" : 25,
"piece of reed" : 10,
"piece of steel" : 1,
"pinch of dung" : 5,
"pinch of soot" : 1,
"pinch of special dust" : 50,
"poem" : 475,
"poison ivy leaf" : 9,
"polished marble" : 18,
"powdered amber" : 100,
"powdered bone" : 20,
"powdered chalk" : 2,
"powdered diamond" : 5000,
"powdered hoof" : 7,
"powdered iron" : 9,
"powdered lime" : 12,
"powdered rhubarb leaf" : 5,
"powdered silver" : 50,
"prose" : 132,
"purple fluorite" : 11,
"pyrite" : 5,
"quatrain" : 68,
"quicksilver" : 100,
"red cloth" : 1,
"red jasper" : 4,
"red spinel" : 40,
"rhetoric" : 1415,
"rhodochrosite" : 35,
"rhodonite" : 17,
"rhyme" : 52,
"rod of iron" : 5,
"rose petals" : 2,
"rose quartz" : 215,
"ruby dust" : 500,
"ruby" : 130,
"rutilated quartz" : 2300,
"sack of salt" : 50,
"sand" : 1,
"sapphire dust" : 500,
"sapphire" : 500,
"seraphinite" : 200,
"sesame seeds" : 4,
"shanty" : 18,
"silver pin" : 10,
"silver rod" : 50,
"silver whistle" : 100,
"silver wire" : 25,
"slug" : 4,
"small candle" : 2,
"small crystal bead" : 5,
"small diamond":750,
"small drum" : 50,
"small horn" : 100,
"small silver mirror" : 50,
"smoky quartz" : 55,
"smoky quartz" : 8,
"snake scale" : 35,
"snakes tongue" : 80,
"snakeskin glove" : 100,
"snowflake obsidian" : 10,
"sodalite" : 2,
"soft clay" : 10,
"soft glove" : 5,
"soliloquy" : 15,
"song" : 128,
"sonnet" : 97,
"spider web" : 15,
"spider" : 10,
"squid ink" : 100,
"squid tentacle" : 100,
"stanza" : 38,
"straw" : 1,
"string" : 1,
"strip of parchment" : 1,
"sulfur" : 25,
"sunstone" : 50,
"talc" : 70,
"tallow" : 1,
"tektite" : 150,
"thread" : 1,
"tigers eye" : 75,
"tiny bag" : 5,
"tiny bell" : 25,
"tiny bucket" : 25,
"tiny chest" : 75,
"tiny fan" : 50,
"tiny hearing trumpet" : 100,
"topaz" : 4,
"tourmaline" : 15,
"trill" : 18,
"turquoise" : 4,
"turtle shell" : 10,
"unakite" : 100,
"vampire dust" : 10000,
"vermilion" : 18,
"verse" : 106,
"water" : 1,
"wemic tears": 6,
"whisper" : 54,
"whistle" : 2,
"white feather" : 5,
"will o wisp essence" : 100,
"wing feather" : 20,
"wood" : 1,
"yellow calcite" : 12,
"yellow jasper" : 8,
"zinc" : 50,
"zoisite" : 52,
]);
