#include "global.h"
#include "random.h"
#include "constants/species.h"
#include "constants/vars.h"
#include "constants/event_objects.h"
#include "constants/opponents.h"
#include "event_data.h"
#include "wild_encounter.h"
#include "battle_setup.h"

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

#define INTRO_BATTLE_OPPONENTS_COUNT 3
const static struct Opponent sIntroBattleOpponents[INTRO_BATTLE_OPPONENTS_COUNT] = {
{
.trainerId = TRAINER_CALVIN_1,
.gfxId = OBJ_EVENT_GFX_YOUNGSTER,
.money = 200
},
{
.trainerId = TRAINER_RICK,
.gfxId = OBJ_EVENT_GFX_BUG_CATCHER,
.money = 200
},
{
.trainerId = TRAINER_ALLEN,
.gfxId = OBJ_EVENT_GFX_CAMPER,
.money = 200
},
};

static void GenerateBattle(const struct Opponent oppList[], u16 count) {
    u16 ix = 0;

    ShufflePermutation(count);
    for (; HasTrainerBeenFought(PX(oppList, ix).trainerId) && ix != count - 1; ix++);
    VarSet(VAR_0x8000, PX(oppList, ix).trainerId);
    VarSet(VAR_OBJ_GFX_ID_0, PX(oppList, ix).gfxId);
    VarSet(VAR_TRAINER_LEVEL_DIFF, 2);
    VarSet(VAR_TRAINER_MONEY_REWARD, PX(oppList, ix).money);
}

void GenerateBattleIntro(void) {
    GenerateBattle(sIntroBattleOpponents, INTRO_BATTLE_OPPONENTS_COUNT);
}
