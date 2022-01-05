#include "global.h"
#include "shop.h"
#include "event_data.h"
#include "constants/items.h"

#include "shop_room.h"

static const u16 sItems[] = {
    ITEM_POKE_BALL,
    ITEM_POTION,
    ITEM_SITRUS_BERRY,
    ITEM_LUM_BERRY,
    ITEM_RARE_CANDY,
    ITEM_NONE
};

void CreateRandomShopMenu(u8 itempoolnum) {
    CreatePokemartMenu(sItems);
}
