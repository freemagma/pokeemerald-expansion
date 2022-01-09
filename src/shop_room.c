#include "global.h"
#include "shop.h"
#include "random.h"
#include "event_data.h"
#include "constants/items.h"

#include "shop_room.h"

#define MAX_SHOP_SIZE 12
#define DEFAULT_SHOP_SIZE 5

static const struct ItemPrice sItemPriceNone = {0};

static const struct ItemPrice sBasicItems[] = {
{.itemId = ITEM_POKE_BALL, .price = 20},
{.itemId = ITEM_HALF_POTION, .price = 50},
{.itemId = ITEM_FULL_HEAL, .price = 50},
{.itemId = ITEM_SITRUS_BERRY, .price = 100},
{.itemId = ITEM_LUM_BERRY, .price = 100},
{.itemId = ITEM_RARE_CANDY, .price = 10},
{0}
};

static const struct ItemPrice sDTutorialA1ItemPool[] = {
{.itemId = ITEM_TM09_BULLET_SEED, .price = 500},
{.itemId = ITEM_TM03_WATER_PULSE, .price = 500},
{.itemId = ITEM_TM28_DIG, .price = 500},
{.itemId = ITEM_TM35_FLAMETHROWER, .price = 900},
{.itemId = ITEM_TM13_ICE_BEAM, .price = 900},
{.itemId = ITEM_TM24_THUNDERBOLT, .price = 900},
{.itemId = ITEM_PROTEIN, .price = 100},
{.itemId = ITEM_CALCIUM, .price = 100},
{.itemId = ITEM_CARBOS, .price = 100},
{.itemId = ITEM_ZINC, .price = 100},
{.itemId = ITEM_HP_UP, .price = 100},
{.itemId = ITEM_IRON, .price = 100},
{.itemId = ITEM_REVIVE, .price = 1500},
{.itemId = ITEM_LEFTOVERS, .price = 700},
{.itemId = ITEM_EXPERT_BELT, .price = 350},
{.itemId = ITEM_SOFT_SAND, .price = 200},
{.itemId = ITEM_BRIGHT_POWDER, .price = 250},
{.itemId = ITEM_KINGS_ROCK, .price = 200},
{0}
};

EWRAM_DATA static struct ItemPrice sRandomShopItems[MAX_SHOP_SIZE + 1] = {0};


EWRAM_DATA static u16 sPermutation[MAX_SHOP_SIZE] = {0};
#define PX(arr, ix) (arr[sPermutation[ix]])

static void PopulateRandomShopItems(const struct ItemPrice *items, u16 count)
{
    u16 length = 0;
    u16 i, j;

    for (; items[length].itemId; length++);

    for (i = 0; i < count; i++) {
        while(1) {
            u16 index = Random() % length;
            for (j = 0; j < i; j++) {
                if (sPermutation[j] == index)
                    break;
            }
            if (j != i)
                continue;
            sPermutation[i] = index;
            break;
        }
    }

    for (i = 0; i < count; i++) {
        sRandomShopItems[i] = PX(items, i);
    }

    sRandomShopItems[count] = sItemPriceNone;
}


void CreateFixedShopMenu(u8 itempoolnum) {
    switch(itempoolnum) {
        case 0:
        default:
            CreatePokemartMenu(sBasicItems);
            break;
    }
}

void GenerateRandomShop(u8 itempoolnum) {
    switch(itempoolnum) {
        case 0:
        default:
            PopulateRandomShopItems(sDTutorialA1ItemPool, DEFAULT_SHOP_SIZE);
            break;
    }
}

void CreateRandomShopMenu() {
    CreatePokemartMenu(sRandomShopItems);
}
