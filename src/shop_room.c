#include "global.h"
#include "shop.h"
#include "event_data.h"
#include "constants/items.h"

#include "shop_room.h"

static const struct ItemPrice sItems[] = {
{.itemId = ITEM_POKE_BALL, .price = 69},
{.itemId = ITEM_HALF_POTION, .price = 200},
{0}
};

void CreateFixedShopMenu(u8 itempoolnum) {
    CreatePokemartMenu(sItems);
}

void CreateRandomShopMenu(u8 itempoolnum) {
    CreatePokemartMenu(sItems);
}
