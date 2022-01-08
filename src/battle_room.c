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
    VarSet(VAR_TRAINER_MONEY_REWARD, opp.money);
}

const static struct Opponent sDTutorial_Opponents0[] = {
{
.trainerId = TRAINER_CALVIN_1,
.gfxId = OBJ_EVENT_GFX_YOUNGSTER,
.money = 300
}
};

const static struct Opponent sDTutorial_Opponents1[] = {
{
.trainerId = TRAINER_RICK,
.gfxId = OBJ_EVENT_GFX_BUG_CATCHER,
.money = 300
},
{
.trainerId = TRAINER_ALLEN,
.gfxId = OBJ_EVENT_GFX_CAMPER,
.money = 300
}
};

const static struct Opponent sDTutorial_EliteOpponents0[] = {
{
.trainerId = TRAINER_ROXANNE_1,
.gfxId = OBJ_EVENT_GFX_ROXANNE,
.money = 500
},
{
.trainerId = TRAINER_WATTSON_1,
.gfxId = OBJ_EVENT_GFX_WATTSON,
.money = 500
}
};


void DungeonTutorial_GenerateBattle(void) {
    switch (GetRouteParam()) {
        case 0:
            GenerateBattle(sDTutorial_Opponents0, ARRAY_COUNT(sDTutorial_Opponents0), 3);
            break;
        case 1:
        default:
            GenerateBattle(sDTutorial_Opponents1, ARRAY_COUNT(sDTutorial_Opponents1), 2);
            break;
    }
}

void DungeonTutorial_GenerateEliteBattle(void) {
    GenerateBattle(sDTutorial_EliteOpponents0, ARRAY_COUNT(sDTutorial_EliteOpponents0), 0);
}
