#include "global.h"
#include "random.h"
#include "constants/species.h"
#include "constants/vars.h"
#include "constants/event_objects.h"
#include "constants/opponents.h"
#include "event_data.h"
#include "wild_encounter.h"
#include "battle_setup.h"
#include "routing.h"

#include "battle_room.h"

#define MAX_PERMUTATION 10
EWRAM_DATA static u16 sPermutation[MAX_PERMUTATION] = {0};

#define PX(arr, ix) (arr[sPermutation[ix]])

static void ShufflePermutation(u16 count) {
    u16 i;

    for (i = 0; i < count; i++)
        sPermutation[i] = i;


    for (i = (count - 1); i > 0; i--) {
        u16 j = Random() % (i + 1);
        u16 arr = sPermutation[j];
        sPermutation[j] = sPermutation[i];
        sPermutation[i] = arr;
    }
}

struct Opponent {
    u16 trainerId;
    u16 gfxId;
    u32 money;
};

static void GenerateBattle(const struct Opponent oppList[], u16 count, u16 levelDiff) {
    u16 ix = 0;
    u16 money;
    struct Opponent opp;

    ShufflePermutation(count);
    for (; HasTrainerBeenFought(PX(oppList, ix).trainerId) && ix != count - 1; ix++);

    opp = PX(oppList, ix);
    if (HasTrainerBeenFought(opp.trainerId)) {
        ClearTrainerFlag(opp.trainerId);
    }

    VarSet(VAR_0x8000, opp.trainerId);
    VarSet(VAR_OBJ_GFX_ID_0, opp.gfxId);
    VarSet(VAR_TRAINER_LEVEL_DIFF, levelDiff);

    money = (opp.money * (90 + (Random() % 21))) / 100;
    VarSet(VAR_TRAINER_MONEY_REWARD, money);
}

const static struct Opponent sDTutorial_Opponents0[] = {
{
.trainerId = TRAINER_TU_DWAYNE,
.gfxId = OBJ_EVENT_GFX_HIKER,
.money = 300
},
{
.trainerId = TRAINER_TU_BRUCE,
.gfxId = OBJ_EVENT_GFX_YOUNGSTER,
.money = 300
},
};

const static struct Opponent sDTutorial_Opponents1[] = {
{
.trainerId = TRAINER_TU_DARIEN,
.gfxId = OBJ_EVENT_GFX_CAMPER,
.money = 400
},
{
.trainerId = TRAINER_TU_SELINA,
.gfxId = OBJ_EVENT_GFX_WOMAN_2,
.money = 400
},
{
.trainerId = TRAINER_TU_KATRINA,
.gfxId = OBJ_EVENT_GFX_GIRL_3,
.money = 400
},
{
.trainerId = TRAINER_TU_LEAH,
.gfxId = OBJ_EVENT_GFX_HEX_MANIAC,
.money = 400
},
{
.trainerId = TRAINER_TU_FREDDY,
.gfxId = OBJ_EVENT_GFX_HIKER,
.money = 400
},
{
.trainerId = TRAINER_TU_EMILY,
.gfxId = OBJ_EVENT_GFX_WOMAN_4,
.money = 400
},

};

const static struct Opponent sDTutorial_EliteOpponents0[] = {
{
.trainerId = TRAINER_TU_ROSEMARY,
.gfxId = OBJ_EVENT_GFX_WOMAN_2,
.money = 700
},
{
.trainerId = TRAINER_TU_EVERETT,
.gfxId = OBJ_EVENT_GFX_MAN_5,
.money = 700
}
};

const static struct Opponent sDTutorial_Bosses[] = {
{
.trainerId = TRAINER_TU_MAGNOLIA,
.gfxId = OBJ_EVENT_GFX_FLANNERY,
.money = 1000,
},
};


void DungeonTutorial_GenerateBattle(void) {
    switch (GetRouteParam()) {
        case 0:
            GenerateBattle(sDTutorial_Opponents0, ARRAY_COUNT(sDTutorial_Opponents0), 4);
            break;
        case 1:
        default:
            GenerateBattle(sDTutorial_Opponents1, ARRAY_COUNT(sDTutorial_Opponents1), 3);
            break;
    }
}

void DungeonTutorial_GenerateEliteBattle(void) {
    GenerateBattle(sDTutorial_EliteOpponents0, ARRAY_COUNT(sDTutorial_EliteOpponents0), 2);
}

void DungeonTutorial_GenerateBossBattle(void) {
    GenerateBattle(sDTutorial_Bosses, ARRAY_COUNT(sDTutorial_Bosses), 0);
}
