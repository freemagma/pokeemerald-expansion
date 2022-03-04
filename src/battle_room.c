#include "global.h"
#include "random.h"
#include "constants/species.h"
#include "constants/vars.h"
#include "constants/event_objects.h"
#include "constants/opponents.h"
#include "constants/trainers.h"
#include "data.h"
#include "event_data.h"
#include "wild_encounter.h"
#include "battle_setup.h"
#include "routing.h"

#include "battle_room.h"

#define MAX_PERMUTATION 10
EWRAM_DATA static u16 sPermutation[MAX_PERMUTATION] = {0};

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

static u16 GetGfxIdFromTrainerId(u16 trainerId) {
    u16 i;
    u16 trainerClass = gTrainers[trainerId].trainerClass;
    u16 isFemale = gTrainers[trainerId].encounterMusic_gender & F_TRAINER_FEMALE;

    if (isFemale) {
        for (i = 0; i < ARRAY_COUNT(BattleRoomFemaleTrainerClasses); i++) {
            if (BattleRoomFemaleTrainerClasses[i] == trainerClass)
                break;
        } 
        return BattleRoomFemaleGfxIds[i];
    } else {
        for (i = 0; i < ARRAY_COUNT(BattleRoomMaleTrainerClasses); i++) {
            if (BattleRoomMaleTrainerClasses[i] == trainerClass)
                break;
        } 
        return BattleRoomMaleGfxIds[i];
    }
}

static void GenerateBattle(u16 trainerMin, u16 trainerMax, u32 baseMoney, u16 levelDiff) {
    u16 ix = 0;
    u16 count = trainerMax - trainerMin + 1;
    u16 money;
    u16 trainerId;

    ShufflePermutation(count);
    for (; HasTrainerBeenFought(trainerMin + sPermutation[ix]) && ix != count - 1; ix++);

    trainerId = trainerMin + sPermutation[ix];
    if (HasTrainerBeenFought(trainerId)) {
        ClearTrainerFlag(trainerId);
    }

    VarSet(VAR_0x8000, trainerId);
    VarSet(VAR_OBJ_GFX_ID_0, GetGfxIdFromTrainerId(trainerId));
    VarSet(VAR_TRAINER_LEVEL_DIFF, levelDiff);

    money = (baseMoney * (90 + (Random() % 21))) / 100;
    VarSet(VAR_TRAINER_MONEY_REWARD, money);
}

void DungeonTutorial_GenerateBattle(void) {
    switch (GetRouteParam()) {
        case 0:
            GenerateBattle(TRAINER_TU_DWAYNE, TRAINER_TU_BRUCE, 300, 4);
            break;
        case 1:
        default:
            GenerateBattle(TRAINER_TU_DARIEN, TRAINER_TU_EMILY, 400, 3);
            break;
    }
}

void DungeonTutorial_GenerateEliteBattle(void) {
    GenerateBattle(TRAINER_TU_ROSEMARY, TRAINER_TU_EVERETT, 700, 2);
}

void DungeonTutorial_GenerateBossBattle(void) {
    GenerateBattle(TRAINER_TU_MAGNOLIA, TRAINER_TU_MAGNOLIA, 1000, 0);
    VarSet(VAR_EXP_MULTIPLIER, 0);
}

void DungeonEden_GenerateBattle(void) {
    switch (GetRouteParam()) {
        case 0:
            GenerateBattle(TRAINER_ED_EDWIN, TRAINER_ED_AMY, 300, 4);
            break;
        case 1:
        default:
            GenerateBattle(TRAINER_TU_DARIEN, TRAINER_TU_EMILY, 400, 3);
            break;
    }
}

void DungeonEden_GenerateEliteBattle(void) {
    GenerateBattle(TRAINER_TU_ROSEMARY, TRAINER_TU_EVERETT, 700, 2);
}

void DungeonEden_GenerateBossBattle(void) {
    GenerateBattle(TRAINER_TU_MAGNOLIA, TRAINER_TU_MAGNOLIA, 1000, 0);
    VarSet(VAR_EXP_MULTIPLIER, 0);
}
