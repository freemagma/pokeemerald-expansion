#include "global.h"
#include "random.h"
#include "constants/species.h"
#include "constants/vars.h"
#include "event_data.h"
#include "wild_encounter.h"

#include "gift_room.h"


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


const static u16 sReturnVars[3] = {VAR_0x8001, VAR_0x8002, VAR_0x8003};
const static u16 sObjFlags[3] = {FLAG_TEMP_1, FLAG_TEMP_2, FLAG_TEMP_3};

static void GetGiftMon(const u16 specList[], u16 count) {
    u16 permIx = 0;
    u16 giftIx = 0;

    ShufflePermutation(count);

    for (; giftIx < 3; giftIx++) {
        for (; permIx < count; permIx++) {
            if (IsUncaughtSpecies(PX(specList, permIx))) {
                VarSet(sReturnVars[giftIx], PX(specList, permIx));
                break;
            }
        }
        // there are no more valid species
        if (permIx == count)
            break;
        permIx++;
    }
    // successfully got three species
    if (giftIx == 3)
        return;
    // delete remaining balls
    for (; giftIx < 3; giftIx++) {
        FlagSet(sObjFlags[giftIx]);
    }
}


const static u16 sDTutorial_GiftMons[] = {
    SPECIES_MAKUHITA, SPECIES_ELECTRIKE, SPECIES_STUNKY,
    SPECIES_RALTS,    SPECIES_GLAMEOW,   SPECIES_SHUPPET};

void DungeonTutorial_GetGiftMon(void) {
    GetGiftMon(sDTutorial_GiftMons, ARRAY_COUNT(sDTutorial_GiftMons));
}
